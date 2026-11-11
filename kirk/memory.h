#pragma once

#include "globals.h"
#include "ntdll.h"

#include <cstdint>
#include <string_view>
#include <winternl.h>
#include <optional>
#include <vector>
#include <memory>

using String = std::optional<std::string>;
using Pointer = std::optional<uintptr_t>;

namespace Memory {
	namespace detail {
		[[nodiscard]] bool read(uintptr_t addr, void* buffer, SIZE_T size);
	}

	[[nodiscard]] String readString(uintptr_t addr);

	[[nodiscard]] std::optional<std::vector<std::byte>> read(uintptr_t addr, uint32_t end);
	[[nodiscard]] bool read(std::vector<std::byte>& buff, uintptr_t addr, uint32_t end);

	template<typename T>
	[[nodiscard]] std::optional<T> read(uintptr_t addr) {
		T buffer{};
		if (!detail::read(addr, &buffer, sizeof(T))) return std::nullopt;
		return buffer;
	}

	template<typename T>
	[[nodiscard]] bool write(uintptr_t addr, const T& value) {
		SIZE_T bytesWritten = 0;
		NTSTATUS status = Luck_WriteVirtualMemory(
			MemGlobals::procHandle,
			reinterpret_cast<PVOID>(addr),
			&value,
			sizeof(T),
			&bytesWritten
		);

		return NT_SUCCESS(status) && bytesWritten == sizeof(T);
	}
}