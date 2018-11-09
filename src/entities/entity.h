#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include "systems/system.h"

class System;

class Entity {
	public:
		int flags = 0;
		virtual ~Entity() {};
};

class EntityManager {
	private:
		static EntityManager* _instance;

		std::vector<Entity*> entities;
		std::vector<System*> systems;

		EntityManager();
		void attachToSystems(Entity* entity);
	public:
		static EntityManager* instance();

		template<typename T>
		T* spawn() {
			T* entity = new T();
			entities.push_back(entity);
			attachToSystems(entity);
			return entity;
		}

		void registerSystem(System* system);
};

enum EntityFlags : int {
	RENDERABLE = (1 << 0),
	CONTROLLABLE = (1 << 1),
};

inline constexpr EntityFlags operator&(EntityFlags x, EntityFlags y) {
	return static_cast<EntityFlags>(static_cast<int>(x) & static_cast<int>(y));
}

inline constexpr EntityFlags operator|(EntityFlags x, EntityFlags y) {
	return static_cast<EntityFlags>(static_cast<int>(x) | static_cast<int>(y));
}

inline constexpr EntityFlags operator^(EntityFlags x, EntityFlags y) {
	return static_cast<EntityFlags>(static_cast<int>(x) ^ static_cast<int>(y));
}

inline constexpr EntityFlags operator~(EntityFlags x) {
	return static_cast<EntityFlags>(~static_cast<int>(x));
}

inline EntityFlags &operator&=(EntityFlags& x, EntityFlags y) {
	x = x & y;
	return x;
}

inline EntityFlags &operator|=(EntityFlags& x, EntityFlags y) {
	x = x | y;
	return x;
}

inline EntityFlags &operator^=(EntityFlags& x, EntityFlags y) {
	x = x ^ y;
	return x;
}

#endif