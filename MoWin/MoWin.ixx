module;

#include <Windows.h>
#include <string>
#include <tuple>

export module MoWin;
export import :Event;
export import :Window;

#undef CreateWindow

namespace MoWin
{

    template<class Ty>
    LRESULT ProcedureLandingPad(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        AnyEvent e{ hwnd, uMsg, wParam, lParam };

        if(uMsg == WM_CREATE)
        {
            try
            {
                CREATESTRUCT& cs = Event<WM_CREATE>::GetCreateStruct(e);
                ClassConstructor<Ty>& constructor = *reinterpret_cast<ClassConstructor<Ty>*>(cs.lpCreateParams);
                e.window.SetUserData(*constructor.Create(hwnd));
            }
            catch(...)
            {
                return Event<WM_CREATE>::Result.Destroy;
            }
        }

        if(auto pThis = e.window.GetUserData<Ty>(); pThis)
        {
            LRESULT result = 0;
            try
            {
                result = (*pThis)(e);
            }
            catch(...)
            {

            }
            if(uMsg == WM_DESTROY)
            {
                delete e.window.GetUserData<Ty>();
            }

            return result;
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    export LRESULT DefaultWindowProcedure(AnyEvent e)
    {
        return DefWindowProc(e.window.GetHandle(), e.messsageType, e.wParam, e.lParam);
    }

#undef RegisterClass
    export struct WindowClassAtom
    {
        ATOM atom;

        operator ATOM() const { return atom; }
        operator LPCSTR() const { return reinterpret_cast<LPCSTR>(atom); }
        operator LPCWSTR() const { return reinterpret_cast<LPCWSTR>(atom); }
    };

    export template<class Ty>
        WindowClassAtom RegisterClass()
    {
        Ty::classDefinition.lpfnWndProc = &ProcedureLandingPad<Ty>;
        return Ty::classAtom = WindowClassAtom{ ::RegisterClassExW(&Ty::classDefinition) };
    }
}