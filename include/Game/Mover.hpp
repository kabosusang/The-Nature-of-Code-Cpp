#pragma once

#include "Game/Utils/Vector.hpp"
#include "Tools/Random.hpp"
#include "base/Painter.hpp"
#include <iostream>
#include "Game/Nature/Liquid.hpp"



class Mover {
public:
	Vector location{};
	Vector velocity{};
	Vector acceleration{};
	float mass{};

	float angle = 0;
	float aVelocity = 0;
	float aAcceleration = 0;

public:
	Mover() {
		auto& canvas = Canvas::getInstance();
		location = { (float)canvas.GetWindowW() / 2, (float)canvas.GetWindowH() / 2 };
		velocity = { 0, 0 };
		acceleration = { -0.001, 0.01 };
		mass = 1.0f;
	}

	Mover(float m, float x, float y) {
		auto& canvas = Canvas::getInstance();
		location = { x, y };
		velocity = { 0, 0 };
		acceleration = { 0, 0};
		mass = m;
	}

	void update() {
		velocity += acceleration;
		location += velocity;
	}

	void edgejudging(float force = -1.0f) {
		auto& canvas = Canvas::getInstance();
		//边缘检测
		if ((location.x > canvas.GetWindowW()) || (location.x < 0)) {
			velocity.x *= force;
		}

		if ((location.y > canvas.GetWindowH()) || (location.y < 0)) {
			velocity.y *= force;
		}
	}

	void display(bool isFilled = true) {
		auto& painter = Painter::getInstance();
		if (isFilled) {
			painter.DrawFilledCircle(location.x, location.y, 16 * mass, White);
		} else {
			painter.DrawCircle(location.x, location.y, 16 * mass);
		}
	}

	void applyForce(Vector force) {
		force.div(mass);
		acceleration.add(force);
	}

	//Liquid
	bool IsInside(Liquid& l){
		return (location.x > l.x && location.x < (l.x + l.w) &&
            location.y > l.y && location.y < (l.y + l.h));
	}

	void drag(Liquid& l){
		float speed = velocity.mag();
		float dragMagnitude = l.c * speed * speed;
		Vector drag = velocity;
		drag.mult(-1);
   	 	drag.normalize();
    	drag.mult(dragMagnitude);

		applyForce(drag);
	}




};