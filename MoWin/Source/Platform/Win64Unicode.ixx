module;

#include <Windows.h>
#include <bit>
export module MoWin.Window:Platform.Win64.Unicode;

export import :Common;

#undef CreateWindow
#undef UnregisterClass
#undef RegisterClass

namespace MoWin
{
    inline namespace W64U
    {
        constexpr Platform filePlatform = Platform::Win64;
        constexpr CharacterSet fileCharacterSet = CharacterSet::Unicode;

        using FilePlatformTraits = PlatformTraits<filePlatform, fileCharacterSet>;
        using FileStringType = LPCWSTR;
        using FileStandardClassType = WNDCLASSW;
        using FileExtendedClassType = WNDCLASSEXW;
    }


    export template<class Ty>
        concept IsWindowClassW = requires
    {
        { Ty::ClassName() } -> std::same_as<FileStringType>;
    } && (HasStaticProcedure<Ty> || HasObjectProcedure<Ty>);


    inline namespace W64U
    {
        template<class Ty>
        concept FileIsWindowClass = IsWindowClassW<Ty>;
    }

    export template<class Ty>
        concept IsFullWindowClassW = FileIsWindowClass<Ty> &&
        StyleDefined<Ty> &&
        ExtraClassBytesDefined<Ty> &&
        ExtraWindowBytesDefined<Ty> &&
        IconDefined<Ty> &&
        CursorDefined<Ty> &&
        BackgroundBrushDefined<Ty> &&
        MenuDefined<Ty, LPCWSTR> &&
        SmallIconDefined<Ty>;

    inline namespace W64U
    {
        template<class Ty>
        concept FileIsFullWindowClass = IsFullWindowClassW<Ty>;
    }

#ifdef _WIN64 
#ifdef _UNICODE

    constexpr Platform defaultPlatform = Platform::Win64;
    constexpr CharacterSet characterSet = CharacterSet::Unicode;

    export template<class Ty>
        concept IsWindowClass = FileIsWindowClass<Ty>;

    export template<class Ty>
        concept FullWindowClass = FileIsFullWindowClass<Ty>;

#endif
#endif


    export template<>
    struct PlatformTraits<filePlatform, fileCharacterSet>
    {
        static constexpr Platform platform_value = filePlatform;
        static constexpr CharacterSet character_set_value = fileCharacterSet;

        using standard_class_type = FileStandardClassType;
        using extended_class_type = FileExtendedClassType;
        using string_type = FileStringType;

        static WindowClassAtom RegisterClass(const standard_class_type& data)
        {
            return WindowClassAtom(RegisterClassW(&data));
        }

        static WindowClassAtom RegisterClass(const extended_class_type& data)
        {
            return WindowClassAtom(RegisterClassExW(&data));
        }

        static bool UnregisterClass(string_type className, HINSTANCE instance)
        {
            return UnregisterClassW(className, instance);
        }

        static LRESULT DefaultProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
        }

        static HWND CreateWindow(WindowStyleEx extendedStyle, string_type className, string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* data)
        {
            return CreateWindowExW(
                static_cast<DWORD>(extendedStyle),
                className,
                windowName,
                static_cast<DWORD>(style),
                x,
                y,
                width,
                height,
                optionalParent,
                menu,
                hInstance,
                data);
        }

        template<class Ty, class RetTy = LONG_PTR>
            requires (sizeof(Ty) == 8 && sizeof(RetTy) == 8)
        static RetTy GetWindowData(HWND hwnd, int index, Ty value)
        {
            return std::bit_cast<RetTy>(SetWindowLongPtrW(hwnd, index, std::bit_cast<LONG_PTR>(value)));
        }

        static LONG_PTR GetWindowData(HWND hwnd, int index)
        {
            return GetWindowLongPtrW(hwnd, index);
        }
    };

    export template<>
    struct DefaultClass<filePlatform, fileCharacterSet> : public DefaultClassCommon
    {
        using string_type = FileStringType;

        static string_type ClassName() { return L"DefaultClassW"; }
        static string_type MenuName() { return nullptr; }

        DefaultClass(HWND hwnd) {}

        static LRESULT Procedure(Event event)
        {
            if(static_cast<UINT>(event.type) == WM_DESTROY)
            {
                PostQuitMessage(0);
            }

            return PlatformTraits<filePlatform, fileCharacterSet>::DefaultProcedure(event.window, static_cast<UINT>(event.type), event.wParam, event.lParam);
        }
    };

    export template<FileIsWindowClass Ty>
        struct WindowClassTraits<Ty> : public WindowClassTraitsBase<Ty, FilePlatformTraits>
    {

    };
}
