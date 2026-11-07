#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "json.hpp"
#include "typestable.h"
#include "offsetstable.h"

struct Field {
	uintptr_t* offset;
	uint32_t* type;

	Field(uintptr_t* offset, uint32_t* type = 0) : offset(offset), type(type) {}
};

struct TypeDef {
	std::unordered_map<std::string, Field> fields;
	uint32_t* start;
	uint32_t* end;

	TypeDef(std::unordered_map<std::string, Field> fields, uint32_t* start = 0, uint32_t* end = 0) : fields(std::move(fields)), start(start), end(end) {}

	void load(nlohmann::json& o, nlohmann::json& t);
};

namespace TypeMap {
	std::unordered_map<std::string, TypeDef> types;

	void loadTypesMap(nlohmann::json& o, nlohmann::json& t);
	void initTypes();
}