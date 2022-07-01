module;

#include <Windows.h>
#include <memory>

export module MoWin.Window;
export import :Common;

#ifdef _WIN64
export import :Win64;
#endif

#undef CreateWindow

export namespace MoWin
{


    template<IsWindowClass Ty>
    class Window
    {
    private:
        using class_traits = WindowClassTraits<Ty>;
        using string_type = class_traits::string_type;
        using window_traits = WindowTraits<string_type>;

    private:
        HWND m_windowHandle;
        Ty m_data;

    public:
        template<class... Params>
        Window(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, Params&&... params) :
            m_windowHandle(CreateHandle(extendedStyle, windowName, style, x, y, width, height, optionalParent, menu, hInstance)),
            m_data(m_windowHandle, std::forward<Params>(params)...)
        {
            //SetWindowLongPtrW(m_windowHandle, GWLP_USERDATA, std::bit_cast<LONG_PTR>(m_data.get()));

            auto f = std::bit_cast<Ty*>(GetWindowLongPtrW(m_windowHandle, GWLP_USERDATA));
            auto f2 = &m_data;
            int i = 0;
        }

        template<class... Params>
        Window(string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, Params&&... params) :
            Window(WindowStyleEx{ 0 }, windowName, style, x, y, width, height, optionalParent, menu, hInstance, std::forward<Params>(params)...)
        {

        }

        Window(const Window& other) = delete;
        Window(Window&& other) noexcept :
            m_windowHandle(std::move(other.m_windowHandle)),
            m_data(std::move(other.m_data))
        {
            window_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, &m_data);
        }

        Window& operator=(const Window& other) = delete;
        Window& operator=(Window&& other) noexcept
        {
            m_windowHandle = std::move(other.m_windowHandle);
            m_data = std::move(other.m_data);
            window_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, &m_data);
            return *this;
        }

        ~Window()
        {
            DestroyWindow(m_windowHandle);
        }


    public:
        operator HWND() const { return m_windowHandle; }

    private:
        HWND CreateHandle(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance)
        {
            if(!class_traits::Register(hInstance))
            {
                //Throw
            }

            return window_traits::CreateWindow(extendedStyle, Ty::ClassName(), windowName, style, x, y, width, height, optionalParent, menu, hInstance, &m_data);
        }
    };
}