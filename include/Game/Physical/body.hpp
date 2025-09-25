#pragma once
#include "Game/Physical/body.hpp"
#include "box2d/math_functions.h"
#include <box2d/box2d.h>

#include "world.hpp"

enum class BodyType {
	kStatic = 0,
	kDynamic,
};

enum class BodyShape {
	kRect = 0,
	kCircle,
	kChain,

};

class BodyImpl {
public:
	BodyImpl() {}
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
protected:
	b2BodyId id_;
};

template <BodyType T, BodyShape S>
class Body final{
	Body();
	Body(b2Vec2 half) {
		static_assert(false, "Error StaticBody");
	}
	void Init() {
		static_assert(false, "Error Init");
	}

	void CreateBody() {
		static_assert(false, "Error CreateBody");
	}
};

template <>
class Body<BodyType::kStatic, BodyShape::kRect> final : public BodyImpl {
public:
	Body() {}
	explicit Body(b2Vec2 half) {
		bodydef_.type = b2_staticBody;
		bodydef_ = b2DefaultBodyDef();
		bodybox_ = b2MakeBox(half.x, half.y); // 修改尺寸：4米宽，0.5米高
		bodyshape_ = b2DefaultShapeDef();
	}
	void Init(b2Vec2 half) {
		bodydef_ = b2DefaultBodyDef();
		bodybox_ = b2MakeBox(half.x, half.y); // 修改尺寸：4米宽，0.5米高
		bodyshape_ = b2DefaultShapeDef();
	}
	void CreateBody(World& world) {
		id_ = b2CreateBody(world.getId(), &bodydef_);
		b2CreatePolygonShape(id_, &bodyshape_, &bodybox_);
	}

public:
	void SetPosition(b2Vec2 p) {
		bodydef_.position = p;
	}
};

template <>
class Body<BodyType::kDynamic, BodyShape::kRect> final : public BodyImpl {
public:
	Body() {}
	explicit Body(b2Vec2 half) {
		bodydef_ = b2DefaultBodyDef();
		bodydef_.type = b2_dynamicBody;
		bodybox_ = b2MakeBox(half.x, half.y); // 修改尺寸：4米宽，0.5米高
		bodyshape_ = b2DefaultShapeDef();
	}
	void Init(b2Vec2 half) {
		bodydef_ = b2DefaultBodyDef();
		bodydef_.type = b2_dynamicBody;
		bodybox_ = b2MakeBox(half.x, half.y); // 修改尺寸：4米宽，0.5米高
		bodyshape_ = b2DefaultShapeDef();
	}
	void CreateBody(World& world) {
		id_ = b2CreateBody(world.getId(), &bodydef_);
		b2CreatePolygonShape(id_, &bodyshape_, &bodybox_);
	}

public:
	void SetPosition(b2Vec2 p) {
		bodydef_.position = p;
	}
};

template <>
class Body<BodyType::kDynamic, BodyShape::kChain> final : public BodyImpl {
public:






};

