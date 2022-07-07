module;
#include <concepts>

#include <Windows.h>
#include <memory>
#include <atomic>
#include <bit>

export module MoWin.Window:Common;

#undef RegisterClass
#undef UnregisterClass
#undef CreateWindow

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
};

//Events
export namespace MoWin
{
    enum class EventType : UINT
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

    enum class EventCatagoryType
    {
        Window_Notifications,
        Keyboard_Notfications,
        All = 255
    };

    template<EventType Type>
    struct TypedEvent;

    template<EventCatagoryType Type>
    struct EventCategory;

    struct EventBase
    {
        HWND window;
        EventType type;
        WPARAM wParam;
        LPARAM lParam;
    };

    struct Event : public EventBase
    {
        using KeyboardInputNotifications = EventCategory<EventCatagoryType::Keyboard_Notfications>;
        using WindowNotifications = EventCategory<EventCatagoryType::Window_Notifications>;
        using All = EventCategory<EventCatagoryType::All>;
    };


#pragma region Event Categories

    template<>
    struct EventCategory<EventCatagoryType::Window_Notifications>
    {
        using ActivateApp = TypedEvent<EventType::Activate_App>;
        using CancelMode = TypedEvent<EventType::Cancel_Mode>;
        using ChildActivate = TypedEvent<EventType::Child_Activate>;
        using Close = TypedEvent<EventType::Close>;
        using Compacting = TypedEvent<EventType::Compacting>;
        using Create = TypedEvent<EventType::Create>;
        using Destroy = TypedEvent<EventType::Destroy>;
        using Enable = TypedEvent<EventType::Enable>;
        using EnterSizeMove = TypedEvent<EventType::Enter_Size_Move>;
        using ExitSizeMove = TypedEvent<EventType::Exit_Size_Move>;
        using GetIcon = TypedEvent<EventType::Get_Icon>;
        using GetMinMaxInfo = TypedEvent<EventType::Get_Min_Max_Info>;
        using InputLanguageChange = TypedEvent<EventType::Input_Language_Change>;
        using InputLanguageChangeRequest = TypedEvent<EventType::Input_Language_Change_Request>;
        using Move = TypedEvent<EventType::Move>;
        using Moving = TypedEvent<EventType::Moving>;
        using NonclientActivate = TypedEvent<EventType::Nonclient_Activate>;
        using NonclientCalculateSize = TypedEvent<EventType::Nonclient_Calculate_Size>;
        using NonclientCreate = TypedEvent<EventType::Nonclient_Create>;
        using NonclientDestroy = TypedEvent<EventType::Nonclient_Destroy>;
        using Null = TypedEvent<EventType::Null>;
        using QueryDragIcon = TypedEvent<EventType::QueryDragIcon>;
        using QueryOpen = TypedEvent<EventType::QueryOpen>;
        using Quit = TypedEvent<EventType::Quit>;
        using ShowWindow = TypedEvent<EventType::ShowWindow>;
        using Size = TypedEvent<EventType::Size>;
        using Sizing = TypedEvent<EventType::Sizing>;
        using StyleChanged = TypedEvent<EventType::Style_Changed>;
        using StyleChanging = TypedEvent<EventType::Style_Changing>;
        using ThemeChanged = TypedEvent<EventType::Theme_Changed>;
        using UsedChanged = TypedEvent<EventType::User_Changed>;
        using WindowPositonChanged = TypedEvent<EventType::Window_Position_Changed>;
        using WindowPositionChanging = TypedEvent<EventType::Window_Position_Changing>;
    };

    template<>
    struct EventCategory<EventCatagoryType::Keyboard_Notfications>
    {
        using Activate = TypedEvent<EventType::Activate>;
        using ApplicationCommand = TypedEvent<EventType::Application_Command>;
        using Char = TypedEvent<EventType::Char>;
        using DeadChar = TypedEvent<EventType::Dead_Char>;
        using Hotkey = TypedEvent<EventType::Hotkey>;
        using KeyDown = TypedEvent<EventType::Key_Down>;
        using KeyUp = TypedEvent<EventType::Key_Up>;
        using KillFocus = TypedEvent<EventType::Kill_Focus>;
        using SetFocus = TypedEvent<EventType::Set_Focus>;
        using SystemDeadChar = TypedEvent<EventType::System_Dead_Char>;
        using SystemKeyDown = TypedEvent<EventType::System_Key_Down>;
        using SystemKeyUp = TypedEvent<EventType::System_Key_Up>;
        using UnicodeChar = TypedEvent<EventType::Unicode_Char>;
    };


    template<>
    struct EventCategory<EventCatagoryType::All>
    {
        //Window notification events
        using ActivateApp = TypedEvent<EventType::Activate_App>;
        using CancelMode = TypedEvent<EventType::Cancel_Mode>;
        using ChildActivate = TypedEvent<EventType::Child_Activate>;
        using Close = TypedEvent<EventType::Close>;
        using Compacting = TypedEvent<EventType::Compacting>;
        using Create = TypedEvent<EventType::Create>;
        using Destroy = TypedEvent<EventType::Destroy>;
        using Enable = TypedEvent<EventType::Enable>;
        using EnterSizeMove = TypedEvent<EventType::Enter_Size_Move>;
        using ExitSizeMove = TypedEvent<EventType::Exit_Size_Move>;
        using GetIcon = TypedEvent<EventType::Get_Icon>;
        using GetMinMaxInfo = TypedEvent<EventType::Get_Min_Max_Info>;
        using InputLanguageChange = TypedEvent<EventType::Input_Language_Change>;
        using InputLanguageChangeRequest = TypedEvent<EventType::Input_Language_Change_Request>;
        using Move = TypedEvent<EventType::Move>;
        using Moving = TypedEvent<EventType::Moving>;
        using NonclientActivate = TypedEvent<EventType::Nonclient_Activate>;
        using NonclientCalculateSize = TypedEvent<EventType::Nonclient_Calculate_Size>;
        using NonclientCreate = TypedEvent<EventType::Nonclient_Create>;
        using NonclientDestroy = TypedEvent<EventType::Nonclient_Destroy>;
        using Null = TypedEvent<EventType::Null>;
        using QueryDragIcon = TypedEvent<EventType::QueryDragIcon>;
        using QueryOpen = TypedEvent<EventType::QueryOpen>;
        using Quit = TypedEvent<EventType::Quit>;
        using ShowWindow = TypedEvent<EventType::ShowWindow>;
        using Size = TypedEvent<EventType::Size>;
        using Sizing = TypedEvent<EventType::Sizing>;
        using StyleChanged = TypedEvent<EventType::Style_Changed>;
        using StyleChanging = TypedEvent<EventType::Style_Changing>;
        using ThemeChanged = TypedEvent<EventType::Theme_Changed>;
        using UsedChanged = TypedEvent<EventType::User_Changed>;
        using WindowPosChanged = TypedEvent<EventType::Window_Position_Changed>;
        using WindowPosChanging = TypedEvent<EventType::Window_Position_Changing>;

        //Keyboard Input Notifications events
        using Activate = TypedEvent<EventType::Activate>;
        using ApplicationCommand = TypedEvent<EventType::Application_Command>;
        using Char = TypedEvent<EventType::Char>;
        using DeadChar = TypedEvent<EventType::Dead_Char>;
        using Hotkey = TypedEvent<EventType::Hotkey>;
        using KeyDown = TypedEvent<EventType::Key_Down>;
        using KeyUp = TypedEvent<EventType::Key_Up>;
        using KillFocus = TypedEvent<EventType::Kill_Focus>;
        using SetFocus = TypedEvent<EventType::Set_Focus>;
        using SystemDeadChar = TypedEvent<EventType::System_Dead_Char>;
        using SystemKeyDown = TypedEvent<EventType::System_Key_Down>;
        using SystemKeyUp = TypedEvent<EventType::System_Key_Up>;
        using UnicodeChar = TypedEvent<EventType::Unicode_Char>;
    };
#pragma endregion

#pragma region Window Notification Events

    template<class Func>
    concept VisitableWindowNotifications =
        std::invocable<Func, TypedEvent<EventType::Activate_App>> ||
        std::invocable<Func, TypedEvent<EventType::Cancel_Mode>> ||
        std::invocable<Func, TypedEvent<EventType::Child_Activate>> ||
        std::invocable<Func, TypedEvent<EventType::Close>> ||
        std::invocable<Func, TypedEvent<EventType::Compacting>> ||
        std::invocable<Func, TypedEvent<EventType::Create>> ||
        std::invocable<Func, TypedEvent<EventType::Destroy>> ||
        std::invocable<Func, TypedEvent<EventType::Enable>> ||
        std::invocable<Func, TypedEvent<EventType::Enter_Size_Move>> ||
        std::invocable<Func, TypedEvent<EventType::Exit_Size_Move>> ||
        std::invocable<Func, TypedEvent<EventType::Get_Icon>> ||
        std::invocable<Func, TypedEvent<EventType::Get_Min_Max_Info>> ||
        std::invocable<Func, TypedEvent<EventType::Input_Language_Change>> ||
        std::invocable<Func, TypedEvent<EventType::Input_Language_Change_Request>> ||
        std::invocable<Func, TypedEvent<EventType::Move>> ||
        std::invocable<Func, TypedEvent<EventType::Moving>> ||
        std::invocable<Func, TypedEvent<EventType::Nonclient_Activate>> ||
        std::invocable<Func, TypedEvent<EventType::Nonclient_Calculate_Size>> ||
        std::invocable<Func, TypedEvent<EventType::Nonclient_Create>> ||
        std::invocable<Func, TypedEvent<EventType::Nonclient_Destroy>> ||
        std::invocable<Func, TypedEvent<EventType::Null>> ||
        std::invocable<Func, TypedEvent<EventType::QueryDragIcon>> ||
        std::invocable<Func, TypedEvent<EventType::QueryOpen>> ||
        std::invocable<Func, TypedEvent<EventType::Quit>> ||
        std::invocable<Func, TypedEvent<EventType::ShowWindow>> ||
        std::invocable<Func, TypedEvent<EventType::Size>> ||
        std::invocable<Func, TypedEvent<EventType::Sizing>> ||
        std::invocable<Func, TypedEvent<EventType::Style_Changed>> ||
        std::invocable<Func, TypedEvent<EventType::Style_Changing>> ||
        std::invocable<Func, TypedEvent<EventType::Theme_Changed>> ||
        std::invocable<Func, TypedEvent<EventType::User_Changed>> ||
        std::invocable<Func, TypedEvent<EventType::Window_Position_Changed>> ||
        std::invocable<Func, TypedEvent<EventType::Window_Position_Changing>>;

    template<>
    struct TypedEvent<EventType::Activate_App> : public EventBase
    {
        bool Activated() const { return wParam; }
        DWORD ThreadID() const { return static_cast<DWORD>(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Cancel_Mode> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::Child_Activate> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::Close> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::Compacting> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::Create> : public EventBase
    {
        template<Platform P, CharacterSet C>
        auto CreateParams() const
        {
            return (*std::bit_cast<typename PlatformTraits<P, C>::window_create_struct_type*>(lParam));
        }
    };
    template<>
    struct TypedEvent<EventType::Destroy> : public EventBase
    {

    };
    template<>
    struct TypedEvent<EventType::Enable> : public EventBase
    {
        bool Enabled() const { return wParam; }
    };
    template<>
    struct TypedEvent<EventType::Enter_Size_Move> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::Exit_Size_Move> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::Get_Icon> : public EventBase
    {
        enum class IconSize
        {
            Small = 0,
            Big = 1,
            Small_2 = 2
        };

        IconSize Size() const { return static_cast<IconSize>(wParam); }
        WORD DPI() const { return static_cast<WORD>(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Get_Min_Max_Info> : public EventBase
    {
        MINMAXINFO& MinMaxInfo() const { return *std::bit_cast<MINMAXINFO*>(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Input_Language_Change> : public EventBase
    {
        WPARAM CodePage() const { return wParam; }
        WORD LanguageIdentifier() const { return LOWORD(lParam); }
        WORD DeviceHandle() const { return HIWORD(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Input_Language_Change_Request> : public EventBase
    {
        bool IsChangeBackward() const { return wParam & INPUTLANGCHANGE_BACKWARD; }
        bool IsChangeForward() const { return wParam & INPUTLANGCHANGE_FORWARD; }
        bool IsSystemCharacterSet() const { return wParam & INPUTLANGCHANGE_SYSCHARSET; }
        WORD LanguageIdentifier() const { return LOWORD(lParam); }
        WORD DeviceHandle() const { return HIWORD(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Move> : public EventBase
    {
        WORD Left() { return LOWORD(lParam); }
        WORD Top() { return HIWORD(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Moving> : public EventBase
    {
        RECT& Rect() const { return *std::bit_cast<RECT*>(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Nonclient_Activate> : public EventBase
    {
        bool Active() const { return wParam; }
        bool RedrawWindow() const { return lParam != -1; }
        //TODO: Figure out the how to interpret the update region of the non-client area using the lParam https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-ncactivate
    };
    template<>
    struct TypedEvent<EventType::Nonclient_Calculate_Size> : public EventBase
    {
        //bool
        NCCALCSIZE_PARAMS& Params() const { return *std::bit_cast<NCCALCSIZE_PARAMS*>(lParam); }
        RECT& Rect() const { return *std::bit_cast<RECT*>(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Nonclient_Create> : public EventBase
    {
        template<Platform P, CharacterSet C>
        auto CreateParams() const
        {
            return (*std::bit_cast<typename PlatformTraits<P, C>::window_create_struct_type*>(lParam));
        }
    };
    template<>
    struct TypedEvent<EventType::Nonclient_Destroy> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::Null> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::QueryDragIcon> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::QueryOpen> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::Quit> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::ShowWindow> : public EventBase
    {
        bool Shown() const { return wParam; }
        bool ParentClosing() const { return lParam == SW_PARENTCLOSING; }
        bool OtherZoom() const { return lParam == SW_OTHERZOOM; }
        bool ParentOpening() const { return lParam == SW_PARENTOPENING; }
        bool OtherUnzoom() const { return lParam == SW_OTHERUNZOOM; }
    };
    template<>
    struct TypedEvent<EventType::Size> : public EventBase
    {
        bool Restored() const { return wParam == SIZE_RESTORED; }
        bool Minimized() const { return wParam == SIZE_MINIMIZED; }
        bool Maximized() const { return wParam == SIZE_MAXIMIZED; }
        bool MaxShow() const { return wParam == SIZE_MAXSHOW; }
        bool MaxHide() const { return wParam == SIZE_MAXHIDE; }

        WORD Width() const { return LOWORD(lParam); }
        WORD Height() const { return HIWORD(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Sizing> : public EventBase
    {
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
        ResizeEdge SelectedEdge() const { return static_cast<ResizeEdge>(wParam); }
        RECT& Rect() const { return *std::bit_cast<RECT*>(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Style_Changed> : public EventBase
    {
        bool IsExtendedStyle() const { return wParam == GWL_EXSTYLE; }
        const STYLESTRUCT& Data() const { return *std::bit_cast<const STYLESTRUCT*>(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Style_Changing> : public EventBase
    {
        bool IsExtendedStyle() const { return wParam == GWL_EXSTYLE; }
        const STYLESTRUCT& Data() const { return *std::bit_cast<const STYLESTRUCT*>(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Theme_Changed> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::User_Changed> : public EventBase
    {
    };
    template<>
    struct TypedEvent<EventType::Window_Position_Changed> : public EventBase
    {
        WINDOWPOS& Data() const { return *std::bit_cast<WINDOWPOS*>(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Window_Position_Changing> : public EventBase
    {
        WINDOWPOS& Data() const { return *std::bit_cast<WINDOWPOS*>(lParam); }
    };

#pragma endregion

#pragma region Keyyboard Notificaiton Events
    template<class Func>
    concept VisitableKeyboardNotifications =
        std::invocable<Func, TypedEvent<EventType::Activate>> ||
        std::invocable<Func, TypedEvent<EventType::Application_Command>> ||
        std::invocable<Func, TypedEvent<EventType::Char>> ||
        std::invocable<Func, TypedEvent<EventType::Dead_Char>> ||
        std::invocable<Func, TypedEvent<EventType::Hotkey>> ||
        std::invocable<Func, TypedEvent<EventType::Key_Down>> ||
        std::invocable<Func, TypedEvent<EventType::Key_Up>> ||
        std::invocable<Func, TypedEvent<EventType::Kill_Focus>> ||
        std::invocable<Func, TypedEvent<EventType::Set_Focus>> ||
        std::invocable<Func, TypedEvent<EventType::System_Dead_Char>> ||
        std::invocable<Func, TypedEvent<EventType::System_Key_Down>> ||
        std::invocable<Func, TypedEvent<EventType::System_Key_Up>> ||
        std::invocable<Func, TypedEvent<EventType::Unicode_Char>>;

    template<>
    struct TypedEvent<EventType::Activate> : public EventBase
    {
        bool Inactive() const { return wParam == WA_INACTIVE; }
        bool Active() const { return wParam == WA_ACTIVE; }
        bool ClickActive() const { return wParam == WA_CLICKACTIVE; }

        //A handle to the window being activated or deactivated, depending on the value of the wParam parameter. 
        //If Inactive(), OtherWindow() is the handle to the window being activated. 
        //If Active() or ClickActive(), OtherWindow() is the handle to the window being deactivated. This handle can be NULL.
        HWND OtherWindow() const { return std::bit_cast<HWND>(lParam); }
    };
    template<>
    struct TypedEvent<EventType::Application_Command> : public EventBase
    {
        HWND AffectedWindow() const { return std::bit_cast<HWND>(wParam); }


    };
    using Char = TypedEvent<EventType::Char>;
    using DeadChar = TypedEvent<EventType::Dead_Char>;
    using Hotkey = TypedEvent<EventType::Hotkey>;
    using KeyDown = TypedEvent<EventType::Key_Down>;
    using KeyUp = TypedEvent<EventType::Key_Up>;
    using KillFocus = TypedEvent<EventType::Kill_Focus>;
    using SetFocus = TypedEvent<EventType::Set_Focus>;
    using SystemDeadChar = TypedEvent<EventType::System_Dead_Char>;
    using SystemKeyDown = TypedEvent<EventType::System_Key_Down>;
    using SystemKeyUp = TypedEvent<EventType::System_Key_Up>;
    using UnicodeChar = TypedEvent<EventType::Unicode_Char>;

#pragma endregion

    template<class Func, EventType E>
    concept VisitableEvent = std::invocable<Func, TypedEvent<E>>;

    template<class Func>
    concept HasVisitableEvent = VisitableWindowNotifications<Func> ||
        VisitableKeyboardNotifications<Func>;


    template<EventType Type, class Func, std::invocable<Event> DefaultFunc>
    LRESULT VisitEventImpl(Func&& visitor, Event&& event, DefaultFunc&& defaultFunc)
    {
        if constexpr(VisitableEvent<Func, Type>)
        {
            return visitor(std::bit_cast<TypedEvent<Type>>(event));
        }
        else
        {
            return defaultFunc(std::forward<Event>(event));
        }
    }

    template<class Func, std::invocable<Event> DefaultFunc>
    LRESULT VisitEvent(Func&& visitor, Event&& event, DefaultFunc&& defaultFunc)
    {
        switch(event.type)
        {
#pragma region Window Notification Event cases
        case EventType::Activate_App:
            return VisitEventImpl<EventType::Activate_App>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Cancel_Mode:
            return VisitEventImpl<EventType::Cancel_Mode>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Child_Activate:
            return VisitEventImpl<EventType::Child_Activate>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Close:
            return VisitEventImpl<EventType::Close>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Compacting:
            return VisitEventImpl<EventType::Compacting>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Create:
            return VisitEventImpl<EventType::Create>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Destroy:
            return VisitEventImpl<EventType::Destroy>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Enable:
            return VisitEventImpl<EventType::Enable>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Enter_Size_Move:
            return VisitEventImpl<EventType::Enter_Size_Move>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Exit_Size_Move:
            return VisitEventImpl<EventType::Exit_Size_Move>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Get_Icon:
            return VisitEventImpl<EventType::Get_Icon>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Get_Min_Max_Info:
            return VisitEventImpl<EventType::Get_Min_Max_Info>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Input_Language_Change:
            return VisitEventImpl<EventType::Input_Language_Change>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Input_Language_Change_Request:
            return VisitEventImpl<EventType::Input_Language_Change_Request>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Move:
            return VisitEventImpl<EventType::Move>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Moving:
            return VisitEventImpl<EventType::Moving>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Nonclient_Activate:
            return VisitEventImpl<EventType::Nonclient_Activate>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Nonclient_Calculate_Size:
            return VisitEventImpl<EventType::Nonclient_Calculate_Size>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Nonclient_Create:
            return VisitEventImpl<EventType::Nonclient_Create>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Nonclient_Destroy:
            return VisitEventImpl<EventType::Nonclient_Destroy>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Null:
            return VisitEventImpl<EventType::Null>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::QueryDragIcon:
            return VisitEventImpl<EventType::QueryDragIcon>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::QueryOpen:
            return VisitEventImpl<EventType::QueryOpen>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Quit:
            return VisitEventImpl<EventType::Quit>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::ShowWindow:
            return VisitEventImpl<EventType::ShowWindow>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Size:
            return VisitEventImpl<EventType::Size>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Sizing:
            return VisitEventImpl<EventType::Sizing>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Style_Changed:
            return VisitEventImpl<EventType::Style_Changed>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Style_Changing:
            return VisitEventImpl<EventType::Style_Changing>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Theme_Changed:
            return VisitEventImpl<EventType::Theme_Changed>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::User_Changed:
            return VisitEventImpl<EventType::User_Changed>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Window_Position_Changed:
            return VisitEventImpl<EventType::Window_Position_Changed>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
        case EventType::Window_Position_Changing:
            return VisitEventImpl<EventType::Window_Position_Changing>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
#pragma endregion

#pragma region Keyboard Notification Event cases
            case EventType::Activate:
                return VisitEventImpl<EventType::Activate>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::Application_Command:
                return VisitEventImpl<EventType::Application_Command>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::Char:
                return VisitEventImpl<EventType::Char>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::Dead_Char:
                return VisitEventImpl<EventType::Dead_Char>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::Hotkey:
                return VisitEventImpl<EventType::Hotkey>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::Key_Down:
                return VisitEventImpl<EventType::Key_Down>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::Key_Up:
                return VisitEventImpl<EventType::Key_Up>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::Kill_Focus:
                return VisitEventImpl<EventType::Kill_Focus>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::Set_Focus:
                return VisitEventImpl<EventType::Set_Focus>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::System_Dead_Char:
                return VisitEventImpl<EventType::System_Dead_Char>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::System_Key_Down:
                return VisitEventImpl<EventType::System_Key_Down>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::System_Key_Up:
                return VisitEventImpl<EventType::System_Key_Up>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
            case EventType::Unicode_Char:
                return VisitEventImpl<EventType::Unicode_Char>(std::forward<Func>(visitor), std::forward<Event>(event), std::forward<DefaultFunc>(defaultFunc));
#pragma endregion

        default:
            return defaultFunc(std::forward<Event>(event));
        }
    }
}

export namespace MoWin
{
    enum class WindowClassAtom : ATOM {};

    //https://docs.microsoft.com/en-us/windows/win32/winmsg/window-class-styles
    enum class WindowClassStyle
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

    template<class Ty>
    concept HasProcedure = requires (Ty self, Event event)
    {
        { self.operator()(event) } -> std::same_as<LRESULT>;
    };

    template<class Ty>
    concept StyleDefined = requires()
    {
        { Ty::Style() } -> std::same_as<WindowClassStyle>;
    };

    template<class Ty>
    concept ExtraClassBytesDefined = requires()
    {
        { Ty::ExtraClassBytes() } -> std::same_as<int>;
    };

    template<class Ty>
    concept ExtraWindowBytesDefined = requires()
    {
        { Ty::ExtraWindowBytes() } -> std::same_as<int>;
    };

    template<class Ty>
    concept IconDefined = requires(HINSTANCE instance)
    {
        { Ty::Icon(instance) } -> std::same_as<HICON>;
    };

    template<class Ty>
    concept CursorDefined = requires(HINSTANCE instance)
    {
        { Ty::Cursor(instance) } -> std::same_as<HCURSOR>;
    };

    template<class Ty>
    concept BackgroundBrushDefined = requires()
    {
        { Ty::BackgroundBrush() } -> std::same_as<HBRUSH>;
    };

    template<class Ty, class CharTy>
    concept MenuDefined = requires()
    {
        { Ty::MenuName() } -> std::same_as<CharTy>;
    };

    template<class Ty>
    concept SmallIconDefined = requires(HINSTANCE instance)
    {
        { Ty::SmallIcon(instance) } -> std::same_as<HICON>;
    };

    template<Platform P, CharacterSet C>
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

    template<class Ty, class GlobalTrait>
    struct WindowClassTraitsBase
    {
    public:
        using platform_traits = GlobalTrait;
        using class_type = platform_traits::extended_class_type;
        using string_type = platform_traits::string_type;

    private:
        inline static bool registered = false;
        inline static std::atomic<unsigned short> m_instanceCount;
        inline static HINSTANCE m_instance;

    public:
        static bool Registered()
        {
            return registered;
        }

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
                windowClass.style = static_cast<UINT>(DefaultClass<string_type>::Style());

            windowClass.lpfnWndProc = &Procedure;

            if constexpr(ExtraClassBytesDefined<Ty>)
                windowClass.cbClsExtra = Ty::ExtraClassBytes();
            else
                windowClass.cbClsExtra = DefaultClass<string_type>::ExtraClassBytes();

            if constexpr(ExtraWindowBytesDefined<Ty>)
                windowClass.cbWndExtra = Ty::ExtraWindowBytes();
            else
                windowClass.cbWndExtra = DefaultClass<string_type>::ExtraWindowBytes();

            windowClass.hInstance = m_instance;

            if constexpr(IconDefined<Ty>)
                windowClass.hIcon = Ty::Icon(m_instance);
            else
                windowClass.hIcon = DefaultClass<string_type>::Icon(m_instance);

            if constexpr(CursorDefined<Ty>)
                windowClass.hCursor = Ty::Cursor(m_instance);
            else
                windowClass.hCursor = DefaultClass<string_type>::Cursor(m_instance);

            if constexpr(BackgroundBrushDefined<Ty>)
                windowClass.hbrBackground = Ty::BackgroundBrush();
            else
                windowClass.hbrBackground = DefaultClass<string_type>::BackgroundBrush();

            if constexpr(MenuDefined<Ty, string_type>)
                windowClass.lpszMenuName = Ty::MenuName();
            else
                windowClass.lpszMenuName = DefaultClass<string_type>::MenuName();

            windowClass.lpszClassName = Ty::ClassName();

            if constexpr(SmallIconDefined<Ty>)
                windowClass.hIconSm = Ty::SmallIcon(m_instance);
            else
                windowClass.hIconSm = DefaultClass<string_type>::SmallIcon(m_instance);

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
            if(uMsg == WM_NCCREATE)
            {
                m_instanceCount++;
                typename platform_traits::window_create_struct_type* createStruct = std::bit_cast<typename platform_traits::window_create_struct_type*>(lParam);
                platform_traits::SetWindowData(hwnd, GWLP_USERDATA, createStruct->lpCreateParams);
            }
            if(uMsg == WM_NCDESTROY)
            {
                Unregister();
            }

            Ty* self = platform_traits::template GetWindowData<Ty*>(hwnd, GWLP_USERDATA);
            auto defProc = [](Event e) { return platform_traits::DefaultProcedure(e); };
            if(self == nullptr)
            {
                return defProc(Event{ hwnd, static_cast<EventType>(uMsg), wParam, lParam });
            }
            return VisitEvent(*self, Event{ hwnd, static_cast<EventType>(uMsg), wParam, lParam }, *self);

        }
    };

    template<class Ty>
    struct WindowClassTraits;


    //https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
    enum class WindowStyle : DWORD
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

    enum class WindowStyleEx : DWORD
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
}