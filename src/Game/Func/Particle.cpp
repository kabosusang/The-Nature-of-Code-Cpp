#include "Game/Func/Particle.hpp"

#include "Game/Particle/Confetti.hpp"
#include "Game/Particle/Particle.hpp"


#include "Game/ParticleSystem.hpp"
#include "Game/Utils/Vector.hpp"
#include <iostream>
#include <vector>

Particle p{ { 100.0f, 100.0f } };

void SingleParticle(Draw* draw) {
	p.run();
	if (p.isDead()) {
		//std::cout << "SingleParticle Dead!\n";
	}
}

std::vector<Particle> particles;
ParticleSystem ps{ { 100, 200 } };

void ClearParticles() {
	p = {};
	ps.clear();
	particles.clear();
}

void MutiParticlesMotion_Init() {
	particles.clear();
	particles.shrink_to_fit();
	for (int i = 0; i < 10; ++i) {
		particles.emplace_back(Particle{ { 200, 200 } });
	}
}

void MutiParticlesMotion() {
	particles.emplace_back(Particle{ { 300, 300 } });

	for (auto& p : particles) {
		p.run();
	}

	// particles.erase(
	//     std::remove_if(particles.begin(), particles.end(),
	//         [](const Particle& p) { return p.isDead(); }),
	//     particles.end()
	// );

	auto it = particles.begin();
	while (it != particles.end()) {
		it->run();
		if (it->isDead()) {
			it = particles.erase(it);
		} else {
			++it;
		}
	}
}

#include "Game/Draw.hpp"

void ParticlesSystemMouseClick(Draw* draw) {
	ps.run();
	if (draw->mousePressed_) {
		ps.addParticle(draw->mouse_);
	}
}

void PolyParticlesSystemMouseClick(Draw* draw) {
	ps.run();
	if (draw->mousePressed_) {
		ps.addParticle_(draw->mouse_);
	}
}


void ForceParticlesSystem_Init(){
	ps.clear();
	ps.origin = {200,200};
}

void ForceParticlesSystem(Draw* draw){
	Vector gravity = {0,0.1f};

	ps.addParticle_f();
	ps.applayForce(gravity);
	ps.run_();
}