#include "Game/Func/Angle.hpp"

#include "Game/Draw.hpp"
#include "Game/Utils/Angle.hpp"
#include "base/Canvas.hpp"
#include <chrono>
#include <cmath>

float angle = 0;
float aVelocity = 0;
float aAcceleration = 0.001;

void AngleMotion_Init() {
	angle = 0;
	aVelocity = 0;
	aAcceleration = 0.001;
}

void AngleMotion(Draw* draw) {
	auto& canvas = Canvas::getInstance();

	g_transform.resetMatrix();
	g_transform.translate(canvas.GetWindowW() / 2.0f, canvas.GetWindowH() / 2.0f);
	g_transform.rotate(radians(angle));
	drawLine(-50.0f, 0.0f, 50.0f, 0.0f);
	drawEllipse(50.0f, 0.0f, 8.0f, 8.0f);
	drawEllipse(-50.0f, 0.0f, 8.0f, 8.0f);
	aVelocity += aAcceleration;
	angle += aVelocity;
}

void PolaAngle(Draw* draw) {
	static auto r = 75.0f;
	static auto theta = 0.0f;
	auto v = PolatoCorrd(r, theta);

	auto& canvas = Canvas::getInstance();

	draw->mover_.location = { v.x + canvas.GetWindowW() / 2.0f, v.y + canvas.GetWindowH() / 2.0f };
	draw->mover_.display();
	theta += 0.01;
}

void SpiralAngle(Draw* draw) {
	static auto r = 10.0f;
	static auto theta = 0.0f;
	auto v = PolatoCorrd(r, theta);

	auto& canvas = Canvas::getInstance();

	draw->mover_.location = { v.x + canvas.GetWindowW() / 2.0f, v.y + canvas.GetWindowH() / 2.0f };
	draw->mover_.display();
	theta += 0.1;
	r += 0.1f;
}

float amplitude = 100;
float period = 120; //frame

void SimpleHarmonicMotion(Draw* draw) {
	float period = 120;
	float amplitude = 100;
	auto& canvas = Canvas::getInstance();
	float x = amplitude * std::cos(TWO_PI * draw->frameCount_ / period);

	g_transform.resetMatrix();
	g_transform.translate(canvas.GetWindowW() / 2.0f, canvas.GetWindowH() / 2.0f);
	drawLine(0.0f, 0.0f, x, 0.0f);
	drawEllipse(x, 0.0f, 20, 20);
}
