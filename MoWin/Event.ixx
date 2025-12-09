module;
#include <Windows.h>

export module MoWin:Event;
import :Window;

namespace MoWin
{
	export struct AnyEvent
	{
		AnyWindowView window;
		UINT messsageType;
		WPARAM wParam;
		LPARAM lParam;
	};

	export template<UINT MessageType>
	struct Event;

	template<>
	struct Event<WM_CREATE> : AnyEvent
	{
		static CREATESTRUCT& GetCreateStruct(const AnyEvent& e) { return *reinterpret_cast<CREATESTRUCT*>(e.lParam); }
		CREATESTRUCT& GetCreateStruct() const { return GetCreateStruct(*this); }

		static constexpr struct
		{
			static constexpr LRESULT Continue = 0;
			static constexpr LRESULT Destroy = -1;
		} Result;
	};

	template<>
	struct Event<WM_DESTROY> : AnyEvent
	{
		struct ResultT
		{
			static constexpr LRESULT Processed = 0;
		};

		static constexpr ResultT Result;
	};
}