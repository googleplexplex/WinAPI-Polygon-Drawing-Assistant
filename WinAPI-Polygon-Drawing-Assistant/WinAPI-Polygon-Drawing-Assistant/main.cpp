#include <Windows.h>

#define WINDOW_CLASS_NAME "WinAPI_Polygon_Drawing_Assistant"
#define WINDOW_NAME "WinAPI Polygon Drawing Assistant"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Game_Init();
void Game_Main();
void Game_Shitdown();
void onMouseClick(HDC clickedWindowHDC, LONG x, LONG y);
void onPaint(HDC hdc, PAINTSTRUCT& ps);

HINSTANCE hInstanceApp;
HWND mainWindowHWND;
constexpr POINT screenSize = { 400, 300 };

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
	//case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		onMouseClick(GetDC(mainWindowHWND), (LONG)LOWORD(lParam), (LONG)HIWORD(lParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

void setWindowCorrectSize()
{
	RECT consoleWindowRect = { 0 };
	GetWindowRect(mainWindowHWND, &consoleWindowRect);
	MoveWindow(mainWindowHWND, consoleWindowRect.left, consoleWindowRect.top, screenSize.x + 4, screenSize.y + 30, NULL);
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


POINT* polygonPoints;
unsigned short polygonPointsCount = 0;

void Game_Init()
{
	return;
}

void Game_Main()
{
	setWindowCorrectSize();
}

void Game_Shitdown()
{
	return;
}


constexpr unsigned short markerRadius = 20;
constexpr COLORREF markerColor = RGB(0, 255, 0);
const HBRUSH markerBrush = (HBRUSH)CreateSolidBrush(markerColor);
void onMouseClick(HDC clickedWindowHDC, LONG x, LONG y)
{
	POINT* oldPoints = polygonPoints;
	polygonPoints = new POINT[polygonPointsCount + 1];
	memcpy(polygonPoints, oldPoints, sizeof(POINT) * polygonPointsCount);
	polygonPoints[polygonPointsCount] = { x, y };
	polygonPointsCount++;

	refreshCanvas();
}

constexpr COLORREF polygonsColor = RGB(0, 0, 255);
const HBRUSH polygonsBrush = (HBRUSH)CreateSolidBrush(polygonsColor);
void onPaint(HDC paintInWindowHDC, PAINTSTRUCT& ps)
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