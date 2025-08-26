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
    Random rdx{0,1};

    auto r = rdx.get();

    if (r < 0.4){
        x_++;
    }else if (r < 0.6) {
        x_--;
    }else if (r < 0.8) {
        y_++;
    }else{
        y_--;
    }
}




