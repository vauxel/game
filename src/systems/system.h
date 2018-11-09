#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <vector>
#include "entities/entity.h"

class Entity;

class System {
	public:
		virtual ~System() {};
		virtual void attachEntity(Entity*) = 0;
		virtual void loop() = 0;

		std::vector<Entity*> entities;
};

#endif