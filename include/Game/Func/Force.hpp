#pragma once
//F = M * A
struct Draw;


void MouseDownWind(Draw* draw);

//Muti Ball
void MutiBallForce_Init(Draw* draw);
void MutiBallForce(Draw* draw);
void FirctionForce(Draw* draw);

void DragMagnitude_Init(Draw* draw);
void DragMagnitude(Draw* draw);

void Attractor_Init();
void Attractor_Draw(Draw* draw);
