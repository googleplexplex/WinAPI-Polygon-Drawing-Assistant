#pragma once
#include <iostream>
#include <windows.h>
#include <string>

std::string compiliedFigure;
bool figureCompilied = false;

inline char* getStringContent(std::string str)
{
	return &(str[0]);
}
bool putInClipboard(std::string puttedString)
{
	if (OpenClipboard(mainWindowHWND))//��������� ����� ������
	{
		HGLOBAL hgBuffer;
		char* chBuffer;
		EmptyClipboard(); //������� �����
		hgBuffer = GlobalAlloc(GMEM_DDESHARE, puttedString.length() + 1);//�������� ������
		chBuffer = (char*)GlobalLock(hgBuffer); //��������� ������
		strcpy(chBuffer, LPCSTR(getStringContent(puttedString)));
		GlobalUnlock(hgBuffer);//������������ ������
		SetClipboardData(CF_TEXT, hgBuffer);//�������� ����� � ����� ������
		CloseClipboard(); //��������� ����� ������
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
	std::string prefics = "const POINT* polygonFigure = { ";
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
		putInClipboard(compiliedFigure);
}

void endPage_onMouseRightButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	if(figureCompilied)
		putInClipboard(compiliedFigure);
}

void endPage_onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
{
	TextOutWithDynamicLength(paintInWindowHDC, 10, 10, "B - Back to draw");
	TextOutWithDynamicLength(paintInWindowHDC, screenSize.x / 2 - 75, screenSize.y - 50, "Press Any Key To Copy Result In Clipboard");
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