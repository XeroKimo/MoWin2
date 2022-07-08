module;

#include <Windows.h>
#include <memory>

export module MoWin.Window;
export import :Common;

#ifdef _WIN64
export import :Platform.Win64.Unicode;
export import :Platform.Win64.MBCS;
#endif

#undef CreateWindow

export namespace MoWin
{

    template<class Ty, class Traits>
    class WindowImpl
    {    
    private:
        using class_traits = WindowClassTraits<Ty>;
        using platform_traits = Traits;
        using string_type = platform_traits::string_type;

    private:
        Ty m_data;
        HWND m_windowHandle;

    public:
        template<class... Params>
        WindowImpl(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, Params&&... params) :
            m_data(std::forward<Params>(params)...),
            m_windowHandle(CreateHandle(extendedStyle, windowName, style, x, y, width, height, optionalParent, menu, hInstance))
        {
        }

        template<class... Params>
        WindowImpl(string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, Params&&... params) :
            WindowImpl(WindowStyleEx{ 0 }, windowName, style, x, y, width, height, optionalParent, menu, hInstance, std::forward<Params>(params)...)
        {

        }

        WindowImpl(const WindowImpl& other) = delete;
        WindowImpl(WindowImpl&& other) noexcept :
            m_data(std::move(other.m_data)),
            m_windowHandle(std::move(other.m_windowHandle))
        {
            other.m_windowHandle = nullptr;
            platform_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, &m_data);
        }

        WindowImpl& operator=(const WindowImpl& other) = delete;
        WindowImpl& operator=(WindowImpl&& other) noexcept
        {
            m_windowHandle = std::move(other.m_windowHandle);
            other.m_windowHandle = nullptr;
            m_data = std::move(other.m_data);
            platform_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, &m_data);
            return *this;
        }

        ~WindowImpl()
        {
            DestroyWindow(m_windowHandle);
        }


    public:
        operator HWND() const { return m_windowHandle; }

    public:
        void Show() const
        {
            ::ShowWindow(m_windowHandle, SW_SHOW);
        }
        void Maximize() const
        {
            ::ShowWindow(m_windowHandle, SW_MAXIMIZE);
        }
        void Minimize() const
        {
            ::ShowWindow(m_windowHandle, SW_MINIMIZE);
        }

        Ty& ClassData() { return m_data; }
        const Ty& ClassData() const { return m_data; }

    private:
        HWND CreateHandle(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance)
        {
            if(!class_traits::Register(hInstance))
            {
                //Throw
            }

            return platform_traits::CreateWindow(extendedStyle, Ty::ClassName(), windowName, style, x, y, width, height, optionalParent, menu, hInstance, &m_data);
        }
    };

    template<IsWindowClassA Ty>
    using WindowA = WindowImpl<Ty, MBCSPlatformTraits>;

    template<IsWindowClassW Ty>
    using WindowW = WindowImpl<Ty, UnicodePlatformTraits>;

    template<IsWindowClass Ty>
    using Window = WindowImpl<Ty, DefaultPlatformTraits>;

}