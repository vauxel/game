#pragma once

#include <unordered_map>
#include "util/logger.h"
#include "systems/system.h"

struct Component {
  bool ready = false;

  virtual ~Component() = default;
};

#include "comp/spatial.h"
#include "comp/render.h"
#include "comp/light.h"

class System;

class Entity {
  public:
    unsigned int getId();
    void setId(unsigned int id);

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
    unsigned int entityId;
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
