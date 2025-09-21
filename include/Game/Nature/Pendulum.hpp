#pragma once
#include "Game/Utils/Vector.hpp"
#include "Game/Utils/Angle.hpp"
#include "base/Painter.hpp"
#include <cmath>

class Pendulum{
public:
    Vector location{};
    Vector origin{};
    float r{}; //摆臂长度
    float angle{}; //摆臂角度
    float aVelocity{}; //角速度
    float aAcceleration{};//角加速度
    float damping{};  //减震幅度

    Pendulum(){

    }
    Pendulum(Vector ori,float r_){
        location ={};
        origin = ori;
        r = r_;
        angle = PI / 4;
        aVelocity = 0.0f;
        aAcceleration = 0.0f;
        damping = 0.995f;
    }

    void go(){
        update();
        display();
    }
private:
    void update(){
        float gravity = 0.4f;
        aAcceleration = (-1 * gravity / r) * std::sin(angle); //角加速度公式

        aVelocity += aAcceleration;
        angle += aVelocity;
        aVelocity *= damping; //减震(模仿空气阻力)
    }

    void display(){
        float xOffset = r * std::sin(angle);
        float yOffset = r * std::cos(angle);
        
        location.x = origin.x + xOffset;
        location.y = origin.y + yOffset;

        auto& painter = Painter::getInstance();
        painter.DrawLine(origin, location, White);
        painter.DrawCircle(location.x, location.y, 16);
        painter.DrawFilledCircle(origin.x, origin.y, 8,{255,255,0,255});
    }



};





