#include "Game/Func/Vehicle.hpp"
#include "Game/Draw.hpp"
#include "Game/Nature/Flock.hpp"
#include "Game/Nature/FlowField.hpp"
#include "Game/Nature/Vehicle.hpp"

#include "Tools/Random.hpp"
#include "base/Canvas.hpp"
#include <algorithm>
#include <memory>

Vehicle ve{ 300, 300 };

//长按鼠标
void SimpleVehicle(Draw* draw) {
	ve.update();
	if (draw->mousePressed_) {
		ve.seek(draw->mouse_);
	}
	ve.display();
}

void SimpleVehicleArrive(Draw* draw) {
	ve.update();
	if (draw->mousePressed_) {
		ve.arrive(draw->mouse_);
	}
	ve.display();
}

std::unique_ptr<FlowField> fied;

void LiveInFlowField_Init() {
	fied = std::make_unique<FlowField>();
}

void LiveInFlowField() {
	ve.update();
	ve.follow(*fied);
	ve.display();
}

std::vector<Vehicle> vehicles;
void ClearVehicles() {
	vehicles.clear();
	vehicles.shrink_to_fit();
}

void GroupBehavior_Init() {
	auto& canvas = Canvas::getInstance();
	vehicles.clear();
	vehicles.resize(100);
	float minW = 0, maxW = (float)canvas.GetWindowW();
	float minH = 0, maxH = (float)canvas.GetWindowH();
	for (auto& ve : vehicles) {
		ve = { Random{ minW, maxW }, Random{ minH, maxH } };
	}
}

void GroupBehavior(Draw* draw) {
	for (auto& ve : vehicles) {
		ve.update();
		if (draw->mousePressed_) {
			ve.arrive(draw->mouse_);
		}
		ve.separate(vehicles);
		ve.display();
	}
}

void GroupApplyBehavior(Draw* draw) {
	for (auto& ve : vehicles) {
		ve.update();
		if (draw->mousePressed_) {
			ve.applyBehaviors(draw->mouse_, vehicles);
		}
		ve.display_();
	}
}

Flock flock;

void FlockBoidsBehavior_Init() {
	auto& canvas = Canvas::getInstance();
	flock.clear();
    for (int i = 0; i < 100; ++i) {
		Boid b = { canvas.GetWindowW() / 2.0f, canvas.GetWindowH() / 2.0f };
		b.velocity = { Random{ -1.0f, 1.0f }, Random{ -1.0f, 1.0f } };
		b.velocity.normalize();
		b.velocity.mult(b.maxspeed * 0.3f);
		flock.addBoid(std::move(b));
	}
}

void FlockBoidsBehavior(Draw* draw) {
	flock.run();
}
