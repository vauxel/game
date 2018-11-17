#ifndef _STATICOBJECT_H_
#define _STATICOBJECT_H_

#include "entity.h"
#include "comp/spatial.h"
#include "comp/model.h"

class StaticObject : public Entity {
	private:
		unsigned int _flags = EntityFlags::RENDERABLE;
		
		Spatial _spatial;
		Model _model;
	public:
		unsigned int flags() { return _flags; }
		Spatial* spatial() override { return &_spatial; }
		Model* model() override { return &_model; }
};

#endif