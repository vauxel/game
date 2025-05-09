#include "resource.h"

ResourceManager* ResourceManager::_instance = 0;
ResourceManager::ResourceManager() {}

ResourceManager* ResourceManager::instance() {
  if (_instance == 0) {
    _instance = new ResourceManager();
  }

  return _instance;
}

void ResourceManager::loadResource(Resource* res, std::string name, std::string path) {
  res->setPath(path.c_str());
  res->setId(resources.size());

  int result = res->load();

  if (result == 0) {
    resources.emplace(name, res);
  } else {
    LOG_ERROR("Failed to load resource \"%s\" at \"%s\"", name.c_str(), path.c_str());
    delete res;
  }
}

void Resource::setId(unsigned int id) {
  resourceId = id;
}

unsigned int Resource::getId() {
  return this->resourceId;
}

void Resource::setPath(const char* path) {
  resourcePath = path;
}

const char* Resource::getPath() {
  return this->resourcePath;
}
