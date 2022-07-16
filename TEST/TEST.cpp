// TEST.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TEST.h"
#include <bit>
//#include "WindowClass.h"
//#include "Window.h"

import MoWin.Window;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


struct TESTWindowClass
{
    static MoWin::WindowClassStyle Style() { return MoWin::WindowClassStyle(CS_HREDRAW | CS_VREDRAW); }
    //static int ExtraClassBytes() { return 0; }
    //static int ExtraWindowBytes() { return 0; }
    static HICON Icon(HINSTANCE instance) { return LoadIcon(instance, MAKEINTRESOURCE(IDI_TEST)); }
    static HCURSOR Cursor(HINSTANCE instance) { return LoadCursor(nullptr, IDC_ARROW); }
    static HBRUSH BackgroundBrush() { return (HBRUSH)(COLOR_WINDOW + 1); }
    static LPCWSTR ClassName() { return szWindowClass; }
    static LPCWSTR MenuName() { return MAKEINTRESOURCEW(IDC_TEST); }
    static HICON SmallIcon(HINSTANCE instance) { return LoadIcon(instance, MAKEINTRESOURCE(IDI_SMALL)); }

    //TESTWindowClass() {}

    HWND hwnd;

    LRESULT operator()(MoWin::Event::WindowNotifications::Destroy event)
    {
        PostQuitMessage(0);
        return 0;
    }

    LRESULT operator()(MoWin::Event event)
    {
        switch(static_cast<UINT>(event.type))
        {
        case WM_COMMAND:
        {
            int wmId = LOWORD(event.wParam);
            // Parse the menu selections:
            switch(wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), event.window, About);
                break;
            case IDM_EXIT:
                DestroyWindow(event.window);
                break;
            default:
                return DefWindowProc(event.window, static_cast<UINT>(event.type), event.wParam, event.lParam);
            }
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(event.window, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(event.window, &ps);
        }
        break;
        default:
            {
                return MoWin::WindowClassTraits<TESTWindowClass>::VisitEvent(*this, event);
            }
        }

        return 0;
    }
};

static_assert(MoWin::HasVisitableEvent<TESTWindowClass>);
static_assert(MoWin::HasProcedure<TESTWindowClass>);
static_assert(MoWin::IsWindowClass<TESTWindowClass>);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEST, szWindowClass, MAX_LOADSTRING);

    SetWindowLongPtr(nullptr, GWLP_USERDATA, 0);
    auto error = GetLastError();
    hInst = hInstance; // Store instance handle in our global variable

    MoWin::Window<TESTWindowClass> window(szTitle, MoWin::WindowStyle(WS_OVERLAPPEDWINDOW | WS_VISIBLE),
       POINT{ 0, 0 }, MoWin::Dimension2D{ 1280, 720 }, nullptr, nullptr, hInstance, MoWin::WindowCreateFlag::None);

    if(!window)
    {
        return FALSE;
    }

    window.Show();
    UpdateWindow(window);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
