#include "message.h"

MessageDispatcher* MessageDispatcher::_instance = 0;
MessageDispatcher::MessageDispatcher() { }
MessageDispatcher::~MessageDispatcher() { }

MessageDispatcher* MessageDispatcher::instance() {
	if (_instance == 0) {
		_instance = new MessageDispatcher();
	}

	return _instance;
}

void MessageDispatcher::registerHandler(MessageType type, MessageHandler* handler) {
	handlers[type].push_back(handler);
}

void MessageDispatcher::dispatch(MessageType type, Message* data) {
	for(unsigned int i = 0; i < handlers[type].size(); i++) {
		handlers[type][i]->handleMessage(type, data);
	}
}