#include "Game/Func/Angle.hpp"

#include "Game/Utils/Angle.hpp"
#include "base/Canvas.hpp"

void AngleMotion(Draw* draw){
    auto& canvas = Canvas::getInstance();

    g_transform.resetMatrix();
    g_transform.translate(canvas.GetWindowW() / 2.0f,canvas.GetWindowH() / 2.0f);

    g_transform.rotate(45.0f);
    drawLine(-50.0f, 0.0f, 50.0f, 0.0f);
    drawEllipse(50.0f, 0.0f, 8.0f, 8.0f);
    drawEllipse(-50.0f, 0.0f, 8.0f, 8.0f);


}