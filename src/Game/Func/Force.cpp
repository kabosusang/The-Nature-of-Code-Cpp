#include "Game/Func/Force.hpp"

#include "Game/Draw.hpp"
#include "Game/Utils/Vector.hpp"

void MouseDownWind(Draw* draw) {
	draw->mover_.acceleration = {};
    draw->mover_.applyForce({0,1.0f});
    if (draw->mousePressed_){
        Vector wind = {0,-2};
        draw->mover_.applyForce(wind);
    }
    draw->mover_.update();
    draw->mover_.display();
}