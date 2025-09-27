#pragma once

struct Draw;
void SimpleVehicle(Draw* draw);
void SimpleVehicleArrive(Draw* draw);


void LiveInFlowField_Init();
void LiveInFlowField();

void GroupBehavior_Init();
void GroupBehavior(Draw* draw);


void GroupApplyBehavior(Draw* draw);


void FlockBoidsBehavior_Init();
void FlockBoidsBehavior(Draw* draw);



