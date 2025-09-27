#include "Game/Draw.hpp"
#include "Game/Func/CeAutomata.hpp"
#include "Game/Utils/Vector.hpp"
#include "Tools/Random.hpp"
#include "base/Canvas.hpp"
#include "base/Painter.hpp"

#include "Game/Func/Angle.hpp"
#include "Game/Func/Box2D.hpp"
#include "Game/Func/Force.hpp"
#include "Game/Func/Particle.hpp"
#include "Game/Func/Vector.hpp"
#include "Game/Func/Vehicle.hpp"

#include <cmath>
#include <iostream>

//Vector
const std::vector<std::string_view> Draw::nodes_vector{
	"WalkerStep",
	"RandomCircle",
	"PingPongBall",
	"MouseBall"
};
//Force
const std::vector<std::string_view> Draw::nodes_force{
	"MouseDownWind",
	"ExternalForce",
	"FirctionForce",
	"DragMagnitude",
	"Attractor"
};

//Angle
const std::vector<std::string_view> Draw::nodes_angle{
	"AngleMotion",
	"PolaAngle",
	"SpiralAngle",
	"SimpleHarmonicMotion",
	"OscillatorMotion",
	"OscillatorXYMotion",
	"SwingsMotion",
	"PendulumMotion"
};

const std::vector<std::string_view> Draw::nodes_partivle{
	"SingleParticle",
	"MutiParticlesMotion",
	"ParticlesSystemMouseClick",
	"PolyParticlesSystemMouseClick",
	"ForceParticlesSystem",

};
//Box2D
const std::vector<std::string_view> Draw::nodes_box2d{
	"LiveWorld",
	"MouseClickMutliBox",
	// "StaticBoundary",
};

const std::vector<std::string_view> Draw::nodes_vehicle{
	"SimpleVehicleMouseClick",
	"SimpleVehicleArriveMouseClick",
	"FlowField",
	"GroupBehavior",
	"GroupApplyBehavior",
	"FlockBoidsBehavior",
};

const std::vector<std::string_view> Draw::nodes_automata{
	"Wolframe",
	"GameLife"
};


uint32_t Draw::index_ = 0;

void Draw::pollevent(SDL_Event& event) {
	if (event.type == SDL_EVENT_MOUSE_MOTION) {
		mouse_.x = event.motion.x;
		mouse_.y = event.motion.y;
	}

	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		mousePressed_ = true;
	} else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
		mousePressed_ = false;
	}

	if (event.key.key == SDLK_SPACE){
		blankPressed_ = true;
	}

}

void Draw::draw(float deltaTime) {
	selectNode(deltaTime);
}

void Draw::present() {
	auto& painter = Painter::getInstance();
	painter.Present();
}

//Remove Resource
extern void ClearMovers();
extern void ClearParticles();
extern void ClearBox();
extern void ClearVehicles();
extern void ClearCA();

void ClearResource() {
	ClearMovers();
	ClearParticles();
	ClearBox();
	ClearVehicles();
	ClearCA();
}

void Draw::selectNode(float deltaTime) {
	frameCount_++;

	static auto first = index_;
	if (first != index_) {
		mover_ = {};
		walker_ = {};
		frameCount_ = {};
		first = index_;
		//Init
		switch (first) {
			case 5: {
				MutiBallForce_Init(this);
			} break;
			case 6: {
				MutiBallForce_Init(this);
			} break;
			case 7: {
				DragMagnitude_Init(this);
			} break;
			case 8: {
				Attractor_Init();
			} break;
			//Angle
			case 9: {
				AngleMotion_Init();
			} break;
			case 13: {
				OscillatorMotion_Init();
			} break;
			case 14: {
				OscillatorXYMotion_Init();
			} break;
			case 15: {
				SwingsMotion_Init();
			} break;
			case 16: {
				PendulumMotion_Init();
			} break;
				//Particle

			case 18: {
				MutiParticlesMotion_Init();
			} break;

			case 21: {
				ForceParticlesSystem_Init();
			} break;

			case 22: {
				LiveWorld_Init();
			} break;

			case 23: {
				MouseClickMutliBox_Init();
			} break;

			case 26: {
				LiveInFlowField_Init();
			} break;

			case 27: {
				GroupBehavior_Init();
			} break;

			case 28: {
				GroupBehavior_Init();
			} break;
			case 29: {
				FlockBoidsBehavior_Init();
			} break;
			case 30: {
				Wolframe_Init();
			} break;
			case 31: {
				GameOfLife_Init();
			} break;






			default: {
				ClearResource();
			}
		}
	}

	switch (index_) {
		//Vector
		case 0: {
			WalkerStep(this);
		} break;
		case 1: {
			RandomCircle();
		} break;

		case 2: {
			PingPongBall(this);
		} break;
		case 3: {
			MouseBall(this);
		} break;
		//Force
		case 4: {
			MouseDownWind(this);
		} break;
		case 5: {
			MutiBallForce(this);
		} break;
		case 6: {
			FirctionForce(this);
		} break;
		case 7: {
			DragMagnitude(this);
		} break;
		case 8: {
			Attractor_Draw(this);
		} break;
		//Angle
		case 9: {
			AngleMotion(this);
		} break;
		case 10: {
			PolaAngle(this);
		} break;
		case 11: {
			SpiralAngle(this);
		} break;
		case 12: {
			SimpleHarmonicMotion(this);
		} break;
		case 13: {
			OscillatorMotion(this);
		} break;
		case 14: {
			OscillatorXYMotion(this);
		} break;
		case 15: {
			SwingsMotion(this);
		} break;
		case 16: {
			PendulumMotion(this);
		} break;
		//Particle
		case 17: {
			SingleParticle(this);
		} break;
		case 18: {
			MutiParticlesMotion();
		} break;
		case 19: {
			ParticlesSystemMouseClick(this);
		} break;
		case 20: {
			PolyParticlesSystemMouseClick(this);
		} break;
		case 21: {
			ForceParticlesSystem(this);
		} break;

		//Box 2D
		case 22: {
			LiveWorld(deltaTime);
		} break;

		case 23: {
			MouseClickMutliBox(this, deltaTime);
		} break;

		//Vehicle
		case 24: {
			SimpleVehicle(this);
		} break;
		case 25: {
			SimpleVehicleArrive(this);
		} break;
		case 26: {
			LiveInFlowField();
		} break;
		case 27: {
			GroupBehavior(this);
		} break;
		case 28: {
			GroupApplyBehavior(this);
		} break;
		case 29: {
			FlockBoidsBehavior(this);
		} break;

		//CA
		case 30: {
			Wolframe(this);
		} break;
		case 31: {
			GameOfLifeUpdate(this);
		} break;




		default:
			break;
	}
}
