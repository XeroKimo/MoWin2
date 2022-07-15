module;

#include <Windows.h>
#include <memory>

export module MoWin.Window;
export import :Common;

#ifdef _WIN64
export import :Platform.Win64.Unicode;
export import :Platform.Win64.MBCS;
#endif

#undef CreateWindow
#undef SendMessage
#undef SendNotifyMessage
#undef SendMessageTimeout
#undef SendMessageCallback

namespace MoWin
{
    template<class DerivedSelf, class PlatformTrait>
    struct WindowInterface
    {
        using platform_traits = PlatformTrait;

        LRESULT SendMessage(EventType event, WPARAM wParam, LPARAM lParam)
        {
            platform_traits::SendMessage(Handle(), event, wParam, lParam);
        }

        //TODO: Do something about lpdwResult out parameter and the flags
        LRESULT SendMessageTimeout(EventType event, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult)
        {
            platform_traits::SendMessageTimeout(Handle(), event, wParam, lParam, fuFlags, uTimeout, lpdwResult);
        }

        LRESULT SendNotifyMessage(EventType event, WPARAM wParam, LPARAM lParam)
        {
            platform_traits::SendNotifyMessage(Handle(), event, wParam, lParam);
        }

        //TODO: Maybe do something about the asyn callback
        BOOL SendMessageCallback(
            EventType event,
            WPARAM wParam,
            LPARAM lParam,
            SENDASYNCPROC lpResultCallBack,
            ULONG_PTR dwData)
        {
            platform_traits::SendMessageCallback(Handle(), event, wParam, lParam, lpResultCallBack, dwData);
        }

        BOOL IsChildOf(HWND parent)
        {
            return ::IsChild(parent, Handle());
        }

        void Hide()
        {
            ::ShowWindow(Handle(), SW_HIDE);
        }

        void Show()
        {
            ::ShowWindow(Handle(), SW_SHOW);
        }

        void Minimize()
        {
            ::ShowWindow(Handle(), SW_MINIMIZE);
        }

        void Maximize()
        {
            ::ShowWindow(Handle(), SW_MAXIMIZE);
        }

        void Restore()
        {
            ::ShowWindow(Handle(), SW_RESTORE);
        }

        //TODO: UpdateLayeredWindow support?
        //BOOL UpdateLayeredWindow(
        //        _In_ HWND hWnd,
        //        _In_opt_ HDC hdcDst,
        //        _In_opt_ POINT* pptDst,
        //        _In_opt_ SIZE* psize,
        //        _In_opt_ HDC hdcSrc,
        //        _In_opt_ POINT* pptSrc,
        //        _In_ COLORREF crKey,
        //        _In_opt_ BLENDFUNCTION* pblend,
        //        _In_ DWORD dwFlags)

        //TODO: UpdateLayeredWindowIndirect support?
        //BOOL UpdateLayeredWindowIndirect(
        //    _In_ HWND hWnd,
        //    _In_ const UPDATELAYEREDWINDOWINFO* pULWInfo);

        //TODO: GetLayeredWindowAttributes support?
            //BOOL GetLayeredWindowAttributes(
            //    _In_ HWND hwnd,
            //    _Out_opt_ COLORREF* pcrKey,
            //    _Out_opt_ BYTE* pbAlpha,
            //    _Out_opt_ DWORD* pdwFlags);

        //TODO: PrintWindow support?
            //BOOL PrintWindow(
            //    _In_ HWND hwnd,
            //    _In_ HDC hdcBlt,
            //    _In_ UINT nFlags);

        //TODO: SetLayeredWindowAttributes support?
            //BOOL SetLayeredWindowAttributes(
            //    _In_ HWND hwnd,
            //    _In_ COLORREF crKey,
            //    _In_ BYTE bAlpha,
            //    _In_ DWORD dwFlags);

        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    MoveWindow(
        //        _In_ HWND hWnd,
        //        _In_ int X,
        //        _In_ int Y,
        //        _In_ int nWidth,
        //        _In_ int nHeight,
        //        _In_ BOOL bRepaint);

        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    SetWindowPos(
        //        _In_ HWND hWnd,
        //        _In_opt_ HWND hWndInsertAfter,
        //        _In_ int X,
        //        _In_ int Y,
        //        _In_ int cx,
        //        _In_ int cy,
        //        _In_ UINT uFlags);

        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    GetWindowPlacement(
        //        _In_ HWND hWnd,
        //        _Inout_ WINDOWPLACEMENT* lpwndpl);

        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    SetWindowPlacement(
        //        _In_ HWND hWnd,
        //        _In_ CONST WINDOWPLACEMENT* lpwndpl);


        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    GetWindowDisplayAffinity(
        //        _In_ HWND hWnd,
        //        _Out_ DWORD* pdwAffinity);

        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    SetWindowDisplayAffinity(
        //        _In_ HWND hWnd,
        //        _In_ DWORD dwAffinity);

        //WINUSERAPI
        //    HDWP
        //    WINAPI
        //    DeferWindowPos(
        //        _In_ HDWP hWinPosInfo,
        //        _In_ HWND hWnd,
        //        _In_opt_ HWND hWndInsertAfter,
        //        _In_ int x,
        //        _In_ int y,
        //        _In_ int cx,
        //        _In_ int cy,
        //        _In_ UINT uFlags);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //IsWindowVisible(
        //    _In_ HWND hWnd);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //IsIconic(
        //    _In_ HWND hWnd);

        //WINUSERAPI
        //BOOL
        //WINAPI
        //BringWindowToTop(
        //    _In_ HWND hWnd);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //IsZoomed(
        //    _In_ HWND hWnd);

        //WINUSERAPI
        //int
        //WINAPI
        //GetDlgCtrlID(
        //    _In_ HWND hWnd);

        //BOOL
        //WINAPI
        //SetDialogControlDpiChangeBehavior(
        //    _In_ HWND hWnd,
        //    _In_ DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS mask,
        //    _In_ DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS values);
        //
        //DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS
        //WINAPI
        //GetDialogControlDpiChangeBehavior(
        //    _In_ HWND hWnd);

        //TODO: AddClipboardFormatListener support?
        //BOOL AddClipboardFormatListener(
        //        _In_ HWND hwnd);

        //TODO: RemoveClipboardFormatListener support?
        //BOOL RemoveClipboardFormatListener(
        //        _In_ HWND hwnd);

        //TODO: RegisterTouchWindow support?
        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    RegisterTouchWindow(
        //        _In_ HWND hwnd,
        //        _In_ ULONG ulFlags);

        //TODO: UnregisterTouchWindow support?
        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    UnregisterTouchWindow(
        //        _In_ HWND hwnd);

        //TODO: IsTouchWindow support?
        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    IsTouchWindow(
        //        _In_ HWND hwnd,
        //        _Out_opt_ PULONG pulFlags);

        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    RegisterPointerInputTarget(
        //        _In_ HWND hwnd,
        //        _In_ POINTER_INPUT_TYPE pointerType);

        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    UnregisterPointerInputTarget(
        //        _In_ HWND hwnd,
        //        _In_ POINTER_INPUT_TYPE pointerType);

        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    RegisterPointerInputTargetEx(
        //        _In_ HWND hwnd,
        //        _In_ POINTER_INPUT_TYPE pointerType,
        //        _In_ BOOL fObserve);

        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    UnregisterPointerInputTargetEx(
        //        _In_ HWND hwnd,
        //        _In_ POINTER_INPUT_TYPE pointerType);
        // 
        //WINUSERAPI
        //    BOOL
        //    WINAPI
        //    RegisterTouchHitTestingWindow(
        //        _In_ HWND hwnd,
        //        _In_ ULONG value);
        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetWindowFeedbackSetting(
        //    _In_ HWND hwnd,
        //    _In_ FEEDBACK_TYPE feedback,
        //    _In_ DWORD dwFlags,
        //    _Inout_ UINT32* pSize,
        //    _Out_writes_bytes_opt_(*pSize) VOID* config);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //SetWindowFeedbackSetting(
        //    _In_ HWND hwnd,
        //    _In_ FEEDBACK_TYPE feedback,
        //    _In_ DWORD dwFlags,
        //    _In_ UINT32 size,
        //    _In_reads_bytes_opt_(size) CONST VOID* configuration);
        // 
        // WINUSERAPI
        //HWND
        //WINAPI
        //SetCapture(
        //    _In_ HWND hWnd);
        // 
        // WINUSERAPI
        //BOOL
        //WINAPI
        //IsWindowUnicode(
        //    _In_ HWND hWnd);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //EnableWindow(
        //    _In_ HWND hWnd,
        //    _In_ BOOL bEnable);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //IsWindowEnabled(
        //    _In_ HWND hWnd);
        // 
        // TODO:: Put the following 2 functions in PlatformTraits
        // WINUSERAPI
        //int
        //WINAPI
        //TranslateAcceleratorA(
        //    _In_ HWND hWnd,
        //    _In_ HACCEL hAccTable,
        //    _In_ LPMSG lpMsg);
        //WINUSERAPI
        //int
        //WINAPI
        //TranslateAcceleratorW(
        //    _In_ HWND hWnd,
        //    _In_ HACCEL hAccTable,
        //    _In_ LPMSG lpMsg);
        // 
        //WINUSERAPI
        //HMENU
        //WINAPI
        //GetMenu(
        //    _In_ HWND hWnd);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //SetMenu(
        //    _In_ HWND hWnd,
        //    _In_opt_ HMENU hMenu);
        // 
        // WINUSERAPI
        //BOOL
        //WINAPI
        //HiliteMenuItem(
        //    _In_ HWND hWnd,
        //    _In_ HMENU hMenu,
        //    _In_ UINT uIDHiliteItem,
        //    _In_ UINT uHilite);
        // 
        // WINUSERAPI
        //BOOL
        //WINAPI
        //DrawMenuBar(
        //    _In_ HWND hWnd);
        // 
        // WINUSERAPI
        //HMENU
        //WINAPI
        //GetSystemMenu(
        //    _In_ HWND hWnd,
        //    _In_ BOOL bRevert);
        // 
        //WINUSERAPI
        //BOOL
        //WINAPI
        //DragDetect(
        //    _In_ HWND hwnd,
        //    _In_ POINT pt);
        // 
        // WINUSERAPI
        //BOOL
        //WINAPI
        //UpdateWindow(
        //    _In_ HWND hWnd);
        //
        //WINUSERAPI
        //HWND
        //WINAPI
        //SetActiveWindow(
        //    _In_ HWND hWnd);
        // 
        // WINUSERAPI
        //VOID
        //WINAPI
        //SwitchToThisWindow(
        //    _In_ HWND hwnd,
        //    _In_ BOOL fUnknown);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //SetForegroundWindow(
        //    _In_ HWND hWnd);
        // 
        // WINUSERAPI
        //HDC
        //WINAPI
        //BeginPaint(
        //    _In_ HWND hWnd,
        //    _Out_ LPPAINTSTRUCT lpPaint);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //EndPaint(
        //    _In_ HWND hWnd,
        //    _In_ CONST PAINTSTRUCT* lpPaint);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetUpdateRect(
        //    _In_ HWND hWnd,
        //    _Out_opt_ LPRECT lpRect,
        //    _In_ BOOL bErase);
        //
        //WINUSERAPI
        //int
        //WINAPI
        //GetUpdateRgn(
        //    _In_ HWND hWnd,
        //    _In_ HRGN hRgn,
        //    _In_ BOOL bErase);
        //
        //WINUSERAPI
        //int
        //WINAPI
        //SetWindowRgn(
        //    _In_ HWND hWnd,
        //    _In_opt_ HRGN hRgn,
        //    _In_ BOOL bRedraw);
        // 
        // WINUSERAPI
        //int
        //WINAPI
        //GetWindowRgn(
        //    _In_ HWND hWnd,
        //    _In_ HRGN hRgn);
        //
        //#if(_WIN32_WINNT >= 0x0501)
        //
        //WINUSERAPI
        //int
        //WINAPI
        //GetWindowRgnBox(
        //    _In_ HWND hWnd,
        //    _Out_ LPRECT lprc);
        //
        //#endif /* _WIN32_WINNT >= 0x0501 */
        //
        //WINUSERAPI
        //int
        //WINAPI
        //ExcludeUpdateRgn(
        //    _In_ HDC hDC,
        //    _In_ HWND hWnd);
        // 
        //WINUSERAPI
        //BOOL
        //WINAPI
        //InvalidateRgn(
        //    _In_ HWND hWnd,
        //    _In_opt_ HRGN hRgn,
        //    _In_ BOOL bErase);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //ValidateRgn(
        //    _In_ HWND hWnd,
        //    _In_opt_ HRGN hRgn);
        // 
        // TODO: Put the next 2 functions in PlatformTraits
        // WINUSERAPI
        //BOOL
        //WINAPI
        //ScrollWindow(
        //    _In_ HWND hWnd,
        //    _In_ int XAmount,
        //    _In_ int YAmount,
        //    _In_opt_ CONST RECT* lpRect,
        //    _In_opt_ CONST RECT* lpClipRect);
        // 
        // WINUSERAPI
        //int
        //WINAPI
        //ScrollWindowEx(
        //    _In_ HWND hWnd,
        //    _In_ int dx,
        //    _In_ int dy,
        //    _In_opt_ CONST RECT* prcScroll,
        //    _In_opt_ CONST RECT* prcClip,
        //    _In_opt_ HRGN hrgnUpdate,
        //    _Out_opt_ LPRECT prcUpdate,
        //    _In_ UINT flags);
        // 
        // WINUSERAPI
        //int
        //WINAPI
        //SetScrollPos(
        //    _In_ HWND hWnd,
        //    _In_ int nBar,
        //    _In_ int nPos,
        //    _In_ BOOL bRedraw);
        //
        //WINUSERAPI
        //int
        //WINAPI
        //GetScrollPos(
        //    _In_ HWND hWnd,
        //    _In_ int nBar);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //SetScrollRange(
        //    _In_ HWND hWnd,
        //    _In_ int nBar,
        //    _In_ int nMinPos,
        //    _In_ int nMaxPos,
        //    _In_ BOOL bRedraw);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetScrollRange(
        //    _In_ HWND hWnd,
        //    _In_ int nBar,
        //    _Out_ LPINT lpMinPos,
        //    _Out_ LPINT lpMaxPos);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //ShowScrollBar(
        //    _In_ HWND hWnd,
        //    _In_ int wBar,
        //    _In_ BOOL bShow);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //EnableScrollBar(
        //    _In_ HWND hWnd,
        //    _In_ UINT wSBflags,
        //    _In_ UINT wArrows);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //BOOL
        //WINAPI
        //SetPropA(
        //    _In_ HWND hWnd,
        //    _In_ LPCSTR lpString,
        //    _In_opt_ HANDLE hData);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //BOOL
        //WINAPI
        //SetPropW(
        //    _In_ HWND hWnd,
        //    _In_ LPCWSTR lpString,
        //    _In_opt_ HANDLE hData);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //HANDLE
        //WINAPI
        //GetPropA(
        //    _In_ HWND hWnd,
        //    _In_ LPCSTR lpString);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //HANDLE
        //WINAPI
        //GetPropW(
        //    _In_ HWND hWnd,
        //    _In_ LPCWSTR lpString);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //HANDLE
        //WINAPI
        //RemovePropA(
        //    _In_ HWND hWnd,
        //    _In_ LPCSTR lpString);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //HANDLE
        //WINAPI
        //RemovePropW(
        //    _In_ HWND hWnd,
        //    _In_ LPCWSTR lpString);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //int
        //WINAPI
        //EnumPropsExA(
        //    _In_ HWND hWnd,
        //    _In_ PROPENUMPROCEXA lpEnumFunc,
        //    _In_ LPARAM lParam);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //int
        //WINAPI
        //EnumPropsExW(
        //    _In_ HWND hWnd,
        //    _In_ PROPENUMPROCEXW lpEnumFunc,
        //    _In_ LPARAM lParam);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //int
        //WINAPI
        //EnumPropsA(
        //    _In_ HWND hWnd,
        //    _In_ PROPENUMPROCA lpEnumFunc);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //int
        //WINAPI
        //EnumPropsW(
        //    _In_ HWND hWnd,
        //    _In_ PROPENUMPROCW lpEnumFunc);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //BOOL
        //WINAPI
        //SetWindowTextA(
        //    _In_ HWND hWnd,
        //    _In_opt_ LPCSTR lpString);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //BOOL
        //WINAPI
        //SetWindowTextW(
        //    _In_ HWND hWnd,
        //    _In_opt_ LPCWSTR lpString);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //int
        //WINAPI
        //GetWindowTextA(
        //    _In_ HWND hWnd,
        //    _Out_writes_(nMaxCount) LPSTR lpString,
        //    _In_ int nMaxCount);
        //_Ret_range_(0, nMaxCount)
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //int
        //WINAPI
        //GetWindowTextW(
        //    _In_ HWND hWnd,
        //    _Out_writes_(nMaxCount) LPWSTR lpString,
        //    _In_ int nMaxCount);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //int
        //WINAPI
        //GetWindowTextLengthA(
        //    _In_ HWND hWnd);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //int
        //WINAPI
        //GetWindowTextLengthW(
        //    _In_ HWND hWnd);
        // 
        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetClientRect(
        //    _In_ HWND hWnd,
        //    _Out_ LPRECT lpRect);
        // 
        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetWindowRect(
        //    _In_ HWND hWnd,
        //    _Out_ LPRECT lpRect);
        // 
        //WINUSERAPI
        //BOOL
        //WINAPI
        //CreateCaret(
        //    _In_ HWND hWnd,
        //    _In_opt_ HBITMAP hBitmap,
        //    _In_ int nWidth,
        //    _In_ int nHeight);
        // 
        // WINUSERAPI
        //BOOL
        //WINAPI
        //ClientToScreen(
        //    _In_ HWND hWnd,
        //    _Inout_ LPPOINT lpPoint);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //ScreenToClient(
        //    _In_ HWND hWnd,
        //    _Inout_ LPPOINT lpPoint);
        //
        //#if(WINVER >= 0x0600)
        //WINUSERAPI
        //BOOL
        //WINAPI
        //LogicalToPhysicalPoint(
        //    _In_ HWND hWnd,
        //    _Inout_ LPPOINT lpPoint);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //PhysicalToLogicalPoint(
        //    _In_ HWND hWnd,
        //    _Inout_ LPPOINT lpPoint);
        // 
        //WINUSERAPI
        //HWND
        //WINAPI
        //ChildWindowFromPointEx(
        //    _In_ HWND hwnd,
        //    _In_ POINT pt,
        //    _In_ UINT flags);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //WORD
        //WINAPI
        //GetWindowWord(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex);
        //
        // TODO: Put in platform traits
        //WINUSERAPI
        //WORD
        //WINAPI
        //SetWindowWord(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex,
        //    _In_ WORD wNewWord);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //LONG
        //WINAPI
        //GetWindowLongA(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //LONG
        //WINAPI
        //GetWindowLongW(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //LONG
        //WINAPI
        //SetWindowLongA(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex,
        //    _In_ LONG dwNewLong);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //LONG
        //WINAPI
        //SetWindowLongW(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex,
        //    _In_ LONG dwNewLong);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //LONG_PTR
        //WINAPI
        //GetWindowLongPtrA(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //LONG_PTR
        //WINAPI
        //GetWindowLongPtrW(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //LONG_PTR
        //WINAPI
        //SetWindowLongPtrA(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex,
        //    _In_ LONG_PTR dwNewLong);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //LONG_PTR
        //WINAPI
        //SetWindowLongPtrW(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex,
        //    _In_ LONG_PTR dwNewLong);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //WORD
        //WINAPI
        //GetClassWord(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex);
        //
        // TODO: Put in platform traits
        //WINUSERAPI
        //WORD
        //WINAPI
        //SetClassWord(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex,
        //    _In_ WORD wNewWord);
        //
        // TODO: Put in platform traits
        //WINUSERAPI
        //DWORD
        //WINAPI
        //GetClassLongA(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex);
        // 
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //DWORD
        //WINAPI
        //GetClassLongW(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //DWORD
        //WINAPI
        //SetClassLongA(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex,
        //    _In_ LONG dwNewLong);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //DWORD
        //WINAPI
        //SetClassLongW(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex,
        //    _In_ LONG dwNewLong);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //ULONG_PTR
        //WINAPI
        //GetClassLongPtrA(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //ULONG_PTR
        //WINAPI
        //SetClassLongPtrA(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex,
        //    _In_ LONG_PTR dwNewLong);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //ULONG_PTR
        //WINAPI
        //SetClassLongPtrW(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex,
        //    _In_ LONG_PTR dwNewLong);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //ULONG_PTR
        //WINAPI
        //GetClassLongPtrW(
        //    _In_ HWND hWnd,
        //    _In_ int nIndex);
        // 
        //WINUSERAPI
        //HWND
        //WINAPI
        //GetParent(
        //    _In_ HWND hWnd);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //int
        //WINAPI
        //GetClassNameA(
        //    _In_ HWND hWnd,
        //    _Out_writes_to_(nMaxCount, return) LPSTR lpClassName,
        //    _In_ int nMaxCount
        //);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //int
        //WINAPI
        //GetClassNameW(
        //    _In_ HWND hWnd,
        //    _Out_writes_to_(nMaxCount, return) LPWSTR lpClassName,
        //    _In_ int nMaxCount
        //);
        //
        //WINUSERAPI
        //DWORD
        //WINAPI
        //GetWindowThreadProcessId(
        //    _In_ HWND hWnd,
        //    _Out_opt_ LPDWORD lpdwProcessId);
        // 
        // WINUSERAPI
        //HWND
        //WINAPI
        //GetLastActivePopup(
        //    _In_ HWND hWnd);
        // 
        // WINUSERAPI
        //HWND
        //WINAPI
        //GetWindow(
        //    _In_ HWND hWnd,
        //    _In_ UINT uCmd);
        // 
        // TODO: Put in platform traits
        // WINUSERAPI
        //LRESULT
        //WINAPI
        //DefFrameProcA(
        //    _In_ HWND hWnd,
        //    _In_opt_ HWND hWndMDIClient,
        //    _In_ UINT uMsg,
        //    _In_ WPARAM wParam,
        //    _In_ LPARAM lParam);
        // 
        // TODO: Put in platform traits
        //WINUSERAPI
        //LRESULT
        //WINAPI
        //DefFrameProcW(
        //    _In_ HWND hWnd,
        //    _In_opt_ HWND hWndMDIClient,
        //    _In_ UINT uMsg,
        //    _In_ WPARAM wParam,
        //    _In_ LPARAM lParam);
        // 
        //WINUSERAPI
        //int
        //WINAPI
        //SetScrollInfo(
        //    _In_ HWND hwnd,
        //    _In_ int nBar,
        //    _In_ LPCSCROLLINFO lpsi,
        //    _In_ BOOL redraw);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetScrollInfo(
        //    _In_ HWND hwnd,
        //    _In_ int nBar,
        //    _Inout_ LPSCROLLINFO lpsi);
        // 
        //WINUSERAPI
        //HMONITOR
        //WINAPI
        //MonitorFromWindow(
        //    _In_ HWND hwnd,
        //    _In_ DWORD dwFlags);
        //WINUSERAPI
        //DPI_AWARENESS_CONTEXT
        //WINAPI
        //GetWindowDpiAwarenessContext(
        //    _In_ HWND hwnd);
        //WINUSERAPI
        //UINT
        //WINAPI
        //GetDpiForWindow(
        //    _In_ HWND hwnd);
        //WINUSERAPI
        //DPI_HOSTING_BEHAVIOR
        //WINAPI
        //GetWindowDpiHostingBehavior(
        //    _In_ HWND hwnd);

        //TODO: Put the following 2 functions in platform traits
        //WINUSERAPI
        //UINT
        //WINAPI
        //GetWindowModuleFileNameA(
        //    _In_ HWND hwnd,
        //    _Out_writes_to_(cchFileNameMax, return) LPSTR pszFileName,
        //    _In_ UINT cchFileNameMax);
        //WINUSERAPI
        //UINT
        //WINAPI
        //GetWindowModuleFileNameW(
        //    _In_ HWND hwnd,
        //    _Out_writes_to_(cchFileNameMax, return) LPWSTR pszFileName,
        //    _In_ UINT cchFileNameMax);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetWindowInfo(
        //    _In_ HWND hwnd,
        //    _Inout_ PWINDOWINFO pwi);

        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetTitleBarInfo(
        //    _In_ HWND hwnd,
        //    _Inout_ PTITLEBARINFO pti);

        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetMenuBarInfo(
        //    _In_ HWND hwnd,
        //    _In_ LONG idObject,
        //    _In_ LONG idItem,
        //    _Inout_ PMENUBARINFO pmbi);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetScrollBarInfo(
        //    _In_ HWND hwnd,
        //    _In_ LONG idObject,
        //    _Inout_ PSCROLLBARINFO psbi);
        //
        //WINUSERAPI
        //HWND
        //WINAPI
        //GetAncestor(
        //    _In_ HWND hwnd,
        //    _In_ UINT gaFlags);

        //Maybe put the following 2 functions in platform traits
        //WINUSERAPI
        //UINT
        //WINAPI
        //RealGetWindowClassA(
        //    _In_ HWND hwnd,
        //    _Out_writes_to_(cchClassNameMax, return) LPSTR ptszClassName,
        //    _In_ UINT cchClassNameMax);
        ///*
        // * This gets the name of the window TYPE, not class.  This allows us to
        // * recognize ThunderButton32 et al.
        // */
        //WINUSERAPI
        //UINT
        //WINAPI
        //RealGetWindowClassW(
        //    _In_ HWND hwnd,
        //    _Out_writes_to_(cchClassNameMax, return) LPWSTR ptszClassName,
        //    _In_ UINT cchClassNameMax);

        //WINUSERAPI
        //DWORD
        //WINAPI
        //GetListBoxInfo(
        //    _In_ HWND hwnd);

        //WINUSERAPI
        //BOOL
        //WINAPI
        //SetGestureConfig(
        //    _In_ HWND hwnd,                                     // window for which configuration is specified
        //    _In_ DWORD dwReserved,                              // reserved, must be 0
        //    _In_ UINT cIDs,                                     // count of GESTURECONFIG structures
        //    _In_reads_(cIDs) PGESTURECONFIG pGestureConfig,    // array of GESTURECONFIG structures, dwIDs will be processed in the
        //                                                        // order specified and repeated occurances will overwrite previous ones
        //    _In_ UINT cbSize);                                  // sizeof(GESTURECONFIG)

        //WINUSERAPI
        //BOOL
        //WINAPI
        //GetGestureConfig(
        //    _In_ HWND hwnd,                                     // window for which configuration is required
        //    _In_ DWORD dwReserved,                              // reserved, must be 0
        //    _In_ DWORD dwFlags,                                 // see GCF_* flags
        //    _In_ PUINT pcIDs,                                   // *pcIDs contains the size, in number of GESTURECONFIG structures,
        //                                                        // of the buffer pointed to by pGestureConfig
        //    _Inout_updates_(*pcIDs) PGESTURECONFIG pGestureConfig,
        //                                                        // pointer to buffer to receive the returned array of GESTURECONFIG structures
        //    _In_ UINT cbSize);                                  // sizeof(GESTURECONFIG)

        //WINUSERAPI
        //BOOL
        //WINAPI
        //ShutdownBlockReasonCreate(
        //    _In_ HWND hWnd,
        //    _In_ LPCWSTR pwszReason);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //ShutdownBlockReasonQuery(
        //    _In_ HWND hWnd,
        //    _Out_writes_opt_(*pcchBuff) LPWSTR pwszBuff,
        //    _Inout_ DWORD* pcchBuff);
        //
        //WINUSERAPI
        //BOOL
        //WINAPI
        //ShutdownBlockReasonDestroy(
        //    _In_ HWND hWnd);

    private:
        HWND Handle() { return *(static_cast<DerivedSelf*>(this)); }
    };

    export template<class Ty, class PlatformTrait>
        requires IsWindowClassImpl<Ty, PlatformTrait>
    class WindowImpl
    {    
    public:
        using class_traits = WindowClassTraits<Ty>;
        using platform_traits = PlatformTrait;
        using string_type = platform_traits::string_type;

    private:
        HWND m_windowHandle;
        Ty m_data;

    public:
        template<class... Params>
        WindowImpl(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, Params&&... params) :
            m_windowHandle(CreateHandle(extendedStyle, windowName, style, x, y, width, height, optionalParent, menu, hInstance)),
            m_data(m_windowHandle, std::forward<Params>(params)...)
        {
        }

        template<class... Params>
        WindowImpl(string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, Params&&... params) :
            WindowImpl(WindowStyleEx{ 0 }, windowName, style, x, y, width, height, optionalParent, menu, hInstance, std::forward<Params>(params)...)
        {

        }

        WindowImpl(const WindowImpl& other) = delete;
        WindowImpl(WindowImpl&& other) noexcept :
            m_windowHandle(std::move(other.m_windowHandle)),
            m_data(std::move(other.m_data))
        {
            other.m_windowHandle = nullptr;

            SetLastError(0);
            platform_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, &m_data);
            if(GetLastError() == ERROR_INVALID_WINDOW_HANDLE)
            {
                //Do nothing
            }
        }

        WindowImpl& operator=(const WindowImpl& other) = delete;
        WindowImpl& operator=(WindowImpl&& other) noexcept
        {
            m_windowHandle = std::move(other.m_windowHandle);
            other.m_windowHandle = nullptr;
            m_data = std::move(other.m_data);

            SetLastError(0);
            platform_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, &m_data);
            if(GetLastError() == ERROR_INVALID_WINDOW_HANDLE)
            {
                //Do nothing
            }
            return *this;
        }

        ~WindowImpl()
        {
            DestroyWindow(m_windowHandle);
        }

    public:
        operator HWND() const { return m_windowHandle; }

    public:
        void Show() const
        {
            ::ShowWindow(m_windowHandle, SW_SHOW);
        }
        void Maximize() const
        {
            ::ShowWindow(m_windowHandle, SW_MAXIMIZE);
        }
        void Minimize() const
        {
            ::ShowWindow(m_windowHandle, SW_MINIMIZE);
        }

        Ty& ClassData() { return m_data; }
        const Ty& ClassData() const { return m_data; }

    private:
        HWND CreateHandle(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance)
        {
            if(!class_traits::Register(hInstance))
            {
                throw std::exception("Failed to register class");
            }

            HWND handle = platform_traits::CreateWindow(extendedStyle, Ty::ClassName(), windowName, style, x, y, width, height, optionalParent, menu, hInstance, nullptr);

            if(handle == nullptr)
            {
                throw std::exception("Handle is null");
            }

            platform_traits::SetWindowData(handle, GWLP_USERDATA, m_data);

            return handle;
        }
    };

    export using EventA = EventImpl<MBCSPlatformTraits>;
    export using EventW = EventImpl<UnicodePlatformTraits>;
    export using Event = EventImpl<DefaultPlatformTraits>;

    export template<EventType Type>
    using TypedEventA = TypedEventImpl<Type, MBCSPlatformTraits>;
    export template<EventType Type>
    using TypedEventW = TypedEventImpl<Type, UnicodePlatformTraits>;
    export template<EventType Type>
    using TypedEvent = TypedEventImpl<Type, DefaultPlatformTraits>;

    export template<IsWindowClassA Ty>
    using WindowA = WindowImpl<Ty, MBCSPlatformTraits>;

    export template<IsWindowClassW Ty>
    using WindowW = WindowImpl<Ty, UnicodePlatformTraits>;

    export template<IsWindowClass Ty>
    using Window = WindowImpl<Ty, DefaultPlatformTraits>;

}