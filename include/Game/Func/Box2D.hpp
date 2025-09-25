#pragma once
#include "base/Canvas.hpp"
#include "box2d/box2d.h"
#include "box2d/math_functions.h"

void LiveWorld_Init();
void LiveWorld(float);


struct Draw;
void MouseClickMutliBox_Init();
void MouseClickMutliBox(Draw* draw,float deltaTime);


void StaticBoundary_Init();
void StaticBoundary(Draw* draw,float deltaTime);







