#include "Game/Walker.hpp"

#include "base/Canvas.hpp"
#include "base/Painter.hpp"

#include "Tools/Random.hpp"
#include <iostream>


Walker::Walker(){
    auto& canvas = Canvas::getInstance();
    x_ = canvas.GetWindowW() / 2;
    y_ = canvas.GetWindowH() / 2;
}

void Walker::display(){
    auto& painter = Painter::getInstance();
    painter.PutPixel(x_, y_, {255,255,255,255});
}

void Walker::step(){
    Random rdx{-1,1};
    Random rdy{-1,1};
   
    auto stepx = rdx.get();
    auto stepy = rdy.get();

    x_ += stepx;
    y_ += stepy;

    // switch (randowm) {
    //     case 0:x_++;break;
    //     case 1:x_--;break;
    //     case 2:y_++;break;
    //     default: y_--;break;
    // }

}




