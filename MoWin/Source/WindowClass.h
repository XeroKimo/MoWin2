#pragma once
#include <bit>
#include <Windows.h>
#include <concepts>
#include <optional>

namespace MoWin
{
    enum class WindowClassAtom : ATOM {};

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

    template<class Ty>
    struct WindowClassTraits;

    template<>
    struct WindowClassTraits<WNDCLASSA>
    {
        using value_type = WNDCLASSA;
        using pointer = WNDCLASSA*;
        using const_pointer = const WNDCLASSA*;
        using reference = WNDCLASSA&;
        using const_reference = const WNDCLASSA&;
        using string_type = decltype(value_type::lpszClassName);

        static WindowClassAtom Register(const_reference data)
        {
            return WindowClassAtom(RegisterClassA(&data));
        }

        static std::optional<value_type>(GetClassInfo)(HINSTANCE hInstance, string_type className)
        {
            value_type classInfo;

            BOOL b = ::GetClassInfoA(hInstance, className, &classInfo);

            if(b == 0)
                return std::nullopt;

            return classInfo;
        }

        static bool Unregister(string_type className, HINSTANCE instance)
        {
            return UnregisterClassA(className, instance);
        }

        static HWND(CreateWindow)(WindowStyleEx dwExStyle,
            string_type lpClassName,
            string_type lpWindowName,
            WindowStyle dwStyle,
            int X,
            int Y,
            int nWidth,
            int nHeight,
            HWND hWndParent,
            HMENU hMenu,
            HINSTANCE hInstance,
            LPVOID lpParam)
        {
            return CreateWindowExA(static_cast<DWORD>(dwExStyle),
                lpClassName,
                lpWindowName,
                static_cast<DWORD>(dwStyle),
                X,
                Y,
                nWidth,
                nHeight,
                hWndParent,
                hMenu,
                hInstance,
                lpParam);
        }
    };

    template<>
    struct WindowClassTraits<WNDCLASSEXA>
    {
        using value_type = WNDCLASSEXA;
        using pointer = WNDCLASSEXA*;
        using const_pointer = const WNDCLASSEXA*;
        using reference = WNDCLASSEXA&;
        using const_reference = const WNDCLASSEXA&;
        using string_type = decltype(value_type::lpszClassName);

        static WindowClassAtom Register(const_reference data)
        {
            return WindowClassAtom(RegisterClassExA(&data));
        }

        static std::optional<value_type>(GetClassInfo)(HINSTANCE hInstance, string_type className)
        {
            value_type classInfo;
            classInfo.cbSize = sizeof(value_type);

            BOOL b = ::GetClassInfoExA(hInstance, className, &classInfo);

            if(b == 0)
                return std::nullopt;

            return classInfo;
        }

        static bool Unregister(string_type className, HINSTANCE instance)
        {
            return UnregisterClassA(className, instance);
        }

        static HWND(CreateWindow)(WindowStyleEx dwExStyle,
            string_type lpClassName,
            string_type lpWindowName,
            WindowStyle dwStyle,
            int X,
            int Y,
            int nWidth,
            int nHeight,
            HWND hWndParent,
            HMENU hMenu,
            HINSTANCE hInstance,
            LPVOID lpParam)
        {
            return CreateWindowExA(static_cast<DWORD>(dwExStyle),
                lpClassName,
                lpWindowName,
                static_cast<DWORD>(dwStyle),
                X,
                Y,
                nWidth,
                nHeight,
                hWndParent,
                hMenu,
                hInstance,
                lpParam);
        }
    };

    template<>
    struct WindowClassTraits<WNDCLASSW>
    {
        using value_type = WNDCLASSW;
        using pointer = WNDCLASSW*;
        using const_pointer = const WNDCLASSW*;
        using reference = WNDCLASSW&;
        using const_reference = const WNDCLASSW&;
        using string_type = decltype(value_type::lpszClassName);

        static WindowClassAtom Register(const_reference data)
        {
            return WindowClassAtom(RegisterClassW(&data));
        }

        static std::optional<value_type>(GetClassInfo)(HINSTANCE hInstance, string_type className)
        {
            value_type classInfo;

            BOOL b = ::GetClassInfoW(hInstance, className, &classInfo);

            if(b == 0)
                return std::nullopt;

            return classInfo;
        }

        static bool Unregister(string_type className, HINSTANCE instance)
        {
            return UnregisterClassW(className, instance);
        }

        static HWND(CreateWindow)(WindowStyleEx dwExStyle,
            string_type lpClassName,
            string_type lpWindowName,
            WindowStyle dwStyle,
            int X,
            int Y,
            int nWidth,
            int nHeight,
            HWND hWndParent,
            HMENU hMenu,
            HINSTANCE hInstance,
            LPVOID lpParam)
        {
            return CreateWindowExW(static_cast<DWORD>(dwExStyle),
                lpClassName,
                lpWindowName,
                static_cast<DWORD>(dwStyle),
                X,
                Y,
                nWidth,
                nHeight,
                hWndParent,
                hMenu,
                hInstance,
                lpParam);
        }
    };

    template<>
    struct WindowClassTraits<WNDCLASSEXW>
    {
        using value_type = WNDCLASSEXW;
        using pointer = WNDCLASSEXW*;
        using const_pointer = const WNDCLASSEXW*;
        using reference = WNDCLASSEXW&;
        using const_reference = const WNDCLASSEXW&;
        using string_type = decltype(value_type::lpszClassName);

        static WindowClassAtom Register(const_reference data)
        {
            return WindowClassAtom(RegisterClassExW(&data));
        }

        static std::optional<value_type> (GetClassInfo)(HINSTANCE hInstance, string_type className)
        {
            value_type classInfo;
            classInfo.cbSize = sizeof(value_type);
             
            BOOL b = ::GetClassInfoExW(hInstance, className, &classInfo);

            if(b == 0)
                return std::nullopt;

            return classInfo;
        }

        static bool Unregister(string_type className, HINSTANCE instance)
        {
            return UnregisterClassW(className, instance);
        }

        static HWND(CreateWindow)(WindowStyleEx dwExStyle,
            string_type lpClassName,
            string_type lpWindowName,
            WindowStyle dwStyle,
            int X,
            int Y,
            int nWidth,
            int nHeight,
            HWND hWndParent,
            HMENU hMenu,
            HINSTANCE hInstance,
            LPVOID lpParam)
        {
            return CreateWindowExW(static_cast<DWORD>(dwExStyle),
                lpClassName,
                lpWindowName,
                static_cast<DWORD>(dwStyle),
                X,
                Y,
                nWidth,
                nHeight,
                hWndParent,
                hMenu,
                hInstance,
                lpParam);
        }
    };


    template<class CharT>
    class WindowClassBase
    {
    private:
        using string_type = CharT;

    protected:
        WindowClassAtom m_atom = 0;

    public:
        WindowClassBase() = default;
        WindowClassBase(WindowClassAtom atom) : m_atom(atom) {}


    public:
        WindowClassAtom GetAtom() const { return m_atom; }

        operator string_type() const
        {
            return std::bit_cast<string_type>(ULONG_PTR(m_atom));
        }
    };

    template<class Ty, class Trait = WindowClassTraits<Ty>>
    class WindowClass : public WindowClassBase<typename Trait::string_type>
    {
    private:
        using traits = Trait;

    public:
        using value_type = typename traits::value_type;
        using pointer = typename traits::pointer;
        using const_pointer = typename traits::const_pointer;
        using reference = typename traits::reference;
        using const_reference = typename traits::const_reference;
        using string_type = typename traits::string_type;

    private:
        HINSTANCE m_hInstance = nullptr;

    public:
        WindowClass(const_reference classType) :
            WindowClassBase<string_type>(traits::Register(classType)),
            m_hInstance(classType.hInstance)
        {

        }

        WindowClass(const WindowClass& other) = delete;
        WindowClass(WindowClass&& other) noexcept = default;

        WindowClass& operator=(const WindowClass& other) = delete;
        WindowClass& operator=(WindowClass&& other) noexcept = default;

        ~WindowClass()
        {
            traits::Unregister(*this, m_hInstance);
        }

        HINSTANCE GetInstance() const { return m_hInstance; }
    };

    template<class Ty, class CharT>
    concept CompatibleWindowClassType = requires(Ty t)
    {
        { t.lpszClassName } -> std::same_as<CharT&>;
    };

    template<class CharT>
    class WindowClassView : public WindowClassBase<CharT>
    {
    public:
        WindowClassView() = default;
        WindowClassView(WindowClassAtom atom) : WindowClassBase<CharT>(atom)
        {
        
        }

        template<CompatibleWindowClassType<CharT> Ty>
        WindowClassView(const WindowClass<Ty>& data) : WindowClassBase<CharT>(data.GetAtom())
        {

        }
    };

    using WindowClassA = WindowClass<WNDCLASSA>;
    using WindowClassExA = WindowClass<WNDCLASSEXA>;
    using WindowClassW = WindowClass<WNDCLASSW>;
    using WindowClassExW = WindowClass<WNDCLASSEXW>;

    using WindowClassAView = WindowClassView<WindowClassTraits<WNDCLASSA>::string_type>;
    using WindowClassWView = WindowClassView<WindowClassTraits<WNDCLASSW>::string_type>;

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
    concept IsStaticWindowClassA = requires(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, HINSTANCE hInstance)
    {
        { Ty::Style() } -> std::same_as<WindowClassStyle>;
        { Ty::ExtraClassBytes() } -> std::same_as<int>;
        { Ty::ExtraWindowBytes() } -> std::same_as<int>;
        { Ty::Icon(hInstance) } -> std::same_as<HICON>;
        { Ty::Cursor(hInstance) } -> std::same_as<HCURSOR>;
        { Ty::BackgroundBrush() } -> std::same_as<HBRUSH>;
        { Ty::ClassName() } -> std::same_as<LPCSTR>;
        { Ty::MenuName() } -> std::same_as<LPCSTR>;
        { Ty::Procedure(hwnd, uMsg, wParam, lParam) } -> std::same_as<LRESULT>;
    };

    template<class Ty>
    concept IsStaticWindowClassW = requires(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, HINSTANCE hInstance)
    {
        { Ty::Style() } -> std::same_as<WindowClassStyle>;
        { Ty::ExtraClassBytes() } -> std::same_as<int>;
        { Ty::ExtraWindowBytes() } -> std::same_as<int>;
        { Ty::Icon(hInstance) } -> std::same_as<HICON>;
        { Ty::Cursor(hInstance) } -> std::same_as<HCURSOR>;
        { Ty::BackgroundBrush() } -> std::same_as<HBRUSH>;
        { Ty::ClassName() } -> std::same_as<LPCWSTR>;
        { Ty::MenuName() } -> std::same_as<LPCWSTR>;
        { Ty::Procedure(hwnd, uMsg, wParam, lParam) } -> std::same_as<LRESULT>;
    };

    template<class Ty>
    concept IsStaticWindowClass = IsStaticWindowClassA<Ty> || IsStaticWindowClassW<Ty>;

    template<class Ty>
    concept IsExtendedWindowClass = requires(HINSTANCE hInstance)
    { 
        { Ty::SmallIcon(hInstance) } -> std::same_as<HICON>;
    };

    struct predefined_class_tag {};

    template<class Ty>
    concept IsPredefinedClass = requires
    {
        typename Ty::predefined_class;
    };

    template<class Ty>
    struct StaticWindowClassTraits;

    template<class Ty, class Traits>
    struct StaticWindowClassTraitsBase
    {
    public:
        using raw_traits = Traits;
        using value_type = raw_traits::value_type;
        using string_type = raw_traits::string_type;

    private:
        inline static bool registered = IsPredefinedClass<Ty>;

    public:
        static bool Registered()
        {
            return registered;
        }

        static bool Register(HINSTANCE instance = nullptr)
        {
            if(registered)
                return registered;

            value_type windowClass
            { 
                .cbSize = sizeof(value_type),
                        /* Win 3.x */
                .style = static_cast<UINT>(Ty::Style()),
                .lpfnWndProc = &Ty::Procedure,
                .cbClsExtra = Ty::ExtraClassBytes(),
                .cbWndExtra = Ty::ExtraWindowBytes(),
                .hInstance = instance,
                .hIcon = Ty::Icon(instance),
                .hCursor = Ty::Cursor(instance),
                .hbrBackground = Ty::BackgroundBrush(),
                .lpszMenuName = Ty::MenuName(),
                .lpszClassName = Ty::ClassName(),
            };

            if constexpr(IsExtendedWindowClass<Ty>)
            {
                windowClass.hIconSm = Ty::SmallIcon(instance);
            }

            registered = raw_traits::Register(windowClass) != WindowClassAtom(0);

            return registered;
        }


        static HWND (CreateWindow)(WindowStyleEx dwExStyle,
            string_type lpWindowName,
            WindowStyle dwStyle,
            int X,
            int Y,
            int nWidth,
            int nHeight,
            HWND hWndParent,
            HMENU hMenu,
            HINSTANCE hInstance,
            LPVOID lpParam)
        {
            return (raw_traits::CreateWindow)(
                dwExStyle,
                Ty::ClassName(),
                lpWindowName,
                dwStyle,
                X,
                Y,
                nWidth,
                nHeight,
                hWndParent,
                hMenu,
                hInstance,
                lpParam);
        }

        static bool Unregister(HINSTANCE instance = nullptr)
        {
            registered = !raw_traits::Unregister(Ty::ClassName(), instance);

            return !registered;
        }
    };

    template<class Ty>
        requires IsStaticWindowClassA<Ty>
    struct StaticWindowClassTraits<Ty> : public StaticWindowClassTraitsBase<Ty, WindowClassTraits<WNDCLASSA>>
    {
    };

    template<class Ty>
        requires IsStaticWindowClassA<Ty> && IsExtendedWindowClass<Ty>
    struct StaticWindowClassTraits<Ty> : public StaticWindowClassTraitsBase<Ty, WindowClassTraits<WNDCLASSEXA>>
    {
    };

    template<class Ty>
        requires IsStaticWindowClassW<Ty>
    struct StaticWindowClassTraits<Ty> : public StaticWindowClassTraitsBase<Ty, WindowClassTraits<WNDCLASSW>>
    {
    };

    template<class Ty>
        requires IsStaticWindowClassW<Ty>&& IsExtendedWindowClass<Ty>
    struct StaticWindowClassTraits<Ty> : public StaticWindowClassTraitsBase<Ty, WindowClassTraits<WNDCLASSEXW>>
    {
    };

    struct DefaultClassA
    {
        static WindowClassStyle Style() { return {}; }
        static int ExtraClassBytes() { return 0; }
        static int ExtraWindowBytes() { return 0; }
        static HICON Icon(HINSTANCE instance = nullptr) { return nullptr; }
        static HCURSOR Cursor(HINSTANCE instance = nullptr) { return LoadCursorA(nullptr, std::bit_cast<LPCSTR>(IDC_ARROW)); }
        static HBRUSH BackgroundBrush() { return GetSysColorBrush(COLOR_BACKGROUND + 1); }
        static LPCSTR ClassName() { return "DefaultClassA"; }
        static LPCSTR MenuName() { return nullptr; }

        static LRESULT Procedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            return DefWindowProcA(hwnd, uMsg, wParam, lParam);
        }
    };

    struct DefaultClassW
    {
        static WindowClassStyle Style() { return {}; }
        static int ExtraClassBytes() { return 0; }
        static int ExtraWindowBytes() { return 0; }
        static HICON Icon(HINSTANCE instance = nullptr) { return nullptr; }
        static HCURSOR Cursor(HINSTANCE instance = nullptr) { return LoadCursorW(nullptr, std::bit_cast<LPCWSTR>(IDC_ARROW)); }
        static HBRUSH BackgroundBrush() { return GetSysColorBrush(COLOR_BACKGROUND + 1); }
        static LPCWSTR ClassName() { return L"DefaultClassW"; }
        static LPCWSTR MenuName() { return nullptr; }

        //Required in order to make itself an extended window class
        static HICON SmallIcon(HINSTANCE instance = nullptr) { return nullptr; }

        static LRESULT Procedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
        }
    };

    struct ButtonA : DefaultClassA
    {
        using predefined_class = predefined_class_tag;

        static LPCSTR ClassName() { return "Button"; }
    };

    struct ButtonW : DefaultClassW
    {
        using predefined_class = predefined_class_tag;

        static LPCWSTR ClassName() { return L"Button"; }
    };

    struct ComboBoxA : DefaultClassA
    {
        using predefined_class = predefined_class_tag;

        static LPCSTR ClassName() { return "ComboBox"; }
    };

    struct ComboBoxW : DefaultClassW
    {
        using predefined_class = predefined_class_tag;

        static LPCWSTR ClassName() { return L"ComboBox"; }
    };

    struct EditA : DefaultClassA
    {
        using predefined_class = predefined_class_tag;

        static LPCSTR ClassName() { return "Edit"; }
    };

    struct EditW : DefaultClassW
    {
        using predefined_class = predefined_class_tag;

        static LPCWSTR ClassName() { return L"Edit"; }
    };

    struct ListBoxA : DefaultClassA
    {
        using predefined_class = predefined_class_tag;

        static LPCSTR ClassName() { return "ListBox"; }
    };

    struct ListBoxW : DefaultClassW
    {
        using predefined_class = predefined_class_tag;

        static LPCWSTR ClassName() { return L"ListBox"; }
    };

    struct MDIClientA : DefaultClassA
    {
        using predefined_class = predefined_class_tag;

        static LPCSTR ClassName() { return "MDIClient"; }
    };

    struct MDIClientW : DefaultClassW
    {
        using predefined_class = predefined_class_tag;

        static LPCWSTR ClassName() { return L"MDIClient"; }
    };

    struct ScrollBarA : DefaultClassA
    {
        using predefined_class = predefined_class_tag;

        static LPCSTR ClassName() { return "ScrollBar"; }
    };

    struct ScrollBarW : DefaultClassW
    {
        using predefined_class = predefined_class_tag;

        static LPCWSTR ClassName() { return L"ScrollBar"; }
    };

    struct StaticA : DefaultClassA
    {
        using predefined_class = predefined_class_tag;

        static LPCSTR ClassName() { return "Static"; }
    };

    struct StaticW : DefaultClassW
    {
        using predefined_class = predefined_class_tag;

        static LPCWSTR ClassName() { return L"Static"; }
    };

    static_assert(IsStaticWindowClassA<DefaultClassA>);
    static_assert(!IsExtendedWindowClass<DefaultClassA>);

    static_assert(IsStaticWindowClassW<DefaultClassW>);
    static_assert(IsExtendedWindowClass<DefaultClassW>);
}