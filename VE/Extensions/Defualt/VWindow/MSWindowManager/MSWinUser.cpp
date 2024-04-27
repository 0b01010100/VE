#include "MSWinUser.h"
//#define UNICODE
#include <Windows.h>
#include <sstream>
//creates a Microsift specefic window
static void* MSW_CreateWindow(const wchar_t* name, long SizeX, long SizeY);
//update window
__declspec(noinline) static  void MSW_UpdateWindow(void* hwnd);
//Gets the client Size of the window
__declspec(noinline) static void MSW_GetClientWindowRect(void* hwnd, long rect[4]);
//Debugging only for MS window creation tool
#define MS_ERROR(error_type, ...) \
{ \
	std::wstringstream stream = {}; \
	stream << error_type << L"\n" <<__VA_ARGS__ << __FILEW__ << L"\n"; \
	printf("%ls", stream.str().c_str()); \
	OutputDebugStringW(stream.str().c_str()); \
	MessageBoxW(0, stream.str().c_str(), error_type, MB_ICONERROR | MB_OK); \
}

struct IWindow
{
    void(*updateWindow);
    void(*getClientWindowRect);
};
void* MSW_init(void* window, const wchar_t* name, long SizeX, long SizeY)
{
    IWindow* wnd =  reinterpret_cast<IWindow*>(window);
    wnd->updateWindow = MSW_UpdateWindow;
    wnd->getClientWindowRect = MSW_GetClientWindowRect;
    void* hwnd = MSW_CreateWindow(name, SizeX, SizeY);
    return hwnd;
}

static void * MSW_CreateWindow(const wchar_t * name, long SizeX, long SizeY)
{
    //describe the window
    WNDCLASSW wc = { 0 };
    //class name
    wc.lpszClassName = name;
    //event handler
    wc.lpfnWndProc = DefWindowProcW;
    //id of the application
    wc.hInstance = GetModuleHandleW(0);
    //windows Cursor
    wc.hCursor = LoadCursorW(0, IDC_IBEAM);

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
__declspec(noinline) static
void MSW_UpdateWindow(void * hwnd)
{
    //check for messages and call event handlers
    MSG msg = {};
    PeekMessageW(&msg, reinterpret_cast<HWND>( hwnd ), 0, 0, PM_REMOVE);
    DispatchMessageW(&msg);
}
__declspec(noinline) static
void MSW_GetClientWindowRect(void* hwnd, long rect[4])
{
    RECT wr;
    GetClientRect(reinterpret_cast<HWND>(hwnd), &wr);
    rect[0] = wr.left;
    rect[1] = wr.top;
    rect[2] = wr.right;
    rect[3] = wr.bottom;
}
