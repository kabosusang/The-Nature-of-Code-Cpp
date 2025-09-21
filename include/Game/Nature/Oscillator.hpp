#pragma once
#include "Game/Utils/Angle.hpp"
#include "Game/Utils/Vector.hpp"
#include "Tools/Random.hpp"
#include "base/Canvas.hpp"
#include <cmath>


class Oscillator {
	Vector angle;
	Vector velocity;
	Vector amplitude; //振幅
public:
	Oscillator() {
		auto& canvas = Canvas::getInstance();
		angle = {};
		velocity = { (float)Random(-0.05, 0.05).get(), (float)Random(-0.05, 0.05).get() };
		amplitude = { (float)Random(0, canvas.GetWindowW() / 2.0f).get(), (float)Random(0, canvas.GetWindowH() / 2.0f).get() };
	}

	void oscillate() {
		angle.add(velocity);
	}

	void display() {
        auto& canvas = Canvas::getInstance();
		float x = std::sin(angle.x) * amplitude.x; //X
		float y = std::sin(angle.y) * amplitude.y; //X

		g_transform.resetMatrix();
		g_transform.translate(canvas.GetWindowW() / 2.0f, canvas.GetWindowH() / 2.0f);
		drawLine(0.0f, 0.0f, x, y);
		drawEllipse(x, y, 20, 20);
	}
};