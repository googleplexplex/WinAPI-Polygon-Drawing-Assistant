#pragma once

void startPage_onMouseLeftButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	setAppState(drawPage);
}

void startPage_onMouseRightButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	setAppState(drawPage);
}

void startPage_onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
{
	TextOutCenter(paintInWindowHDC, 50, "F - End draw");
	TextOutCenter(paintInWindowHDC, screenSize.y - 50, "Press Any Key To Start");
}

void startPage_onKeyPressed(unsigned int key)
{
	setAppState(drawPage);
}

void startPage_onCommandCatch(unsigned int idCatcher)
{
	
}