export module MoWin;

export import :Platform;
export import :Events;
export import :Window;

namespace MoWin
{
    export using EventA = EventImpl<MBCSPlatformTraits>;
    export using EventW = EventImpl<UnicodePlatformTraits>;
    export using Event = EventImpl<DefaultPlatformTraits>;

    export template<EventType Type>
        using TypedEventA = TypedEventImpl<Type, MBCSPlatformTraits>;
    export template<EventType Type>
        using TypedEventW = TypedEventImpl<Type, UnicodePlatformTraits>;
    export template<EventType Type>
        using TypedEvent = TypedEventImpl<Type, DefaultPlatformTraits>;

    export template<IsWindowClassA Ty>
        using WindowA = WindowImpl<Ty, MBCSPlatformTraits>;

    export template<IsWindowClassW Ty>
        using WindowW = WindowImpl<Ty, UnicodePlatformTraits>;

    export template<IsWindowClass Ty>
        using Window = WindowImpl<Ty, DefaultPlatformTraits>;

}