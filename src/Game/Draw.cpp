#include "Game/Draw.hpp"
#include "Tools/Random.hpp"
#include "base/Canvas.hpp"
#include "base/Painter.hpp"

auto& painter = Painter::getInstance();
auto& canvas = Canvas::getInstance();

std::vector<std::string_view> Draw::nodes{
	"WalkerStep",
	"RandomCircle"
};

uint32_t Draw::index_ = 0;

void Draw::draw() {
	selectNode();
}

void Draw::present() {
	auto& painter = Painter::getInstance();
	painter.Present();
}

void WalkerStep(Draw* draw);
void RandomCircle();

void Draw::selectNode() {
	switch (index_) {
		case 0: {
			WalkerStep(this);
		} break;

		case 1: {
			RandomCircle();
		} break;


        default: break;
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
