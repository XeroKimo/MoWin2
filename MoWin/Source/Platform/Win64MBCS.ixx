module;

#include <Windows.h>
#include <bit>
export module MoWin.Window:Platform.Win64.MBCS;

import :Common;

#undef CreateWindow
#undef UnregisterClass
#undef RegisterClass

#define SOMETHING_RANDOM

namespace MoWin
{
    namespace W64M
    {
        constexpr Platform filePlatform = Platform::Win64;
        constexpr CharacterSet fileCharacterSet = CharacterSet::MBCS;

        using FilePlatformTraits = PlatformTraits<filePlatform, fileCharacterSet>;
        using FileStringType = LPCSTR;
        using FileStandardClassType = WNDCLASSA;
        using FileExtendedClassType = WNDCLASSEXA;
        using FileWindowCreateStruct = CREATESTRUCTA;


        template<class Ty>
        concept FileHasVisitableEvent = HasVisitableEventImpl<Ty, FilePlatformTraits>;

        template<class Ty>
        concept FileHasProcedure = HasProcedureImpl<Ty, FilePlatformTraits>;
    }

    export template<class Ty>
        concept HasVisitableEventA = W64M::FileHasVisitableEvent<Ty>;

    export template<class Ty>
        concept HasProcedureA = W64M::FileHasProcedure<Ty>;

    export template<class Ty>
        concept IsWindowClassA = requires
    {
        { Ty::ClassName() } -> std::same_as<W64M::FileStringType>;
    } && (HasProcedureA<Ty> || HasVisitableEventA<Ty>);


    namespace W64M
    {
        template<class Ty>
        concept FileIsWindowClass = IsWindowClassA<Ty>;
    }

    export template<class Ty>
        concept IsFullWindowClassA = W64M::FileIsWindowClass<Ty> &&
        StyleDefined<Ty> &&
        ExtraClassBytesDefined<Ty> &&
        ExtraWindowBytesDefined<Ty> &&
        IconDefined<Ty> &&
        CursorDefined<Ty> &&
        BackgroundBrushDefined<Ty> &&
        MenuDefined<Ty, LPCWSTR> &&
        SmallIconDefined<Ty>;

    namespace W64M
    {
        template<class Ty>
        concept FileIsFullWindowClass = IsFullWindowClassA<Ty>;
    }

#ifdef _WIN64 
    export using MBCSPlatformTraits = PlatformTraits<W64M::filePlatform, W64M::fileCharacterSet>;
#ifdef _MBCS

    export inline constexpr Platform defaultPlatform = W64M::filePlatform;
    export inline constexpr CharacterSet characterSet = W64M::fileCharacterSet;

    export template<class Ty>
        concept IsWindowClass = W64M::FileIsWindowClass<Ty>;

    export template<class Ty>
        concept IsFullWindowClass = W64M::FileIsFullWindowClass<Ty>;

    export using DefaultPlatformTraits = MBCSPlatformTraits;

    export template<class Ty>
    concept HasProcedure = W64M::FileHasProcedure<Ty>;

    export template<class Ty>
    concept HasVisitableEvent = W64M::FileHasVisitableEvent<Ty>;
#endif
#endif


    export template<>
    struct PlatformTraits<W64M::filePlatform, W64M::fileCharacterSet>
    {
        static constexpr Platform platform_value = W64M::filePlatform;
        static constexpr CharacterSet character_set_value = W64M::fileCharacterSet;

        using standard_class_type = W64M::FileStandardClassType;
        using extended_class_type = W64M::FileExtendedClassType;
        using window_create_struct_type = W64M::FileWindowCreateStruct;
        using string_type = W64M::FileStringType;

        static WindowClassAtom RegisterClass(const standard_class_type& data)
        {
            return WindowClassAtom(RegisterClassA(&data));
        }

        static WindowClassAtom RegisterClass(const extended_class_type& data)
        {
            return WindowClassAtom(RegisterClassExA(&data));
        }

        static bool UnregisterClass(string_type className, HINSTANCE instance)
        {
            return UnregisterClassA(className, instance);
        }

        static LRESULT DefaultProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
        }

        static LRESULT DefaultProcedure(EventImpl<W64M::FilePlatformTraits> event)
        {
            return DefaultProcedure(event.window, static_cast<UINT>(event.type), event.wParam, event.lParam);
        }

        static HWND CreateWindow(WindowStyleEx extendedStyle, string_type className, string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* data)
        {
            return CreateWindowExA(
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
            return std::bit_cast<RetTy>(SetWindowLongPtrA(hwnd, index, std::bit_cast<LONG_PTR>(value)));
        }        
        
        template<class Ty = LONG_PTR>
            requires (sizeof(Ty) == 8)
        static Ty GetWindowData(HWND hwnd, int index)
        {
            return std::bit_cast<Ty>(GetWindowLongPtrA(hwnd, index));
        }
    };

    template<>
    struct DefaultClass<W64M::FilePlatformTraits> : public DefaultClassCommon
    {
        using string_type = W64M::FileStringType;

        static string_type ClassName() { return "DefaultClassW"; }
        static string_type MenuName() { return nullptr; }

        DefaultClass(HWND hwnd) {}

        static LRESULT Procedure(EventImpl<W64M::FilePlatformTraits> event)
        {
            if(static_cast<UINT>(event.type) == WM_DESTROY)
            {
                PostQuitMessage(0);
            }

            return W64M::FilePlatformTraits::DefaultProcedure(event);
        }
    };

    template<W64M::FileIsWindowClass Ty>
    struct WindowClassTraits<Ty> : public WindowClassTraitsBase<Ty, W64M::FilePlatformTraits>
    {

    };
}
