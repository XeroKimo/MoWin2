#pragma once
#include "WindowClass.h"

namespace MoWin
{

    class WindowView;

    template<class... Ty>
    class Window;
    
    template<>
    class Window<>
    {
        HWND m_windowHandle;

    public:
        Window(WindowStyleEx extendedStyle, LPCSTR className, LPCSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData)
        {
            m_windowHandle = (WindowClassTraits<WNDCLASSA>::CreateWindow)(
                extendedStyle,
                className,
                windowName,
                style,
                x,
                y,
                width,
                height,
                optionalParent,
                menu,
                hInstance,
                extraData);
        }

        Window(WindowStyleEx extendedStyle, LPCWSTR className, LPCWSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData)
        {
            m_windowHandle = (WindowClassTraits<WNDCLASSW>::CreateWindow)(
                extendedStyle,
                className,
                windowName,
                style,
                x,
                y,
                width,
                height,
                optionalParent,
                menu,
                hInstance,
                extraData);
        }

        Window(WindowStyleEx extendedStyle, WindowClassAView windowClass, LPCSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) :
            Window(extendedStyle, static_cast<LPCSTR>(windowClass), windowName, style, x, y, width, height, optionalParent, menu, hInstance, extraData)
        {
        }

        Window(WindowStyleEx extendedStyle, WindowClassWView windowClass, LPCWSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) :
            Window(extendedStyle, static_cast<LPCWSTR>(windowClass), windowName, style, x, y, width, height, optionalParent, menu, hInstance, extraData)
        {
        }

        Window(LPCSTR className, LPCSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) :
            Window(WindowStyleEx{ 0 }, className, windowName, style, x, y, width, height, optionalParent, menu, hInstance, extraData)
        {
        }

        Window(LPCWSTR className, LPCWSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) :
            Window(WindowStyleEx{ 0 }, className, windowName, style, x, y, width, height, optionalParent, menu, hInstance, extraData)
        {
        }

        Window(WindowClassAView windowClass, LPCSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) :
            Window(static_cast<LPCSTR>(windowClass), windowName, style, x, y, width, height, optionalParent, menu, hInstance, extraData)
        {
        }

        Window(WindowClassWView windowClass, LPCWSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) :
            Window(static_cast<LPCWSTR>(windowClass), windowName, style, x, y, width, height, optionalParent, menu, hInstance, extraData)
        {
        }

        operator HWND() const { return m_windowHandle; }
    };

    Window(WindowStyleEx extendedStyle, LPCSTR className, LPCSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) -> Window<>;
    Window(WindowStyleEx extendedStyle, LPCWSTR className, LPCWSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) -> Window<>;
    Window(WindowStyleEx extendedStyle, WindowClassAView className, LPCSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) -> Window<>;
    Window(WindowStyleEx extendedStyle, WindowClassWView className, LPCWSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) -> Window<>;

    Window(LPCSTR className, LPCSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) -> Window<>;
    Window(LPCWSTR className, LPCWSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) -> Window<>;
    Window(WindowClassAView className, LPCSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) -> Window<>;
    Window(WindowClassWView className, LPCWSTR windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) -> Window<>;

    template<IsStaticWindowClass Ty>
    class Window<Ty>
    {
    private:
        using window_class_traits = StaticWindowClassTraits<Ty>;
        using string_type = window_class_traits::string_type;

    private:
        HWND m_windowHandle;

    public:
        Window(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData)
        {
            if(!window_class_traits::Registered())
                window_class_traits::Register(hInstance);

            m_windowHandle = (window_class_traits::CreateWindow)(
                extendedStyle,
                windowName,
                style,
                x,
                y,
                width,
                height,
                optionalParent,
                menu,
                hInstance,
                extraData);
        }

        Window(string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, void* extraData) :
            Window(WindowStyleEx{ 0 }, windowName, style, x, y, width, height, optionalParent, menu, hInstance, extraData)
        {

        }

        operator HWND() const { return m_windowHandle; }
    };
}