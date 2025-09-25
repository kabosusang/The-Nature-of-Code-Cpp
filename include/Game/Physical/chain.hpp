#pragma once
#include "body.hpp"
#include "box2d/collision.h"

class ShapeBodyImpl {
public:
	ShapeBodyImpl() {}
	b2BodyDef& getDef() { return bodydef_; }
	b2Polygon& getPloygon() { return bodybox_; }
	b2ShapeDef& getShap() { return bodyshape_; }

	b2BodyId getId() { return id_; }
	void setId(b2BodyId id) { id_ = id; }

	void destory() {
		if (id_.index1 != 0) {
			b2DestroyBody(id_);
		}
	}

    bool isValid(){
       return b2Body_IsValid(id_);
    }

protected:
	b2BodyDef bodydef_{};
	b2Polygon bodybox_{};
	b2ShapeDef bodyshape_{};
    b2ChainSegment chape_;
protected:
	b2BodyId id_;
};





