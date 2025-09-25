#pragma once
#include "base/Painter.hpp"
#include "body.hpp"
#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "world.hpp"

#define PIXELS_PER_METER 100.0f

inline constexpr b2Vec2 PixeltoGrid(float pixelX, float pixelY) {
	return { pixelX / PIXELS_PER_METER, pixelY / PIXELS_PER_METER };
}

inline constexpr float scalarPixelsToWorld(float val) {
	return val / PIXELS_PER_METER;
}

inline constexpr float scalarWorldToPixels(float val) {
	return PIXELS_PER_METER * val;
}

inline constexpr b2Vec2 scalarWorldToPixels(b2Vec2 v) {
	return { v.x * PIXELS_PER_METER,
		v.y * PIXELS_PER_METER };
}

inline b2Vec2 coordPixelsToWorld(b2Vec2 v) {
	auto& canvas = Canvas::getInstance();

	float centeredX = v.x - (canvas.GetWindowW() / 2.0f);
	float centeredY = v.y - (canvas.GetWindowH() / 2.0f);

	centeredY = -centeredY;
	return PixeltoGrid(centeredX, centeredY);
}

inline b2Vec2 coordWorldToPixels(b2Vec2 v) {
	auto& canvas = Canvas::getInstance();

	b2Vec2 pixelPos = scalarWorldToPixels(v);
	pixelPos.y = -pixelPos.y;
	pixelPos.x += canvas.GetWindowW() / 2.0f;
	pixelPos.y += canvas.GetWindowH() / 2.0f;
	return pixelPos;
}

inline b2Vec2 coordPixelsToWorld(float pixelX, float pixelY) {
	return coordPixelsToWorld({ pixelX, pixelY });
}

inline b2Vec2 coordWorldToPixels(float worldX, float worldY) {
	return coordWorldToPixels({ worldX, worldY });
}

class Box {
public:
	float w;
	float h;
	Body<BodyType::kDynamic, BodyShape::kRect> body;
	b2WorldId worldId_;
	bool isdead_ = false;

	explicit Box(World& world, b2Vec2 position) {
		worldId_ = world.getId();
		w = h = scalarWorldToPixels(0.5f);
		body.Init({ 0.25f, 0.25f });
		body.SetPosition(position);
		body.getShap().density = 1.0f;
		body.getShap().material.friction = 1.0f;
		body.CreateBody(world);
		if (!body.isValid()) {
			std::cout << "错误：Body 创建失败" << std::endl;
		}
	}

	Box() {}
	~Box() {
		if (body.isValid()) {
			destory();
		}
	}
	void Init(World& world, b2Vec2 position) {
		w = h = scalarWorldToPixels(0.5f);
		worldId_ = world.getId();

		body.Init({ 0.25f, 0.25f });
		body.SetPosition(position);
		body.getShap().density = 1.0f;
		body.getShap().material.friction = 1.0f;
		body.CreateBody(world);
	}

	void destory() {
		if (body.isValid()) {
			body.destory();
		}
	}

	void run() {
		display();
	}
	bool isValid() {
		return body.isValid();
	}

public:
	void display() {
		auto& painter = Painter::getInstance();
		b2Transform groundTransform = b2Body_GetTransform(body.getId());
		b2Vec2 groundScreenPos = coordWorldToPixels(groundTransform.p);
		painter.DrawRect(
				groundScreenPos.x - w / 2,
				groundScreenPos.y - h / 2,
				w,
				h,
				White);
	}
};
