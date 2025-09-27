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

	void setMag(float magnitude) {
        float currentMag = mag();
        if (currentMag > 0) { 
            float scale = magnitude / currentMag;
            x *= scale;
            y *= scale;
        } else {
            x = magnitude;
            y = 0;
        }
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

	float heading2D() const {
		return std::atan2(y, x);
	}

	static float dist(const Vector& v1, const Vector& v2) {
		float dx = v2.x - v1.x;
		float dy = v2.y - v1.y;
		return std::sqrt(dx * dx + dy * dy);
	}
};