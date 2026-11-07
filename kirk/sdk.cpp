#include "sdk.h"

using namespace Sdk;

std::optional<Player::Object> Sdk::Player::getPlayer() {
	return std::optional<Player::Object>();
}

std::optional<Workspace::Object> Sdk::Workspace::getWorkspace(uintptr_t addr) {
	return std::optional<Workspace::Object>();
}

std::optional<Primitive::Object> Sdk::Primitive::getPrimitive(uintptr_t addr) {
	return std::optional<Primitive::Object>();
}

std::optional<BasePart::Object> Sdk::BasePart::getBasePart(uintptr_t addr) {
	return std::optional<BasePart::Object>();
}

String Sdk::Instance::getName(uintptr_t addr) {
	return String();
}

String Sdk::Instance::getClassName(uintptr_t addr) {
	return String();
}

std::optional<std::vector<uintptr_t>> Sdk::Instance::getChildren(const Instance::Object& obj) {
	return std::optional<std::vector<uintptr_t>>();
}

std::optional<Instance::Object> Sdk::Instance::getInstance(uintptr_t addr) {
	return std::optional<Instance::Object>();
}
