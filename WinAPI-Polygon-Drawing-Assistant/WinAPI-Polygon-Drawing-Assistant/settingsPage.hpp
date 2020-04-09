#pragma once
#include <Windows.h>
#include "windowElementClass.hpp"
#include "startPage.hpp"

#define ID_TEXTBOX_XSIZE 5
#define ID_TEXTBOX_YSIZE 6
#define ID_BUTTON_BACK 7
#define ID_BUTTON_APPLY 8

constexpr unsigned int setPage_windowElementsCount = 4;
windowElementClass setPage_windowElements[setPage_windowElementsCount] = {
	windowTextBoxClass("", (HMENU)ID_TEXTBOX_XSIZE, { screenSize.x / 3 * 2, screenSize.y / 4 }, { 100, 20 }),
	windowTextBoxClass("", (HMENU)ID_TEXTBOX_YSIZE, { screenSize.x / 3 * 2, screenSize.y / 4 + 30 }, { 100, 20 }),
	windowButtonClass("Apply", (HMENU)ID_BUTTON_APPLY, { screenSize.x - 100 - 30, screenSize.y - 30 - 30 }, { 100, 30 }),
	windowButtonClass("Back", (HMENU)ID_BUTTON_BACK, { 30, screenSize.y - 30 - 30 }, { 100, 30 }) };


void setPage_onCalled()
{
	
}

void setPage_onMouseLeftButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{

}

void setPage_onMouseRightButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{

}

void setPage_onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
{
	
}

void setPage_onKeyPressed(unsigned int key)
{

}

void setPage_onCommandCatch(unsigned int idCatcher, unsigned int param)
{
	char* textBoxXSizeContentStr = new char[5];
	char* textBoxYSizeContentStr = new char[5];
	unsigned int textBoxXSizeContent;
	unsigned int textBoxYSizeContent;
	switch (idCatcher)
	{
	case ID_BUTTON_APPLY:
		GetWindowTextA(setPage_windowElements[ID_TEXTBOX_XSIZE].hwnd, textBoxXSizeContentStr, 5);
		GetWindowTextA(setPage_windowElements[ID_TEXTBOX_YSIZE].hwnd, textBoxYSizeContentStr, 5);
		screenSize = { atoi(textBoxXSizeContentStr), atoi(textBoxYSizeContentStr) };
	case ID_BUTTON_BACK:
		callPage(startPage);
		break;
	case ID_TEXTBOX_XSIZE:
		switch (param)
		{
		case EN_CHANGE:
			GetWindowTextA(setPage_windowElements[ID_TEXTBOX_XSIZE].hwnd, textBoxXSizeContentStr, 5);
			GetWindowTextA(setPage_windowElements[ID_TEXTBOX_YSIZE].hwnd, textBoxYSizeContentStr, 5);
			textBoxXSizeContent = atoi(textBoxXSizeContentStr);
			textBoxYSizeContent = atoi(textBoxYSizeContentStr);
			if(textBoxXSizeContent != NULL && textBoxYSizeContent != NULL
				&& textBoxXSizeContent > 300 && textBoxYSizeContent > 300
				&& textBoxXSizeContent < 1920 && textBoxYSizeContent < 1080)
			break;
		}
	case ID_TEXTBOX_YSIZE:
		break;
	}
}