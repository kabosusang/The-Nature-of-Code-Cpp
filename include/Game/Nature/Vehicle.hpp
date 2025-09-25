#pragma once

#include "Game/Utils/Angle.hpp"
#include "Game/Utils/Vector.hpp"
#include "base/Painter.hpp"

class Vehicle {
public:
	Vector location;
	Vector velocity;
	Vector acceleration;
	float r;
	float maxspeed;
	float maxforce;
	Vehicle(float x, float y) {
		acceleration = {};
		velocity = {};
		location = { x, y };
		r = 3.0f;
		maxspeed = 4;
		maxforce = 0.1f;
	}

	void update() {
		velocity.add(acceleration);
		velocity.limit(maxspeed);
		location.add(velocity);
		acceleration.mult(0);
	}

	void applyForce(Vector force) {
		force.div(1);
		acceleration.add(force);
	}

	void seek(Vector target) {
		auto desired = Vector::sub(target, location);
		desired.normalize();
		desired.mult(maxspeed);
		auto steer = Vector::sub(desired, velocity);
		steer.limit(maxforce);

		applyForce(steer);
	}

	void arrive(Vector target) {
		auto desired = Vector::sub(target, location);
		auto d = desired.mag();
		desired.normalize();
		if (d < 100) {
			auto m = map(d, 0.0f, 100.0f, 0.0f, maxspeed);
			desired.mult(m);
		} else {
			desired.mult(maxspeed);
		}

		auto steer = Vector::sub(desired, velocity);
		steer.limit(maxforce);

		applyForce(steer);
	}

	void display() {
		float theta = velocity.heading2D() + PI / 2;
		g_transform.pushMatrix();
		g_transform.translate(location.x, location.y);
		g_transform.rotate(theta);
		drawTriangle({ 0, -r * 2 }, { -r, r * 2 }, { r, r * 2 }, White);
		g_transform.popMatrix();
	}
};