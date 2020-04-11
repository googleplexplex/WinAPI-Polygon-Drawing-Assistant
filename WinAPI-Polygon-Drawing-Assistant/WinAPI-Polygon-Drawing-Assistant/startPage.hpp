#pragma once
#include "windowElementClass.hpp"
#include "settingsPage.hpp"

#define ID_BUTTON_START 3
#define ID_BUTTON_SETTINGS 4

constexpr unsigned int startPage_windowElementsCount = 2;
windowElementClass startPage_windowElements[startPage_windowElementsCount] = {
	windowButtonClass("Start Draw", (HMENU)ID_BUTTON_START, { screenSize.x - 100 - 30, screenSize.y - 30 - 30 }, { 100, 30 }),
	windowButtonClass("Settings", (HMENU)ID_BUTTON_SETTINGS, { 30, screenSize.y - 30 - 30 }, { 100, 30 }) };

void startPage_UpdateWindowElementsPosition()
{
	startPage_windowElements[ID_BUTTON_START].pos = { screenSize.x - 100 - 30, screenSize.y - 30 - 30 };
	startPage_windowElements[ID_BUTTON_SETTINGS].pos = { 30, screenSize.y - 30 - 30 };
}


void startPage_onCalled()
{
	startPage_UpdateWindowElementsPosition();
}

void startPage_onMouseLeftButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	
}

void startPage_onMouseRightButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	
}

void startPage_onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
{
	/*TextOutCenter(paintInWindowHDC, 50, "F - End draw");
	TextOutCenter(paintInWindowHDC, screenSize.y - 50, "Press Any Key To Start");*/
}

void startPage_onKeyPressed(unsigned int key)
{
	
}

void startPage_onCommandCatch(unsigned int idCatcher, unsigned int param)
{
	switch (idCatcher)
	{
	case ID_BUTTON_START:
		callPage(drawPage);
		break;
	case ID_BUTTON_SETTINGS:
		callPage(setPage);
		break;
	default:
		break;
	}
}