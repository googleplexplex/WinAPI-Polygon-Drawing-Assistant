#pragma once
#include <iostream>
typedef std::pair<const char*, unsigned int> string;

bool putInClipboard(string puttedString)
{
	if (OpenClipboard(mainWindowHWND))//открываем буфер обмена
	{
		HGLOBAL hgBuffer;
		char* chBuffer;
		EmptyClipboard(); //очищаем буфер
		hgBuffer = GlobalAlloc(GMEM_DDESHARE, puttedString.second + 1);//выделяем память
		chBuffer = (char*)GlobalLock(hgBuffer); //блокируем память
		strcpy(chBuffer, LPCSTR(puttedString.first));
		GlobalUnlock(hgBuffer);//разблокируем память
		SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
		CloseClipboard(); //закрываем буфер обмена
		return true;
	} else
		return false;
}
string compileFigureToCode()
{
	return { "HELLO CLIPBOARD", strlen("HELLO CLIPBOARD") }; //TEST
}

void endPage_onMouseLeftButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	putInClipboard(compileFigureToCode());
}

void endPage_onMouseRightButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	putInClipboard(compileFigureToCode());
}

void endPage_onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
{
	TextOutWithDynamicLength(paintInWindowHDC, 10, 10, "B - Back to draw");
	TextOutWithDynamicLength(paintInWindowHDC, screenSize.x / 2 - 75, screenSize.y - 50, "Press Any Key To Copy Result In Clipboard");
}

void endPage_onKeyPressed(unsigned int key)
{
	putInClipboard(compileFigureToCode());
	if (key == KB_CODE('b') || key == KB_CODE_BIG('B'))
	{
		setAppState(drawPage);
	}
}