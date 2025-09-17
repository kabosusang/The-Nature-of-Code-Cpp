#pragma once
#include "base/Painter.hpp"

class Liquid {
public:
    float x,y,w,h;
    float c;

    Liquid(){}
    Liquid(float x_,float y_,float w_,float h_,float c_)
    :x(x_),y(y_),w(w_),h(h_),c(c_){}

    void display(){
        auto& painter = Painter::getInstance();
        painter.DrawRect(x, y, w, h,{100,100,100,255});
    }



};