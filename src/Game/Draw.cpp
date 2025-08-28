#include "Game/Draw.hpp"
#include "Tools/Random.hpp"
#include "base/Canvas.hpp"
#include "base/Painter.hpp"


auto& painter= Painter::getInstance();
auto& canvas = Canvas::getInstance();


void Draw::draw() {
    //Random Walker
	//walker_.step();
	//walker_.display();

    NormalRandom x{0.0f,(double)canvas.GetWindowW()};
    painter.DrawCircle(x.get(),220,16);
     

}

void Draw::present(){
    auto& painter = Painter::getInstance();
    painter.Present();
}