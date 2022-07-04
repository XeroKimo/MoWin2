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
    namespace W64U
    {
        constexpr Platform filePlatform = Platform::Win64;
        constexpr CharacterSet fileCharacterSet = CharacterSet::Unicode;

        using FilePlatformTraits = PlatformTraits<filePlatform, fileCharacterSet>;
        using FileStringType = LPCWSTR;
        using FileStandardClassType = WNDCLASSW;
        using FileExtendedClassType = WNDCLASSEXW;
        using FileWindowCreateStruct = CREATESTRUCTW;
    }


    export template<class Ty>
        concept IsWindowClassW = requires
    {
        { Ty::ClassName() } -> std::same_as<W64U::FileStringType>;
    } && HasProcedure<Ty>;


    namespace W64U
    {
        template<class Ty>
        concept FileIsWindowClass = IsWindowClassW<Ty>;
    }

    export template<class Ty>
        concept IsFullWindowClassW = W64U::FileIsWindowClass<Ty> &&
        StyleDefined<Ty> &&
        ExtraClassBytesDefined<Ty> &&
        ExtraWindowBytesDefined<Ty> &&
        IconDefined<Ty> &&
        CursorDefined<Ty> &&
        BackgroundBrushDefined<Ty> &&
        MenuDefined<Ty, LPCWSTR> &&
        SmallIconDefined<Ty>;

    namespace W64U
    {
        template<class Ty>
        concept FileIsFullWindowClass = IsFullWindowClassW<Ty>;
    }

#ifdef _WIN64 

    export using UnicodePlatformTraits = PlatformTraits<W64U::filePlatform, W64U::fileCharacterSet>;
#ifdef _UNICODE

    constexpr Platform defaultPlatform = W64U::filePlatform;
    constexpr CharacterSet characterSet = W64U::fileCharacterSet;

    export template<class Ty>
        concept IsWindowClass = W64U::FileIsWindowClass<Ty>;

    export template<class Ty>
        concept IsFullWindowClass = W64U::FileIsFullWindowClass<Ty>;

    export using DefaultPlatformTraits = UnicodePlatformTraits;
#endif
#endif

    export template<>
    struct PlatformTraits<W64U::filePlatform, W64U::fileCharacterSet>
    {
        static constexpr Platform platform_value = W64U::filePlatform;
        static constexpr CharacterSet character_set_value = W64U::fileCharacterSet;

        using standard_class_type = W64U::FileStandardClassType;
        using extended_class_type = W64U::FileExtendedClassType;
        using window_create_struct_type = W64U::FileWindowCreateStruct;
        using string_type = W64U::FileStringType;

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
        static RetTy SetWindowData(HWND hwnd, int index, Ty value)
        {
            return std::bit_cast<RetTy>(SetWindowLongPtrW(hwnd, index, std::bit_cast<LONG_PTR>(value)));
        }

        template<class Ty = LONG_PTR>
            requires (sizeof(Ty) == 8)
        static Ty GetWindowData(HWND hwnd, int index)
        {
            return std::bit_cast<Ty>(GetWindowLongPtrW(hwnd, index));
        }
    };

    export template<>
    struct DefaultClass<W64U::filePlatform, W64U::fileCharacterSet> : public DefaultClassCommon
    {
        using string_type = W64U::FileStringType;

        static string_type ClassName() { return L"DefaultClassW"; }
        static string_type MenuName() { return nullptr; }

        DefaultClass(HWND hwnd) {}

        static LRESULT Procedure(Event event)
        {
            if(static_cast<UINT>(event.type) == WM_DESTROY)
            {
                PostQuitMessage(0);
            }

            return PlatformTraits<W64U::filePlatform, W64U::fileCharacterSet>::DefaultProcedure(event.window, static_cast<UINT>(event.type), event.wParam, event.lParam);
        }
    };

    export template<W64U::FileIsWindowClass Ty>
        struct WindowClassTraits<Ty> : public WindowClassTraitsBase<Ty, W64U::FilePlatformTraits>
    {

    };
}
