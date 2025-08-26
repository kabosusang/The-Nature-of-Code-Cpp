#include "Game/Draw.hpp"
#include "base/Painter.hpp"

void Draw::draw() {
	walker_.step();
	walker_.display();
}

void Draw::present(){
    auto& painter = Painter::getInstance();
    painter.Present();
}