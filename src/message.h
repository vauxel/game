#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>
#include <vector>
#include <functional>
#include <queue>
#include <map>

enum MessageType {
	INPUT
};

struct Message {
	virtual ~Message() {};
};

class MessageHandler {
	public:
		virtual void handleMessage(MessageType type, Message* msg) = 0;
};

class MessageDispatcher {
	public:
		static MessageDispatcher* instance();
		void registerHandler(MessageType type, MessageHandler* receiver);
		void dispatch(MessageType type, Message* msg);
	private:
		static MessageDispatcher* _instance;
		std::map<MessageType, std::vector<MessageHandler*>> handlers;

		MessageDispatcher();
		~MessageDispatcher();
};

#endif