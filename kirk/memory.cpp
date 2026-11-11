#include "memory.h"

#include <array>

bool Memory::detail::read(uintptr_t addr, void* buffer, SIZE_T size) {
	SIZE_T bytesRead = 0;

	NTSTATUS status = Luck_ReadVirtualMemory(
		Globals::procHandle,
		reinterpret_cast<PVOID>(addr),
		buffer,
		size,
		&bytesRead
	);

	return NT_SUCCESS(status) && bytesRead == size;
}

String Memory::readString(uintptr_t addr) {
	std::array<char, 32> buff{};
	if (!detail::read(addr, buff.data(), buff.size())) return std::nullopt;

	int32_t len;
	std::memcpy(&len, buff.data() + 0x10, sizeof(len));
	if (len <= 0 || len > 0x1000) return std::nullopt;

	if (len < 16) return std::string(buff.data(), len);

	uintptr_t strAddr;
	std::memcpy(&strAddr, buff.data(), sizeof(strAddr));

	std::string result(len, '\0');
	if (!detail::read(strAddr, result.data(), result.size())) return std::nullopt;

	return result;
}

std::optional<std::vector<std::byte>> Memory::read(uintptr_t addr, uint32_t end) {
	std::vector<std::byte> buff(end);
	if (!detail::read(addr, buff.data(), buff.size())) return std::nullopt;
	return buff;
}

bool Memory::read(std::vector<std::byte>& buff, uintptr_t addr, uint32_t end) {
	buff.reserve(end);
	return detail::read(addr, buff.data(), buff.size());
}
