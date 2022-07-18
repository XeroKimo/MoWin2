module;
#include <concepts>

#include <Windows.h>
#include <memory>
#include <atomic>
#include <bit>
#include <variant>

export module MoWin.Window:Common;

#undef RegisterClass
#undef UnregisterClass
#undef CreateWindow

#undef SendMessage
#undef SendNotifyMessage
#undef SendMessageTimeout
#undef SendMessageCallback

namespace MoWin
{
    export enum class Platform
    {
        Win32,
        Win64
    };

    export enum class CharacterSet
    {
        MBCS,
        Unicode
    };

    export template<Platform P, CharacterSet C>
        struct PlatformTraits;

    export struct Dimension2D
    {
        LONG width;
        LONG height;
    };

    export struct Rect : public RECT
    {
        Rect() = default;
        Rect(POINT position, Dimension2D size) :
            RECT{ position.x, position.y, position.x + size.width, position.y + size.height }
        {

        }

        POINT Center() const { return POINT{ (left + right) / 2, (top + bottom) / 2 }; }
        Dimension2D Lengths() const { return Dimension2D{ right - left, bottom - top }; }
    };

#pragma region Events

    export enum class EventType : UINT
    {
        //Window notification events
        Activate_App = WM_ACTIVATEAPP,
        Cancel_Mode = WM_CANCELMODE,
        Child_Activate = WM_CHILDACTIVATE,
        Close = WM_CLOSE,
        Compacting = WM_COMPACTING,
        Create = WM_CREATE,
        Destroy = WM_DESTROY,
        Enable = WM_ENABLE,
        Enter_Size_Move = WM_ENTERSIZEMOVE,
        Exit_Size_Move = WM_EXITSIZEMOVE,
        Get_Icon = WM_GETICON,
        Get_Min_Max_Info = WM_GETMINMAXINFO,
        Input_Language_Change = WM_INPUTLANGCHANGE,
        Input_Language_Change_Request = WM_INPUTLANGCHANGEREQUEST,
        Move = WM_MOVE,
        Moving = WM_MOVING,
        Nonclient_Activate = WM_NCACTIVATE,
        Nonclient_Calculate_Size = WM_NCCALCSIZE,
        Nonclient_Create = WM_NCCREATE,
        Nonclient_Destroy = WM_NCDESTROY,
        Null = WM_NULL,
        QueryDragIcon = WM_QUERYDRAGICON,
        QueryOpen = WM_QUERYOPEN,
        Quit = WM_QUIT,
        ShowWindow = WM_SHOWWINDOW,
        Size = WM_SIZE,
        Sizing = WM_SIZING,
        Style_Changed = WM_STYLECHANGED,
        Style_Changing = WM_STYLECHANGING,
        Theme_Changed = WM_THEMECHANGED,
        User_Changed = WM_USERCHANGED,
        Window_Position_Changed = WM_WINDOWPOSCHANGED,
        Window_Position_Changing = WM_WINDOWPOSCHANGING,

        //Keyboard Input Notification Events
        Activate = WM_ACTIVATE,
        Application_Command = WM_APPCOMMAND,
        Char = WM_CHAR,
        Dead_Char = WM_DEADCHAR,
        Hotkey = WM_HOTKEY,
        Key_Down = WM_KEYDOWN,
        Key_Up = WM_KEYUP,
        Kill_Focus = WM_KILLFOCUS,
        Set_Focus = WM_SETFOCUS,
        System_Dead_Char = WM_SYSDEADCHAR,
        System_Key_Down = WM_SYSKEYDOWN,
        System_Key_Up = WM_SYSKEYUP,
        Unicode_Char = WM_UNICHAR,
    };

    export enum class EventCatagoryType
    {
        Window_Notifications,
        Keyboard_Notfications,
        All = 255
    };

    export template<EventType Type, class PlatformTrait>
        struct TypedEventImpl;

    export template<EventCatagoryType Type, class PlatformTrait>
        struct EventCategoryImpl;

    export template<class PlatformTrait>
        struct EventBase
    {
        HWND window;
        EventType type;
        WPARAM wParam;
        LPARAM lParam;
    };

    export template<class PlatformTrait>
        struct EventImpl : public EventBase<PlatformTrait>
    {
        using platform_traits = PlatformTrait;
        using KeyboardInputNotifications = EventCategoryImpl<EventCatagoryType::Keyboard_Notfications, PlatformTrait>;
        using WindowNotifications = EventCategoryImpl<EventCatagoryType::Window_Notifications, PlatformTrait>;
        using All = EventCategoryImpl<EventCatagoryType::All, PlatformTrait>;
    };

    template<class Func, class RetVal, class... Args>
    concept invocable_r = std::is_invocable_r_v<RetVal, Func, Args...>;

#pragma region EventTy Categories

    export template<class PlatformTrait>
        struct EventCategoryImpl<EventCatagoryType::Window_Notifications, PlatformTrait>
    {
        using ActivateApp = TypedEventImpl<EventType::Activate_App, PlatformTrait>;
        using CancelMode = TypedEventImpl<EventType::Cancel_Mode, PlatformTrait>;
        using ChildActivate = TypedEventImpl<EventType::Child_Activate, PlatformTrait>;
        using Close = TypedEventImpl<EventType::Close, PlatformTrait>;
        using Compacting = TypedEventImpl<EventType::Compacting, PlatformTrait>;
        using Create = TypedEventImpl<EventType::Create, PlatformTrait>;
        using Destroy = TypedEventImpl<EventType::Destroy, PlatformTrait>;
        using Enable = TypedEventImpl<EventType::Enable, PlatformTrait>;
        using EnterSizeMove = TypedEventImpl<EventType::Enter_Size_Move, PlatformTrait>;
        using ExitSizeMove = TypedEventImpl<EventType::Exit_Size_Move, PlatformTrait>;
        using GetIcon = TypedEventImpl<EventType::Get_Icon, PlatformTrait>;
        using GetMinMaxInfo = TypedEventImpl<EventType::Get_Min_Max_Info, PlatformTrait>;
        using InputLanguageChange = TypedEventImpl<EventType::Input_Language_Change, PlatformTrait>;
        using InputLanguageChangeRequest = TypedEventImpl<EventType::Input_Language_Change_Request, PlatformTrait>;
        using Move = TypedEventImpl<EventType::Move, PlatformTrait>;
        using Moving = TypedEventImpl<EventType::Moving, PlatformTrait>;
        using NonclientActivate = TypedEventImpl<EventType::Nonclient_Activate, PlatformTrait>;
        using NonclientCalculateSize = TypedEventImpl<EventType::Nonclient_Calculate_Size, PlatformTrait>;
        using NonclientCreate = TypedEventImpl<EventType::Nonclient_Create, PlatformTrait>;
        using NonclientDestroy = TypedEventImpl<EventType::Nonclient_Destroy, PlatformTrait>;
        using Null = TypedEventImpl<EventType::Null, PlatformTrait>;
        using QueryDragIcon = TypedEventImpl<EventType::QueryDragIcon, PlatformTrait>;
        using QueryOpen = TypedEventImpl<EventType::QueryOpen, PlatformTrait>;
        using Quit = TypedEventImpl<EventType::Quit, PlatformTrait>;
        using ShowWindow = TypedEventImpl<EventType::ShowWindow, PlatformTrait>;
        using Size = TypedEventImpl<EventType::Size, PlatformTrait>;
        using Sizing = TypedEventImpl<EventType::Sizing, PlatformTrait>;
        using StyleChanged = TypedEventImpl<EventType::Style_Changed, PlatformTrait>;
        using StyleChanging = TypedEventImpl<EventType::Style_Changing, PlatformTrait>;
        using ThemeChanged = TypedEventImpl<EventType::Theme_Changed, PlatformTrait>;
        using UsedChanged = TypedEventImpl<EventType::User_Changed, PlatformTrait>;
        using WindowPositonChanged = TypedEventImpl<EventType::Window_Position_Changed, PlatformTrait>;
        using WindowPositionChanging = TypedEventImpl<EventType::Window_Position_Changing, PlatformTrait>;
    };

    export template<class PlatformTrait>
        struct EventCategoryImpl<EventCatagoryType::Keyboard_Notfications, PlatformTrait>
    {
        using Activate = TypedEventImpl<EventType::Activate, PlatformTrait>;
        using ApplicationCommand = TypedEventImpl<EventType::Application_Command, PlatformTrait>;
        using Char = TypedEventImpl<EventType::Char, PlatformTrait>;
        using DeadChar = TypedEventImpl<EventType::Dead_Char, PlatformTrait>;
        using Hotkey = TypedEventImpl<EventType::Hotkey, PlatformTrait>;
        using KeyDown = TypedEventImpl<EventType::Key_Down, PlatformTrait>;
        using KeyUp = TypedEventImpl<EventType::Key_Up, PlatformTrait>;
        using KillFocus = TypedEventImpl<EventType::Kill_Focus, PlatformTrait>;
        using SetFocus = TypedEventImpl<EventType::Set_Focus, PlatformTrait>;
        using SystemDeadChar = TypedEventImpl<EventType::System_Dead_Char, PlatformTrait>;
        using SystemKeyDown = TypedEventImpl<EventType::System_Key_Down, PlatformTrait>;
        using SystemKeyUp = TypedEventImpl<EventType::System_Key_Up, PlatformTrait>;
        using UnicodeChar = TypedEventImpl<EventType::Unicode_Char, PlatformTrait>;
    };


    export template<class PlatformTrait>
        struct EventCategoryImpl<EventCatagoryType::All, PlatformTrait>
    {
        //Window notification events
        using ActivateApp = TypedEventImpl<EventType::Activate_App, PlatformTrait>;
        using CancelMode = TypedEventImpl<EventType::Cancel_Mode, PlatformTrait>;
        using ChildActivate = TypedEventImpl<EventType::Child_Activate, PlatformTrait>;
        using Close = TypedEventImpl<EventType::Close, PlatformTrait>;
        using Compacting = TypedEventImpl<EventType::Compacting, PlatformTrait>;
        using Create = TypedEventImpl<EventType::Create, PlatformTrait>;
        using Destroy = TypedEventImpl<EventType::Destroy, PlatformTrait>;
        using Enable = TypedEventImpl<EventType::Enable, PlatformTrait>;
        using EnterSizeMove = TypedEventImpl<EventType::Enter_Size_Move, PlatformTrait>;
        using ExitSizeMove = TypedEventImpl<EventType::Exit_Size_Move, PlatformTrait>;
        using GetIcon = TypedEventImpl<EventType::Get_Icon, PlatformTrait>;
        using GetMinMaxInfo = TypedEventImpl<EventType::Get_Min_Max_Info, PlatformTrait>;
        using InputLanguageChange = TypedEventImpl<EventType::Input_Language_Change, PlatformTrait>;
        using InputLanguageChangeRequest = TypedEventImpl<EventType::Input_Language_Change_Request, PlatformTrait>;
        using Move = TypedEventImpl<EventType::Move, PlatformTrait>;
        using Moving = TypedEventImpl<EventType::Moving, PlatformTrait>;
        using NonclientActivate = TypedEventImpl<EventType::Nonclient_Activate, PlatformTrait>;
        using NonclientCalculateSize = TypedEventImpl<EventType::Nonclient_Calculate_Size, PlatformTrait>;
        using NonclientCreate = TypedEventImpl<EventType::Nonclient_Create, PlatformTrait>;
        using NonclientDestroy = TypedEventImpl<EventType::Nonclient_Destroy, PlatformTrait>;
        using Null = TypedEventImpl<EventType::Null, PlatformTrait>;
        using QueryDragIcon = TypedEventImpl<EventType::QueryDragIcon, PlatformTrait>;
        using QueryOpen = TypedEventImpl<EventType::QueryOpen, PlatformTrait>;
        using Quit = TypedEventImpl<EventType::Quit, PlatformTrait>;
        using ShowWindow = TypedEventImpl<EventType::ShowWindow, PlatformTrait>;
        using Size = TypedEventImpl<EventType::Size, PlatformTrait>;
        using Sizing = TypedEventImpl<EventType::Sizing, PlatformTrait>;
        using StyleChanged = TypedEventImpl<EventType::Style_Changed, PlatformTrait>;
        using StyleChanging = TypedEventImpl<EventType::Style_Changing, PlatformTrait>;
        using ThemeChanged = TypedEventImpl<EventType::Theme_Changed, PlatformTrait>;
        using UsedChanged = TypedEventImpl<EventType::User_Changed, PlatformTrait>;
        using WindowPosChanged = TypedEventImpl<EventType::Window_Position_Changed, PlatformTrait>;
        using WindowPosChanging = TypedEventImpl<EventType::Window_Position_Changing, PlatformTrait>;

        //Keyboard Input Notifications events
        using Activate = TypedEventImpl<EventType::Activate, PlatformTrait>;
        using ApplicationCommand = TypedEventImpl<EventType::Application_Command, PlatformTrait>;
        using Char = TypedEventImpl<EventType::Char, PlatformTrait>;
        using DeadChar = TypedEventImpl<EventType::Dead_Char, PlatformTrait>;
        using Hotkey = TypedEventImpl<EventType::Hotkey, PlatformTrait>;
        using KeyDown = TypedEventImpl<EventType::Key_Down, PlatformTrait>;
        using KeyUp = TypedEventImpl<EventType::Key_Up, PlatformTrait>;
        using KillFocus = TypedEventImpl<EventType::Kill_Focus, PlatformTrait>;
        using SetFocus = TypedEventImpl<EventType::Set_Focus, PlatformTrait>;
        using SystemDeadChar = TypedEventImpl<EventType::System_Dead_Char, PlatformTrait>;
        using SystemKeyDown = TypedEventImpl<EventType::System_Key_Down, PlatformTrait>;
        using SystemKeyUp = TypedEventImpl<EventType::System_Key_Up, PlatformTrait>;
        using UnicodeChar = TypedEventImpl<EventType::Unicode_Char, PlatformTrait>;
    };
#pragma endregion

#pragma region Window Notification Events

    export template<class Func, class PlatformTrait>
        concept VisitableWindowNotifications =
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Activate_App, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Cancel_Mode, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Child_Activate, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Close, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Compacting, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Create, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Destroy, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Enable, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Enter_Size_Move, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Exit_Size_Move, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Get_Icon, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Get_Min_Max_Info, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Input_Language_Change, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Input_Language_Change_Request, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Move, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Moving, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Nonclient_Activate, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Nonclient_Calculate_Size, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Nonclient_Create, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Nonclient_Destroy, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Null, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::QueryDragIcon, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::QueryOpen, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Quit, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::ShowWindow, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Size, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Sizing, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Style_Changed, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Style_Changing, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Theme_Changed, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::User_Changed, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Window_Position_Changed, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Window_Position_Changing, PlatformTrait>>;

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Activate_App, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        bool Activated() const noexcept { return wParam; }
        DWORD ThreadID() const noexcept { return static_cast<DWORD>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Cancel_Mode, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Child_Activate, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Close, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Compacting, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Create, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        auto CreateParams() const noexcept
        {
            return (*std::bit_cast<typename PlatformTrait::window_create_struct_type*>(lParam));
        }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Destroy, PlatformTrait> : public EventBase<PlatformTrait>
    {

    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Enable, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        bool Enabled() const noexcept { return wParam; }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Enter_Size_Move, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Exit_Size_Move, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Get_Icon, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        enum class IconSize
        {
            Small = 0,
            Big = 1,
            Small_2 = 2
        };

        IconSize Size() const noexcept { return static_cast<IconSize>(wParam); }
        WORD DPI() const noexcept { return static_cast<WORD>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Get_Min_Max_Info, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        MINMAXINFO& MinMaxInfo() const noexcept { return *std::bit_cast<MINMAXINFO*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Input_Language_Change, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        WPARAM CodePage() const noexcept { return wParam; }
        WORD LanguageIdentifier() const noexcept { return LOWORD(lParam); }
        WORD DeviceHandle() const noexcept { return HIWORD(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Input_Language_Change_Request, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        bool IsChangeBackward() const noexcept { return wParam & INPUTLANGCHANGE_BACKWARD; }
        bool IsChangeForward() const noexcept { return wParam & INPUTLANGCHANGE_FORWARD; }
        bool IsSystemCharacterSet() const noexcept { return wParam & INPUTLANGCHANGE_SYSCHARSET; }
        WORD LanguageIdentifier() const noexcept { return LOWORD(lParam); }
        WORD DeviceHandle() const noexcept { return HIWORD(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Move, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        WORD Left() { return LOWORD(lParam); }
        WORD Top() { return HIWORD(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Moving, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        RECT& Rect() const noexcept { return *std::bit_cast<RECT*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Nonclient_Activate, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        bool Active() const noexcept { return wParam; }
        bool RedrawWindow() const noexcept { return lParam != -1; }
        //TODO: Figure out the how to interpret the update region of the non-client area using the lParam https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-ncactivate
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Nonclient_Calculate_Size, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        //bool
        NCCALCSIZE_PARAMS& Params() const noexcept { return *std::bit_cast<NCCALCSIZE_PARAMS*>(lParam); }
        RECT& Rect() const noexcept { return *std::bit_cast<RECT*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Nonclient_Create, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        auto CreateParams() const noexcept
        {
            return (*std::bit_cast<typename PlatformTrait::window_create_struct_type*>(lParam));
        }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Nonclient_Destroy, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Null, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::QueryDragIcon, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::QueryOpen, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Quit, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::ShowWindow, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        bool Shown() const noexcept { return wParam; }
        bool ParentClosing() const noexcept { return lParam == SW_PARENTCLOSING; }
        bool OtherZoom() const noexcept { return lParam == SW_OTHERZOOM; }
        bool ParentOpening() const noexcept { return lParam == SW_PARENTOPENING; }
        bool OtherUnzoom() const noexcept { return lParam == SW_OTHERUNZOOM; }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Size, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        bool Restored() const noexcept { return wParam == SIZE_RESTORED; }
        bool Minimized() const noexcept { return wParam == SIZE_MINIMIZED; }
        bool Maximized() const noexcept { return wParam == SIZE_MAXIMIZED; }
        bool MaxShow() const noexcept { return wParam == SIZE_MAXSHOW; }
        bool MaxHide() const noexcept { return wParam == SIZE_MAXHIDE; }

        WORD Width() const noexcept { return LOWORD(lParam); }
        WORD Height() const noexcept { return HIWORD(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Sizing, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        enum class ResizeEdge
        {
            Left = WMSZ_LEFT,
            Right = WMSZ_RIGHT,
            Top = WMSZ_TOP,
            Top_Left = WMSZ_TOPLEFT,
            Top_Right = WMSZ_TOPRIGHT,
            Bottom = WMSZ_BOTTOM,
            Bottom_Left = WMSZ_BOTTOMLEFT,
            Bottom_Right = WMSZ_BOTTOMRIGHT,
        };
        ResizeEdge SelectedEdge() const noexcept { return static_cast<ResizeEdge>(wParam); }
        RECT& Rect() const noexcept { return *std::bit_cast<RECT*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Style_Changed, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        bool IsExtendedStyle() const noexcept { return wParam == GWL_EXSTYLE; }
        const STYLESTRUCT& Data() const noexcept { return *std::bit_cast<const STYLESTRUCT*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Style_Changing, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        bool IsExtendedStyle() const noexcept { return wParam == GWL_EXSTYLE; }
        const STYLESTRUCT& Data() const noexcept { return *std::bit_cast<const STYLESTRUCT*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Theme_Changed, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::User_Changed, PlatformTrait> : public EventBase<PlatformTrait>
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Window_Position_Changed, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        WINDOWPOS& Data() const noexcept { return *std::bit_cast<WINDOWPOS*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Window_Position_Changing, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        WINDOWPOS& Data() const noexcept { return *std::bit_cast<WINDOWPOS*>(lParam); }
    };

#pragma endregion

#pragma region Keyboard Notificaiton Events
    export template<class Func, class PlatformTrait>
        concept VisitableKeyboardNotifications =
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Activate, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Application_Command, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Char, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Dead_Char, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Hotkey, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Key_Down, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Key_Up, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Kill_Focus, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Set_Focus, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::System_Dead_Char, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::System_Key_Down, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::System_Key_Up, PlatformTrait>> ||
        invocable_r<Func, LRESULT, TypedEventImpl<EventType::Unicode_Char, PlatformTrait>>;

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Activate, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        bool Inactive() const noexcept { return wParam == WA_INACTIVE; }
        bool Active() const noexcept { return wParam == WA_ACTIVE; }
        bool ClickActive() const noexcept { return wParam == WA_CLICKACTIVE; }

        //A handle to the window being activated or deactivated, depending on the value of the wParam parameter. 
        //If Inactive(), OtherWindow() is the handle to the window being activated. 
        //If Active() or ClickActive(), OtherWindow() is the handle to the window being deactivated. This handle can be NULL.
        HWND OtherWindow() const noexcept { return std::bit_cast<HWND>(lParam); }
    };

    export enum class ApplicationCommandType
    {
        Bass_Boost = APPCOMMAND_BASS_BOOST,
        Bass_Down = APPCOMMAND_BASS_DOWN,
        Bass_Up = APPCOMMAND_BASS_UP,
        Browser_Backward = APPCOMMAND_BROWSER_BACKWARD,
        Browser_Favorites = APPCOMMAND_BROWSER_FAVORITES,
        Browser_Forward = APPCOMMAND_BROWSER_FORWARD,
        Browser_Home = APPCOMMAND_BROWSER_HOME,
        Browser_Refresh = APPCOMMAND_BROWSER_REFRESH,
        Browser_Search = APPCOMMAND_BROWSER_SEARCH,
        Browser_Stop = APPCOMMAND_BROWSER_STOP,
        Close = APPCOMMAND_CLOSE,
        Copy = APPCOMMAND_COPY,
        Correct_List = APPCOMMAND_CORRECTION_LIST,
        Cut = APPCOMMAND_CUT,
        Dictate_Or_Command_Control_Toggle = APPCOMMAND_DICTATE_OR_COMMAND_CONTROL_TOGGLE,
        Find = APPCOMMAND_FIND,
        Forward_Mail = APPCOMMAND_FORWARD_MAIL,
        Help = APPCOMMAND_HELP,
        Launch_App_1 = APPCOMMAND_LAUNCH_APP1,
        Launch_App_2 = APPCOMMAND_LAUNCH_APP2,
        Launch_Mail = APPCOMMAND_LAUNCH_MAIL,
        Launch_Media_Select = APPCOMMAND_LAUNCH_MEDIA_SELECT,
        Media_Channel_Down = APPCOMMAND_MEDIA_CHANNEL_DOWN,
        Media_Channel_Up = APPCOMMAND_MEDIA_CHANNEL_UP,
        Media_Fast_Forward = APPCOMMAND_MEDIA_FAST_FORWARD,
        Media_Next_Track = APPCOMMAND_MEDIA_NEXTTRACK,
        Media_Pause = APPCOMMAND_MEDIA_PAUSE,
        Media_Play = APPCOMMAND_MEDIA_PLAY,
        Media_Play_Pause = APPCOMMAND_MEDIA_PLAY_PAUSE,
        Media_Previous_Track = APPCOMMAND_MEDIA_PREVIOUSTRACK,
        Media_Record = APPCOMMAND_MEDIA_RECORD,
        Media_Rewind = APPCOMMAND_MEDIA_REWIND,
        Media_Stop = APPCOMMAND_MEDIA_STOP,
        Mic_On_Off_Toggle = APPCOMMAND_MIC_ON_OFF_TOGGLE,
        Microphone_Volume_Down = APPCOMMAND_MICROPHONE_VOLUME_DOWN,
        Microphone_Volume_Mute = APPCOMMAND_MICROPHONE_VOLUME_MUTE,
        Microphone_Volume_Up = APPCOMMAND_MICROPHONE_VOLUME_UP,
        New = APPCOMMAND_NEW,
        Open = APPCOMMAND_OPEN,
        Paste = APPCOMMAND_PASTE,
        Print = APPCOMMAND_PRINT,
        Redo = APPCOMMAND_REDO,
        Reply_To_Mail = APPCOMMAND_REPLY_TO_MAIL,
        Save = APPCOMMAND_SAVE,
        Send_Mail = APPCOMMAND_SEND_MAIL,
        Spell_Check = APPCOMMAND_SPELL_CHECK,
        Treble_Down = APPCOMMAND_TREBLE_DOWN,
        Treble_Up = APPCOMMAND_TREBLE_UP,
        Undo = APPCOMMAND_UNDO,
        Volume_Down = APPCOMMAND_VOLUME_DOWN,
        Volume_Mute = APPCOMMAND_VOLUME_MUTE,
        Volume_Up = APPCOMMAND_VOLUME_UP,
    };

    export enum class ApplicationDeviceType
    {
        Keyboard = FAPPCOMMAND_KEY,
        Mouse = FAPPCOMMAND_MOUSE,
        OEM = FAPPCOMMAND_OEM
    };

    export enum class ApplicationKeyState
    {
        Control = MK_CONTROL,
        Mouse_Left_Button = MK_LBUTTON,
        Mouse_Middle_Button = MK_MBUTTON,
        Mouse_Right_Button = MK_RBUTTON,
        Shift = MK_SHIFT,
        X_Button_1 = MK_XBUTTON1,
        X_Button_2 = MK_XBUTTON2,
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Application_Command, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        HWND AffectedWindow() const noexcept { return std::bit_cast<HWND>(wParam); }
        ApplicationCommandType Command() const noexcept { return static_cast<ApplicationCommandType>(GET_APPCOMMAND_LPARAM(lParam)); }
        ApplicationDeviceType Device() const noexcept { return static_cast<ApplicationDeviceType>(GET_DEVICE_LPARAM(lParam)); }
        ApplicationKeyState KeyState() const noexcept { return static_cast<ApplicationKeyState>(GET_KEYSTATE_LPARAM(lParam)); }

    };

    export enum class VirtualKey
    {
        Left_Mouse_Button = VK_LBUTTON,
        Right_Mouse_Button = VK_RBUTTON,
        Cancel = VK_CANCEL,
        Middle_Mouse_Button = VK_MBUTTON,
        X1_Mouse_Button = VK_XBUTTON1,
        X2_Mouse_Button = VK_XBUTTON2,
        Undefined_0,
        Back = VK_BACK,
        Tab = VK_TAB,
        Reserved_0,
        Reserved_1,
        Clear = VK_CLEAR,
        Return = VK_RETURN,
        Undefined_1,
        Undefined_2, //Reserved 1, Underfined 2

        Shift = VK_SHIFT,
        Ctrl = VK_CONTROL,
        Alt = VK_MENU,
        Pause = VK_PAUSE,
        Caps_Lock = VK_CAPITAL,
        Kana = VK_KANA,
        Hangul = VK_HANGUL,
        IME_On = VK_IME_ON,
        Junja = VK_JUNJA,
        Final = VK_FINAL,
        Hanja = VK_HANJA,
        Kanji = VK_KANJI,
        IME_Off = VK_IME_OFF,
        Escape = VK_ESCAPE,
        IME_Convert = VK_CONVERT,
        IME_NonConvert = VK_NONCONVERT,
        IME_Accept = VK_ACCEPT,
        IME_Mode_Change = VK_MODECHANGE,

        SpaceBar = VK_SPACE,
        Page_Up = VK_PRIOR,
        Page_Down = VK_NEXT,
        End = VK_END,
        Home = VK_HOME,
        Left_Arrow = VK_LEFT,
        Up_Arrow = VK_UP,
        Right_Arrow = VK_RIGHT,
        Down_Arrow = VK_DOWN,
        Select = VK_SELECT,
        Print = VK_PRINT,
        Execute = VK_EXECUTE,
        Print_Screen = VK_SNAPSHOT,
        Insert = VK_INSERT,
        Delete = VK_DELETE,
        Help = VK_HELP,

        Num0 = 0x30,
        Num1 = 0x31,
        Num2 = 0x32,
        Num3 = 0x33,
        Num4 = 0x34,
        Num5 = 0x35,
        Num6 = 0x36,
        Num7 = 0x37,
        Num8 = 0x38,
        Num9 = 0x39,
        Undefined_3 = 0x3A,
        Undefined_4 = 0x3B,
        Undefined_5 = 0x3C,
        Undefined_6 = 0x3D,
        Undefined_7 = 0x3E,
        Undefined_8 = 0x3F, //Undefined 8

        A = 0x41,
        B = 0x42,
        C = 0x43,
        D = 0x44,
        E = 0x45,
        F = 0x46,
        G = 0x47,
        H = 0x48,
        I = 0x49,
        J = 0x4A,
        K = 0x4B,
        L = 0x4C,
        M = 0x4D,
        N = 0x4E,
        O = 0x4F,

        P = 0x50,
        Q = 0x51,
        R = 0x52,
        S = 0x53,
        T = 0x54,
        U = 0x55,
        V = 0x56,
        W = 0x57,
        X = 0x58,
        Y = 0x59,
        Z = 0x5A,
        Left_Windows = VK_LWIN,
        Right_Windows = VK_RWIN,
        Applications = VK_APPS,
        Reserved_2,
        Sleep = VK_SLEEP,   //Reserved 2

        Num_Pad0 = VK_NUMPAD0,
        Num_Pad1 = VK_NUMPAD1,
        Num_Pad2 = VK_NUMPAD2,
        Num_Pad3 = VK_NUMPAD3,
        Num_Pad4 = VK_NUMPAD4,
        Num_Pad5 = VK_NUMPAD5,
        Num_Pad6 = VK_NUMPAD6,
        Num_Pad7 = VK_NUMPAD7,
        Num_Pad8 = VK_NUMPAD8,
        Num_Pad9 = VK_NUMPAD9,
        Num_Pad_Mulitply = VK_MULTIPLY,
        Num_Pad_Add = VK_ADD,
        Num_Pad_Separator = VK_SEPARATOR,
        Num_Pad_Subtract = VK_SUBTRACT,
        Num_Pad_Decimal = VK_DECIMAL,
        Num_Pad_Devide = VK_DIVIDE,

        F1 = VK_F1,
        F2 = VK_F2,
        F3 = VK_F3,
        F4 = VK_F4,
        F5 = VK_F5,
        F6 = VK_F6,
        F7 = VK_F7,
        F8 = VK_F8,
        F9 = VK_F9,
        F10 = VK_F10,
        F11 = VK_F11,
        F12 = VK_F12,
        F13 = VK_F13,
        F14 = VK_F14,
        F15 = VK_F15,
        F16 = VK_F16,

        F17 = VK_F17,
        F18 = VK_F18,
        F19 = VK_F19,
        F20 = VK_F20,
        F21 = VK_F21,
        F22 = VK_F22,
        F23 = VK_F23,
        F24 = VK_F24,
        Unassigned_0,
        Unassigned_1,
        Unassigned_2,
        Unassigned_3,
        Unassigned_4,
        Unassigned_5,
        Unassigned_6,
        Unassigned_7, //Unassigned 7

        Num_Lock = VK_NUMLOCK,
        Scroll_Lock = VK_SCROLL,
        OEM_Specific_0,
        OEM_Specific_1,
        OEM_Specific_2,
        OEM_Specific_3,
        OEM_Specific_4,
        Unassigned_8,
        Unassigned_9,
        Unassigned_10,
        Unassigned_11,
        Unassigned_12,
        Unassigned_13,
        Unassigned_14,
        Unassigned_15,
        Unassigned_16, //OEM Specific 4, Unassinged 16

        Left_Shift = VK_LSHIFT,
        Right_Shift = VK_RSHIFT,
        Left_Control = VK_LCONTROL,
        Right_Control = VK_RCONTROL,
        Left_Menu = VK_LMENU,
        Right_Menu = VK_RMENU,
        Browser_Back = VK_BROWSER_BACK,
        Browser_Forward = VK_BROWSER_FORWARD,
        Browser_Refresh = VK_BROWSER_REFRESH,
        Browser_Stop = VK_BROWSER_STOP,
        Browser_Search = VK_BROWSER_SEARCH,
        Browser_Favorites = VK_BROWSER_FAVORITES,
        Browser_Home = VK_BROWSER_HOME,
        Volume_Mute = VK_VOLUME_MUTE,
        Volume_Down = VK_VOLUME_DOWN,
        Volume_Up = VK_VOLUME_UP,

        Media_Next_Track = VK_MEDIA_NEXT_TRACK,
        Media_Previous_Track = VK_MEDIA_PREV_TRACK,
        Media_Stop = VK_MEDIA_STOP,
        Media_Play_Pause = VK_MEDIA_PLAY_PAUSE,
        Launch_Mail = VK_LAUNCH_MAIL,
        Launch_Media_Select = VK_LAUNCH_MEDIA_SELECT,
        Launch_App1 = VK_LAUNCH_APP1,
        Launch_App2 = VK_LAUNCH_APP2,
        Reserved_3,
        Reserved_4,
        OEM_1 = VK_OEM_1,
        OEM_Plus = VK_OEM_PLUS,
        OEM_Comma = VK_OEM_COMMA,
        OEM_Minus = VK_OEM_MINUS,
        OEM_Period = VK_OEM_PERIOD,
        OEM_2 = VK_OEM_2,  //Reserved 4

        OEM_3 = VK_OEM_3,
        Reserved_5,
        Reserved_6,
        Reserved_7,
        Reserved_8,
        Reserved_9,
        Reserved_10,
        Reserved_11,
        Reserved_12,
        Reserved_13,
        Reserved_14,
        Reserved_15,
        Reserved_16,
        Reserved_17,
        Reserved_18,
        Reserved_19, //Reserved 19

        Reserved_20,
        Reserved_21,
        Reserved_22,
        Reserved_23,
        Reserved_24,
        Reserved_25,
        Reserved_26,
        Reserved_27,
        Unassigned_17,
        Unassigned_18,
        Unassigned_19,
        OEM_4 = VK_OEM_4,
        OEM_5 = VK_OEM_5,
        OEM_6 = VK_OEM_6,
        OEM_7 = VK_OEM_7,
        OEM_8 = VK_OEM_8,  //Reserved 27, Unassigned 19

        Reserved_28,
        OEM_Specific_5,
        OEM_102 = VK_OEM_102,
        OEM_Specific_6,
        OEM_Specific_7,
        IME_Process_Key = VK_PROCESSKEY,
        OEM_Specific_8,
        Packet = VK_PACKET,
        Unassigned_20,
        OEM_Specific_9,
        OEM_Specific_10,
        OEM_Specific_11,
        OEM_Specific_12,
        OEM_Specific_13,
        OEM_Specific_14,
        OEM_Specific_15, //Reserved 28, OEM Specific 16, Unassigned 20

        OEM_Specific_16,
        OEM_Specific_17,
        OEM_Specific_18,
        OEM_Specific_19,
        OEM_Specific_20,
        OEM_Specific_21,
        Attn = VK_ATTN,
        CrSel = VK_CRSEL,
        ExSel = VK_EXSEL,
        Erase_EOF = VK_EREOF,
        Play = VK_PLAY,
        Zoom = VK_ZOOM,
        Reserved_29 = VK_NONAME,
        PA1 = VK_PA1,
        OEM_Clear = VK_OEM_CLEAR,
    };

    template<class DerivedSelf>
    struct KeyMessage
    {
        WORD RepeatCount() const noexcept { return LOWORD(Get().lParam); }
        BYTE ScanCode() const noexcept { return LOBYTE(HIWORD(Get().lParam)); }
        bool IsAltDown() const noexcept { return (HIWORD(Get().lParam) & KF_ALTDOWN) == KF_ALTDOWN; }
        bool IsDialogMode() const noexcept { return (HIWORD(Get().lParam) & KF_DLGMODE) == KF_DLGMODE; }
        bool IsExtendedKey() const noexcept { return (HIWORD(Get().lParam) & KF_EXTENDED) == KF_EXTENDED; }
        bool IsMenuMode() const noexcept { return (HIWORD(Get().lParam) & KF_MENUMODE) == KF_MENUMODE; }
        bool IsPreviousStateDown() const noexcept { return (HIWORD(Get().lParam) & KF_REPEAT) == KF_REPEAT; }
        bool IsKeyUp() const noexcept { return (HIWORD(Get().lParam) & KF_UP) == KF_UP; }
        bool IsKeyDown() const noexcept { return (HIWORD(Get().lParam) & KF_UP) == 0; }

    private:
        DerivedSelf& Get() noexcept { return static_cast<DerivedSelf&>(*this); }
        const DerivedSelf& Get() const noexcept { return static_cast<DerivedSelf&>(*this); }
    };

    template<class DerivedSelf>
    struct VirtualKeyMessage : public KeyMessage<DerivedSelf>
    {
        VirtualKey Key() const noexcept { return static_cast<VirtualKey>(Get().wParam); }

    private:
        DerivedSelf& Get() noexcept { return static_cast<DerivedSelf&>(*this); }
        const DerivedSelf& Get() const noexcept { return static_cast<DerivedSelf&>(*this); }
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Char, PlatformTrait> : public EventBase<PlatformTrait>, public KeyMessage<TypedEventImpl<EventType::Char, PlatformTrait>>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        auto Key() const noexcept
        {
            if constexpr(PlatformTrait::character_set == CharacterSet::MBCS)
            {
                return static_cast<char8_t>(wParam);
            }
            else
            {
                return static_cast<char16_t>(wParam);
            }
        }
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Dead_Char, PlatformTrait> : public EventBase<PlatformTrait>, public KeyMessage<TypedEventImpl<EventType::Dead_Char, PlatformTrait>>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        auto Key() const noexcept
        {
            if constexpr(PlatformTrait::character_set == CharacterSet::MBCS)
            {
                return static_cast<char8_t>(wParam);
            }
            else
            {
                return static_cast<char16_t>(wParam);
            }
        }
    };

    enum class HotkeyModifier
    {
        Alt = MOD_ALT,
        Control = MOD_CONTROL,
        Shift = MOD_SHIFT,
        Win = MOD_WIN
    };

    DEFINE_ENUM_FLAG_OPERATORS(HotkeyModifier);

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Hotkey, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        WPARAM HotkeyID() const noexcept
        {
            return wParam;
        }

        VirtualKey Key() const noexcept
        {
            return static_cast<VirtualKey>(HIWORD(lParam));
        }

        HotkeyModifier Modifiers() const noexcept
        {
            return static_cast<HotkeyModifier>(LOWORD(lParam));
        }
    };


    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Key_Down, PlatformTrait> : public EventBase<PlatformTrait>, public VirtualKeyMessage<TypedEventImpl<EventType::Key_Down, PlatformTrait>>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Key_Up, PlatformTrait> : public EventBase<PlatformTrait>, public VirtualKeyMessage<TypedEventImpl<EventType::Key_Up, PlatformTrait>>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Kill_Focus, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        HWND OtherWindow() const noexcept { return std::bit_cast<HWND>(wParam); }
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Set_Focus, PlatformTrait> : public EventBase<PlatformTrait>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        HWND OtherWindow() const noexcept { return std::bit_cast<HWND>(wParam); }
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::System_Dead_Char, PlatformTrait> : public EventBase<PlatformTrait>, public VirtualKeyMessage<TypedEventImpl<EventType::System_Dead_Char, PlatformTrait>>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;

        auto Key() const noexcept
        {
            if constexpr(PlatformTrait::character_set == CharacterSet::MBCS)
            {
                return static_cast<char8_t>(wParam);
            }
            else
            {
                return static_cast<char16_t>(wParam);
            }
        }
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::System_Key_Down, PlatformTrait> : public EventBase<PlatformTrait>, public VirtualKeyMessage<TypedEventImpl<EventType::System_Key_Down, PlatformTrait>>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::System_Key_Up, PlatformTrait> : public EventBase<PlatformTrait>, public VirtualKeyMessage<TypedEventImpl<EventType::System_Key_Up, PlatformTrait>>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Unicode_Char, PlatformTrait> : public EventBase<PlatformTrait>, public KeyMessage<TypedEventImpl<EventType::Unicode_Char, PlatformTrait>>
    {
        using EventBase<PlatformTrait>::window;
        using EventBase<PlatformTrait>::type;
        using EventBase<PlatformTrait>::wParam;
        using EventBase<PlatformTrait>::lParam;


        auto Key() const noexcept
        {
            return static_cast<char32_t>(wParam);
        }
    };

#pragma endregion

    template<class Func, EventType E, class PlatformTrait>
    concept VisitableEventImpl = std::invocable<Func, TypedEventImpl<E, PlatformTrait>>;

    template<class Func, class PlatformTrait>
    concept HasVisitableEventImpl = VisitableWindowNotifications<Func, PlatformTrait> ||
        VisitableKeyboardNotifications<Func, PlatformTrait>;

    template<EventType Type, class EventTy, class Func, std::invocable<EventTy> DefaultFunc>
    LRESULT VisitEventImpl(Func&& visitor, EventTy event, DefaultFunc&& defaultFunc)
    {
        if constexpr(VisitableEventImpl<Func, Type, typename std::remove_reference_t<EventTy>::platform_traits>)
        {
            return visitor(std::bit_cast<TypedEventImpl<Type, typename std::remove_reference_t<EventTy>::platform_traits>>(event));
        }
        else
        {
            return defaultFunc(std::forward<EventTy>(event));
        }
    }

    export template<class Func, class EventTy, std::invocable<EventTy> DefaultFunc>
        LRESULT VisitEvent(Func&& visitor, EventTy event, DefaultFunc&& defaultFunc)
    {
        switch(event.type)
        {
#pragma region Window Notification EventImpl cases
        case EventType::Activate_App:
            return VisitEventImpl<EventType::Activate_App>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Cancel_Mode:
            return VisitEventImpl<EventType::Cancel_Mode>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Child_Activate:
            return VisitEventImpl<EventType::Child_Activate>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Close:
            return VisitEventImpl<EventType::Close>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Compacting:
            return VisitEventImpl<EventType::Compacting>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Create:
            return VisitEventImpl<EventType::Create>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Destroy:
            return VisitEventImpl<EventType::Destroy>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Enable:
            return VisitEventImpl<EventType::Enable>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Enter_Size_Move:
            return VisitEventImpl<EventType::Enter_Size_Move>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Exit_Size_Move:
            return VisitEventImpl<EventType::Exit_Size_Move>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Get_Icon:
            return VisitEventImpl<EventType::Get_Icon>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Get_Min_Max_Info:
            return VisitEventImpl<EventType::Get_Min_Max_Info>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Input_Language_Change:
            return VisitEventImpl<EventType::Input_Language_Change>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Input_Language_Change_Request:
            return VisitEventImpl<EventType::Input_Language_Change_Request>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Move:
            return VisitEventImpl<EventType::Move>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Moving:
            return VisitEventImpl<EventType::Moving>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Nonclient_Activate:
            return VisitEventImpl<EventType::Nonclient_Activate>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Nonclient_Calculate_Size:
            return VisitEventImpl<EventType::Nonclient_Calculate_Size>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Nonclient_Create:
            return VisitEventImpl<EventType::Nonclient_Create>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Nonclient_Destroy:
            return VisitEventImpl<EventType::Nonclient_Destroy>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Null:
            return VisitEventImpl<EventType::Null>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::QueryDragIcon:
            return VisitEventImpl<EventType::QueryDragIcon>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::QueryOpen:
            return VisitEventImpl<EventType::QueryOpen>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Quit:
            return VisitEventImpl<EventType::Quit>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::ShowWindow:
            return VisitEventImpl<EventType::ShowWindow>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Size:
            return VisitEventImpl<EventType::Size>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Sizing:
            return VisitEventImpl<EventType::Sizing>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Style_Changed:
            return VisitEventImpl<EventType::Style_Changed>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Style_Changing:
            return VisitEventImpl<EventType::Style_Changing>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Theme_Changed:
            return VisitEventImpl<EventType::Theme_Changed>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::User_Changed:
            return VisitEventImpl<EventType::User_Changed>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Window_Position_Changed:
            return VisitEventImpl<EventType::Window_Position_Changed>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Window_Position_Changing:
            return VisitEventImpl<EventType::Window_Position_Changing>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
#pragma endregion

#pragma region Keyboard Notification EventTy cases
        case EventType::Activate:
            return VisitEventImpl<EventType::Activate>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Application_Command:
            return VisitEventImpl<EventType::Application_Command>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Char:
            return VisitEventImpl<EventType::Char>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Dead_Char:
            return VisitEventImpl<EventType::Dead_Char>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Hotkey:
            return VisitEventImpl<EventType::Hotkey>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Key_Down:
            return VisitEventImpl<EventType::Key_Down>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Key_Up:
            return VisitEventImpl<EventType::Key_Up>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Kill_Focus:
            return VisitEventImpl<EventType::Kill_Focus>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Set_Focus:
            return VisitEventImpl<EventType::Set_Focus>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::System_Dead_Char:
            return VisitEventImpl<EventType::System_Dead_Char>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::System_Key_Down:
            return VisitEventImpl<EventType::System_Key_Down>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::System_Key_Up:
            return VisitEventImpl<EventType::System_Key_Up>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Unicode_Char:
            return VisitEventImpl<EventType::Unicode_Char>(std::forward<Func>(visitor), std::forward<EventTy>(event), std::forward<DefaultFunc>(defaultFunc));
#pragma endregion

        default:
            return defaultFunc(std::forward<EventTy>(event));
        }
    }

#pragma endregion Events

#pragma region Window Class

    export enum class WindowClassAtom : ATOM {};

    //https://docs.microsoft.com/en-us/windows/win32/winmsg/window-class-styles
    export enum class WindowClassStyle
    {
        //Aligns the window's client area on a byte boundary (in the x direction). This style affects the width of the window and its horizontal placement on the display.
        Byte_Align_Client,

        //Aligns the window on a byte boundary (in the x direction). This style affects the width of the window and its horizontal placement on the display.
        Byte_Align_Window,

        //	Allocates one device context to be shared by all windows in the class. Because window classes are process specific, 
        //it is possible for multiple threads of an application to create a window of the same class. 
        //It is also possible for the threads to attempt to use the device context simultaneously. 
        //When this happens, the system allows only one thread to successfully finish its drawing operation.
        Class_Device_Context,

        //Sends a double-click message to the window procedure when the user double-clicks the mouse while the cursor is within a window belonging to the class.
        Double_Clicks,

        //Enables the drop shadow effect on a window. The effect is turned on and off through SPI_SETDROPSHADOW. Typically, this is enabled for small, 
        //short-lived windows such as menus to emphasize their Z-order relationship to other windows. 
        //Windows created from a class with this style must be top-level windows; they may not be child windows.
        Drop_Shadow,

        //Indicates that the window class is an application global class. For more information, see the "Application Global Classes" section of About Window Classes.
        Global_Class,

        //Redraws the entire window if a movement or size adjustment changes the width of the client area.
        Horizontal_Redraw,

        //Disables Close on the window menu.
        No_Close,

        //Allocates a unique device context for each window in the class.
        Own_Device_Context,

        //Sets the clipping rectangle of the child window to that of the parent window so that the child can draw on the parent. 
        //A window with the CS_PARENTDC style bit receives a regular device context from the system's cache of device contexts. 
        //It does not give the child the parent's device context or device context settings. Specifying CS_PARENTDC enhances an application's performance.
        Parent_Device_Context,

        //Saves, as a bitmap, the portion of the screen image obscured by a window of this class. When the window is removed, 
        //the system uses the saved bitmap to restore the screen image, including other windows that were obscured. 
        // Therefore, the system does not send WM_PAINT messages to windows that were obscured if the memory used by the 
        // bitmap has not been discarded and if other screen actions have not invalidated the stored image.
        //This style is useful for small windows(for example, menus or dialog boxes) that are displayed brieflyand then removed 
        //before other screen activity takes place.This style increases the time required to display the window, because the system must first allocate memory to store the bitmap.
        Save_Bits,

        //Redraws the entire window if a movement or size adjustment changes the height of the client area.
        Vertical_Redraw
    };

    DEFINE_ENUM_FLAG_OPERATORS(WindowClassStyle);

    template<class Ty, class PlatformTrait>
    concept HasProcedureImpl = requires (Ty self, EventImpl<PlatformTrait> event)
    {
        { self.operator()(event) } -> std::same_as<LRESULT>;
    };

    template<class Ty, class PlatformTraits>
    concept IsWindowClassImpl = requires(Ty self)
    {
        requires std::is_constructible_v<Ty, HWND>;
        requires std::is_move_constructible_v<Ty>;
        requires std::is_move_assignable_v<Ty>;
        requires (HasProcedureImpl<Ty, PlatformTraits> || HasVisitableEventImpl<Ty, PlatformTraits>);
        { Ty::ClassName() } -> std::same_as<typename PlatformTraits::string_type>;
    };

    export template<class Ty>
        concept StyleDefined = requires()
    {
        { Ty::Style() } -> std::same_as<WindowClassStyle>;
    };

    export template<class Ty>
        concept ExtraClassBytesDefined = requires()
    {
        { Ty::ExtraClassBytes() } -> std::same_as<int>;
    };

    export template<class Ty>
        concept ExtraWindowBytesDefined = requires()
    {
        { Ty::ExtraWindowBytes() } -> std::same_as<int>;
    };

    export template<class Ty>
        concept IconDefined = requires(HINSTANCE instance)
    {
        { Ty::Icon(instance) } -> std::same_as<HICON>;
    };

    export template<class Ty>
        concept CursorDefined = requires(HINSTANCE instance)
    {
        { Ty::Cursor(instance) } -> std::same_as<HCURSOR>;
    };

    export template<class Ty>
        concept BackgroundBrushDefined = requires()
    {
        { Ty::BackgroundBrush() } -> std::same_as<HBRUSH>;
    };

    export template<class Ty, class CharTy>
        concept MenuDefined = requires()
    {
        { Ty::MenuName() } -> std::same_as<CharTy>;
    };

    export template<class Ty>
        concept SmallIconDefined = requires(HINSTANCE instance)
    {
        { Ty::SmallIcon(instance) } -> std::same_as<HICON>;
    };

    export template<class PlatformTrait>
        struct DefaultClass;

    struct DefaultClassCommon
    {
        static WindowClassStyle Style() { return {}; }
        static int ExtraClassBytes() { return 0; }
        static int ExtraWindowBytes() { return 0; }
        static HICON Icon(HINSTANCE instance) { return nullptr; }
        static HCURSOR Cursor(HINSTANCE instance) { return nullptr; }
        static HBRUSH BackgroundBrush() { return nullptr; }
        static HICON SmallIcon(HINSTANCE instance) { return nullptr; }
    };


    template<class Ty, class PlatformTrait>
    struct WindowClassTraitsBase
    {
    public:
        using platform_traits = PlatformTrait;
        using class_type = platform_traits::extended_class_type;
        using string_type = platform_traits::string_type;

    private:
        inline static bool registered = false;
        inline static std::atomic<unsigned short> m_instanceCount;
        inline static HINSTANCE m_instance;

        template<class Ty, class Traits>
            requires IsWindowClassImpl<Ty, Traits>
        friend class WindowImpl;

    public:
        static bool Registered()
        {
            return registered;
        }

        static LRESULT DefaultProcedure(EventImpl<platform_traits> e)
        {
            return platform_traits::DefaultProcedure(std::forward<EventImpl<platform_traits>>(e));
        }

        static LRESULT VisitEvent(Ty& self, EventImpl<platform_traits> e)
        {
            return ::MoWin::VisitEvent(self, e, DefaultProcedure);
        }

    private:
        static bool Register(HINSTANCE instance = nullptr)
        {
            if(Registered())
            {
                return true;
            }

            m_instance = instance;

            class_type windowClass;
            windowClass.cbSize = sizeof(class_type);

            if constexpr(StyleDefined<Ty>)
                windowClass.style = static_cast<UINT>(Ty::Style());
            else
                windowClass.style = static_cast<UINT>(DefaultClass<platform_traits>::Style());

            windowClass.lpfnWndProc = &Procedure;

            if constexpr(ExtraClassBytesDefined<Ty>)
                windowClass.cbClsExtra = Ty::ExtraClassBytes();
            else
                windowClass.cbClsExtra = DefaultClass<platform_traits>::ExtraClassBytes();

            if constexpr(ExtraWindowBytesDefined<Ty>)
                windowClass.cbWndExtra = Ty::ExtraWindowBytes();
            else
                windowClass.cbWndExtra = DefaultClass<platform_traits>::ExtraWindowBytes();

            windowClass.hInstance = m_instance;

            if constexpr(IconDefined<Ty>)
                windowClass.hIcon = Ty::Icon(m_instance);
            else
                windowClass.hIcon = DefaultClass<platform_traits>::Icon(m_instance);

            if constexpr(CursorDefined<Ty>)
                windowClass.hCursor = Ty::Cursor(m_instance);
            else
                windowClass.hCursor = DefaultClass<platform_traits>::Cursor(m_instance);

            if constexpr(BackgroundBrushDefined<Ty>)
                windowClass.hbrBackground = Ty::BackgroundBrush();
            else
                windowClass.hbrBackground = DefaultClass<platform_traits>::BackgroundBrush();

            if constexpr(MenuDefined<Ty, string_type>)
                windowClass.lpszMenuName = Ty::MenuName();
            else
                windowClass.lpszMenuName = DefaultClass<platform_traits>::MenuName();

            windowClass.lpszClassName = Ty::ClassName();

            if constexpr(SmallIconDefined<Ty>)
                windowClass.hIconSm = Ty::SmallIcon(m_instance);
            else
                windowClass.hIconSm = DefaultClass<platform_traits>::SmallIcon(m_instance);

            registered = platform_traits::RegisterClass(windowClass) != WindowClassAtom(0);

            if(!registered)
            {
                //Throw
            }

            return registered;
        }

        static void Unregister()
        {
            unsigned short count = m_instanceCount.load();
            if(count == 0)
            {
                if(registered)
                    registered = platform_traits::UnregisterClass(Ty::ClassName(), m_instance);
                return;
            }


            count = --m_instanceCount;

            if(count == 0)
                registered = platform_traits::UnregisterClass(Ty::ClassName(), m_instance);
        }

        static LRESULT Procedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            Ty* self = platform_traits::template GetWindowData<Ty*>(hwnd, GWLP_USERDATA);

            switch(uMsg)
            {
            case WM_NCCREATE:
                m_instanceCount++;
                break;
            case WM_NCDESTROY:
                if(self != nullptr)
                {
                    delete self;
                }

                Unregister();
                break;
            }

            if(self == nullptr)
            {
                return DefaultProcedure(EventImpl<platform_traits>{ hwnd, static_cast<EventType>(uMsg), wParam, lParam });
            }
            else
            {
                if constexpr(HasProcedureImpl<Ty, platform_traits>)
                {
                    return (*self)(EventImpl<platform_traits>{ hwnd, static_cast<EventType>(uMsg), wParam, lParam });
                }
                else
                {
                    return VisitEvent(*self, EventImpl<platform_traits>{ hwnd, static_cast<EventType>(uMsg), wParam, lParam });
                }
            }
        }
    };

    export template<class Ty>
        struct WindowClassTraits;

#pragma endregion Window Class

#pragma region Window
    //https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
    export enum class WindowStyle : DWORD
    {
        //The window has a thin-line border.
        Border = WS_BORDER,

        //The window has a title bar (includes the WS_BORDER style).
        Caption = WS_CAPTION,

        //The window is a child window. A window with this style cannot have a menu bar. This style cannot be used with the WS_POPUP style.
        Child = WS_CHILD,

        //Same as the WS_CHILD style.
        Child_Window = WS_CHILDWINDOW,

        //Excludes the area occupied by child windows when drawing occurs within the parent window. This style is used when creating the parent window.
        Clip_Children = WS_CLIPCHILDREN,

        //Clips child windows relative to each other; that is, when a particular child window receives a WM_PAINT message, the WS_CLIPSIBLINGS style clips all other overlapping child windows out of the region of the child window to be updated. If WS_CLIPSIBLINGS is not specified and child windows overlap, it is possible, when drawing within the client area of a child window, to draw within the client area of a neighboring child window.
        Clip_Siblings = WS_CLIPSIBLINGS,

        //The window is initially disabled. A disabled window cannot receive input from the user. To change this after a window has been created, use the EnableWindow function.
        Disabled = WS_DISABLED,

        //The window has a border of a style typically used with dialog boxes. A window with this style cannot have a title bar.
        Dialog_Frame = WS_DLGFRAME,

        //The window is the first control of a group of controls. The group consists of this first control and all controls defined after it, up to the next control with the WS_GROUP style. The first control in each group usually has the WS_TABSTOP style so that the user can move from group to group. The user can subsequently change the keyboard focus from one control in the group to the next control in the group by using the direction keys.
        //You can turn this style onand off to change dialog box navigation.To change this style after a window has been created, use the SetWindowLong function.
        Group = WS_GROUP,

        //The window has a horizontal scroll bar.
        Horizontal_Scroll = WS_HSCROLL,

        //The window is initially minimized. Same as the WS_MINIMIZE style.
        Iconic = WS_ICONIC,

        //The window is initially maximized.
        Maximize = WS_MAXIMIZE,

        //The window has a maximize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified.
        Maximize_Box = WS_MAXIMIZEBOX,

        //The window is initially minimized. Same as the WS_ICONIC style.
        Minimize = WS_MINIMIZE,

        //The window has a minimize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified.
        Minimize_Box = WS_MINIMIZEBOX,

        //The window is an overlapped window. An overlapped window has a title bar and a border. Same as the WS_TILED style.
        Overlapped = WS_OVERLAPPED,

        //The window is an overlapped window. Same as the WS_TILEDWINDOW style.
        Overlapped_Window = WS_OVERLAPPEDWINDOW,

        //The window is a pop-up window. This style cannot be used with the WS_CHILD style.
        Pop_Up = WS_POPUP,

        //The window is a pop-up window. The WS_CAPTION and WS_POPUPWINDOW styles must be combined to make the window menu visible.
        Pop_Up_Window = WS_POPUPWINDOW,

        //The window has a sizing border. Same as the WS_THICKFRAME style.
        Size_Box = WS_SIZEBOX,

        //The window has a window menu on its title bar. The WS_CAPTION style must also be specified.
        Sys_Menu = WS_SYSMENU,

        //The window is a control that can receive the keyboard focus when the user presses the TAB key. Pressing the TAB key changes the keyboard focus to the next control with the WS_TABSTOP style.
        //You can turn this style onand off to change dialog box navigation.To change this style after a window has been created, use the SetWindowLong function.For user - created windows and modeless dialogs to work with tab stops, alter the message loop to call the IsDialogMessage function.
        Tab_Stop = WS_TABSTOP,

        //The window has a sizing border. Same as the WS_SIZEBOX style.
        Thick_Frame = WS_THICKFRAME,

        //The window is an overlapped window. An overlapped window has a title bar and a border. Same as the WS_OVERLAPPED style.
        Tiled = WS_TILED,

        //The window is an overlapped window. Same as the WS_OVERLAPPEDWINDOW style.
        Tiled_Window = WS_TILEDWINDOW,

        //The window is initially visible.
        //This style can be turned onand off by using the ShowWindow or SetWindowPos function.
        Visible = WS_VISIBLE,

        //The window has a vertical scroll bar.
        Vertical_Scroll = WS_VSCROLL
    };

    DEFINE_ENUM_FLAG_OPERATORS(WindowStyle);

    export enum class WindowStyleEx : DWORD
    {
        Accept_Files = WS_EX_ACCEPTFILES,
        App_Window = WS_EX_APPWINDOW,
        Client_Edge = WS_EX_CLIENTEDGE,
        Composited = WS_EX_COMPOSITED,
        Context_Help = WS_EX_CONTEXTHELP,
        Control_Parent = WS_EX_CONTROLPARENT,
        DLG_Modal_Frame = WS_EX_DLGMODALFRAME,
        Layered = WS_EX_LAYERED,
        Layout_RTL = WS_EX_LAYOUTRTL,
        Left = WS_EX_LEFT,
        Left_Scroll_Bar = WS_EX_LEFTSCROLLBAR,
        Left_To_Right_Reading = WS_EX_LTRREADING,
        MDI_Child = WS_EX_MDICHILD,
        No_Activate = WS_EX_NOACTIVATE,
        No_Inherit_Layout = WS_EX_NOINHERITLAYOUT,
        No_Parent_Notify = WS_EX_NOPARENTNOTIFY,
        No_Direction_Bitmap = WS_EX_NOREDIRECTIONBITMAP,
        Overlapped_Window = WS_EX_OVERLAPPEDWINDOW,
        Palette_Window = WS_EX_PALETTEWINDOW,
        Right = WS_EX_RIGHT,
        Right_Scroll_Bar = WS_EX_RIGHTSCROLLBAR,
        Right_To_Left_Reading = WS_EX_RTLREADING,
        Static_Edge = WS_EX_STATICEDGE,
        Tool_Window = WS_EX_TOOLWINDOW,
        Top_Most = WS_EX_TOPMOST,
        Transparent = WS_EX_TRANSPARENT,
        Window_Edge = WS_EX_WINDOWEDGE
    };

    DEFINE_ENUM_FLAG_OPERATORS(WindowStyleEx);


    template<class DerivedSelf, class PlatformTrait>
    struct WindowInterface
    {
        using platform_traits = PlatformTrait;

        LRESULT SendMessage(EventType event, WPARAM wParam, LPARAM lParam) const
        {
            platform_traits::SendMessage(Handle(), event, wParam, lParam);
        }

        //TODO: Do something about lpdwResult out parameter and the flags
        LRESULT SendMessageTimeout(EventType event, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult) const
        {
            platform_traits::SendMessageTimeout(Handle(), event, wParam, lParam, fuFlags, uTimeout, lpdwResult);
        }

        LRESULT SendNotifyMessage(EventType event, WPARAM wParam, LPARAM lParam) const
        {
            platform_traits::SendNotifyMessage(Handle(), event, wParam, lParam);
        }

        //TODO: Maybe do something about the asyn callback
        BOOL SendMessageCallback(
            EventType event,
            WPARAM wParam,
            LPARAM lParam,
            SENDASYNCPROC lpResultCallBack,
            ULONG_PTR dwData) const
        {
            platform_traits::SendMessageCallback(Handle(), event, wParam, lParam, lpResultCallBack, dwData);
        }

        BOOL IsChildOf(HWND parent) const
        {
            return ::IsChild(parent, Handle());
        }

        void Hide() const
        {
            ::ShowWindow(Handle(), SW_HIDE);
        }

        void Show() const
        {
            ::ShowWindow(Handle(), SW_SHOW);
        }

        void Minimize() const
        {
            ::ShowWindow(Handle(), SW_MINIMIZE);
        }

        void Maximize() const
        {
            ::ShowWindow(Handle(), SW_MAXIMIZE);
        }

        void Restore() const
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
        RECT GetClientRect() const
        {
            RECT rect;
            ::GetClientRect(Handle(), &rect);
            return rect;
        }

        RECT GetWindowRect() const
        {
            RECT rect;
            ::GetWindowRect(Handle(), &rect);
            return rect;
        }
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
        HWND Handle() const { return *(static_cast<const DerivedSelf*>(this)); }
    };

    export enum class WindowCreateFlag
    {
        None = 0,
        Adjust_Size_For_Client = 1 << 0
    };
    DEFINE_ENUM_FLAG_OPERATORS(WindowCreateFlag);

    export template<class Ty, class PlatformTrait>
        requires IsWindowClassImpl<Ty, PlatformTrait>
    class WindowImpl : public WindowInterface<WindowImpl<Ty, PlatformTrait>, PlatformTrait>
    {
    public:
        using class_traits = WindowClassTraits<Ty>;
        using platform_traits = PlatformTrait;
        using string_type = platform_traits::string_type;

    private:
        HWND m_windowHandle;

    public:
        template<class... Params>
        WindowImpl(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, POINT position, Dimension2D lengths, HWND optionalParent, HMENU menu, HINSTANCE hInstance, WindowCreateFlag flags, Params&&... params) :
            m_windowHandle(CreateHandle(extendedStyle, windowName, style, Rect{ position, lengths }, optionalParent, menu, hInstance, flags))
        {
            Ty* data = new Ty(m_windowHandle, std::forward<Params>(params)...);
            platform_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, data);
        }

        template<class... Params>
        WindowImpl(string_type windowName, WindowStyle style, POINT position, Dimension2D lengths, HWND optionalParent, HMENU menu, HINSTANCE hInstance, WindowCreateFlag flags, Params&&... params) :
            WindowImpl(WindowStyleEx{ 0 }, windowName, style, position, lengths, optionalParent, menu, hInstance, flags, std::forward<Params>(params)...)
        {

        }

        WindowImpl(const WindowImpl& other) = delete;
        WindowImpl(WindowImpl&& other) noexcept :
            m_windowHandle(std::move(other.m_windowHandle))
        {
            other.m_windowHandle = nullptr;

            SetLastError(0);
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

            SetLastError(0);
            if(GetLastError() == ERROR_INVALID_WINDOW_HANDLE)
            {
                //Do nothing
            }
            return *this;
        }

        bool operator==(std::nullptr_t) const { return ::IsWindow(m_windowHandle); }
        bool operator!=(std::nullptr_t) const { return ::IsWindow(m_windowHandle); }

        ~WindowImpl()
        {
            DestroyWindow(m_windowHandle);
        }



    public:
        operator HWND() const { return m_windowHandle; }

    public:
        Ty& ClassData() { return *platform_traits::template GetWindowData<Ty*>(m_windowHandle, GWLP_USERDATA); }
        const Ty& ClassData() const { return *platform_traits::template GetWindowData<Ty*>(m_windowHandle, GWLP_USERDATA); }

    private:
        HWND CreateHandle(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, Rect windowRect, HWND optionalParent, HMENU menu, HINSTANCE hInstance, WindowCreateFlag flags)
        {
            if(!class_traits::Register(hInstance))
            {
                throw std::exception("Failed to register class");
            }

            if((flags & WindowCreateFlag::Adjust_Size_For_Client) == WindowCreateFlag::Adjust_Size_For_Client)
            {
                ::AdjustWindowRectEx(&windowRect, static_cast<DWORD>(style), menu != nullptr, static_cast<DWORD>(extendedStyle));
            }

            HWND handle = platform_traits::CreateWindow(extendedStyle, Ty::ClassName(), windowName, style, windowRect.left, windowRect.top, windowRect.Lengths().width, windowRect.Lengths().height, optionalParent, menu, hInstance, nullptr);

            Rect rect;
            ::GetWindowRect(handle, &rect);

            if(handle == nullptr)
            {
                throw std::exception("Handle is null");
            }

            return handle;
        }
    };

#pragma endregion Window
}