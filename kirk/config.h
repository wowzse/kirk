#pragma once

#include "globals.h"

struct ConfigStruct {
	bool esp{ false };
};

namespace Config {
	ConfigStruct* current = new ConfigStruct();
	ConfigStruct* fresh = new ConfigStruct();

	inline void swap() {
		auto temp = current;
		fresh = current;
		current = temp;
		Globals::updateConfig.store(false);
	}
}