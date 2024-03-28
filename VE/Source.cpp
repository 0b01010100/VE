#include <Windows.h>
#include <iostream>
int main()
{
    //describe the window
    WNDCLASSW wc = {};
    //class name
    wc.lpszClassName = L"VGERW";
    //event handler
    wc.lpfnWndProc = DefWindowProc;
    //id of the application
    wc.hInstance = GetModuleHandle(0);
    //windows Cursor
    wc.hCursor = LoadCursor(0, IDC_IBEAM);
    //make window color red
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
    //store description for later use in the CreateWindow function 

    //get screen screen width
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    //get screen screen height
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    //register this windows description to be used later in the CreateWindow function
    RegisterClass(&wc);

    //adjust the window size based on the window style and desired client size
    RECT rc = { 0, 0, screenWidth / 2, screenHeight / 2 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, 0);

    //find the correct window width and height
    int windowWidth = rc.right - rc.left;
    int windowHeight = rc.bottom - rc.top;

    //center window x and y position. Depeneding on your monitor size and the style the window might not be fully centered. maybe off just by a small decimal number, if numberes were not divided evenly
    double xpos = (screenWidth - windowWidth) / 2.0;
    double ypos = (screenHeight - windowHeight) / 2.0;

    //create window
    HWND hwnd = CreateWindow(
        L"VGERW", //window class name 
        L"Virtule Game Engine", //window display name 
        WS_OVERLAPPEDWINDOW, // commons window styles
        xpos, ypos, //pos x and y
        windowWidth, windowHeight, //width and height 
        0, 0, 
        wc.hInstance,//application instance
        0);
    //make window visable
    ShowWindow(hwnd, SW_SHOW);
    //check for messages and call event handlers
    while (true)
    {
        MSG msg = {};
        PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE);
        DispatchMessage(&msg);
    }
}