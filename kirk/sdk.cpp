#include "sdk.h"

using namespace Sdk;

std::optional<Sdk::Instance::Header> Sdk::Instance::getHeader(uintptr_t addr) {
	auto buff = Memory::read(addr, Types::Instance::end);
	if (!buff) return std::nullopt;

	Instance::Header h{};
	memcpy(&h.classDescriptor, buff->data() + Offsets::Instance::ClassDescriptor, sizeof(uintptr_t));
	memcpy(&h.nameContainer, buff->data() + Offsets::Instance::NameContainer, sizeof(uintptr_t));
	return h;
}

String Sdk::Instance::getClassName(uintptr_t addr) {
	auto it = Instance::classNames.find(addr);
	if (it != Instance::classNames.end()) return it->second;

	auto cont = Memory::read<uintptr_t>(addr + Offsets::Instance::ClassDescriptor);
	if (!cont) return std::nullopt;
	auto name = Memory::readString(*cont + Offsets::Instance::ClassName);
	if (name) Instance::classNames.emplace(addr, *name);
	return name;
}