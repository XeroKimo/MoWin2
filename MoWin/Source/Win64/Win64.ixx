module;

#include <Windows.h>
#include <concepts>
#include <bit>

export module MoWin.Window:Win64;


#ifdef _UNICODE
export import :Win64.Unicode;
#endif

export namespace MoWin
{

}