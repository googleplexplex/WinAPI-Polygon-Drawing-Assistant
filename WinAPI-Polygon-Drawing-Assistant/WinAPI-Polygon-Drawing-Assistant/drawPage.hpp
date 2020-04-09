#pragma once
#include <Windows.h>
#define sqr(x) ((x)*(x))

constexpr unsigned short markerRadius = 20;
constexpr COLORREF markerColor = RGB(0, 255, 0);
const HBRUSH markerBrush = (HBRUSH)CreateSolidBrush(markerColor);
constexpr COLORREF polygonsColor = RGB(0, 0, 255);
const HBRUSH polygonsBrush = (HBRUSH)CreateSolidBrush(polygonsColor);

constexpr unsigned int drawPage_windowElementsCount = 0;
windowElementClass* drawPage_windowElements = NULL;

void drawPage_onCalled()
{

}

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
	for (int i = 0; i < polygonPointsCount; i++)
	{
		double rangeBetweenClickAndPoint = sqrt(sqr(x - polygonPoints[i].x) + sqr(y - polygonPoints[i].y));
		if (rangeBetweenClickAndPoint < markerRadius)
		{
			POINT* oldPoints = polygonPoints;
			polygonPoints = new POINT[polygonPointsCount - 1];
			memcpy(polygonPoints, oldPoints, sizeof(POINT) * i);
			memcpy(&polygonPoints[i], &oldPoints[i + 1], sizeof(POINT) * (polygonPointsCount - i - 1));
			polygonPointsCount--;

			refreshCanvas();
			return;
		}
	}
}

void drawPage_onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
{
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
	if (key == KB_CODE('f') || key == KB_CODE_BIG('F'))
	{
		callPage(endPage);
	}
}

void drawPage_onCommandCatch(unsigned int idCatcher)
{

}