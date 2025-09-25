#include "Game/Func/Box2D.hpp"
#include "Game/Draw.hpp"
#include "base/Painter.hpp"
#include "box2d/box2d.h"
#include "box2d/collision.h"
#include "box2d/types.h"
#include <iostream>
#include <vector>

#include "Game/Physical/body.hpp"
#include "Game/Physical/boxdraw.hpp"
#include "Game/Physical/world.hpp"

//World
World world;

//Ground
Body<BodyType::kStatic, BodyShape::kRect> ground;
//box
Body<BodyType::kDynamic, BodyShape::kRect> box;

void ClearLiveWorld() {
	//Clear
	if (ground.isValid() && world.isValid()) {
		ground.destory();
	}

	if (box.isValid() && world.isValid()) {
		box.destory();
	}
}

void LiveWorld_Init() {
	auto& canvas = Canvas::getInstance();
	//Clear
	ClearLiveWorld();

	world.Init({ 0.0f, -10.0f });
	//Ground
	b2Vec2 groundWorldPos = coordPixelsToWorld(
			canvas.GetWindowW() / 2.0f,
			canvas.GetWindowH() - (scalarWorldToPixels(0.5f) / 2.0f));
	ground.Init({ 2.0f, 0.25f });
	ground.SetPosition(groundWorldPos);
	ground.CreateBody(world);

	//Dynamic

	b2Vec2 centerWorldPos = coordPixelsToWorld({
			canvas.GetWindowW() / 2.0f,
			canvas.GetWindowH() / 2.0f //
	});
	box.Init({ 0.25f, 0.25f });
	box.SetPosition(centerWorldPos);
	box.getShap().density = 1.0f;
	box.getShap().material.friction = 1.0f;
	box.CreateBody(world);
}

void LiveWorld(float deltaTime) {
	auto& painter = Painter::getInstance();
	b2World_Step(world.getId(), deltaTime, 8);

	//box
	b2Transform dynamicTransform = b2Body_GetTransform(box.getId());
	b2Vec2 screenPos = coordWorldToPixels(dynamicTransform.p);
	float dynamicSize = scalarWorldToPixels(0.5f); // 0.5米 = 50像素
	painter.DrawRect(
			screenPos.x - dynamicSize / 2,
			screenPos.y - dynamicSize / 2,
			dynamicSize,
			dynamicSize,
			White);
	//ground
	b2Transform groundTransform = b2Body_GetTransform(ground.getId());
	b2Vec2 groundScreenPos = coordWorldToPixels(groundTransform.p);
	float groundWidth = scalarWorldToPixels(4.0f); // 4米宽
	float groundHeight = scalarWorldToPixels(0.5f); // 0.5米高
	painter.DrawRect(
			groundScreenPos.x - groundWidth / 2,
			groundScreenPos.y - groundHeight / 2,
			groundWidth,
			groundHeight,
			Red);
}

std::vector<Box> boxes;
void ClearBox() {
	boxes.clear();
	boxes.shrink_to_fit();
}

void MouseClickMutliBox_Init() {
    auto& canvas = Canvas::getInstance();
	ClearBox();
	ClearLiveWorld();
    boxes.reserve(1000);
	world.Init({ 0.0f, -10.0f });
    //Ground
	b2Vec2 groundWorldPos = coordPixelsToWorld(
			canvas.GetWindowW() / 2.0f,
			canvas.GetWindowH() - (scalarWorldToPixels(0.5f) / 2.0f));
	ground.Init({ 8.0f, 0.25f });
	ground.SetPosition(groundWorldPos);
	ground.CreateBody(world);
}

void MouseClickMutliBox(Draw* draw, float deltaTime) {
	b2World_Step(world.getId(), deltaTime, 8);
	if (draw->mousePressed_) {
		b2Vec2 groundWorldPos = coordPixelsToWorld(
				draw->mouse_.x,
				draw->mouse_.y);
		boxes.emplace_back(world, groundWorldPos);
	}


	auto it = boxes.begin();
	while (it != boxes.end()) {
        if ((*it).isValid()){
            (*it).run();
        }
		++it;
	}
    auto& painter = Painter::getInstance();
    b2Transform groundTransform = b2Body_GetTransform(ground.getId());
	b2Vec2 groundScreenPos = coordWorldToPixels(groundTransform.p);
	float groundWidth = scalarWorldToPixels(16.0f);
	float groundHeight = scalarWorldToPixels(0.5f); // 0.5米高
	painter.DrawRect(
			groundScreenPos.x - groundWidth / 2,
			groundScreenPos.y - groundHeight / 2,
			groundWidth,
			groundHeight,
			Red);

}

void StaticBoundary_Init(){

}
void StaticBoundary(Draw* draw,float deltaTime){
	
}
























