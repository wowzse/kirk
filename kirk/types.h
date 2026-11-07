#pragma once

#include <vector>
#include <string>

#include "sdk.h"
#include "structs.h"

struct Mesh {

};

struct Part {
	uintptr_t part;
	uintptr_t prim;

	Vector3 pos;
	Vector3 rot;
	Vector3 size;

	const Mesh& mesh;
	
	bool update();

	void setPart(uintptr_t npart) {
		auto dn = Sdk::Part::getPrim(npart);
		if (!dn) return;

		part = npart;
		prim = *dn;

		update();
	}
};

struct Object {
	uintptr_t addr;
	std::string name;
	std::string className;

	std::vector<Part> parts;

	virtual ~Object() = default;
	Object(uintptr_t addr) : addr(addr) {}

	std::optional<Part*> getPart(int index) {
		if (index >= parts.size()) return std::nullopt;
		return &parts[index];
	}

	bool updateParts() {
		for (auto& part : parts) {
			if (!part.update()) return false;
		}
	}

	virtual bool update() { return true; }

};

struct Player : public Object {
	using Object::Object;

	bool update() override;
};

struct Map : public Object {
	using Object::Object;

	bool update() override;
};