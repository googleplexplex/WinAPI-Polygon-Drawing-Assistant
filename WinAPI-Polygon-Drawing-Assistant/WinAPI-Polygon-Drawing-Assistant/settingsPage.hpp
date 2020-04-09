#pragma once
#include "windowElementClass.hpp"
#include "startPage.hpp"

#define ID_TEXTBOX_XSIZE 5
#define ID_TEXTBOX_XSIZE 6
#define ID_BUTTON_BACK 7

constexpr unsigned int setPage_windowElementsCount = 1;
windowElementClass setPage_windowElements[setPage_windowElementsCount] = {
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

void setPage_onCommandCatch(unsigned int idCatcher)
{
	switch (idCatcher)
	{
	case ID_BUTTON_BACK:
		callPage(startPage);
		break;
	}
}