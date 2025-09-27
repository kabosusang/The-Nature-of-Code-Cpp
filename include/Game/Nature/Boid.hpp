#pragma once

#include "Game/Utils/Angle.hpp"
#include "Game/Utils/Vector.hpp"
#include "base/Painter.hpp"
#include <vector>

class Boid {
public:
	Vector location{};
	Vector velocity{};
	Vector acceleration{};
	float r{};
	float maxspeed{};
	float maxforce{};
	Boid() = default;
	Boid(float x, float y) {
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

		auto& canvas = Canvas::getInstance();
		if (location.x < -50 || location.x > canvas.GetWindowW() + 50 ||
				location.y < -50 || location.y > canvas.GetWindowH() + 50) {
			location = Vector(canvas.GetWindowW() / 2, canvas.GetWindowH() / 2);
			velocity = Vector(0, 0);
		}
	}

	void applyForce(Vector force) {
        if (force.x == 0 && force.y == 0)return;
		force.div(1);
		acceleration.add(force);
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

	//6.12
	Vector separate_(std::vector<Boid>& vechicles) {
		static float desiredseparation = 20;
		auto sum = Vector{};
		int count{};
		for (auto& other : vechicles) {
			auto d = Vector::dist(location, other.location);
			if ((d > 0) && (d < desiredseparation)) {
				auto diff = Vector::sub(location, other.location);
				diff.normalize();
				diff.div(d);
				sum.add(diff);
				count++;
			}
		}

		if (count > 0) {
			sum.div(count);
			sum.normalize();
			sum.mult(maxspeed);
			auto steer = Vector::sub(sum, velocity);
			steer.limit(maxforce);
			//applyForce(steer);
			return steer;
		}

		return {};
	}

	Vector seek_(Vector target) {
		auto desired = Vector::sub(target, location);
		desired.normalize();
		desired.mult(maxspeed);
		auto steer = Vector::sub(desired, velocity);
		steer.limit(maxforce);
		return steer;
	}

	void applyBehaviors(Vector mouseXY, std::vector<Boid>& vechicles) {
		auto separate = separate_(vechicles);
		auto seek = seek_(mouseXY);
		separate.mult(1.5);
		seek.mult(0.5);
		applyForce(separate);
		applyForce(seek);
	}

	void display_() {
		auto& painter = Painter::getInstance();
		painter.DrawFilledCircle(location.x, location.y, 10, White);
	}

	//Boids
	Vector align(std::vector<Boid>& boids) {
		static float neighbordist = 50;
		auto sum = Vector{};
		int count = 0;
		for (auto& other : boids) {
			auto d = Vector::dist(location, other.location);
			if ((d > 0) && (d < neighbordist)) {
				sum.add(other.velocity);
				count++;
			}
		}

		if (count > 0) {
			sum.div(count);
			sum.normalize();
			sum.mult(maxspeed);
			auto steer = Vector::sub(sum, velocity);
			steer.limit(maxforce);
			return steer;
		}
		return {};
	}

    Vector cohesion(std::vector<Boid>& boids){
        float neighbordist = 50;
        auto sum = Vector{};
        int count = 0;
        for (auto& other : boids) {
			auto d = Vector::dist(location, other.location);
			if ((d > 0) && (d < neighbordist)) {
				sum.add(other.location);
				count++;
			}
		}

        if (count > 0){
            sum.div(count);
            return seek_(sum);
        }

        return {};
    }

    void run(std::vector<Boid>& boids){
        update();
        flock(boids); 
        display();
    }


	void flock(std::vector<Boid>& boids) {
		auto sep = separate_(boids); //分离
		auto ali = align(boids); //对齐
		auto coh = cohesion(boids); //聚集

        sep.mult(1.5);
        ali.mult(1);
        coh.mult(1);

        applyForce(sep);
        applyForce(ali);
        applyForce(coh);
    
    }
};