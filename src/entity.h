#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <unordered_map>
#include "util/logger.h"
#include "systems/system.h"

struct Component {
	virtual ~Component() = default;
};

#include "comp/spatial.h"
#include "comp/render.h"

class System;

class Entity {
	public:
		void setId(int id);

		template<typename T, typename... Args>
		T* assign(Args... args) {
			T* comp = new T(args...);
			components[&typeid(*comp)] = comp;
			return comp;
		}

		template<typename T>
		T* get() {
			return components.count(&typeid(T)) != 0 ? dynamic_cast<T*>(components[&typeid(T)]) : nullptr;
		}

		template<typename T>
		bool has() {
			return get<T>() != nullptr;
		}
	private:
		int entityId;
		std::unordered_map<const std::type_info*, Component*> components;
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
		void instantiate(Entity* entity);
		void registerSystem(System* system);
};

#endif