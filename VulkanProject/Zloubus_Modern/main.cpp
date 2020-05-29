#include <iostream>
#include <Windows.h>
#include "VulkanRenderer.h"

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	if (Message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	else if (Message == WM_CREATE)
	{
		MessageBoxA(hwnd, "Window was created", "HEllo", MB_ICONINFORMATION);
	}
	return DefWindowProc(hwnd, Message, wparam, lparam);
}

int main()
{
	try {
		HINSTANCE hInstance = GetModuleHandleA(nullptr);

		WNDCLASSEX wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszClassName = TEXT("MyWndClass");
		RegisterClassEx(&wcex);

		HWND hwnd = CreateWindow(
			TEXT("MyWndClass"),
			TEXT("My Window"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			640,
			480,
			NULL,
			NULL,
			hInstance,
			NULL);

		if (!hwnd)
		{
			throw runtime_error("ERROR: Cannot create window");
		}

		VulkanRenderer vkRenderer = VulkanRenderer();

		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		UpdateWindow(hwnd);

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	catch (const exception& e) {
		cout << e.what() << endl;
		system("pause");
	}

	return 0;
}