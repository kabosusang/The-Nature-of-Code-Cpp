#include "Game/Func/Vehicle.hpp"
#include "Game/Nature/Vehicle.hpp"
#include "Game/Draw.hpp"


Vehicle ve{100,100};

//长按鼠标
void SimpleVehicle(Draw* draw){
    ve.update();
    if (draw->mousePressed_){
        ve.seek(draw->mouse_);
    }
    ve.display();
}

void SimpleVehicleArrive(Draw* draw){
    ve.update();
    if (draw->mousePressed_){
        ve.arrive(draw->mouse_);
    }
    ve.display();
}










