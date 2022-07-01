module;

#include <Windows.h>
#include <concepts>
#include <bit>

export module MoWin.Window:Win64.Unicode;

import :Common;

#undef RegisterClass
#undef UnregisterClass
#undef CreateWindow

export namespace MoWin
{
    template<class Ty>
    concept IsWindowClass = requires
    {
        { Ty::ClassName() } -> std::same_as<LPCWSTR>;
    } && (HasStaticProcedure<Ty> || HasObjectProcedure<Ty>);

    template<class Ty>
    concept FullWindowClass = IsWindowClass<Ty> && 
        StyleDefined<Ty> &&
        ExtraClassBytesDefined<Ty> &&
        ExtraWindowBytesDefined<Ty> &&
        IconDefined<Ty> &&
        CursorDefined<Ty> &&
        BackgroundBrushDefined<Ty> &&
        MenuDefined<Ty, LPCWSTR> && 
        SmallIconDefined<Ty>;

    

    template<>
    struct WindowTraits<LPCWSTR>
    {
        using standard_class_type = WNDCLASSW;
        using extended_class_type = WNDCLASSEXW;
        using string_type = LPCWSTR;

        static WindowClassAtom Register(const standard_class_type& data)
        {
            return WindowClassAtom(RegisterClassW(&data));
        }

        static WindowClassAtom Register(const extended_class_type& data)
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

        template<class Ty>
            requires (sizeof(Ty) == sizeof(void*))
        static LONG_PTR SetWindowData(HWND windowHandle, int offset, Ty data)
        {
            return SetWindowLongPtrW(windowHandle, offset, std::bit_cast<LONG_PTR>(data));
        }
    };

    template<>
    struct DefaultClass<LPCWSTR> : public DefaultClassCommon
    {
        using string_type = LPCWSTR;

        static string_type ClassName() { return L"DefaultClassW"; }
        static string_type MenuName() { return nullptr; }

        DefaultClass(HWND hwnd) {}

        static LRESULT Procedure(Event event)
        {
            if(static_cast<UINT>(event.type) == WM_DESTROY)
            {
                PostQuitMessage(0);
            }

            return WindowTraits<string_type>::DefaultProcedure(event.window, static_cast<UINT>(event.type), event.wParam, event.lParam);
        }
    };

    template<IsWindowClass Ty>
    struct WindowClassTraits<Ty> : public WindowClassTraitsBase<Ty, WindowTraits<LPCWSTR>>
    {
    };
}
