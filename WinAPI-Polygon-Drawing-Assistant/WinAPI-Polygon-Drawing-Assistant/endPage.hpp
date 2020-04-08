#pragma once
#include <iostream>
#include <windows.h>
#include <string>

std::string compiliedFigure;
bool figureCompilied = false;

#define ID_TEXTBOX_OUTPUTRESULT 2
#define ID_BUTTON_BACK 3
#define ID_BUTTON_CLIPBOARDCOPY 4

constexpr unsigned int endPage_windowElementsCount = 3;
windowElementClass endPage_windowElements[endPage_windowElementsCount] = {
	windowTextBoxClass("", (HMENU)ID_TEXTBOX_OUTPUTRESULT, { 15, screenSize.y / 4 }, { screenSize.x - 2 * 15, 150 }),
	windowButtonClass("Back To Draw", (HMENU)ID_BUTTON_BACK, { screenSize.x - 100 - 30, screenSize.y - 30 - 30 }, { 100, 30 }),
	windowButtonClass("Copy Result in Clipboard", (HMENU)ID_BUTTON_CLIPBOARDCOPY, { 30, screenSize.y - 30 - 30 }, { 200, 30 }) };


bool inline pointInRect(RECT rect, POINT point)
{
	return ( rect.top < point.y &&
		rect.left < point.x &&
		rect.bottom > point.y &&
		rect.right > point.x );
}

bool putInClipboard(std::string _puttedString)
{
	LPCSTR puttedString = _puttedString.c_str();
	if (OpenClipboard(mainWindowHWND))//открываем буфер обмена
	{
		HGLOBAL hgBuffer;
		char* chBuffer;
		EmptyClipboard(); //очищаем буфер
		hgBuffer = GlobalAlloc(GMEM_DDESHARE, _puttedString.length() + 1);//выделяем память
		chBuffer = (char*)GlobalLock(hgBuffer); //блокируем память
		strcpy(chBuffer, LPCSTR(puttedString));
		GlobalUnlock(hgBuffer);//разблокируем память
		SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
		CloseClipboard(); //закрываем буфер обмена
		return true;
	} else
		return false;
}
std::string compilePoint(POINT compiliedPoint)
{
	std::string result = "{ ";
	result += std::to_string(compiliedPoint.x);
	result += ", ";
	result += std::to_string(compiliedPoint.x);
	result += " }";
	return result;
}
std::string compileFigureToCode()
{
	std::string prefics = "constexpr unsigned int polygonFigurePointsCount = " + std::to_string(polygonPointsCount) + std::string(";\r\nconst POINT polygonFigurePoints[polygonFigurePointsCount] = { ");
	std::string betweenData = ", ";
	std::string postfics = " };";

	std::string result = prefics;
	for (int i = 0; i < polygonPointsCount; i++)
	{
		result += compilePoint(polygonPoints[i]);
		if(i != polygonPointsCount - 1)
			result += betweenData;
	}
	result += postfics;

	return result;
}

void endPage_onCalled()
{
	compiliedFigure = compileFigureToCode();
	figureCompilied = true;

	createAllElements(endPage_windowElements, endPage_windowElementsCount);
	SetWindowText(endPage_windowElements[ID_TEXTBOX_OUTPUTRESULT].hwnd, compiliedFigure.c_str());
}

void endPage_onMouseLeftButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	
}

void endPage_onMouseRightButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	
}

void endPage_onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
{
	TextOutCenter(paintInWindowHDC, 20, "Thanks to using");
	TextOutCenter(paintInWindowHDC, endPage_windowElements[0].pos.y - GetTextExtentPoint32Size("Figure points code:").y - 10, "Figure points code:");
}

void endPage_onKeyPressed(unsigned int key)
{
	
}

void endPage_onCommandCatch(unsigned int idCatcher)
{
	switch (idCatcher)
	{
	case ID_TEXTBOX_OUTPUTRESULT:
		break;
	case ID_BUTTON_BACK:
		setAppState(drawPage);
		figureCompilied = false;
		deleteAllElements(endPage_windowElements, endPage_windowElementsCount);
		break;
	case ID_BUTTON_CLIPBOARDCOPY:
		if (figureCompilied)
		{
			putInClipboard(compiliedFigure.c_str());
			SetWindowText(endPage_windowElements[ID_TEXTBOX_OUTPUTRESULT].hwnd, compiliedFigure.c_str());
		}
		break;
	default:
		break;
	}
}