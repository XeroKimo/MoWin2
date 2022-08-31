module;

#include <Windows.h>
#include <memory>

export module MoWin:Window;
export import :Window.Common;

#undef CreateWindow

namespace MoWin
{
    template<class DerivedSelf, class PlatformTrait>
    struct WindowInterface
    {
        using platform_traits = PlatformTrait;

        BOOL IsChildOf(HWND parent) const
        {
            return ::IsChild(parent, Handle());
        }

        void Hide() const
        {
            ::ShowWindow(Handle(), SW_HIDE);
        }

        void Show() const
        {
            ::ShowWindow(Handle(), SW_SHOW);
        }

        void Minimize() const
        {
            ::ShowWindow(Handle(), SW_MINIMIZE);
        }

        void Maximize() const
        {
            ::ShowWindow(Handle(), SW_MAXIMIZE);
        }

        void Restore() const
        {
            ::ShowWindow(Handle(), SW_RESTORE);
        }
    private:
        HWND Handle() const { return *(static_cast<const DerivedSelf*>(this)); }
    };

    export enum class WindowCreateFlag
    {
        None = 0,
        Adjust_Size_For_Client = 1 << 0
    };
    DEFINE_ENUM_FLAG_OPERATORS(WindowCreateFlag);

    export template<class Ty, class PlatformTrait>
        requires IsWindowClassImpl<Ty, PlatformTrait>
    class WindowImpl : public WindowInterface<WindowImpl<Ty, PlatformTrait>, PlatformTrait>
    {
    public:
        using class_traits = WindowClassTraits<Ty>;
        using platform_traits = PlatformTrait;
        using string_type = platform_traits::string_type;

    private:
        HWND m_windowHandle;

    public:
        template<class... Params>
        WindowImpl(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, POINT position, Dimension2D lengths, HWND optionalParent, HMENU menu, HINSTANCE hInstance, WindowCreateFlag flags, Params&&... params) :
            m_windowHandle(CreateHandle(extendedStyle, windowName, style, Rect{ position, lengths }, optionalParent, menu, hInstance, flags))
        {
            Ty* data = new Ty(m_windowHandle, std::forward<Params>(params)...);
            platform_traits::SetWindowData(m_windowHandle, GWLP_USERDATA, data);
        }

        template<class... Params>
        WindowImpl(string_type windowName, WindowStyle style, POINT position, Dimension2D lengths, HWND optionalParent, HMENU menu, HINSTANCE hInstance, WindowCreateFlag flags, Params&&... params) :
            WindowImpl(WindowStyleEx{ 0 }, windowName, style, position, lengths, optionalParent, menu, hInstance, flags, std::forward<Params>(params)...)
        {

        }

        WindowImpl(const WindowImpl& other) = delete;
        WindowImpl(WindowImpl&& other) noexcept :
            m_windowHandle(std::move(other.m_windowHandle))
        {
            other.m_windowHandle = nullptr;

            SetLastError(0);
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

            SetLastError(0);
            if(GetLastError() == ERROR_INVALID_WINDOW_HANDLE)
            {
                //Do nothing
            }
            return *this;
        }

        bool operator==(std::nullptr_t) const { return ::IsWindow(m_windowHandle); }
        bool operator!=(std::nullptr_t) const { return ::IsWindow(m_windowHandle); }

        ~WindowImpl()
        {
            DestroyWindow(m_windowHandle);
        }



    public:
        operator HWND() const { return m_windowHandle; }

    public:
        Ty& ClassData() { return *platform_traits::template GetWindowData<Ty*>(m_windowHandle, GWLP_USERDATA); }
        const Ty& ClassData() const { return *platform_traits::template GetWindowData<Ty*>(m_windowHandle, GWLP_USERDATA); }

    private:
        HWND CreateHandle(WindowStyleEx extendedStyle, string_type windowName, WindowStyle style, Rect windowRect, HWND optionalParent, HMENU menu, HINSTANCE hInstance, WindowCreateFlag flags)
        {
            class_traits::Register(hInstance);

            if((flags & WindowCreateFlag::Adjust_Size_For_Client) == WindowCreateFlag::Adjust_Size_For_Client)
            {
                ::AdjustWindowRectEx(&windowRect, static_cast<DWORD>(style), menu != nullptr, static_cast<DWORD>(extendedStyle));
            }

            HWND handle = platform_traits::CreateWindow(extendedStyle, Ty::ClassName(), windowName, style, windowRect.left, windowRect.top, windowRect.Lengths().width, windowRect.Lengths().height, optionalParent, menu, hInstance, nullptr);

            Rect rect;
            ::GetWindowRect(handle, &rect);

            if(handle == nullptr)
            {
                throw std::exception("Handle is null");
            }

            return handle;
        }
    };
}