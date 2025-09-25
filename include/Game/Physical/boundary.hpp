#pragma once
#include "base/Painter.hpp"
#include "boxdraw.hpp"

class Boundary {
	float x, y;
	float w, h;
	Body<BodyType::kStatic, BodyShape::kRect> body;
    
	Boundary(World& world,float x_,float y_,float w_,float h_){
        x = x_; y = y_;w = w_;h = h_;
		body.Init({ 0.25f, 0.25f });
		body.SetPosition(coordPixelsToWorld(x,y));
		body.CreateBody(world);
    }

	void display(){
		auto& painter = Painter::getInstance();
		painter.DrawRect(x, y, w, h, White);
	}
};
