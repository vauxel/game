#ifndef _INPUT_MESSAGE_H_
#define _INPUT_MESSAGE_H_

#include "message.h"

struct InputMsg : Message {
	int keycode;
	InputMsg(int keycode) : keycode(keycode) {};
};

#endif