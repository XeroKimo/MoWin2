module;

#include <concepts>
#include <bit>   
#include <Windows.h>

export module MoWin:Events;
import :Platform.Common;

namespace MoWin
{

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

    export template<EventCatagoryType Type, class PlatformTrait>
    struct EventCategoryImpl;

    export struct EventBase
    {
        HWND window;
        EventType type;
        WPARAM wParam;
        LPARAM lParam;
    };

    export template<EventType Type, class PlatformTrait>
    struct TypedEventImpl : public EventBase
    {
    };

    export template<class PlatformTrait>
    struct EventImpl : public EventBase
    {
        using platform_traits = PlatformTrait;
        using KeyboardInputNotifications = EventCategoryImpl<EventCatagoryType::Keyboard_Notfications, PlatformTrait>;
        using WindowNotifications = EventCategoryImpl<EventCatagoryType::Window_Notifications, PlatformTrait>;
        using All = EventCategoryImpl<EventCatagoryType::All, PlatformTrait>;
    };

    template<class Func, class RetVal, class... Args>
    concept invocable_r = std::is_invocable_r_v<RetVal, Func, Args...>;

    template<class Ty>
    constexpr bool is_event_impl = false;    
    
    template<class PlatformTrait>
    constexpr bool is_event_impl<EventImpl<PlatformTrait>> = true;

    template<class Ty>
    concept IsEvent = is_event_impl<Ty>;

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
    struct TypedEventImpl<EventType::Activate_App, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        bool Activated() const noexcept { return wParam; }
        DWORD ThreadID() const noexcept { return static_cast<DWORD>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Cancel_Mode, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Child_Activate, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Close, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Compacting, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Create, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        auto CreateParams() const noexcept
        {
            return (*reinterpret_cast<typename PlatformTrait::window_create_struct_type*>(lParam));
        }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Destroy, PlatformTrait> : public EventBase
    {

    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Enable, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        bool Enabled() const noexcept { return wParam; }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Enter_Size_Move, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Exit_Size_Move, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Get_Icon, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

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
    struct TypedEventImpl<EventType::Get_Min_Max_Info, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        MINMAXINFO& MinMaxInfo() const noexcept { return *reinterpret_cast<MINMAXINFO*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Input_Language_Change, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        WPARAM CodePage() const noexcept { return wParam; }
        WORD LanguageIdentifier() const noexcept { return LOWORD(lParam); }
        WORD DeviceHandle() const noexcept { return HIWORD(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Input_Language_Change_Request, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        bool IsChangeBackward() const noexcept { return wParam & INPUTLANGCHANGE_BACKWARD; }
        bool IsChangeForward() const noexcept { return wParam & INPUTLANGCHANGE_FORWARD; }
        bool IsSystemCharacterSet() const noexcept { return wParam & INPUTLANGCHANGE_SYSCHARSET; }
        WORD LanguageIdentifier() const noexcept { return LOWORD(lParam); }
        WORD DeviceHandle() const noexcept { return HIWORD(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Move, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        WORD Left() { return LOWORD(lParam); }
        WORD Top() { return HIWORD(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Moving, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        RECT& Rect() const noexcept { return *reinterpret_cast<RECT*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Nonclient_Activate, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        bool Active() const noexcept { return wParam; }
        bool RedrawWindow() const noexcept { return lParam != -1; }
        //TODO: Figure out the how to interpret the update region of the non-client area using the lParam https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-ncactivate
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Nonclient_Calculate_Size, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        //bool
        NCCALCSIZE_PARAMS& Params() const noexcept { return *reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam); }
        RECT& Rect() const noexcept { return *reinterpret_cast<RECT*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Nonclient_Create, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        auto CreateParams() const noexcept
        {
            return (*reinterpret_cast<typename PlatformTrait::window_create_struct_type*>(lParam));
        }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Nonclient_Destroy, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Null, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::QueryDragIcon, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::QueryOpen, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Quit, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::ShowWindow, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        bool Shown() const noexcept { return wParam; }
        bool ParentClosing() const noexcept { return lParam == SW_PARENTCLOSING; }
        bool OtherZoom() const noexcept { return lParam == SW_OTHERZOOM; }
        bool ParentOpening() const noexcept { return lParam == SW_PARENTOPENING; }
        bool OtherUnzoom() const noexcept { return lParam == SW_OTHERUNZOOM; }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Size, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        bool Restored() const noexcept { return wParam == SIZE_RESTORED; }
        bool Minimized() const noexcept { return wParam == SIZE_MINIMIZED; }
        bool Maximized() const noexcept { return wParam == SIZE_MAXIMIZED; }
        bool MaxShow() const noexcept { return wParam == SIZE_MAXSHOW; }
        bool MaxHide() const noexcept { return wParam == SIZE_MAXHIDE; }

        WORD Width() const noexcept { return LOWORD(lParam); }
        WORD Height() const noexcept { return HIWORD(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Sizing, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

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
        RECT& Rect() const noexcept { return *reinterpret_cast<RECT*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Style_Changed, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        bool IsExtendedStyle() const noexcept { return wParam == GWL_EXSTYLE; }
        const STYLESTRUCT& Data() const noexcept { return *reinterpret_cast<const STYLESTRUCT*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Style_Changing, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        bool IsExtendedStyle() const noexcept { return wParam == GWL_EXSTYLE; }
        const STYLESTRUCT& Data() const noexcept { return *reinterpret_cast<const STYLESTRUCT*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Theme_Changed, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::User_Changed, PlatformTrait> : public EventBase
    {
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Window_Position_Changed, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        WINDOWPOS& Data() const noexcept { return *reinterpret_cast<WINDOWPOS*>(lParam); }
    };
    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Window_Position_Changing, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        WINDOWPOS& Data() const noexcept { return *reinterpret_cast<WINDOWPOS*>(lParam); }
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
    struct TypedEventImpl<EventType::Activate, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        bool Inactive() const noexcept { return wParam == WA_INACTIVE; }
        bool Active() const noexcept { return wParam == WA_ACTIVE; }
        bool ClickActive() const noexcept { return wParam == WA_CLICKACTIVE; }

        //A handle to the window being activated or deactivated, depending on the value of the wParam parameter. 
        //If Inactive(), OtherWindow() is the handle to the window being activated. 
        //If Active() or ClickActive(), OtherWindow() is the handle to the window being deactivated. This handle can be NULL.
        HWND OtherWindow() const noexcept { return reinterpret_cast<HWND>(lParam); }
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
    struct TypedEventImpl<EventType::Application_Command, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        HWND AffectedWindow() const noexcept { return reinterpret_cast<HWND>(wParam); }
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
    struct TypedEventImpl<EventType::Char, PlatformTrait> : public EventBase, public KeyMessage<TypedEventImpl<EventType::Char, PlatformTrait>>
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

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
    struct TypedEventImpl<EventType::Dead_Char, PlatformTrait> : public EventBase, public KeyMessage<TypedEventImpl<EventType::Dead_Char, PlatformTrait>>
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

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
    struct TypedEventImpl<EventType::Hotkey, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

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
    struct TypedEventImpl<EventType::Key_Down, PlatformTrait> : public EventBase, public VirtualKeyMessage<TypedEventImpl<EventType::Key_Down, PlatformTrait>>
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Key_Up, PlatformTrait> : public EventBase, public VirtualKeyMessage<TypedEventImpl<EventType::Key_Up, PlatformTrait>>
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Kill_Focus, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        HWND OtherWindow() const noexcept { return reinterpret_cast<HWND>(wParam); }
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Set_Focus, PlatformTrait> : public EventBase
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

        HWND OtherWindow() const noexcept { return reinterpret_cast<HWND>(wParam); }
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::System_Dead_Char, PlatformTrait> : public EventBase, public VirtualKeyMessage<TypedEventImpl<EventType::System_Dead_Char, PlatformTrait>>
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;

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
    struct TypedEventImpl<EventType::System_Key_Down, PlatformTrait> : public EventBase, public VirtualKeyMessage<TypedEventImpl<EventType::System_Key_Down, PlatformTrait>>
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::System_Key_Up, PlatformTrait> : public EventBase, public VirtualKeyMessage<TypedEventImpl<EventType::System_Key_Up, PlatformTrait>>
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;
    };

    template<class PlatformTrait>
    struct TypedEventImpl<EventType::Unicode_Char, PlatformTrait> : public EventBase, public KeyMessage<TypedEventImpl<EventType::Unicode_Char, PlatformTrait>>
    {
        using EventBase::window;
        using EventBase::type;
        using EventBase::wParam;
        using EventBase::lParam;


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

    template<EventType Type, IsEvent EventTy, invocable_r<LRESULT, EventTy> Func, invocable_r<LRESULT, EventTy> DefaultFunc>
    LRESULT VisitEventImpl(Func&& visitor, EventTy&& event, DefaultFunc&& defaultFunc)
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

    export template<IsEvent EventTy, invocable_r<LRESULT, EventTy> Func, invocable_r<LRESULT, EventTy> DefaultFunc>
    LRESULT VisitEvent(Func&& visitor, EventTy&& event, DefaultFunc&& defaultFunc)
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
}