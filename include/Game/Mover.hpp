#pragma once

#include "Game/Utils/Vector.hpp"
#include "Tools/Random.hpp"
#include "base/Painter.hpp"
#include <iostream>

class Mover {
public:
	Vector location{};
	Vector velocity{};

	Vector acceleration{};

public:
	Mover() {
		auto& canvas = Canvas::getInstance();
		location = {(float)canvas.GetWindowW() / 2,(float)canvas.GetWindowH() / 2};
		velocity = {0,0};
		acceleration = {-0.001,0.01};
	}

	void update() {
		velocity +=acceleration;
		velocity.limit(10);
		location += velocity;
		edgejudging();
	}

	void edgejudging() {
		auto& canvas = Canvas::getInstance();
		//边缘检测
		if ((location.x > canvas.GetWindowW()) || (location.x < 0)) {
			velocity.x *= -1;
		}

		if ((location.y > canvas.GetWindowH()) || (location.y < 0)) {
			velocity.y *= -1;
		}
	}

	void display() {
		auto& painter = Painter::getInstance();
		painter.DrawFilledCircle(location.x, location.y, 16, White);
	}
};