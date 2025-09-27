#pragma once

#include "Boid.hpp"
#include "Game/Utils/Vector.hpp"
#include <vector>
class Flock {
	std::vector<Boid> boids;

public:
	Flock() {}

    void clear(){
        boids.clear();
    }

	void run() {
		for (auto& b : boids) {
			b.run(boids);
		}
	}

    void addBoid(Boid&& b){
        boids.push_back(b);
    }
};