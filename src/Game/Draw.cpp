#include "Game/Draw.hpp"
#include "Game/Utils/Vector.hpp"
#include "Tools/Random.hpp"
#include "base/Canvas.hpp"
#include "base/Painter.hpp"

auto& painter = Painter::getInstance();
auto& canvas = Canvas::getInstance();

std::vector<std::string_view> Draw::nodes{
	"WalkerStep",
	"RandomCircle",
	"PingPongBall",
	"MouseBall"
};

uint32_t Draw::index_ = 0;

void Draw::pollevent(SDL_Event& event) {
	if (event.type == SDL_EVENT_MOUSE_MOTION){
		mouse_.x = event.motion.x;
		mouse_.y = event.motion.y;
	}

}


void Draw::draw() {
	selectNode();
}

void Draw::present() {
	auto& painter = Painter::getInstance();
	painter.Present();
}
///////////////////////////////////---------------/////////////////////////////////////////////////////////
void WalkerStep(Draw* draw);
void RandomCircle();
void PingPongBall(Draw* draw);
void MouseBall(Draw* draw);
//////////////////////////////////////////////////////////////////////////////////////////////////


void Draw::selectNode() {
	static auto first = index_;
	if (first != index_){
		mover_ = {};
		walker_ = {};
		first = index_;
	}
	
	switch (index_) {
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






		default:
			break;
	}
}

void WalkerStep(Draw* draw) {
	draw->walker_.step();
	draw->walker_.display();
}

void RandomCircle() {
	for (int i{}; i < 10; ++i) {
		NormalRandom x{ 0.0f, (double)canvas.GetWindowW() };
		painter.DrawCircle(x.get(), 220, 16);
	}
}

void PingPongBall(Draw* draw) {
	draw->mover_.update();
	draw->mover_.display();
}

void MouseBall(Draw* draw){
	Vector dir = Vector::sub(draw->mouse_, draw->mover_.location);
	dir.normalize();
	dir.mult(0.5);
	draw->mover_.acceleration = dir;
	draw->mover_.update();
	draw->mover_.display();
	
}