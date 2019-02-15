#ifndef _STATICOBJECT_H_
#define _STATICOBJECT_H_

#include "entity.h"
#include "comp/spatial.h"
#include "comp/render.h"

class StaticObject : public Entity {
	private:
		unsigned int _flags = EntityFlags::RENDERABLE;
		
		Spatial _spatial;
		Render _render;
	public:
		unsigned int flags() { return _flags; }
		Spatial* spatial() override { return &_spatial; }
		Render* render() override { return &_render; }
};

#endif