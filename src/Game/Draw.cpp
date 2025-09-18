#include "Game/Draw.hpp"
#include "Game/Utils/Vector.hpp"
#include "Tools/Random.hpp"
#include "base/Canvas.hpp"
#include "base/Painter.hpp"


//Vector
#include "Game/Func/Vector.hpp"
#include "Game/Func/Force.hpp"



const std::vector<std::string_view> Draw::nodes_vector{
	"WalkerStep",
	"RandomCircle",
	"PingPongBall",
	"MouseBall"
};

const std::vector<std::string_view> Draw::nodes_force{
	"MouseDownWind",
	"ExternalForce",
	"FirctionForce",
	"DragMagnitude",
	"Attractor"
};


uint32_t Draw::index_ = 0;

void Draw::pollevent(SDL_Event& event) {
	if (event.type == SDL_EVENT_MOUSE_MOTION){
		mouse_.x = event.motion.x;
		mouse_.y = event.motion.y;
	}

	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
		mousePressed_ = true;
	}else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
		mousePressed_ = false;
	}
}


void Draw::draw() {
	selectNode();
}

void Draw::present() {
	auto& painter = Painter::getInstance();
	painter.Present();
}

//Remove Resource
extern void ClearMovers();


void Draw::selectNode() {
	static auto first = index_;
	if (first != index_){
		mover_ = {};
		walker_ = {};
		first = index_;
		//Init
		switch (first) {
			case 5:{
				MutiBallForce_Init(this);
			}break;
			case 6:{
				MutiBallForce_Init(this);
			}break;
			case 7:{
				DragMagnitude_Init(this);
			}break;
			case 8:{
				Attractor_Init();
			}break;

			default:{
				ClearMovers();
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
		case 4:{
			MouseDownWind(this);
		}break;
		case 5:{
			MutiBallForce(this);
		}break;
		case 6:{
			FirctionForce(this);
		}break;
		case 7:{
			DragMagnitude(this);
		}break;
		case 8:{
			Attractor_Draw(this);
		}break;
		




		default:
			break;
	}
}







