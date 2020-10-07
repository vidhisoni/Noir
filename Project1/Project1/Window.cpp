#include "Window.h"
#include <Windows.h>

#define NOIR_WINDOW_CLASS "Noir Engine"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		case WM_CLOSE:
			if (MessageBox(hwnd, "Are you sure?", "Noir Engine", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hwnd);
			}
			// Else: User canceled. Do nothing.
		return 0;

		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
				EndPaint(hwnd, &ps);
			}
		return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window()
{
	pWindowHandle = nullptr;
}

Window::~Window()
{
	pWindowHandle = nullptr;
}

void Window::mOpenWindow()
{
	// Register the window class.

	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = NOIR_WINDOW_CLASS;

	RegisterClass(&wc);

	// Create the window.

	pWindowHandle = CreateWindowEx(
		0,                              // Optional window styles.
		NOIR_WINDOW_CLASS,              // Window class
		NOIR_WINDOW_CLASS,				// Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (pWindowHandle == NULL)
	{
		return;
	}

	ShowWindow((HWND)pWindowHandle, SW_SHOW);

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}