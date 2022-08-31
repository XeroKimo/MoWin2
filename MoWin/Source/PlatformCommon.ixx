module;

#include <Windows.h>

export module MoWin:Platform.Common;

namespace MoWin
{
    export enum class Platform
    {
        Win32,
        Win64
    };

    export enum class CharacterSet
    {
        MBCS,
        Unicode
    };

    export template<Platform P, CharacterSet C>
        struct PlatformTraits;

    export struct Dimension2D
    {
        LONG width;
        LONG height;
    };

    export struct Rect : public RECT
    {
        Rect() = default;
        Rect(POINT position, Dimension2D size) :
            RECT{ position.x, position.y, position.x + size.width, position.y + size.height }
        {

        }

        POINT Center() const { return POINT{ (left + right) / 2, (top + bottom) / 2 }; }
        Dimension2D Lengths() const { return Dimension2D{ right - left, bottom - top }; }
    };

}