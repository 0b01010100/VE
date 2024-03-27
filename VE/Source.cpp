#include <Windows.h>
#include <iostream>

int main() 
{

    //describe the window
    WNDCLASSW wc = {};
    //class name
    wc.lpszClassName = L"jo";
    //event handler
    wc.lpfnWndProc = DefWindowProc;
    //id of the application
    wc.hInstance = GetModuleHandle(0);
    //windows Cursor
    wc.hCursor = LoadCursor(0, IDC_UPARROW);
    //make window color red
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
    //store description for later use in the CreateWindow function 
    RegisterClass(&wc);
    //create window

    HWND hwnd = CreateWindow(L"jo", L"josh", WS_OVERLAPPEDWINDOW,
        0, 0, //pos x and y
        300, 300, //width and height 
        0, 0, wc.hInstance, 0);

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