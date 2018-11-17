#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include "resources/mesh.h"
//#include "resources/material.h"

class Model {
	public:
		Mesh* mesh;
		//Material* material;

		void init(const std::string meshName, const std::string matName);
};

#endif