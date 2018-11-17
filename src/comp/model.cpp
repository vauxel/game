#include "model.h"

void Model::init(const std::string meshName, const std::string matName) {
    mesh = ResourceManager::instance()->getResource<Mesh>(meshName);
    //material = ResourceManager::instance()->getResource<Material>(matName);
}