module;

#include <Windows.h>
#include <string>

export module MoWin:Window;

namespace MoWin
{
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

    export enum class WindowClassStyle : DWORD
    {
        ByteAlignClient = CS_BYTEALIGNCLIENT,
        ByteAlignWindow = CS_BYTEALIGNWINDOW,
        ClassDC = CS_CLASSDC,
        DoubleClicks = CS_DBLCLKS,
        DropShadow = CS_DROPSHADOW,
        GlobalClass = CS_GLOBALCLASS,
        HorizontalRedraw = CS_HREDRAW,
        NoClose = CS_NOCLOSE,
        OwnDC = CS_OWNDC,
        ParentDC = CS_PARENTDC,
        SaveBits = CS_SAVEBITS,
        VerticalRedraw = CS_VREDRAW
    };

    DEFINE_ENUM_FLAG_OPERATORS(WindowClassStyle);

    struct WindowBase
    {
        HWND windowHandle;

        BOOL IsChildOf(HWND parent)
        {
            return ::IsChild(parent, windowHandle);
        }

        void Hide()
        {
            ::ShowWindow(windowHandle, SW_HIDE);
        }

        void Show()
        {
            ::ShowWindow(windowHandle, SW_SHOW);
        }

        void Minimize()
        {
            ::ShowWindow(windowHandle, SW_MINIMIZE);
        }

        void Maximize()
        {
            ::ShowWindow(windowHandle, SW_MAXIMIZE);
        }

        void Restore()
        {
            ::ShowWindow(windowHandle, SW_RESTORE);
        }

        HWND GetHandle() const noexcept { return windowHandle; }

        RECT GetClientRect() const
        {
            RECT rect;
            ::GetClientRect(windowHandle, &rect);
            return rect;
        }

        template<class Ty>
        void SetUserData(Ty& data)
        {
            SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&data));
        }

        template<class Ty>
        Ty* GetUserData() { return reinterpret_cast<Ty*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA)); }
    };

    export class AnyWindowView;

    export struct Rect : RECT
    {
        int Width() const { return right - left; }
        int Height() const { return bottom - top; }
    };

    export struct NonClientSize
    {
        int width;
        int height;
    };

    export struct ClientSize
    {
        int width;
        int height;
    };

    export template<class Ty>
        class Window : private WindowBase
    {
    private:
        Ty* cachedUserData = nullptr;

    public:
        template<class... ConstructorArgs>
        Window(std::wstring windowName,
            WindowStyle style,
            WindowStyleEx extendedStyle,
            int x,
            int y,
            NonClientSize size,
            AnyWindowView optionalParent,
            HMENU menu,
            HINSTANCE instance,
            ConstructorArgs&&... args);

        template<class... ConstructorArgs>
        Window(std::wstring windowName,
            WindowStyle style,
            WindowStyleEx extendedStyle,
            int x,
            int y,
            ClientSize size,
            AnyWindowView optionalParent,
            HMENU menu,
            HINSTANCE instance,
            ConstructorArgs&&... args);

        Window(const Window&) = delete;
        Window(Window&& other) noexcept :
            WindowBase{ std::exchange(other.windowHandle, nullptr) },
            cachedUserData{ std::exchange(other.cachedUserData, nullptr) }
        {

        }

        ~Window()
        {
            if(windowHandle)
                DestroyWindow(windowHandle);
        }

        Window& operator=(const Window&) = delete;
        Window& operator=(Window&& other) noexcept
        {
            Window temp = std::move(other);
            std::swap(windowHandle, temp.windowHandle);
            std::swap(cachedUserData, temp.cachedUserData);
            return *this;
        }

    public:
        using WindowBase::IsChildOf;
        using WindowBase::Hide;
        using WindowBase::Show;
        using WindowBase::Minimize;
        using WindowBase::Maximize;
        using WindowBase::Restore;
        using WindowBase::GetClientRect;
        using WindowBase::GetHandle;

        Ty& GetUserData() const { return *cachedUserData; }
    };

    export template<class Ty>
        class WindowView : private WindowBase
    {
    private:
        Ty* cachedUserData = nullptr;

    public:
        WindowView() : WindowBase{} {}
        WindowView(HWND hwnd) : WindowBase{ hwnd },
            cachedUserData{ WindowBase::GetUserData<Ty>() }
        {
        }
        WindowView(const Window<Ty>& window) : WindowBase{ window.GetHandle() },
            cachedUserData{ &window.GetUserData() }
        {
        }

    public:
        using WindowBase::IsChildOf;
        using WindowBase::Hide;
        using WindowBase::Show;
        using WindowBase::Minimize;
        using WindowBase::Maximize;
        using WindowBase::Restore;
        using WindowBase::GetClientRect;
        using WindowBase::GetHandle;

        Ty& GetUserData() { return *WindowBase::template GetUserData<Ty>(); }
    };

    export class AnyWindowView : private WindowBase
    {
    public:
        AnyWindowView() : WindowBase{} {}
        AnyWindowView(HWND hwnd) : WindowBase{ hwnd } {}
        template<class Ty>
        AnyWindowView(const Window<Ty>& window) : WindowBase{ window.GetHandle() } {}
        template<class Ty>
        AnyWindowView(const WindowView<Ty>& window) : WindowBase{ window.GetHandle() } {}

    public:
        using WindowBase::IsChildOf;
        using WindowBase::Hide;
        using WindowBase::Show;
        using WindowBase::Minimize;
        using WindowBase::Maximize;
        using WindowBase::Restore;
        using WindowBase::GetClientRect;
        using WindowBase::GetHandle;
        using WindowBase::SetUserData;
        using WindowBase::GetUserData;
    };

    template<class Ty>
    struct ClassConstructor
    {
        void* args;
        Ty* (*pad)(AnyWindowView, void*);

        template<class... ConstructorArgs>
        ClassConstructor(std::tuple<ConstructorArgs...>& args) :
            args{ &args },
            pad{ &LandingPad<ConstructorArgs...> }
        {

        }

        Ty* Create(AnyWindowView window)
        {
            return (*pad)(window, args);
        }

        template<class... ConstructorArgs>
        static Ty* LandingPad(AnyWindowView window, void* args)
        {
            std::tuple<ConstructorArgs...>& cArgs = *reinterpret_cast<std::tuple<ConstructorArgs...>*>(args);
            return std::apply([window](auto&&... args)
            {
                return new Ty(window, std::forward<decltype(args)>(args)...);
            }, cArgs);
        }
    };

#undef CreateWindow
    template<class Ty, class... ConstructorArgs>
    HWND CreateWindow(
        std::wstring windowName,
        WindowStyle style,
        WindowStyleEx extendedStyle,
        int x,
        int y,
        NonClientSize size,
        AnyWindowView optionalParent,
        HMENU menu,
        HINSTANCE instance,
        std::tuple<ConstructorArgs...> args)
    {
        auto constructor = ClassConstructor<Ty>{ args };

        return CreateWindowExW(
            static_cast<DWORD>(extendedStyle),
            Ty::classAtom,
            windowName.c_str(),
            static_cast<DWORD>(style),
            x,
            y,
            size.width,
            size.height,
            optionalParent.GetHandle(),
            menu,
            instance,
            &constructor);
    }

    template<class Ty, class... ConstructorArgs>
    HWND CreateWindow(
        std::wstring windowName,
        WindowStyle style,
        WindowStyleEx extendedStyle,
        int x,
        int y,
        ClientSize size,
        AnyWindowView optionalParent,
        HMENU menu,
        HINSTANCE instance,
        std::tuple<ConstructorArgs...> args)
    {
        auto constructor = ClassConstructor<Ty>{ args };

        Rect rect{};
        rect.right = size.width;
        rect.bottom = size.height;
        AdjustWindowRect(&rect, std::to_underlying(style), menu != nullptr);

        return CreateWindowExW(
            static_cast<DWORD>(extendedStyle),
            Ty::classAtom,
            windowName.c_str(),
            static_cast<DWORD>(style),
            x,
            y,
            rect.Width(),
            rect.Height(),
            optionalParent.GetHandle(),
            menu,
            instance,
            &constructor);
    }

    template<class Ty>
    template<class... ConstructorArgs>
    Window<Ty>::Window(std::wstring windowName,
        WindowStyle style,
        WindowStyleEx extendedStyle,
        int x,
        int y,
        NonClientSize size,
        AnyWindowView optionalParent,
        HMENU menu,
        HINSTANCE instance,
        ConstructorArgs&&... args) :
        WindowBase{ MoWin::CreateWindow<Ty>(
            windowName,
            style,
            extendedStyle,
            x,
            y,
            size,
            optionalParent,
            menu,
            instance,
            std::tuple<ConstructorArgs...>{ args... }) },
        cachedUserData{ WindowBase::GetUserData<Ty>() }
    {

    }

    template<class Ty>
    template<class... ConstructorArgs>
    Window<Ty>::Window(std::wstring windowName,
        WindowStyle style,
        WindowStyleEx extendedStyle,
        int x,
        int y,
        ClientSize size,
        AnyWindowView optionalParent,
        HMENU menu,
        HINSTANCE instance,
        ConstructorArgs&&... args) :
        WindowBase{ MoWin::CreateWindow<Ty>(
            windowName,
            style,
            extendedStyle,
            x,
            y,
            size,
            optionalParent,
            menu,
            instance,
            std::tuple<ConstructorArgs...>{ args... }) },
        cachedUserData{ WindowBase::GetUserData<Ty>() }
    {

    }
}