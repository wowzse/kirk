#pragma once

#include <windows.h>
#include <optional>
#include <string>
#include <vector>

#include "typestable.h"
#include "offsetstable.h"
#include "structs.h"
#include "memory.h"

using Pointer = std::optional<uintptr_t>;
using String = std::optional<std::string>;

namespace Sdk {
	struct Object {
		std::vector<std::byte> buffer;
		uintptr_t addr;
		uint32_t end;

		Object(uintptr_t addr, uint32_t end) : addr(addr), end(end) {};
	};

	namespace Player {
		struct Object {
			uintptr_t localPlayer;
			std::string displayName;
			uintptr_t modelInstance;
			int teamColor;
			int accountAge;
		};

		std::optional<Player::Object> getPlayer(uintptr_t addr);
	}

	namespace Workspace {
		struct Object {
			uintptr_t world;
			uintptr_t currentCamera;
		};

		std::optional<Workspace::Object> getWorkspace(uintptr_t addr);
	}

	namespace Primitive {
		struct Object {
			uintptr_t validate;
			Matrix3x3 rotation;
			Vector3 position;
			Vector3 assemblyLinearVelocity;
			Vector3 size;
			uintptr_t owner;
		};

		std::optional<Primitive::Object> getPrimitive(uintptr_t addr);
	}

	namespace Instance {
		String getName(uintptr_t addr);
		String getClassName(uintptr_t addr);

		struct Object {
			std::string name;
			std::string className;
			uintptr_t parent;
			uintptr_t children;
		};

		bool getChildren(const Instance::Object& obj, std::vector<uintptr_t>& vec);
		std::optional<Instance::Object> getInstance(uintptr_t addr);
	}

	namespace BasePart {
		struct Object {
			uintptr_t primitive;
			int shape;
		};

		std::optional<BasePart::Object> getBasePart(uintptr_t addr);
	}
}