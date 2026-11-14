#pragma once

#include <windows.h>
#include <optional>
#include <string>
#include <vector>
#include <unordered_map>

#include "typestable.h"
#include "offsetstable.h"
#include "structs.h"
#include "memory.h"

using Pointer = std::optional<uintptr_t>;
using String = std::optional<std::string>;

namespace Sdk {
	template<typename T>
	inline T field(const std::byte* base, uintptr_t off) {
		T v{};
		memcpy(&v, base + off, sizeof(T));
		return v;
	}

	namespace Instance {
		inline std::unordered_map<uintptr_t, std::string> classNames;

		struct Header {
			uintptr_t classDescriptor;
			uintptr_t nameContainer;
		};

		String getClassName(uintptr_t addr);
		std::optional<Instance::Header> getHeader(uintptr_t addr);
	}
}