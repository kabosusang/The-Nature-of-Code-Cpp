#pragma once
#include "base/Canvas.hpp"
#include "box2d/box2d.h"
#include "box2d/math_functions.h"

void LiveWorld_Init();
void LiveWorld();
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
	//pixelPos.y = -pixelPos.y;
	pixelPos.x += canvas.GetWindowW() / 2.0f;
	pixelPos.y += canvas.GetWindowH() / 2.0f;
	return pixelPos;
}

inline b2Vec2 coordPixelsToWorld(float pixelX, float pixelY) {
    return coordPixelsToWorld({pixelX, pixelY});
}

inline b2Vec2 coordWorldToPixels(float worldX, float worldY) {
    return coordWorldToPixels({worldX, worldY});
}


