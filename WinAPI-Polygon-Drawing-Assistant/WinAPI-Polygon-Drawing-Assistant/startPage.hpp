#pragma once

#define ID_BUTTON_START 0
#define ID_BUTTON_SETTINGS 1

constexpr unsigned int startPage_windowElementsCount = 2;
windowElementClass startPage_windowElements[startPage_windowElementsCount] = {
	windowButtonClass("Start Draw", (HMENU)ID_BUTTON_START, { screenSize.x - 100 - 30, screenSize.y - 30 - 30 }, { 100, 30 }),
	windowButtonClass("Settings", (HMENU)ID_BUTTON_SETTINGS, { 30, screenSize.y - 30 - 30 }, { 100, 30 }) };

void startPage_onCalled()
{
	createAllElements(startPage_windowElements, startPage_windowElementsCount);
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

void startPage_onCommandCatch(unsigned int idCatcher)
{
	switch (idCatcher)
	{
	case ID_BUTTON_START:
		deleteAllElements(startPage_windowElements, startPage_windowElementsCount);
		setAppState(drawPage);
		break;
	case ID_BUTTON_SETTINGS:
		deleteAllElements(startPage_windowElements, startPage_windowElementsCount); //TODO
		setAppState(drawPage);
		break;
	default:
		break;
	}
}