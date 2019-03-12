#ifndef _RENDER_H_
#define _RENDER_H_

#include <string>
#include "util/logger.h"
#include "entity.h"
#include "resources/model.h"
#include "resources/texture.h"

struct Render : public Component {
	Model* model;
	Texture* texture;

	Render(std::string modelName, std::string texName);
	void render();
};

#endif