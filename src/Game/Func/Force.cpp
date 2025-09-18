#include "Game/Func/Force.hpp"

#include "Game/Draw.hpp"
#include "Game/Mover.hpp"
#include "Game/Nature/Liquid.hpp"
#include "Game/Utils/Vector.hpp"
#include "base/Painter.hpp"


#include <algorithm>
#include <array>
#include <cstdarg>
#include <vector>

void MouseDownWind(Draw* draw) {
	draw->mover_.acceleration = {};
	//gravity
	draw->mover_.applyForce({ 0, 0.1f });
	if (draw->mousePressed_) {
		Vector wind = { 0, -0.2f };
		draw->mover_.applyForce(wind);
	}
	//Edge
	draw->mover_.edgejudging();

	draw->mover_.update();
	draw->mover_.display();
}

std::unique_ptr<std::vector<Mover>> moversPtr;
void ClearMovers() {
	moversPtr.reset();
}

void MutiBallForce_Init(Draw* draw) {
	auto& canvas = Canvas::getInstance();
	moversPtr.reset();
	moversPtr = std::make_unique<std::vector<Mover>>();
	moversPtr->reserve(102);

	for (int i = 0; i < 100; i++) {
		moversPtr->emplace_back((float)Random(0.1, 5).get(), 0, 0);
	}

	moversPtr->emplace_back(10, 0, canvas.GetWindowH() / 2.0f);
	moversPtr->emplace_back(0.1, (float)canvas.GetWindowW(), canvas.GetWindowH() / 2.0f);
}

void MutiBallForce(Draw* draw) {
	if (!moversPtr) {
		return;
	}

	Vector wind = { 0.01f, 0.0f };
	Vector gravity = { 0, 0.1f };

	for (auto& m : *moversPtr) {
		m.acceleration = {};
		m.applyForce(wind);
		m.applyForce(gravity);
		m.update();
		m.display(false);
		m.edgejudging();
	}
}

void FirctionForce(Draw* draw) {
	if (!moversPtr) {
		return;
	}

	Vector wind = { 0.01f, 0.0f };
	Vector gravity = { 0, 0.1f };

	float c = 0.03f;
	for (auto& m : *moversPtr) {
		m.acceleration = {};
		auto firction = m.velocity;
		firction.mult(-1);
		firction.normalize();
		firction.mult(c);

		m.applyForce(firction);
		m.applyForce(wind);
		m.applyForce(gravity);
		m.update();
		m.display(false);
		m.edgejudging();
	}
}

Liquid liquid;
void DragMagnitude_Init(Draw* draw) {
	auto& canvas = Canvas::getInstance();
	liquid = { 0, (float)canvas.GetWindowH() / 2, (float)canvas.GetWindowW(), (float)canvas.GetWindowH() / 2, 0.1 };

	moversPtr.reset();
	moversPtr = std::make_unique<std::vector<Mover>>();
	moversPtr->reserve(100);

	for (int i = 0; i < 5; i++) {
		moversPtr->emplace_back((float)Random(0.1, 5).get(), (i + 1) * 100, 0);
	}
}

void DragMagnitude(Draw* draw) {
	liquid.display();

	for (auto& m : *moversPtr) {
		m.acceleration = {};

		float m1 = 0.1 * m.mass;
		Vector gravity = { 0, m1 };
		m.applyForce(gravity);

		if (m.IsInside(liquid)) {
			m.drag(liquid);
		}
		m.update();
		m.display(false);
		m.edgejudging();
	}
}

class Attractor {
	float mass;
    float G;
	Vector location;

public:
	Attractor() {
		auto& canvas = Canvas::getInstance();
		location = { (float)canvas.GetWindowW() / 2, (float)canvas.GetWindowH() / 2 };
		mass = 20.0f;
        G = 0.4f;
	}

	void display() {
		auto& painter = Painter::getInstance();
		painter.DrawFilledCircle(location.x, location.y, 2 * mass, White);
	}
	Vector attract(Mover& m) {
		auto force = Vector::sub(location, m.location);
		float distance = force.mag();
        distance = std::clamp(distance,5.0f,25.0f);
		force.normalize();

		float strength = (G * mass * m.mass) / (distance * distance);
		force.mult(strength);
		return force;
	}
};

Mover m;
Attractor att;
void Attractor_Init() {
	m = {1,100,100};
	att = {};
}

void Attractor_Draw(Draw* draw) {
    auto force = att.attract(m);
    m.applyForce(force);
	m.update();

	att.display();
	m.display();
    m.edgejudging();
}
