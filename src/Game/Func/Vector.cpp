#include "Game/Func/Vector.hpp"
#include "Game/Draw.hpp"
auto& painter = Painter::getInstance();
auto& canvas = Canvas::getInstance();



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
	draw->mover_.velocity.limit(10);
	draw->mover_.update();
	draw->mover_.edgejudging(-1);
	draw->mover_.display();
}

void MouseBall(Draw* draw){
	Vector dir = Vector::sub(draw->mouse_, draw->mover_.location);
	dir.normalize();
	dir.mult(0.5);
	draw->mover_.acceleration = dir;
	draw->mover_.velocity.limit(10);
	draw->mover_.update();
	draw->mover_.edgejudging(-1);
	draw->mover_.display();
}
