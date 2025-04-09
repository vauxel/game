#include "entity.h"

EntityManager* EntityManager::_instance = 0;
EntityManager::EntityManager() {}

EntityManager* EntityManager::instance() {
  if (_instance == 0) {
    _instance = new EntityManager();
  }

  return _instance;
}

void EntityManager::registerSystem(System* system) {
  systems.emplace_back(system);
}

void EntityManager::attachToSystems(Entity* entity) {
  for (size_t i = 0; i < systems.size(); i++) {
    systems[i]->attachEntity(entity);
  }
}

void EntityManager::detachFromSystems(Entity* entity) {
  for (size_t i = 0; i < systems.size(); i++) {
    systems[i]->detachEntity(entity);
  }
}

void EntityManager::instantiate(Entity* entity) {
  entity->setId(++lastEntityId);
  attachToSystems(entity);
  LOG_DEBUG("Entity [id=%d] instantiated", lastEntityId);
}

unsigned int Entity::getId() {
  return entityId;
}

void Entity::setId(unsigned int id) {
  if (!entityId) {
    entityId = id;
  }
}
