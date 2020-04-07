#pragma once
#include <iostream>
#include <windows.h>
#include <string>

std::string compiliedFigure;
bool figureCompilied = false;

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

	textBoxHWND = CreateWindow("edit", compiliedFigure.c_str(),
		SS_LEFT | WS_GROUP | WS_CHILD | WS_VISIBLE | ES_MULTILINE,
		textBoxPos.x, textBoxPos.y, textBoxSize.x, textBoxSize.y,
		mainWindowHWND, (HMENU)ID_TEXTBOX, hInst, NULL);

	clipboardCopyButtonHWND = CreateWindow("button", "Copy Result in Clipboard",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		clipboardCopyButtonPos.x, clipboardCopyButtonPos.y, clipboardCopyButtonSize.x, clipboardCopyButtonSize.y,
		mainWindowHWND, (HMENU)ID_CLIPBOARDCOPYBUTTON, hInst, NULL);

	backButtonHWND = CreateWindow("button", "Back to Draw",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		backButtonPos.x, backButtonPos.y, backButtonSize.x, backButtonSize.y,
		mainWindowHWND, (HMENU)ID_BACKBUTTON, hInst, NULL);
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
	TextOutCenter(paintInWindowHDC, textBoxPos.y - GetTextExtentPoint32Size("Figure points code:").y - 10, "Figure points code:");
}

void endPage_onKeyPressed(unsigned int key)
{
	
}

void endPage_onCommandCatch(unsigned int idCatcher)
{
	switch (idCatcher)
	{
	case ID_TEXTBOX:
		break;
	case ID_BACKBUTTON:
		setAppState(drawPage);
		figureCompilied = false;
		DestroyWindow(textBoxHWND);
		DestroyWindow(clipboardCopyButtonHWND);
		DestroyWindow(backButtonHWND);
		break;
	case ID_CLIPBOARDCOPYBUTTON:
		if (figureCompilied)
		{
			putInClipboard(compiliedFigure.c_str());
			SetWindowText(mainWindowHWND, compiliedFigure.c_str());
		}
		break;
	}
}