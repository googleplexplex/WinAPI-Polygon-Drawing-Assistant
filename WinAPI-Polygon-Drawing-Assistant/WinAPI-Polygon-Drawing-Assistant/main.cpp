#include <Windows.h>

#define WINDOW_CLASS_NAME "WinAPI_Polygon_Drawing_Assistant"
#define WINDOW_NAME "WinAPI Polygon Drawing Assistant"

#define KB_CODE(charset) (0x41 + (charset - 'a'))
#define KB_CODE_BIG(charset) (0x41 + (charset - 'A'))
#define TextOutWithDynamicLength(hdc, x, y, str) TextOut(hdc, x, y, str, strlen(str))

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Game_Init();
void Game_Main();
void Game_Shitdown();

void onMouseLeftButtonClick(HDC clickedWindowHDC, LONG x, LONG y);
void onMouseRightButtonClick(HDC clickedWindowHDC, LONG x, LONG y);
void onPaint(HDC hdc, PAINTSTRUCT& ps);
void onKeyPressed(unsigned int key);

void clearWindow(HDC clearedWindowHDC);
void inline refreshCanvas();

HINSTANCE hInstanceApp;
HWND mainWindowHWND;
constexpr POINT screenSize = { 400, 300 };
typedef enum appStateEnum
{
	startPage = 0,
	drawPage,
	endPage
};
appStateEnum _appState;
void setAppState(appStateEnum newAppState)
{
	_appState = newAppState;
	clearWindow(GetDC(mainWindowHWND));
	refreshCanvas();
}

POINT* polygonPoints;
unsigned short polygonPointsCount = 0;

#include "endPage.hpp"
#include "drawPage.hpp"
#include "startPage.hpp"

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{

	WNDCLASSEX winClass;
	HWND hwnd;
	MSG msg;
	HDC hdc;

	winClass.cbSize = sizeof(WNDCLASSEX);

	winClass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = WINDOW_CLASS_NAME;
	winClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	hInstanceApp = hInstance;

	if (!RegisterClassEx(&winClass))
		return 0;

	if (!(hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, screenSize.x, screenSize.y,
		NULL, NULL,
		hInstance,
		NULL)))
		return 0;

	mainWindowHWND = hwnd;

	Game_Init();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Game_Main();
	}

	Game_Shitdown();

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		onPaint(hdc, ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_RBUTTONDOWN:
		onMouseRightButtonClick(GetDC(mainWindowHWND), (LONG)LOWORD(lParam), (LONG)HIWORD(lParam));
		break;
	case WM_LBUTTONDOWN:
		onMouseLeftButtonClick(GetDC(mainWindowHWND), (LONG)LOWORD(lParam), (LONG)HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		onKeyPressed((unsigned int)wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

void clearWindow(HDC clearedWindowHDC)
{
	RECT consoleWindowRect = { 0 };
	GetWindowRect(mainWindowHWND, &consoleWindowRect);
	const HBRUSH oldBrush = (HBRUSH)SelectObject(clearedWindowHDC, (HBRUSH)CreateSolidBrush(RGB(0, 0, 0)));

	Rectangle(clearedWindowHDC, consoleWindowRect.left, consoleWindowRect.top, consoleWindowRect.right, consoleWindowRect.bottom);
	
	SelectObject(clearedWindowHDC, oldBrush);
}

void inline refreshCanvas()
{
	InvalidateRect(mainWindowHWND, NULL, NULL);
	SendMessage(mainWindowHWND, WM_PAINT, NULL, NULL);
}

void setWindowCorrectSize()
{
	RECT consoleWindowRect = { 0 };
	GetWindowRect(mainWindowHWND, &consoleWindowRect);
	MoveWindow(mainWindowHWND, consoleWindowRect.left, consoleWindowRect.top, screenSize.x + 4, screenSize.y + 30, NULL);
}


void Game_Init()
{
	_appState = startPage;
}

void Game_Main()
{
	setWindowCorrectSize();
}

void Game_Shitdown()
{
	return;
}


void onMouseLeftButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	switch (_appState)
	{
	case startPage:
		startPage_onMouseLeftButtonClick(clickedWindowHDC, x, y);
		return;
	case drawPage:
		drawPage_onMouseLeftButtonClick(clickedWindowHDC, x, y);
		return;
	case endPage:
		endPage_onMouseLeftButtonClick(clickedWindowHDC, x, y);
		return;
	}
}

void onMouseRightButtonClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	switch (_appState)
	{
	case startPage:
		startPage_onMouseRightButtonClick(clickedWindowHDC, x, y);
		return;
	case drawPage:
		drawPage_onMouseRightButtonClick(clickedWindowHDC, x, y);
		return;
	case endPage:
		endPage_onMouseRightButtonClick(clickedWindowHDC, x, y);
		return;
	}
}

void onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
{
	clearWindow(paintInWindowHDC);
	switch (_appState)
	{
	case startPage:
		startPage_onPaint(paintInWindowHDC, ps);
		return;
	case drawPage:
		drawPage_onPaint(paintInWindowHDC, ps);
		return;
	case endPage:
		endPage_onPaint(paintInWindowHDC, ps);
		return;
	}
}

void onKeyPressed(unsigned int key)
{
	switch (_appState)
	{
	case startPage:
		startPage_onKeyPressed(key);
		return;
	case drawPage:
		drawPage_onKeyPressed(key);
		return;
	case endPage:
		endPage_onKeyPressed(key);
		return;
	}
}