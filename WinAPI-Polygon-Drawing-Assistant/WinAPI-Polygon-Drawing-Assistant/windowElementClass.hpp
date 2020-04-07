#pragma once

class windowElementClass
{
public:
	HWND hwnd;
	LPCSTR content;
	HMENU id;
	POINT pos;
	POINT size;
protected:
	LPCSTR className;
	DWORD styles;
public:
	windowElementClass(LPCSTR _className, LPCSTR _content, HMENU _id, DWORD _styles, POINT _pos, POINT _size)
	{
		className = _className;
		content = _content;
		id = _id;
		styles = _styles;
		pos = _pos;
		size = _size;
	}
	windowElementClass() {}
	void createElement()
	{
		hwnd = CreateWindow(className, content,
			styles,
			pos.x, pos.y, size.x, size.y,
			mainWindowHWND, id, hInst, NULL);
	}
	void deleteElement()
	{
		DestroyWindow(hwnd);
	}
};
struct windowButtonClass : windowElementClass
{
	windowButtonClass(LPCSTR _content, HMENU _id, POINT _pos, POINT _size)
	{
		className = "button";
		styles = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;
		content = _content;
		id = _id;
		pos = _pos;
		size = _size;
	}
};
struct windowTextBoxClass : windowElementClass
{
	windowTextBoxClass(LPCSTR _content, HMENU _id, POINT _pos, POINT _size)
	{
		className = "edit";
		styles = WS_CHILD | WS_VISIBLE | SS_LEFT | WS_GROUP | ES_MULTILINE;
		content = _content;
		id = _id;
		pos = _pos;
		size = _size;
	}
};

void createAllElements(windowElementClass* elementsArray, unsigned int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		elementsArray[i].createElement();
	}
}

void deleteAllElements(windowElementClass* elementsArray, unsigned int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		elementsArray[i].deleteElement();
	}
}