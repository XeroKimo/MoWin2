#include <winapifamily.h>
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef INT_PTR(CALLBACK* DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef VOID(CALLBACK* TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);

typedef BOOL(CALLBACK* WNDENUMPROC)(HWND, LPARAM);
typedef VOID(CALLBACK* SENDASYNCPROC)(HWND, UINT, ULONG_PTR, LRESULT);

typedef BOOL(CALLBACK* PROPENUMPROCA)(HWND, LPCSTR, HANDLE);
typedef BOOL(CALLBACK* PROPENUMPROCW)(HWND, LPCWSTR, HANDLE);

typedef BOOL(CALLBACK* PROPENUMPROCEXA)(HWND, LPSTR, HANDLE, ULONG_PTR);
typedef BOOL(CALLBACK* PROPENUMPROCEXW)(HWND, LPWSTR, HANDLE, ULONG_PTR);


WINUSERAPI
BOOL
WINAPI
IsHungAppWindow(
    _In_ HWND hwnd);

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

WINUSERAPI
BOOL
WINAPI
DrawCaption(
    _In_ HWND hwnd,
    _In_ HDC hdc,
    _In_ CONST RECT* lprect,
    _In_ UINT flags);

WINUSERAPI
BOOL
WINAPI
DrawAnimatedRects(
    _In_opt_ HWND hwnd,
    _In_ int idAni,
    _In_ CONST RECT* lprcFrom,
    _In_ CONST RECT* lprcTo);

WINUSERAPI
BOOL
WINAPI
GetMessageA(
    _Out_ LPMSG lpMsg,
    _In_opt_ HWND hWnd,
    _In_ UINT wMsgFilterMin,
    _In_ UINT wMsgFilterMax);
WINUSERAPI
BOOL
WINAPI
GetMessageW(
    _Out_ LPMSG lpMsg,
    _In_opt_ HWND hWnd,
    _In_ UINT wMsgFilterMin,
    _In_ UINT wMsgFilterMax);

__inline
BOOL
GetMessage(
    LPMSG lpMsg,
    HWND hWnd,
    UINT wMsgFilterMin,
    UINT wMsgFilterMax
)
{
#ifdef UNICODE
    return GetMessageW(
#else
    return GetMessageA(
#endif
        lpMsg,
        hWnd,
        wMsgFilterMin,
        wMsgFilterMax
    );
}


WINUSERAPI
BOOL
WINAPI
PeekMessageA(
    _Out_ LPMSG lpMsg,
    _In_opt_ HWND hWnd,
    _In_ UINT wMsgFilterMin,
    _In_ UINT wMsgFilterMax,
    _In_ UINT wRemoveMsg);
WINUSERAPI
BOOL
WINAPI
PeekMessageW(
    _Out_ LPMSG lpMsg,
    _In_opt_ HWND hWnd,
    _In_ UINT wMsgFilterMin,
    _In_ UINT wMsgFilterMax,
    _In_ UINT wRemoveMsg);

WINUSERAPI
BOOL
WINAPI
RegisterHotKey(
    _In_opt_ HWND hWnd,
    _In_ int id,
    _In_ UINT fsModifiers,
    _In_ UINT vk);

WINUSERAPI
BOOL
WINAPI
UnregisterHotKey(
    _In_opt_ HWND hWnd,
    _In_ int id);

WINUSERAPI
LRESULT
WINAPI
SendMessageA(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _Pre_maybenull_ _Post_valid_ WPARAM wParam,
    _Pre_maybenull_ _Post_valid_ LPARAM lParam);
WINUSERAPI
LRESULT
WINAPI
SendMessageW(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _Pre_maybenull_ _Post_valid_ WPARAM wParam,
    _Pre_maybenull_ _Post_valid_ LPARAM lParam);


__inline
LRESULT
SendMessage(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
)
{
#ifdef UNICODE
    return SendMessageW(
#else
    return SendMessageA(
#endif
        hWnd,
        Msg,
        wParam,
        lParam
    );
}

WINUSERAPI
LRESULT
WINAPI
SendMessageTimeoutA(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam,
    _In_ UINT fuFlags,
    _In_ UINT uTimeout,
    _Out_opt_ PDWORD_PTR lpdwResult);
WINUSERAPI
LRESULT
WINAPI
SendMessageTimeoutW(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam,
    _In_ UINT fuFlags,
    _In_ UINT uTimeout,
    _Out_opt_ PDWORD_PTR lpdwResult);

WINUSERAPI
BOOL
WINAPI
SendNotifyMessageA(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
WINUSERAPI
BOOL
WINAPI
SendNotifyMessageW(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
SendMessageCallbackA(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam,
    _In_ SENDASYNCPROC lpResultCallBack,
    _In_ ULONG_PTR dwData);
WINUSERAPI
BOOL
WINAPI
SendMessageCallbackW(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam,
    _In_ SENDASYNCPROC lpResultCallBack,
    _In_ ULONG_PTR dwData);


WINUSERAPI
BOOL
WINAPI
PostMessageA(
    _In_opt_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
WINUSERAPI
BOOL
WINAPI
PostMessageW(
    _In_opt_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);

DefWindowProcA(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
WINUSERAPI
#ifndef _MAC
LRESULT
WINAPI
#else
LRESULT
CALLBACK
#endif
DefWindowProcW(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
#ifdef UNICODE
#define DefWindowProc  DefWindowProcW
#else
#define DefWindowProc  DefWindowProcA
#endif // !UNICODE

WINUSERAPI
VOID
WINAPI
PostQuitMessage(
    _In_ int nExitCode);

#ifdef STRICT

WINUSERAPI
LRESULT
WINAPI
CallWindowProcA(
    _In_ WNDPROC lpPrevWndFunc,
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
WINUSERAPI
LRESULT
WINAPI
CallWindowProcW(
    _In_ WNDPROC lpPrevWndFunc,
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
#ifdef UNICODE
#define CallWindowProc  CallWindowProcW
#else
#define CallWindowProc  CallWindowProcA
#endif // !UNICODE

#else /* !STRICT */

WINUSERAPI
LRESULT
WINAPI
CallWindowProcA(
    _In_ FARPROC lpPrevWndFunc,
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
WINUSERAPI
LRESULT
WINAPI
CallWindowProcW(
    _In_ FARPROC lpPrevWndFunc,
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);

WINUSERAPI
HWND
WINAPI
CreateWindowExA(
    _In_ DWORD dwExStyle,
    _In_opt_ LPCSTR lpClassName,
    _In_opt_ LPCSTR lpWindowName,
    _In_ DWORD dwStyle,
    _In_ int X,
    _In_ int Y,
    _In_ int nWidth,
    _In_ int nHeight,
    _In_opt_ HWND hWndParent,
    _In_opt_ HMENU hMenu,
    _In_opt_ HINSTANCE hInstance,
    _In_opt_ LPVOID lpParam);
WINUSERAPI
HWND
WINAPI
CreateWindowExW(
    _In_ DWORD dwExStyle,
    _In_opt_ LPCWSTR lpClassName,
    _In_opt_ LPCWSTR lpWindowName,
    _In_ DWORD dwStyle,
    _In_ int X,
    _In_ int Y,
    _In_ int nWidth,
    _In_ int nHeight,
    _In_opt_ HWND hWndParent,
    _In_opt_ HMENU hMenu,
    _In_opt_ HINSTANCE hInstance,
    _In_opt_ LPVOID lpParam);
#ifdef UNICODE
#define CreateWindowEx  CreateWindowExW
#else
#define CreateWindowEx  CreateWindowExA
#endif // !UNICODE

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_GAMES) */
#pragma endregion

#define CreateWindowA(lpClassName, lpWindowName, dwStyle, x, y,\
nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)\
CreateWindowExA(0L, lpClassName, lpWindowName, dwStyle, x, y,\
nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)
#define CreateWindowW(lpClassName, lpWindowName, dwStyle, x, y,\
nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)\
CreateWindowExW(0L, lpClassName, lpWindowName, dwStyle, x, y,\
nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)
#ifdef UNICODE
#define CreateWindow  CreateWindowW
#else
#define CreateWindow  CreateWindowA
#endif // !UNICODE

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


WINUSERAPI
BOOL
WINAPI
IsWindow(
    _In_opt_ HWND hWnd);


WINUSERAPI
BOOL
WINAPI
IsMenu(
    _In_ HMENU hMenu);

WINUSERAPI
BOOL
WINAPI
IsChild(
    _In_ HWND hWndParent,
    _In_ HWND hWnd);

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#pragma endregion

#pragma region Desktop or Games Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_GAMES)

WINUSERAPI
BOOL
WINAPI
DestroyWindow(
    _In_ HWND hWnd);

WINUSERAPI
BOOL
WINAPI
ShowWindow(
    _In_ HWND hWnd,
    _In_ int nCmdShow);

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_GAMES) */
#pragma endregion

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

#if(WINVER >= 0x0500)
WINUSERAPI
BOOL
WINAPI
AnimateWindow(
    _In_ HWND hWnd,
    _In_ DWORD dwTime,
    _In_ DWORD dwFlags);
#endif /* WINVER >= 0x0500 */

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#pragma endregion

#if(_WIN32_WINNT >= 0x0500)
#if defined(_WINGDI_) && !defined(NOGDI)

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

WINUSERAPI
BOOL
WINAPI
UpdateLayeredWindow(
    _In_ HWND hWnd,
    _In_opt_ HDC hdcDst,
    _In_opt_ POINT* pptDst,
    _In_opt_ SIZE* psize,
    _In_opt_ HDC hdcSrc,
    _In_opt_ POINT* pptSrc,
    _In_ COLORREF crKey,
    _In_opt_ BLENDFUNCTION* pblend,
    _In_ DWORD dwFlags);

/*
 * Layered Window Update information
 */
typedef struct tagUPDATELAYEREDWINDOWINFO
{
    DWORD cbSize;
    HDC hdcDst;
    const POINT* pptDst;
    const SIZE* psize;
    HDC hdcSrc;
    const POINT* pptSrc;
    COLORREF crKey;
    const BLENDFUNCTION* pblend;
    DWORD dwFlags;
    const RECT* prcDirty;
} UPDATELAYEREDWINDOWINFO, * PUPDATELAYEREDWINDOWINFO;


#if (_WIN32_WINNT < 0x0502)
typedef
#endif /* _WIN32_WINNT < 0x0502 */
WINUSERAPI
BOOL
WINAPI
UpdateLayeredWindowIndirect(
    _In_ HWND hWnd,
    _In_ const UPDATELAYEREDWINDOWINFO* pULWInfo);

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#pragma endregion

#endif

#if(_WIN32_WINNT >= 0x0501)

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

WINUSERAPI
BOOL
WINAPI
GetLayeredWindowAttributes(
    _In_ HWND hwnd,
    _Out_opt_ COLORREF* pcrKey,
    _Out_opt_ BYTE* pbAlpha,
    _Out_opt_ DWORD* pdwFlags);

#define PW_CLIENTONLY           0x00000001

#if(_WIN32_WINNT >= 0x0603)
#define PW_RENDERFULLCONTENT    0x00000002
#endif /* _WIN32_WINNT >= 0x0603 */


WINUSERAPI
BOOL
WINAPI
PrintWindow(
    _In_ HWND hwnd,
    _In_ HDC hdcBlt,
    _In_ UINT nFlags);

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#pragma endregion

#endif /* _WIN32_WINNT >= 0x0501 */

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

WINUSERAPI
BOOL
WINAPI
SetLayeredWindowAttributes(
    _In_ HWND hwnd,
    _In_ COLORREF crKey,
    _In_ BYTE bAlpha,
    _In_ DWORD dwFlags);

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


#if(WINVER >= 0x0400)
WINUSERAPI
BOOL
WINAPI
ShowWindowAsync(
    _In_  HWND hWnd,
    _In_  int nCmdShow);
#endif /* WINVER >= 0x0400 */

WINUSERAPI
BOOL
WINAPI
FlashWindow(
    _In_  HWND hWnd,
    _In_  BOOL bInvert);

#if(WINVER >= 0x0500)
typedef struct {
    UINT  cbSize;
    HWND  hwnd;
    DWORD dwFlags;
    UINT  uCount;
    DWORD dwTimeout;
} FLASHWINFO, * PFLASHWINFO;


WINUSERAPI
BOOL
WINAPI
ShowOwnedPopups(
    _In_  HWND hWnd,
    _In_  BOOL fShow);

WINUSERAPI
BOOL
WINAPI
OpenIcon(
    _In_  HWND hWnd);

WINUSERAPI
BOOL
WINAPI
CloseWindow(
    _In_  HWND hWnd);

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#pragma endregion

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_GAMES)

WINUSERAPI
BOOL
WINAPI
MoveWindow(
    _In_ HWND hWnd,
    _In_ int X,
    _In_ int Y,
    _In_ int nWidth,
    _In_ int nHeight,
    _In_ BOOL bRepaint);

WINUSERAPI
BOOL
WINAPI
SetWindowPos(
    _In_ HWND hWnd,
    _In_opt_ HWND hWndInsertAfter,
    _In_ int X,
    _In_ int Y,
    _In_ int cx,
    _In_ int cy,
    _In_ UINT uFlags);

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_GAMES) */
#pragma endregion

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

WINUSERAPI
BOOL
WINAPI
GetWindowPlacement(
    _In_ HWND hWnd,
    _Inout_ WINDOWPLACEMENT* lpwndpl);

WINUSERAPI
BOOL
WINAPI
SetWindowPlacement(
    _In_ HWND hWnd,
    _In_ CONST WINDOWPLACEMENT* lpwndpl);

#if(_WIN32_WINNT >= 0x0601)
#define WDA_NONE        0x00000000
#define WDA_MONITOR     0x00000001
#define WDA_EXCLUDEFROMCAPTURE 0x00000011


WINUSERAPI
BOOL
WINAPI
GetWindowDisplayAffinity(
    _In_ HWND hWnd,
    _Out_ DWORD* pdwAffinity);

WINUSERAPI
BOOL
WINAPI
SetWindowDisplayAffinity(
    _In_ HWND hWnd,
    _In_ DWORD dwAffinity);

#endif /* _WIN32_WINNT >= 0x0601 */

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#pragma endregion

#ifndef NODEFERWINDOWPOS

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

WINUSERAPI
HDWP
WINAPI
BeginDeferWindowPos(
    _In_ int nNumWindows);

WINUSERAPI
HDWP
WINAPI
DeferWindowPos(
    _In_ HDWP hWinPosInfo,
    _In_ HWND hWnd,
    _In_opt_ HWND hWndInsertAfter,
    _In_ int x,
    _In_ int y,
    _In_ int cx,
    _In_ int cy,
    _In_ UINT uFlags);


#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#pragma endregion

#endif /* !NODEFERWINDOWPOS */

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_GAMES)

WINUSERAPI
BOOL
WINAPI
IsWindowVisible(
    _In_ HWND hWnd);

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_GAMES) */
#pragma endregion

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

WINUSERAPI
BOOL
WINAPI
IsIconic(
    _In_ HWND hWnd);

WINUSERAPI
BOOL
WINAPI
BringWindowToTop(
    _In_ HWND hWnd);

WINUSERAPI
BOOL
WINAPI
IsZoomed(
    _In_ HWND hWnd);
WINUSERAPI
HWND
WINAPI
CreateDialogParamA(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCSTR lpTemplateName,
    _In_opt_ HWND hWndParent,
    _In_opt_ DLGPROC lpDialogFunc,
    _In_ LPARAM dwInitParam);
WINUSERAPI
HWND
WINAPI
CreateDialogParamW(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCWSTR lpTemplateName,
    _In_opt_ HWND hWndParent,
    _In_opt_ DLGPROC lpDialogFunc,
    _In_ LPARAM dwInitParam);
#ifdef UNICODE
#define CreateDialogParam  CreateDialogParamW
#else
#define CreateDialogParam  CreateDialogParamA
#endif // !UNICODE

WINUSERAPI
HWND
WINAPI
CreateDialogIndirectParamA(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCDLGTEMPLATEA lpTemplate,
    _In_opt_ HWND hWndParent,
    _In_opt_ DLGPROC lpDialogFunc,
    _In_ LPARAM dwInitParam);
WINUSERAPI
HWND
WINAPI
CreateDialogIndirectParamW(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCDLGTEMPLATEW lpTemplate,
    _In_opt_ HWND hWndParent,
    _In_opt_ DLGPROC lpDialogFunc,
    _In_ LPARAM dwInitParam);
#ifdef UNICODE
#define CreateDialogIndirectParam  CreateDialogIndirectParamW
#else
#define CreateDialogIndirectParam  CreateDialogIndirectParamA
#endif // !UNICODE

#define CreateDialogA(hInstance, lpName, hWndParent, lpDialogFunc) \
CreateDialogParamA(hInstance, lpName, hWndParent, lpDialogFunc, 0L)
#define CreateDialogW(hInstance, lpName, hWndParent, lpDialogFunc) \
CreateDialogParamW(hInstance, lpName, hWndParent, lpDialogFunc, 0L)
#ifdef UNICODE
#define CreateDialog  CreateDialogW
#else
#define CreateDialog  CreateDialogA
#endif // !UNICODE

#define CreateDialogIndirectA(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
CreateDialogIndirectParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
#define CreateDialogIndirectW(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
CreateDialogIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
#ifdef UNICODE
#define CreateDialogIndirect  CreateDialogIndirectW
#else
#define CreateDialogIndirect  CreateDialogIndirectA
#endif // !UNICODE

WINUSERAPI
INT_PTR
WINAPI
DialogBoxParamA(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCSTR lpTemplateName,
    _In_opt_ HWND hWndParent,
    _In_opt_ DLGPROC lpDialogFunc,
    _In_ LPARAM dwInitParam);
WINUSERAPI
INT_PTR
WINAPI
DialogBoxParamW(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCWSTR lpTemplateName,
    _In_opt_ HWND hWndParent,
    _In_opt_ DLGPROC lpDialogFunc,
    _In_ LPARAM dwInitParam);
#ifdef UNICODE
#define DialogBoxParam  DialogBoxParamW
#else
#define DialogBoxParam  DialogBoxParamA
#endif // !UNICODE

WINUSERAPI
INT_PTR
WINAPI
DialogBoxIndirectParamA(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCDLGTEMPLATEA hDialogTemplate,
    _In_opt_ HWND hWndParent,
    _In_opt_ DLGPROC lpDialogFunc,
    _In_ LPARAM dwInitParam);
WINUSERAPI
INT_PTR
WINAPI
DialogBoxIndirectParamW(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCDLGTEMPLATEW hDialogTemplate,
    _In_opt_ HWND hWndParent,
    _In_opt_ DLGPROC lpDialogFunc,
    _In_ LPARAM dwInitParam);
#ifdef UNICODE
#define DialogBoxIndirectParam  DialogBoxIndirectParamW
#else
#define DialogBoxIndirectParam  DialogBoxIndirectParamA
#endif // !UNICODE

#define DialogBoxA(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
DialogBoxParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
#define DialogBoxW(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
DialogBoxParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
#ifdef UNICODE
#define DialogBox  DialogBoxW
#else
#define DialogBox  DialogBoxA
#endif // !UNICODE

#define DialogBoxIndirectA(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
DialogBoxIndirectParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
#define DialogBoxIndirectW(hInstance, lpTemplate, hWndParent, lpDialogFunc) \
DialogBoxIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
#ifdef UNICODE
#define DialogBoxIndirect  DialogBoxIndirectW
#else
#define DialogBoxIndirect  DialogBoxIndirectA
#endif // !UNICODE

WINUSERAPI
BOOL
WINAPI
EndDialog(
    _In_ HWND hDlg,
    _In_ INT_PTR nResult);

WINUSERAPI
HWND
WINAPI
GetDlgItem(
    _In_opt_ HWND hDlg,
    _In_ int nIDDlgItem);

WINUSERAPI
BOOL
WINAPI
SetDlgItemInt(
    _In_ HWND hDlg,
    _In_ int nIDDlgItem,
    _In_ UINT uValue,
    _In_ BOOL bSigned);

WINUSERAPI
UINT
WINAPI
GetDlgItemInt(
    _In_ HWND hDlg,
    _In_ int nIDDlgItem,
    _Out_opt_ BOOL* lpTranslated,
    _In_ BOOL bSigned);

WINUSERAPI
BOOL
WINAPI
SetDlgItemTextA(
    _In_ HWND hDlg,
    _In_ int nIDDlgItem,
    _In_ LPCSTR lpString);
WINUSERAPI
BOOL
WINAPI
SetDlgItemTextW(
    _In_ HWND hDlg,
    _In_ int nIDDlgItem,
    _In_ LPCWSTR lpString);
#ifdef UNICODE
#define SetDlgItemText  SetDlgItemTextW
#else
#define SetDlgItemText  SetDlgItemTextA
#endif // !UNICODE

_Ret_range_(0, cchMax)
WINUSERAPI
UINT
WINAPI
GetDlgItemTextA(
    _In_ HWND hDlg,
    _In_ int nIDDlgItem,
    _Out_writes_(cchMax) LPSTR lpString,
    _In_ int cchMax);
_Ret_range_(0, cchMax)
WINUSERAPI
UINT
WINAPI
GetDlgItemTextW(
    _In_ HWND hDlg,
    _In_ int nIDDlgItem,
    _Out_writes_(cchMax) LPWSTR lpString,
    _In_ int cchMax);
#ifdef UNICODE
#define GetDlgItemText  GetDlgItemTextW
#else
#define GetDlgItemText  GetDlgItemTextA
#endif // !UNICODE

WINUSERAPI
BOOL
WINAPI
CheckDlgButton(
    _In_ HWND hDlg,
    _In_ int nIDButton,
    _In_ UINT uCheck);

WINUSERAPI
BOOL
WINAPI
CheckRadioButton(
    _In_ HWND hDlg,
    _In_ int nIDFirstButton,
    _In_ int nIDLastButton,
    _In_ int nIDCheckButton);

WINUSERAPI
UINT
WINAPI
IsDlgButtonChecked(
    _In_ HWND hDlg,
    _In_ int nIDButton);

WINUSERAPI
LRESULT
WINAPI
SendDlgItemMessageA(
    _In_ HWND hDlg,
    _In_ int nIDDlgItem,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
WINUSERAPI
LRESULT
WINAPI
SendDlgItemMessageW(
    _In_ HWND hDlg,
    _In_ int nIDDlgItem,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
#ifdef UNICODE
#define SendDlgItemMessage  SendDlgItemMessageW
#else
#define SendDlgItemMessage  SendDlgItemMessageA
#endif // !UNICODE

WINUSERAPI
HWND
WINAPI
GetNextDlgGroupItem(
    _In_ HWND hDlg,
    _In_opt_ HWND hCtl,
    _In_ BOOL bPrevious);

WINUSERAPI
HWND
WINAPI
GetNextDlgTabItem(
    _In_ HWND hDlg,
    _In_opt_ HWND hCtl,
    _In_ BOOL bPrevious);

WINUSERAPI
int
WINAPI
GetDlgCtrlID(
    _In_ HWND hWnd);

WINUSERAPI
long
WINAPI
GetDialogBaseUnits(VOID);


WINUSERAPI
#ifndef _MAC
LRESULT
WINAPI
#else
LRESULT
CALLBACK
#endif
DefDlgProcA(
    _In_ HWND hDlg,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
WINUSERAPI
#ifndef _MAC
LRESULT
WINAPI
#else
LRESULT
CALLBACK
#endif
DefDlgProcW(
    _In_ HWND hDlg,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);

BOOL
WINAPI
SetDialogControlDpiChangeBehavior(
    _In_ HWND hWnd,
    _In_ DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS mask,
    _In_ DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS values);

DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS
WINAPI
GetDialogControlDpiChangeBehavior(
    _In_ HWND hWnd);

BOOL
WINAPI
SetDialogDpiChangeBehavior(
    _In_ HWND hDlg,
    _In_ DIALOG_DPI_CHANGE_BEHAVIORS mask,
    _In_ DIALOG_DPI_CHANGE_BEHAVIORS values);

DIALOG_DPI_CHANGE_BEHAVIORS
WINAPI
GetDialogDpiChangeBehavior(
    _In_ HWND hDlg);

WINUSERAPI
BOOL
WINAPI
OpenClipboard(
    _In_opt_ HWND hWndNewOwner);
#endif /* WINVER >= 0x0500 */

WINUSERAPI
HWND
WINAPI
GetClipboardOwner(
    VOID);

WINUSERAPI
HWND
WINAPI
SetClipboardViewer(
    _In_ HWND hWndNewViewer);

WINUSERAPI
HWND
WINAPI
GetClipboardViewer(
    VOID);

WINUSERAPI
BOOL
WINAPI
ChangeClipboardChain(
    _In_ HWND hWndRemove,
    _In_ HWND hWndNewNext);

WINUSERAPI
HWND
WINAPI
GetOpenClipboardWindow(
    VOID);

#if(WINVER >= 0x0600)
WINUSERAPI
BOOL
WINAPI
AddClipboardFormatListener(
    _In_ HWND hwnd);

WINUSERAPI
BOOL
WINAPI
RemoveClipboardFormatListener(
    _In_ HWND hwnd);

WINUSERAPI
HWND
WINAPI
SetFocus(
    _In_opt_ HWND hWnd);

WINUSERAPI
HWND
WINAPI
GetActiveWindow(
    VOID);

WINUSERAPI
HWND
WINAPI
GetFocus(
    VOID);

WINUSERAPI
BOOL
WINAPI
RegisterTouchWindow(
    _In_ HWND hwnd,
    _In_ ULONG ulFlags);

WINUSERAPI
BOOL
WINAPI
UnregisterTouchWindow(
    _In_ HWND hwnd);

WINUSERAPI
BOOL
WINAPI
IsTouchWindow(
    _In_ HWND hwnd,
    _Out_opt_ PULONG pulFlags);

WINUSERAPI
BOOL
WINAPI
RegisterPointerInputTarget(
    _In_ HWND hwnd,
    _In_ POINTER_INPUT_TYPE pointerType);

WINUSERAPI
BOOL
WINAPI
UnregisterPointerInputTarget(
    _In_ HWND hwnd,
    _In_ POINTER_INPUT_TYPE pointerType);

WINUSERAPI
BOOL
WINAPI
RegisterPointerInputTargetEx(
    _In_ HWND hwnd,
    _In_ POINTER_INPUT_TYPE pointerType,
    _In_ BOOL fObserve);

WINUSERAPI
BOOL
WINAPI
UnregisterPointerInputTargetEx(
    _In_ HWND hwnd,
    _In_ POINTER_INPUT_TYPE pointerType);

WINUSERAPI
BOOL
WINAPI
RegisterTouchHitTestingWindow(
    _In_ HWND hwnd,
    _In_ ULONG value);

WINUSERAPI
BOOL
WINAPI
GetWindowFeedbackSetting(
    _In_ HWND hwnd,
    _In_ FEEDBACK_TYPE feedback,
    _In_ DWORD dwFlags,
    _Inout_ UINT32* pSize,
    _Out_writes_bytes_opt_(*pSize) VOID* config);

WINUSERAPI
BOOL
WINAPI
SetWindowFeedbackSetting(
    _In_ HWND hwnd,
    _In_ FEEDBACK_TYPE feedback,
    _In_ DWORD dwFlags,
    _In_ UINT32 size,
    _In_reads_bytes_opt_(size) CONST VOID* configuration);


WINUSERAPI
HWND
WINAPI
GetCapture(
    VOID);

WINUSERAPI
HWND
WINAPI
SetCapture(
    _In_ HWND hWnd);

WINUSERAPI
UINT_PTR
WINAPI
SetTimer(
    _In_opt_ HWND hWnd,
    _In_ UINT_PTR nIDEvent,
    _In_ UINT uElapse,
    _In_opt_ TIMERPROC lpTimerFunc);

WINUSERAPI
UINT_PTR
WINAPI
SetCoalescableTimer(
    _In_opt_ HWND hWnd,
    _In_ UINT_PTR nIDEvent,
    _In_ UINT uElapse,
    _In_opt_ TIMERPROC lpTimerFunc,
    _In_ ULONG uToleranceDelay);

WINUSERAPI
BOOL
WINAPI
KillTimer(
    _In_opt_ HWND hWnd,
    _In_ UINT_PTR uIDEvent);

WINUSERAPI
BOOL
WINAPI
IsWindowUnicode(
    _In_ HWND hWnd);

WINUSERAPI
BOOL
WINAPI
EnableWindow(
    _In_ HWND hWnd,
    _In_ BOOL bEnable);

WINUSERAPI
BOOL
WINAPI
IsWindowEnabled(
    _In_ HWND hWnd);

WINUSERAPI
int
WINAPI
TranslateAcceleratorA(
    _In_ HWND hWnd,
    _In_ HACCEL hAccTable,
    _In_ LPMSG lpMsg);
WINUSERAPI
int
WINAPI
TranslateAcceleratorW(
    _In_ HWND hWnd,
    _In_ HACCEL hAccTable,
    _In_ LPMSG lpMsg);

WINUSERAPI
HMENU
WINAPI
GetMenu(
    _In_ HWND hWnd);

WINUSERAPI
BOOL
WINAPI
SetMenu(
    _In_ HWND hWnd,
    _In_opt_ HMENU hMenu);

WINUSERAPI
BOOL
WINAPI
HiliteMenuItem(
    _In_ HWND hWnd,
    _In_ HMENU hMenu,
    _In_ UINT uIDHiliteItem,
    _In_ UINT uHilite);


WINUSERAPI
BOOL
WINAPI
DrawMenuBar(
    _In_ HWND hWnd);


WINUSERAPI
HMENU
WINAPI
GetSystemMenu(
    _In_ HWND hWnd,
    _In_ BOOL bRevert);


WINUSERAPI
BOOL
WINAPI
TrackPopupMenu(
    _In_ HMENU hMenu,
    _In_ UINT uFlags,
    _In_ int x,
    _In_ int y,
    _Reserved_ int nReserved,
    _In_ HWND hWnd,
    _Reserved_ CONST RECT* prcRect);

WINUSERAPI
BOOL
WINAPI
TrackPopupMenuEx(
    _In_ HMENU hMenu,
    _In_ UINT uFlags,
    _In_ int x,
    _In_ int y,
    _In_ HWND hwnd,
    _In_opt_ LPTPMPARAMS lptpm);

WINUSERAPI
BOOL
WINAPI
GetMenuItemRect(
    _In_opt_ HWND hWnd,
    _In_ HMENU hMenu,
    _In_ UINT uItem,
    _Out_ LPRECT lprcItem);

WINUSERAPI
int
WINAPI
MenuItemFromPoint(
    _In_opt_ HWND hWnd,
    _In_ HMENU hMenu,
    _In_ POINT ptScreen);

WINUSERAPI
DWORD
WINAPI
DragObject(
    _In_ HWND hwndParent,
    _In_ HWND hwndFrom,
    _In_ UINT fmt,
    _In_ ULONG_PTR data,
    _In_opt_ HCURSOR hcur);

WINUSERAPI
BOOL
WINAPI
DragDetect(
    _In_ HWND hwnd,
    _In_ POINT pt);

WINUSERAPI
BOOL
WINAPI
UpdateWindow(
    _In_ HWND hWnd);

WINUSERAPI
HWND
WINAPI
SetActiveWindow(
    _In_ HWND hWnd);

WINUSERAPI
HWND
WINAPI
GetForegroundWindow(
    VOID);

WINUSERAPI
VOID
WINAPI
SwitchToThisWindow(
    _In_ HWND hwnd,
    _In_ BOOL fUnknown);
#endif /* WINVER >= 0x0400 */


WINUSERAPI
BOOL
WINAPI
SetForegroundWindow(
    _In_ HWND hWnd);

WINUSERAPI
HWND
WINAPI
WindowFromDC(
    _In_ HDC hDC);

WINUSERAPI
HDC
WINAPI
GetDC(
    _In_opt_ HWND hWnd);

WINUSERAPI
HDC
WINAPI
GetDCEx(
    _In_opt_ HWND hWnd,
    _In_opt_ HRGN hrgnClip,
    _In_ DWORD flags);

WINUSERAPI
HDC
WINAPI
GetWindowDC(
    _In_opt_ HWND hWnd);

WINUSERAPI
int
WINAPI
ReleaseDC(
    _In_opt_ HWND hWnd,
    _In_ HDC hDC);

WINUSERAPI
HDC
WINAPI
BeginPaint(
    _In_ HWND hWnd,
    _Out_ LPPAINTSTRUCT lpPaint);

WINUSERAPI
BOOL
WINAPI
EndPaint(
    _In_ HWND hWnd,
    _In_ CONST PAINTSTRUCT* lpPaint);

WINUSERAPI
BOOL
WINAPI
GetUpdateRect(
    _In_ HWND hWnd,
    _Out_opt_ LPRECT lpRect,
    _In_ BOOL bErase);

WINUSERAPI
int
WINAPI
GetUpdateRgn(
    _In_ HWND hWnd,
    _In_ HRGN hRgn,
    _In_ BOOL bErase);

WINUSERAPI
int
WINAPI
SetWindowRgn(
    _In_ HWND hWnd,
    _In_opt_ HRGN hRgn,
    _In_ BOOL bRedraw);

WINUSERAPI
int
WINAPI
GetWindowRgn(
    _In_ HWND hWnd,
    _In_ HRGN hRgn);


WINUSERAPI
int
WINAPI
GetWindowRgnBox(
    _In_ HWND hWnd,
    _Out_ LPRECT lprc);

WINUSERAPI
int
WINAPI
ExcludeUpdateRgn(
    _In_ HDC hDC,
    _In_ HWND hWnd);

WINUSERAPI
BOOL
WINAPI
InvalidateRect(
    _In_opt_ HWND hWnd,
    _In_opt_ CONST RECT* lpRect,
    _In_ BOOL bErase);

WINUSERAPI
BOOL
WINAPI
ValidateRect(
    _In_opt_ HWND hWnd,
    _In_opt_ CONST RECT* lpRect);

WINUSERAPI
BOOL
WINAPI
InvalidateRgn(
    _In_ HWND hWnd,
    _In_opt_ HRGN hRgn,
    _In_ BOOL bErase);

WINUSERAPI
BOOL
WINAPI
ValidateRgn(
    _In_ HWND hWnd,
    _In_opt_ HRGN hRgn);


WINUSERAPI
BOOL
WINAPI
RedrawWindow(
    _In_opt_ HWND hWnd,
    _In_opt_ CONST RECT* lprcUpdate,
    _In_opt_ HRGN hrgnUpdate,
    _In_ UINT flags);

WINUSERAPI
BOOL
WINAPI
LockWindowUpdate(
    _In_opt_ HWND hWndLock);

WINUSERAPI
BOOL
WINAPI
ScrollWindow(
    _In_ HWND hWnd,
    _In_ int XAmount,
    _In_ int YAmount,
    _In_opt_ CONST RECT* lpRect,
    _In_opt_ CONST RECT* lpClipRect);

WINUSERAPI
BOOL
WINAPI
ScrollDC(
    _In_ HDC hDC,
    _In_ int dx,
    _In_ int dy,
    _In_opt_ CONST RECT* lprcScroll,
    _In_opt_ CONST RECT* lprcClip,
    _In_opt_ HRGN hrgnUpdate,
    _Out_opt_ LPRECT lprcUpdate);

WINUSERAPI
int
WINAPI
ScrollWindowEx(
    _In_ HWND hWnd,
    _In_ int dx,
    _In_ int dy,
    _In_opt_ CONST RECT* prcScroll,
    _In_opt_ CONST RECT* prcClip,
    _In_opt_ HRGN hrgnUpdate,
    _Out_opt_ LPRECT prcUpdate,
    _In_ UINT flags);

WINUSERAPI
int
WINAPI
SetScrollPos(
    _In_ HWND hWnd,
    _In_ int nBar,
    _In_ int nPos,
    _In_ BOOL bRedraw);

WINUSERAPI
int
WINAPI
GetScrollPos(
    _In_ HWND hWnd,
    _In_ int nBar);

WINUSERAPI
BOOL
WINAPI
SetScrollRange(
    _In_ HWND hWnd,
    _In_ int nBar,
    _In_ int nMinPos,
    _In_ int nMaxPos,
    _In_ BOOL bRedraw);

WINUSERAPI
BOOL
WINAPI
GetScrollRange(
    _In_ HWND hWnd,
    _In_ int nBar,
    _Out_ LPINT lpMinPos,
    _Out_ LPINT lpMaxPos);

WINUSERAPI
BOOL
WINAPI
ShowScrollBar(
    _In_ HWND hWnd,
    _In_ int wBar,
    _In_ BOOL bShow);

WINUSERAPI
BOOL
WINAPI
EnableScrollBar(
    _In_ HWND hWnd,
    _In_ UINT wSBflags,
    _In_ UINT wArrows);

WINUSERAPI
BOOL
WINAPI
SetPropA(
    _In_ HWND hWnd,
    _In_ LPCSTR lpString,
    _In_opt_ HANDLE hData);
WINUSERAPI
BOOL
WINAPI
SetPropW(
    _In_ HWND hWnd,
    _In_ LPCWSTR lpString,
    _In_opt_ HANDLE hData);

WINUSERAPI
HANDLE
WINAPI
GetPropA(
    _In_ HWND hWnd,
    _In_ LPCSTR lpString);
WINUSERAPI
HANDLE
WINAPI
GetPropW(
    _In_ HWND hWnd,
    _In_ LPCWSTR lpString);

WINUSERAPI
HANDLE
WINAPI
RemovePropA(
    _In_ HWND hWnd,
    _In_ LPCSTR lpString);
WINUSERAPI
HANDLE
WINAPI
RemovePropW(
    _In_ HWND hWnd,
    _In_ LPCWSTR lpString);

WINUSERAPI
int
WINAPI
EnumPropsExA(
    _In_ HWND hWnd,
    _In_ PROPENUMPROCEXA lpEnumFunc,
    _In_ LPARAM lParam);
WINUSERAPI
int
WINAPI
EnumPropsExW(
    _In_ HWND hWnd,
    _In_ PROPENUMPROCEXW lpEnumFunc,
    _In_ LPARAM lParam);

WINUSERAPI
int
WINAPI
EnumPropsA(
    _In_ HWND hWnd,
    _In_ PROPENUMPROCA lpEnumFunc);
WINUSERAPI
int
WINAPI
EnumPropsW(
    _In_ HWND hWnd,
    _In_ PROPENUMPROCW lpEnumFunc);

WINUSERAPI
BOOL
WINAPI
SetWindowTextA(
    _In_ HWND hWnd,
    _In_opt_ LPCSTR lpString);
WINUSERAPI
BOOL
WINAPI
SetWindowTextW(
    _In_ HWND hWnd,
    _In_opt_ LPCWSTR lpString);

_Ret_range_(0, nMaxCount)
WINUSERAPI
int
WINAPI
GetWindowTextA(
    _In_ HWND hWnd,
    _Out_writes_(nMaxCount) LPSTR lpString,
    _In_ int nMaxCount);

_Ret_range_(0, nMaxCount)
WINUSERAPI
int
WINAPI
GetWindowTextW(
    _In_ HWND hWnd,
    _Out_writes_(nMaxCount) LPWSTR lpString,
    _In_ int nMaxCount);

WINUSERAPI
int
WINAPI
GetWindowTextLengthA(
    _In_ HWND hWnd);
WINUSERAPI
int
WINAPI
GetWindowTextLengthW(
    _In_ HWND hWnd);

WINUSERAPI
BOOL
WINAPI
GetClientRect(
    _In_ HWND hWnd,
    _Out_ LPRECT lpRect);

WINUSERAPI
BOOL
WINAPI
GetWindowRect(
    _In_ HWND hWnd,
    _Out_ LPRECT lpRect);

WINUSERAPI
BOOL
WINAPI
SetWindowContextHelpId(
    _In_ HWND,
    _In_ DWORD);

WINUSERAPI
DWORD
WINAPI
GetWindowContextHelpId(
    _In_ HWND);

WINUSERAPI
int
WINAPI
MessageBoxA(
    _In_opt_ HWND hWnd,
    _In_opt_ LPCSTR lpText,
    _In_opt_ LPCSTR lpCaption,
    _In_ UINT uType);
WINUSERAPI
int
WINAPI
MessageBoxW(
    _In_opt_ HWND hWnd,
    _In_opt_ LPCWSTR lpText,
    _In_opt_ LPCWSTR lpCaption,
    _In_ UINT uType);

__inline
int
MessageBox(
    HWND hWnd,
    LPCTSTR lpText,
    LPCTSTR lpCaption,
    UINT uType
)
{
#ifdef UNICODE
    return MessageBoxW(
#else
    return MessageBoxA(
#endif
        hWnd,
    lpText,
    lpCaption,
    uType
    );
}

WINUSERAPI
int
WINAPI
MessageBoxExA(
    _In_opt_ HWND hWnd,
    _In_opt_ LPCSTR lpText,
    _In_opt_ LPCSTR lpCaption,
    _In_ UINT uType,
    _In_ WORD wLanguageId);
WINUSERAPI
int
WINAPI
MessageBoxExW(
    _In_opt_ HWND hWnd,
    _In_opt_ LPCWSTR lpText,
    _In_opt_ LPCWSTR lpCaption,
    _In_ UINT uType,
    _In_ WORD wLanguageId);

WINUSERAPI
BOOL
WINAPI
CreateCaret(
    _In_ HWND hWnd,
    _In_opt_ HBITMAP hBitmap,
    _In_ int nWidth,
    _In_ int nHeight);

WINUSERAPI
BOOL
WINAPI
HideCaret(
    _In_opt_ HWND hWnd);

WINUSERAPI
BOOL
WINAPI
ShowCaret(
    _In_opt_ HWND hWnd);

WINUSERAPI
BOOL
WINAPI
ClientToScreen(
    _In_ HWND hWnd,
    _Inout_ LPPOINT lpPoint);

WINUSERAPI
BOOL
WINAPI
ScreenToClient(
    _In_ HWND hWnd,
    _Inout_ LPPOINT lpPoint);

#if(WINVER >= 0x0600)
WINUSERAPI
BOOL
WINAPI
LogicalToPhysicalPoint(
    _In_ HWND hWnd,
    _Inout_ LPPOINT lpPoint);

WINUSERAPI
BOOL
WINAPI
PhysicalToLogicalPoint(
    _In_ HWND hWnd,
    _Inout_ LPPOINT lpPoint);

#endif /* WINVER >= 0x0600 */

#if(WINVER >= 0x0603)
WINUSERAPI
BOOL
WINAPI
LogicalToPhysicalPointForPerMonitorDPI(
    _In_opt_ HWND hWnd,
    _Inout_ LPPOINT lpPoint);

WINUSERAPI
BOOL
WINAPI
PhysicalToLogicalPointForPerMonitorDPI(
    _In_opt_ HWND hWnd,
    _Inout_ LPPOINT lpPoint);

#endif /* WINVER >= 0x0603 */

WINUSERAPI
int
WINAPI
MapWindowPoints(
    _In_opt_ HWND hWndFrom,
    _In_opt_ HWND hWndTo,
    _Inout_updates_(cPoints) LPPOINT lpPoints,
    _In_ UINT cPoints);

WINUSERAPI
HWND
WINAPI
WindowFromPoint(
    _In_ POINT Point);

#if(WINVER >= 0x0600)
WINUSERAPI
HWND
WINAPI
WindowFromPhysicalPoint(
    _In_ POINT Point);
#endif /* WINVER >= 0x0600 */

WINUSERAPI
HWND
WINAPI
ChildWindowFromPoint(
    _In_ HWND hWndParent,
    _In_ POINT Point);

WINUSERAPI
HWND
WINAPI
ChildWindowFromPointEx(
    _In_ HWND hwnd,
    _In_ POINT pt,
    _In_ UINT flags);

WINUSERAPI
WORD
WINAPI
GetWindowWord(
    _In_ HWND hWnd,
    _In_ int nIndex);

WINUSERAPI
WORD
WINAPI
SetWindowWord(
    _In_ HWND hWnd,
    _In_ int nIndex,
    _In_ WORD wNewWord);

WINUSERAPI
LONG
WINAPI
GetWindowLongA(
    _In_ HWND hWnd,
    _In_ int nIndex);
WINUSERAPI
LONG
WINAPI
GetWindowLongW(
    _In_ HWND hWnd,
    _In_ int nIndex);

WINUSERAPI
LONG
WINAPI
SetWindowLongA(
    _In_ HWND hWnd,
    _In_ int nIndex,
    _In_ LONG dwNewLong);

WINUSERAPI
LONG
WINAPI
SetWindowLongW(
    _In_ HWND hWnd,
    _In_ int nIndex,
    _In_ LONG dwNewLong);

WINUSERAPI
LONG_PTR
WINAPI
GetWindowLongPtrA(
    _In_ HWND hWnd,
    _In_ int nIndex);

WINUSERAPI
LONG_PTR
WINAPI
GetWindowLongPtrW(
    _In_ HWND hWnd,
    _In_ int nIndex);

WINUSERAPI
LONG_PTR
WINAPI
SetWindowLongPtrA(
    _In_ HWND hWnd,
    _In_ int nIndex,
    _In_ LONG_PTR dwNewLong);

WINUSERAPI
LONG_PTR
WINAPI
SetWindowLongPtrW(
    _In_ HWND hWnd,
    _In_ int nIndex,
    _In_ LONG_PTR dwNewLong);

WINUSERAPI
WORD
WINAPI
GetClassWord(
    _In_ HWND hWnd,
    _In_ int nIndex);

WINUSERAPI
WORD
WINAPI
SetClassWord(
    _In_ HWND hWnd,
    _In_ int nIndex,
    _In_ WORD wNewWord);

WINUSERAPI
DWORD
WINAPI
GetClassLongA(
    _In_ HWND hWnd,
    _In_ int nIndex);

WINUSERAPI
DWORD
WINAPI
GetClassLongW(
    _In_ HWND hWnd,
    _In_ int nIndex);

WINUSERAPI
DWORD
WINAPI
SetClassLongA(
    _In_ HWND hWnd,
    _In_ int nIndex,
    _In_ LONG dwNewLong);

WINUSERAPI
DWORD
WINAPI
SetClassLongW(
    _In_ HWND hWnd,
    _In_ int nIndex,
    _In_ LONG dwNewLong);

WINUSERAPI
ULONG_PTR
WINAPI
GetClassLongPtrA(
    _In_ HWND hWnd,
    _In_ int nIndex);
WINUSERAPI
ULONG_PTR
WINAPI
GetClassLongPtrW(
    _In_ HWND hWnd,
    _In_ int nIndex);

WINUSERAPI
ULONG_PTR
WINAPI
SetClassLongPtrA(
    _In_ HWND hWnd,
    _In_ int nIndex,
    _In_ LONG_PTR dwNewLong);

WINUSERAPI
ULONG_PTR
WINAPI
SetClassLongPtrW(
    _In_ HWND hWnd,
    _In_ int nIndex,
    _In_ LONG_PTR dwNewLong);

WINUSERAPI
HWND
WINAPI
GetDesktopWindow(
    VOID);

WINUSERAPI
HWND
WINAPI
GetParent(
    _In_ HWND hWnd);

WINUSERAPI
HWND
WINAPI
SetParent(
    _In_ HWND hWndChild,
    _In_opt_ HWND hWndNewParent);

WINUSERAPI
BOOL
WINAPI
EnumChildWindows(
    _In_opt_ HWND hWndParent,
    _In_ WNDENUMPROC lpEnumFunc,
    _In_ LPARAM lParam);


WINUSERAPI
HWND
WINAPI
FindWindowA(
    _In_opt_ LPCSTR lpClassName,
    _In_opt_ LPCSTR lpWindowName);

WINUSERAPI
HWND
WINAPI
FindWindowW(
    _In_opt_ LPCWSTR lpClassName,
    _In_opt_ LPCWSTR lpWindowName);

#if(WINVER >= 0x0400)
WINUSERAPI
HWND
WINAPI
FindWindowExA(
    _In_opt_ HWND hWndParent,
    _In_opt_ HWND hWndChildAfter,
    _In_opt_ LPCSTR lpszClass,
    _In_opt_ LPCSTR lpszWindow);

WINUSERAPI
HWND
WINAPI
FindWindowExW(
    _In_opt_ HWND hWndParent,
    _In_opt_ HWND hWndChildAfter,
    _In_opt_ LPCWSTR lpszClass,
    _In_opt_ LPCWSTR lpszWindow);

WINUSERAPI
HWND
WINAPI
GetShellWindow(
    VOID);

WINUSERAPI
BOOL
WINAPI
RegisterShellHookWindow(
    _In_ HWND hwnd);

WINUSERAPI
BOOL
WINAPI
DeregisterShellHookWindow(
    _In_ HWND hwnd);

WINUSERAPI
int
WINAPI
GetClassNameA(
    _In_ HWND hWnd,
    _Out_writes_to_(nMaxCount, return) LPSTR lpClassName,
    _In_ int nMaxCount
);

WINUSERAPI
int
WINAPI
GetClassNameW(
    _In_ HWND hWnd,
    _Out_writes_to_(nMaxCount, return) LPWSTR lpClassName,
    _In_ int nMaxCount
);

#if defined(_M_CEE)
#undef GetClassName
__inline
int
GetClassName(
    HWND hWnd,
    LPTSTR lpClassName,
    int nMaxCount
)
{
#ifdef UNICODE
    return GetClassNameW(
#else
    return GetClassNameA(
#endif
        hWnd,
    lpClassName,
    nMaxCount
    );
}
#endif  /* _M_CEE */

WINUSERAPI
HWND
WINAPI
GetTopWindow(
    _In_opt_ HWND hWnd);

WINUSERAPI
DWORD
WINAPI
GetWindowThreadProcessId(
    _In_ HWND hWnd,
    _Out_opt_ LPDWORD lpdwProcessId);


WINUSERAPI
HWND
WINAPI
GetLastActivePopup(
    _In_ HWND hWnd);

WINUSERAPI
HWND
WINAPI
GetWindow(
    _In_ HWND hWnd,
    _In_ UINT uCmd);

WINUSERAPI
BOOL
WINAPI
IsDialogMessageA(
    _In_ HWND hDlg,
    _In_ LPMSG lpMsg);

WINUSERAPI
BOOL
WINAPI
IsDialogMessageW(
    _In_ HWND hDlg,
    _In_ LPMSG lpMsg);

WINUSERAPI
BOOL
WINAPI
MapDialogRect(
    _In_ HWND hDlg,
    _Inout_ LPRECT lpRect);

WINUSERAPI
int
WINAPI
DlgDirListA(
    _In_ HWND hDlg,
    _Inout_ LPSTR lpPathSpec,
    _In_ int nIDListBox,
    _In_ int nIDStaticPath,
    _In_ UINT uFileType);

WINUSERAPI
int
WINAPI
DlgDirListW(
    _In_ HWND hDlg,
    _Inout_ LPWSTR lpPathSpec,
    _In_ int nIDListBox,
    _In_ int nIDStaticPath,
    _In_ UINT uFileType);

WINUSERAPI
BOOL
WINAPI
DlgDirSelectExA(
    _In_ HWND hwndDlg,
    _Out_writes_(chCount) LPSTR lpString,
    _In_ int chCount,
    _In_ int idListBox);

WINUSERAPI
BOOL
WINAPI
DlgDirSelectExW(
    _In_ HWND hwndDlg,
    _Out_writes_(chCount) LPWSTR lpString,
    _In_ int chCount,
    _In_ int idListBox);

WINUSERAPI
int
WINAPI
DlgDirListComboBoxA(
    _In_ HWND hDlg,
    _Inout_ LPSTR lpPathSpec,
    _In_ int nIDComboBox,
    _In_ int nIDStaticPath,
    _In_ UINT uFiletype);

WINUSERAPI
int
WINAPI
DlgDirListComboBoxW(
    _In_ HWND hDlg,
    _Inout_ LPWSTR lpPathSpec,
    _In_ int nIDComboBox,
    _In_ int nIDStaticPath,
    _In_ UINT uFiletype);

WINUSERAPI
BOOL
WINAPI
DlgDirSelectComboBoxExA(
    _In_ HWND hwndDlg,
    _Out_writes_(cchOut) LPSTR lpString,
    _In_ int cchOut,
    _In_ int idComboBox);

WINUSERAPI
BOOL
WINAPI
DlgDirSelectComboBoxExW(
    _In_ HWND hwndDlg,
    _Out_writes_(cchOut) LPWSTR lpString,
    _In_ int cchOut,
    _In_ int idComboBox);

WINUSERAPI
int
WINAPI
SetScrollInfo(
    _In_ HWND hwnd,
    _In_ int nBar,
    _In_ LPCSCROLLINFO lpsi,
    _In_ BOOL redraw);

WINUSERAPI
BOOL
WINAPI
GetScrollInfo(
    _In_ HWND hwnd,
    _In_ int nBar,
    _Inout_ LPSCROLLINFO lpsi);

WINUSERAPI
LRESULT
WINAPI
DefFrameProcA(
    _In_ HWND hWnd,
    _In_opt_ HWND hWndMDIClient,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);

WINUSERAPI
LRESULT
WINAPI
DefFrameProcW(
    _In_ HWND hWnd,
    _In_opt_ HWND hWndMDIClient,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);

WINUSERAPI
#ifndef _MAC
LRESULT
WINAPI
#else
LRESULT
CALLBACK
#endif
DefMDIChildProcA(
    _In_ HWND hWnd,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);
WINUSERAPI
#ifndef _MAC
LRESULT
WINAPI
#else
LRESULT
CALLBACK
#endif
DefMDIChildProcW(
    _In_ HWND hWnd,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
TranslateMDISysAccel(
    _In_ HWND hWndClient,
    _In_ LPMSG lpMsg);

#endif /* !NOMSG */

WINUSERAPI
UINT
WINAPI
ArrangeIconicWindows(
    _In_ HWND hWnd);

WINUSERAPI
HWND
WINAPI
CreateMDIWindowA(
    _In_ LPCSTR lpClassName,
    _In_ LPCSTR lpWindowName,
    _In_ DWORD dwStyle,
    _In_ int X,
    _In_ int Y,
    _In_ int nWidth,
    _In_ int nHeight,
    _In_opt_ HWND hWndParent,
    _In_opt_ HINSTANCE hInstance,
    _In_ LPARAM lParam);

WINUSERAPI
HWND
WINAPI
CreateMDIWindowW(
    _In_ LPCWSTR lpClassName,
    _In_ LPCWSTR lpWindowName,
    _In_ DWORD dwStyle,
    _In_ int X,
    _In_ int Y,
    _In_ int nWidth,
    _In_ int nHeight,
    _In_opt_ HWND hWndParent,
    _In_opt_ HINSTANCE hInstance,
    _In_ LPARAM lParam);

WINUSERAPI
WORD
WINAPI
TileWindows(
    _In_opt_ HWND hwndParent,
    _In_ UINT wHow,
    _In_opt_ CONST RECT * lpRect,
    _In_ UINT cKids,
    _In_reads_opt_(cKids) const HWND FAR * lpKids);

WINUSERAPI
WORD
WINAPI CascadeWindows(
    _In_opt_ HWND hwndParent,
    _In_ UINT wHow,
    _In_opt_ CONST RECT * lpRect,
    _In_ UINT cKids,
    _In_reads_opt_(cKids) const HWND FAR * lpKids);

WINUSERAPI
BOOL
WINAPI
WinHelpA(
    _In_opt_ HWND hWndMain,
    _In_opt_ LPCSTR lpszHelp,
    _In_ UINT uCommand,
    _In_ ULONG_PTR dwData);

WINUSERAPI
BOOL
WINAPI
WinHelpW(
    _In_opt_ HWND hWndMain,
    _In_opt_ LPCWSTR lpszHelp,
    _In_ UINT uCommand,
    _In_ ULONG_PTR dwData);

WINUSERAPI
LONG
WINAPI
ChangeDisplaySettingsExA(
    _In_opt_ LPCSTR lpszDeviceName,
    _In_opt_ DEVMODEA * lpDevMode,
    _Reserved_ HWND hwnd,
    _In_ DWORD dwflags,
    _In_opt_ LPVOID lParam);

WINUSERAPI
LONG
WINAPI
ChangeDisplaySettingsExW(
    _In_opt_ LPCWSTR lpszDeviceName,
    _In_opt_ DEVMODEW * lpDevMode,
    _Reserved_ HWND hwnd,
    _In_ DWORD dwflags,
    _In_opt_ LPVOID lParam);

WINUSERAPI
int
WINAPI
InternalGetWindowText(
    _In_ HWND hWnd,
    _Out_writes_to_(cchMaxCount, return +1) LPWSTR pString,
    _In_ int cchMaxCount);


#if defined(WINNT)
WINUSERAPI
BOOL
WINAPI
EndTask(
    _In_ HWND hWnd,
    _In_ BOOL fShutDown,
    _In_ BOOL fForce);
#endif

WINUSERAPI
HMONITOR
WINAPI
MonitorFromWindow(
    _In_ HWND hwnd,
    _In_ DWORD dwFlags);

WINUSERAPI
VOID
WINAPI
NotifyWinEvent(
    _In_ DWORD event,
    _In_ HWND  hwnd,
    _In_ LONG  idObject,
    _In_ LONG  idChild);

typedef VOID(CALLBACK* WINEVENTPROC)(
    HWINEVENTHOOK hWinEventHook,
    DWORD         event,
    HWND          hwnd,
    LONG          idObject,
    LONG          idChild,
    DWORD         idEventThread,
    DWORD         dwmsEventTime);

WINUSERAPI
DPI_AWARENESS_CONTEXT
WINAPI
GetWindowDpiAwarenessContext(
    _In_ HWND hwnd);

WINUSERAPI
UINT
WINAPI
GetDpiForWindow(
    _In_ HWND hwnd);

WINUSERAPI
BOOL
WINAPI
EnableNonClientDpiScaling(
    _In_ HWND hwnd);

WINUSERAPI
BOOL
WINAPI
InheritWindowMonitor(
    _In_ HWND hwnd,
    _In_opt_ HWND hwndInherit);

WINUSERAPI
DPI_HOSTING_BEHAVIOR
WINAPI
GetWindowDpiHostingBehavior(
    _In_ HWND hwnd);

WINUSERAPI
UINT
WINAPI
GetWindowModuleFileNameA(
    _In_ HWND hwnd,
    _Out_writes_to_(cchFileNameMax, return) LPSTR pszFileName,
    _In_ UINT cchFileNameMax);

WINUSERAPI
UINT
WINAPI
GetWindowModuleFileNameW(
    _In_ HWND hwnd,
    _Out_writes_to_(cchFileNameMax, return) LPWSTR pszFileName,
    _In_ UINT cchFileNameMax);

WINUSERAPI
BOOL
WINAPI
GetWindowInfo(
    _In_ HWND hwnd,
    _Inout_ PWINDOWINFO pwi);

WINUSERAPI
BOOL
WINAPI
GetTitleBarInfo(
    _In_ HWND hwnd,
    _Inout_ PTITLEBARINFO pti);

WINUSERAPI
BOOL
WINAPI
GetMenuBarInfo(
    _In_ HWND hwnd,
    _In_ LONG idObject,
    _In_ LONG idItem,
    _Inout_ PMENUBARINFO pmbi);

WINUSERAPI
BOOL
WINAPI
GetScrollBarInfo(
    _In_ HWND hwnd,
    _In_ LONG idObject,
    _Inout_ PSCROLLBARINFO psbi);

WINUSERAPI
BOOL
WINAPI
GetComboBoxInfo(
    _In_ HWND hwndCombo,
    _Inout_ PCOMBOBOXINFO pcbi);

WINUSERAPI
HWND
WINAPI
GetAncestor(
    _In_ HWND hwnd,
    _In_ UINT gaFlags);

WINUSERAPI
HWND
WINAPI
RealChildWindowFromPoint(
    _In_ HWND hwndParent,
    _In_ POINT ptParentClientCoords);

WINUSERAPI
UINT
WINAPI
RealGetWindowClassA(
    _In_ HWND hwnd,
    _Out_writes_to_(cchClassNameMax, return) LPSTR ptszClassName,
    _In_ UINT cchClassNameMax);

WINUSERAPI
UINT
WINAPI
RealGetWindowClassW(
    _In_ HWND hwnd,
    _Out_writes_to_(cchClassNameMax, return) LPWSTR ptszClassName,
    _In_ UINT cchClassNameMax);

WINUSERAPI
BOOL
WINAPI
GetAltTabInfoA(
    _In_opt_ HWND hwnd,
    _In_ int iItem,
    _Inout_ PALTTABINFO pati,
    _Out_writes_opt_(cchItemText) LPSTR pszItemText,
    _In_ UINT cchItemText);

WINUSERAPI
BOOL
WINAPI
GetAltTabInfoW(
    _In_opt_ HWND hwnd,
    _In_ int iItem,
    _Inout_ PALTTABINFO pati,
    _Out_writes_opt_(cchItemText) LPWSTR pszItemText,
    _In_ UINT cchItemText);

WINUSERAPI
DWORD
WINAPI
GetListBoxInfo(
    _In_ HWND hwnd);

WINUSERAPI
BOOL
WINAPI
RegisterPointerDeviceNotifications(
    _In_ HWND window,
    _In_ BOOL notifyRange);

WINUSERAPI
BOOL
WINAPI
ChangeWindowMessageFilterEx(
    _In_ HWND hwnd,                                         // Window
    _In_ UINT message,                                      // WM_ message
    _In_ DWORD action,                                      // Message filter action value
    _Inout_opt_ PCHANGEFILTERSTRUCT pChangeFilterStruct);   // Optional

WINUSERAPI
BOOL
WINAPI
SetGestureConfig(
    _In_ HWND hwnd,                                     // window for which configuration is specified
    _In_ DWORD dwReserved,                              // reserved, must be 0
    _In_ UINT cIDs,                                     // count of GESTURECONFIG structures
    _In_reads_(cIDs) PGESTURECONFIG pGestureConfig,    // array of GESTURECONFIG structures, dwIDs will be processed in the
                                                        // order specified and repeated occurances will overwrite previous ones
    _In_ UINT cbSize);                                  // sizeof(GESTURECONFIG)

WINUSERAPI
BOOL
WINAPI
GetGestureConfig(
    _In_ HWND hwnd,                                     // window for which configuration is required
    _In_ DWORD dwReserved,                              // reserved, must be 0
    _In_ DWORD dwFlags,                                 // see GCF_* flags
    _In_ PUINT pcIDs,                                   // *pcIDs contains the size, in number of GESTURECONFIG structures,
                                                        // of the buffer pointed to by pGestureConfig
    _Inout_updates_(*pcIDs) PGESTURECONFIG pGestureConfig,
                                                        // pointer to buffer to receive the returned array of GESTURECONFIG structures
    _In_ UINT cbSize);                                  // sizeof(GESTURECONFIG)

WINUSERAPI
BOOL
WINAPI
ShutdownBlockReasonCreate(
    _In_ HWND hWnd,
    _In_ LPCWSTR pwszReason);

WINUSERAPI
BOOL
WINAPI
ShutdownBlockReasonQuery(
    _In_ HWND hWnd,
    _Out_writes_opt_(*pcchBuff) LPWSTR pwszBuff,
    _Inout_ DWORD * pcchBuff);

WINUSERAPI
BOOL
WINAPI
ShutdownBlockReasonDestroy(
    _In_ HWND hWnd);
