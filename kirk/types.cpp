#include "types.h"

bool Part::update() {
	return Sdk::Part::getPrimData(prim, pos, rot, size);
}

bool Player::update() {
    return false;
}

bool Map::update() {
    return false;
}
