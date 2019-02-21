#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include "systems/system.h"
#include "comp/spatial.h"
#include "comp/render.h"

class System;

enum EntityFlags {
	NONE = 0x00,
	RENDERABLE = 0x01,
	CONTROLLABLE = 0x02
};

class Entity {
	public:
		int entityId;

		virtual unsigned int flags() { return EntityFlags::NONE; }
		virtual Spatial* spatial() { return nullptr; }
		virtual Render* render() { return nullptr; }
};

class EntityManager {
	private:
		static EntityManager* _instance;
		
		int lastEntityId = 0;
		std::vector<System*> systems;

		EntityManager();
		void attachToSystems(Entity* entity);
		void detachFromSystems(Entity* entity);
	public:
		static EntityManager* instance();

		template<typename T>
		T* spawn() {
			T* entity = new T();
			entity->entityId = ++lastEntityId;
			attachToSystems(entity);
			return entity;
		}

		void registerSystem(System* system);
};

#endif