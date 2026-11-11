#include "sdk.h"

using namespace Sdk;

std::optional<Player::Object> Sdk::Player::getPlayer(uintptr_t addr) {
	auto buffer = Memory::read(addr, Types::Player::end);
	if (!buffer) return std::nullopt;

	Player::Object p{};
	memcpy(&p.localPlayer, buffer.value().data() + Offsets::Player::LocalPlayer, Types::Player::LocalPlayer);
	memcpy(&p.displayName, buffer.value().data() + Offsets::Player::DisplayName, Types::Player::DisplayName);
	memcpy(&p.modelInstance, buffer.value().data() + Offsets::Player::ModelInstance, Types::Player::ModelInstance);
	memcpy(&p.teamColor, buffer.value().data() + Offsets::Player::TeamColor, Types::Player::TeamColor);
	memcpy(&p.accountAge, buffer.value().data() + Offsets::Player::AccountAge, Types::Player::AccountAge);
	return p;
}

std::optional<Workspace::Object> Sdk::Workspace::getWorkspace(uintptr_t addr) {
	auto buffer = Memory::read(addr, Types::Workspace::end);
	if (!buffer) return std::nullopt;

	Workspace::Object w{};
	memcpy(&w.world, buffer.value().data() + Offsets::Workspace::World, Types::Workspace::World);
	memcpy(&w.currentCamera, buffer.value().data() + Offsets::Workspace::CurrentCamera, Types::Workspace::CurrentCamera);
	return w;
}

std::optional<Primitive::Object> Sdk::Primitive::getPrimitive(uintptr_t addr) {
	auto buffer = Memory::read(addr, Types::Primitive::end);
	if (!buffer) return std::nullopt;

	Primitive::Object p{};
	memcpy(&p.validate, buffer.value().data() + Offsets::Primitive::Validate, Types::Primitive::Validate);

	if ((p.validate & 1) != 0) return std::nullopt;

	memcpy(&p.rotation, buffer.value().data() + Offsets::Primitive::Rotation, Types::Primitive::Rotation);
	memcpy(&p.position, buffer.value().data() + Offsets::Primitive::Position, Types::Primitive::Position);
	memcpy(&p.assemblyLinearVelocity, buffer.value().data() + Offsets::Primitive::AssemblyLinearVelocity, Types::Primitive::AssemblyLinearVelocity);
	memcpy(&p.size, buffer.value().data() + Offsets::Primitive::Size, Types::Primitive::Size);
	memcpy(&p.owner, buffer.value().data() + Offsets::Primitive::Owner, Types::Primitive::Owner);

	return p;
}

std::optional<BasePart::Object> Sdk::BasePart::getBasePart(uintptr_t addr) {
	auto buffer = Memory::read(addr, Types::BasePart::end);
	if (!buffer) return std::nullopt;

	BasePart::Object b{};
	memcpy(&b.primitive, buffer.value().data() + Offsets::BasePart::Primitive, Types::BasePart::Primitive);
	memcpy(&b.shape, buffer.value().data() + Offsets::BasePart::Shape, Types::BasePart::Shape);

	return b;
}

String Sdk::Instance::getName(uintptr_t addr) {
	return String();
}

String Sdk::Instance::getClassName(uintptr_t addr) {
	return String();
}

bool Sdk::Instance::getChildren(const Instance::Object& obj, std::vector<uintptr_t>& vec) {
	auto buff = Memory::read(obj.children, 16);
	if (!buff) return false;
	uintptr_t start, end;
	memcpy(&start, buff.value().data(), sizeof(uintptr_t));
	memcpy(&end, buff.value().data() + sizeof(uintptr_t), sizeof(uintptr_t));

	if (end < start) return false;

	buff = Memory::read(start, end);
	if (!buff) return false;

	constexpr size_t step = sizeof(std::shared_ptr<uintptr_t>);
	size_t count = buff.value().size() / step;

	vec.reserve(vec.size() + count);

	for (size_t i = 0; i < count; ++i) {
		uintptr_t child;
		memcpy(&child, buff.value().data() + i * step, sizeof(uintptr_t));
		if (child) vec.push_back(child);
	}

	return true;
}

std::optional<Instance::Object> Sdk::Instance::getInstance(uintptr_t addr) {
	return std::optional<Instance::Object>();
}
