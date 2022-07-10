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
        HWND m_windowHandle;
        Ty m_data;

    public:
        template<class... Params>
        WindowImpl(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, Params&&... params) :
            m_windowHandle(CreateHandle(extendedStyle, windowName, style, x, y, width, height, optionalParent, menu, hInstance)),
            m_data(m_windowHandle, std::forward<Params>(params)...)
        {
            platform_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, &m_data);
        }

        template<class... Params>
        WindowImpl(string_type windowName, WindowStyle style, int x, int y, int width, int height, HWND optionalParent, HMENU menu, HINSTANCE hInstance, Params&&... params) :
            WindowImpl(WindowStyleEx{ 0 }, windowName, style, x, y, width, height, optionalParent, menu, hInstance, std::forward<Params>(params)...)
        {

        }

        WindowImpl(const WindowImpl& other) = delete;
        WindowImpl(WindowImpl&& other) noexcept :
            m_windowHandle(std::move(other.m_windowHandle)),
            m_data(std::move(other.m_data))
        {
            other.m_windowHandle = nullptr;
            SetLastError(0);
            platform_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, &m_data);

            if(GetLastError() == ERROR_INVALID_WINDOW_HANDLE)
            {
                //Do nothing
            }
        }

        WindowImpl& operator=(const WindowImpl& other) = delete;
        WindowImpl& operator=(WindowImpl&& other) noexcept
        {
            m_windowHandle = std::move(other.m_windowHandle);
            other.m_windowHandle = nullptr;
            m_data = std::move(other.m_data);
            SetLastError(0);
            platform_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, &m_data);

            if(GetLastError() == ERROR_INVALID_WINDOW_HANDLE)
            {
                //Do nothing
            }
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
                throw std::exception("Failed to register class");
            }

            HWND handle = platform_traits::CreateWindow(extendedStyle, Ty::ClassName(), windowName, style, x, y, width, height, optionalParent, menu, hInstance, nullptr);

            if(handle == nullptr)
            {
                throw std::exception("Handle is null");
            }

            return handle;
        }
    };

    using EventA = EventImpl<MBCSPlatformTraits>;
    using EventW = EventImpl<UnicodePlatformTraits>;
    using Event = EventImpl<DefaultPlatformTraits>;

    template<EventType Type>
    using TypedEventA = TypedEventImpl<Type, MBCSPlatformTraits>;
    template<EventType Type>
    using TypedEventW = TypedEventImpl<Type, UnicodePlatformTraits>;
    template<EventType Type>
    using TypedEvent = TypedEventImpl<Type, DefaultPlatformTraits>;

    template<IsWindowClassA Ty>
        requires (!IsWindowClassW<Ty>)
    using WindowA = WindowImpl<Ty, MBCSPlatformTraits>;

    template<IsWindowClassW Ty>
        requires (!IsWindowClassA<Ty>)
    using WindowW = WindowImpl<Ty, UnicodePlatformTraits>;

    template<IsWindowClass Ty>
    using Window = WindowImpl<Ty, DefaultPlatformTraits>;

}