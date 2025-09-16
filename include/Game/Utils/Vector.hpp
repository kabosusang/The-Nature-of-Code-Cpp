#pragma once

#include <cmath>
struct Vector {
	float x;
	float y;

	void operator+=(Vector& other) {
		x = x + other.x;
		y = y + other.y;
	}

	void operator-=(Vector& other) {
		x = x - other.x;
		y = y - other.y;
	}

	void div(float m) {
		x /= m;
		y /= m;
	}

	void add(Vector v) {
		x = x + v.x;
		y = y + v.y;
	}

	float mag() {
		return std::sqrt(x * x + y * y);
	}

	void normalize() {
		float m = mag();
		if (m != 0) {
			div(m);
		}
	}

	void limit(float max) {
		if (x >= max) {
			x = max;
		}

		if (y >= max) {
			y = max;
		}
	}

	static Vector sub(Vector v1, Vector v2) {
		return { v1.x - v2.x, v1.y - v2.y };
	}

	void mult(float m) {
		x *= m;
		y *= m;
	}
};