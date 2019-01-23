#include "resource.h"

ResourceManager* ResourceManager::_instance = 0;
ResourceManager::ResourceManager() {}

ResourceManager* ResourceManager::instance() {
	if(_instance == 0) {
		_instance = new ResourceManager();
	}

	return _instance;
}

void ResourceManager::loadResource(Resource* res, const string name, const string path) {
	res->setPath(path);
	res->setId(resources.size());

	int result = res->load();

	if(result == 0) {
		resources.emplace(name, res);
	} else {
		delete res;
	}
}

void Resource::setId(unsigned int id) {
	resourceId = id;
}

void Resource::setPath(const std::string path) {
	resourcePath = path;
}