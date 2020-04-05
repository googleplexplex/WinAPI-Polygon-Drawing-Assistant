#pragma once
#include <Windows.h>

constexpr unsigned short markerRadius = 20;
constexpr COLORREF markerColor = RGB(0, 255, 0);
const HBRUSH markerBrush = (HBRUSH)CreateSolidBrush(markerColor);
void drawPage_onMouseLeftButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	POINT* oldPoints = polygonPoints;
	polygonPoints = new POINT[polygonPointsCount + 1];
	memcpy(polygonPoints, oldPoints, sizeof(POINT) * polygonPointsCount);
	polygonPoints[polygonPointsCount] = { x, y };
	polygonPointsCount++;

	refreshCanvas();
}

void drawPage_onMouseRightButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	
}

constexpr COLORREF polygonsColor = RGB(0, 0, 255);
const HBRUSH polygonsBrush = (HBRUSH)CreateSolidBrush(polygonsColor);
void drawPage_onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
{
	clearWindow(paintInWindowHDC);

	if (polygonPointsCount > 2)
	{
		const HBRUSH oldBrush = (HBRUSH)SelectObject(paintInWindowHDC, polygonsBrush);

		Polygon(paintInWindowHDC, polygonPoints, polygonPointsCount);

		SelectObject(paintInWindowHDC, oldBrush);
	}

	const HBRUSH oldBrush = (HBRUSH)SelectObject(paintInWindowHDC, markerBrush);
	for (int i = 0; i < polygonPointsCount; i++)
	{
		Ellipse(paintInWindowHDC, polygonPoints[i].x - markerRadius / 2, polygonPoints[i].y - markerRadius / 2, polygonPoints[i].x + markerRadius / 2, polygonPoints[i].y + markerRadius / 2);
	}
	SelectObject(paintInWindowHDC, oldBrush);
}

void drawPage_onKeyPressed(unsigned int key)
{

}