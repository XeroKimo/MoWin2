#pragma once
#include <bit>
#include <Windows.h>
#include <concepts>
#include <optional>

namespace MoWin
{
    enum class WindowClassAtom : ATOM {};

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
}