#pragma once

#include <vector>
#include "entity.h"
#include "message.h"

class Entity;

class System : public MessageHandler {
	public:
		virtual ~System() {};
		virtual void attachEntity(Entity* entity) = 0;
		virtual void detachEntity(Entity* entity) {
			for(unsigned int i = 0; i < entities.size(); i++) {
				if(entities[i] == entity) {
					entities.erase(entities.begin() + i);
					break;
				}
			}
		};
		virtual void loop() = 0;

		std::vector<Entity*> entities;
};
