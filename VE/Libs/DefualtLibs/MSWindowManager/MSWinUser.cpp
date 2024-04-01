#include "MSWinUser.h"

void * MS_CreateWindow(const wchar_t * name, long SizeX, long SizeY)
{
    //describe the window
    WNDCLASSW wc = {};
    //class name
    wc.lpszClassName = name;
    //event handler
    wc.lpfnWndProc = DefWindowProcW;
    //id of the application
    wc.hInstance = GetModuleHandle(0);
    //windows Cursor
    wc.hCursor = LoadCursor(0, IDC_IBEAM);

    //get screen screen width
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    //get screen screen height
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    //register this windows description to be used later in the CreateWindow function
    RegisterClassW(&wc);

    //if user typed in zero make the window Width the monitor screen width div by 2
    if (SizeX == 0) SizeX = screenWidth / 2;
    //if user typed in zero make the window Height the monitor screen width div by 2
    if (SizeY == 0) SizeY = screenHeight / 2;

    //adjust the window size based on the window style and desired client size
    RECT rc = { 0L, 0L, SizeX, SizeY };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, 0);

    //find the correct window width and height
    int windowWidth = rc.right - rc.left;
    int windowHeight = rc.bottom - rc.top;

    //center window x and y position. Depeneding on your monitor size and the style the window might not be fully centered. maybe off just by a small decimal number, if numberes were not divided evenly
    int xpos = (screenWidth - windowWidth) / 2;
    int ypos = (screenHeight - windowHeight) / 2;

    //create window
    HWND hwnd = CreateWindowW(
    name, //window class name 
    name, //window display name 
    WS_OVERLAPPEDWINDOW, // commons window styles
    xpos, ypos, //pos x and y
    windowWidth, windowHeight, //width and height 
    0, 0,
    wc.hInstance,//application instance
    0);
    if (hwnd == nullptr) 
    {
        MS_ERROR(L"MS window creation error", L"Failed to create window in File: ");
    }
    //make window visable
    ShowWindow(hwnd, SW_SHOW);
    return hwnd;
}

void MS_UpdateWindow(void * hwnd)
{
    //check for messages and call event handlers
    MSG msg = {};
    PeekMessageW(&msg, (HWND)hwnd, 0, 0, PM_REMOVE);
    DispatchMessageW(&msg);
}
