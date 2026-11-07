#pragma once

#include "fields.h"
#include "globals.h"
#include "req.h"

inline bool jCheck(nlohmann::json& j) {
	return j.contains("error") || !j.contains("Offsets");
}

inline bool loadOffsets() {
	std::wstring oendpt = L"/" + Globals::procVersion + L"/offsets.json";
	std::wstring tendpt = L"/" + Globals::procVersion + L"/types.json";

	std::optional<std::string> ores = httpReq(L"offsets.imtheo.lol", oendpt);
	std::optional<std::string> tres = httpReq(L"offsets.imtheo.lol", tendpt);
	if (!ores || !tres) return false;

	nlohmann::json oresp = nlohmann::json::parse(*ores);
	nlohmann::json tresp = nlohmann::json::parse(*tres);

	if (jCheck(oresp) || jCheck(tresp)) return false;

	TypeMap::loadTypesMap(oresp["Offsets"], tresp["Types"]);
}