#pragma once

#include <string>
#include "util/logger.h"
#include "entity.h"
#include "resources/model.h"
#include "resources/texture.h"
#include "resources/shader.h"

struct Render : public Component {
	Model* model;
	Texture* texture;

	Render(std::string modelName, std::string texName);
	void render(Shader* shader);
};
