#pragma once

#include "utilities/utilities.h"

namespace Debug
{
	class Listener : public Utilities::Singleton::ISingleton<Listener> {
	public:
		bool PrintDebug(const RE::TESObjectREFR* a_ref);

	private:
	};
}