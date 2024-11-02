#include "papyrus.h"

#include "Debug/debug.h"

namespace Papyrus
{
	std::vector<int> GetVersion(STATIC_ARGS) {
		return { Plugin::VERSION[0], Plugin::VERSION[1], Plugin::VERSION[2] };
	}

	RE::BSFixedString DebugReference(STATIC_ARGS)
	{
		logger::debug("Call for debug");
		const auto ref = RE::Console::GetSelectedRef().get();
		if (!ref) {
			return "No reference.";
		}

		if (!Debug::Listener::GetSingleton()->PrintDebug(ref)) {
			return "Failed to debug selected reference.";
		}

		std::string_view refName = ref->GetName();
		const auto baseObject = ref->GetBaseObject();
		if (!baseObject) {
			return "Debugged reference.";
		}

		refName = refName.empty() ? Utilities::EDID::GetEditorID(ref) : refName;
		refName = refName.empty() ? baseObject->GetName() : refName;
		refName = refName.empty() ? baseObject->GetFormEditorID() : refName;
		refName = refName.empty() ? Utilities::EDID::GetEditorID(baseObject) : refName;

		if (refName.empty()) {
			return "Debugged reference.";
		}

		return fmt::format("Debugged {}.", refName);
	}

	void Bind(VM& a_vm) {
		BIND(GetVersion);
		BIND(DebugReference);
	}

	bool RegisterFunctions(VM* a_vm) {
		Bind(*a_vm);
		return true;
	}
}
