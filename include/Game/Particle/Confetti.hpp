#pragma once

#include "Game/Utils/Vector.hpp"
#include "Particle.hpp"
#include "base/Canvas.hpp"
#include "Game/Utils/Angle.hpp"
#include "base/Painter.hpp"
#include <iostream>


class Confetti :public Particle{
public:
    Confetti(Vector ori):Particle(ori){

    }

    virtual void display() override{
        auto& canvas = Canvas::getInstance();
        auto theta = map<float>(location.x, 0, canvas.GetWindowW(), 0, TWO_PI * 2);

        g_transform.resetMatrix();
        g_transform.pushMatrix();
        g_transform.translate(location.x, location.y);
        g_transform.rotate(theta);
        drawRect(0, 0, Green);
        g_transform.popMatrix();
    }

};