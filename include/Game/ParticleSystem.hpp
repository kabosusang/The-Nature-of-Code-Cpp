#pragma once

#include "Game/Particle/Confetti.hpp"
#include "Game/Particle/Particle.hpp"


#include "Game/Utils/Vector.hpp"
#include "Particle/Confetti.hpp"
#include "Tools/Random.hpp"
#include <vector>
class ParticleSystem {
public:
	std::vector<std::unique_ptr<Particle>> particles{};
	Vector origin{};

	ParticleSystem(Vector location) {
		origin = location;
	}

	void addParticle(Vector ori) {
		particles.push_back(std::make_unique<Particle>(ori));
	}

	void addParticle_(Vector ori) {
		float r = Random{ 0, 1 };
		if (r < 0.5f) {
			particles.push_back(std::make_unique<Confetti>(ori));
		} else {
			particles.push_back(std::make_unique<Particle>(ori));
		}
	}

	void addParticle_f() {
		particles.push_back(std::make_unique<Particle>(origin, false));
	}

	void applayForce(Vector force) {
		for (auto& p : particles) {
			p->applyForce(force);
		}
	}

	void clear() {
		particles.clear();
		particles.shrink_to_fit();
		origin = {};
	}

	void run() {
		auto it = particles.begin();
		while (it != particles.end()) {
			(*it)->run();
			if ((*it)->isDead()) {
				it = particles.erase(it);
			} else {
				++it;
			}
		}
	}

	void run_() {
		auto it = particles.begin();
		while (it != particles.end()) {
			(*it)->run_();
			if ((*it)->isDead()) {
				it = particles.erase(it);
			} else {
				++it;
			}
		}
	}
};
