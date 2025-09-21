#pragma once

#include "Game/Utils/Vector.hpp"
#include "Tools/Random.hpp"
#include "base/Painter.hpp"
class Particle {
public:
	Vector location;
	Vector velocity;
	Vector acceleration;
	float lifespan; //生存时长
	float mass{ 1 };

	Particle() {
		location = {};
		velocity = { Random{ -1, 1 }, Random{ -1, 1 } };
		acceleration = { 0, 0.05f };
		lifespan = 255.0f;
	}
	Particle(Vector l) {
		location = l;
		velocity = { Random{ -1, 1 }, Random{ -1, 1 } };
		acceleration = { 0, 0.05f };
		lifespan = 255.0f;
	}

	void applyForce(Vector force) {
		force.div(mass);
		acceleration.add(force);
	}

	void run() {
		update();
		display();
	}

	void update() {
		velocity.add(acceleration);
		location.add(velocity);
		lifespan -= 2.0f;
	}

	Particle(Vector l, float enableforce) {
		location = l;
		acceleration = { 0, 0.05 };
		lifespan = 255.0f;
		velocity = { Random{ -1, 1 }, Random{ -2, 0 } };
	}

	void update_() {
		velocity.add(acceleration);
		location.add(velocity);
		acceleration.mult(0);
		lifespan -= 2.0f;
	}

	void run_() {
		update_();
		display();
	}

	virtual void display() {
		auto& painter = Painter::getInstance();
		painter.DrawFilledCircle(location.x, location.y, 8, White);
	}

	bool isDead() const {
		if (lifespan < 0.01f) {
			return true;
		} else {
			return false;
		}
	}
};