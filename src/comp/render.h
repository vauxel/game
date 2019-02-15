#ifndef _RENDER_H_
#define _RENDER_H_

#include <string>
#include "resources/model.h"
#include "resources/texture.h"

class Render {
	public:
		Model* model;
		Texture* texture;

		void init(std::string modelName, std::string texName);
		void render();
};

#endif