module;
#include <concepts>

#include <Windows.h>
#include <memory>
#include <atomic>
#include <bit>
#include <variant>

export module MoWin:Window.Common;
import :Events;

#undef RegisterClass
#undef UnregisterClass
#undef CreateWindow

#undef SendMessage
#undef SendNotifyMessage
#undef SendMessageTimeout
#undef SendMessageCallback

namespace MoWin
{

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
    concept IsWindowClassImpl = requires
    {
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
        static void Register(HINSTANCE instance = nullptr)
        {
            if(Registered())
            {
                return;
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
                auto f = GetLastError();
                int i = 0;
                //Throw
            }
        }

        static void Unregister()
        {
            if(!platform_traits::UnregisterClass(Ty::ClassName(), m_instance))
            {
                if(GetLastError() == ERROR_CLASS_HAS_WINDOWS)
                {
                    return;
                }
            }

            registered = false;
        }

        static LRESULT Procedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            Ty* self = platform_traits::template GetWindowData<Ty*>(hwnd, GWLP_USERDATA);

            switch(uMsg)
            {
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
}