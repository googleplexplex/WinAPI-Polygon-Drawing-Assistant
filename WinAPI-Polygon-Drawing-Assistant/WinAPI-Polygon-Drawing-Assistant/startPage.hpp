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
	TextOutWithDynamicLength(paintInWindowHDC, 10, 10, "F - End draw");
	TextOutWithDynamicLength(paintInWindowHDC, screenSize.x / 2 - 75, screenSize.y - 50, "Press Any Key To Start");
}

void startPage_onKeyPressed(unsigned int key)
{
	setAppState(drawPage);
}