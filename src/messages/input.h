#pragma once

#include "message.h"

struct InputMsg : Message {
	int keycode;
	InputMsg(int keycode) : keycode(keycode) {};
};
