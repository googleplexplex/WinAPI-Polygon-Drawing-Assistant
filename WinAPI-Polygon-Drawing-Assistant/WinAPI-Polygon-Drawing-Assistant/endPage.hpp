#pragma once
#include <iostream>
#include <windows.h>
#include <string>

std::string compiliedFigure;
bool figureCompilied = false;

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
	std::string prefics = "constexpr unsigned int polygonFigurePointsCount = " + std::to_string(polygonPointsCount) + std::string(";\nconst POINT polygonFigurePoints[polygonFigurePointsCount] = { ");
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

void endPage_onMouseLeftButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	if (figureCompilied)
		putInClipboard(compiliedFigure.c_str());
}

void endPage_onMouseRightButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	if(figureCompilied)
		putInClipboard(compiliedFigure.c_str());
}

void endPage_onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
{
	TextOutWithDynamicLength(paintInWindowHDC, 10, 10, "B - Back to draw");
	TextOutWithDynamicLength(paintInWindowHDC, 0, screenSize.y - 50, "Press Any Key To Copy Result In Clipboard");
	compiliedFigure = compileFigureToCode();
	figureCompilied = true;
}

void endPage_onKeyPressed(unsigned int key)
{
	putInClipboard(compileFigureToCode());
	if (key == KB_CODE('b') || key == KB_CODE_BIG('B'))
	{
		setAppState(drawPage);
		figureCompilied = false;
	}
}