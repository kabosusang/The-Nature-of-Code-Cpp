#include "Game/Func/Force.hpp"

#include "Game/Draw.hpp"
#include "Game/Mover.hpp"
#include "Game/Utils/Vector.hpp"
#include <array>
#include <vector>

void MouseDownWind(Draw* draw) {
	draw->mover_.acceleration = {};
	//gravity
	draw->mover_.applyForce({ 0, 0.1f });
	if (draw->mousePressed_) {
		Vector wind = { 0, -0.2f };
		draw->mover_.applyForce(wind);
	}
	//Edge
	draw->mover_.edgejudging();

	draw->mover_.update();
	draw->mover_.display();
}



std::unique_ptr<std::vector<Mover>> moversPtr;
void ClearMovers() {
    moversPtr.reset();
}

void MutiBallForce_Init(Draw* draw) {
    auto& canvas = Canvas::getInstance();
    moversPtr = std::make_unique<std::vector<Mover>>();
    moversPtr->reserve(102);
    
    for (int i = 0; i < 100; i++) {
        moversPtr->emplace_back((float)Random(0.1, 5).get(), 0, 0);
    }

    moversPtr->emplace_back(10, 0, canvas.GetWindowH() / 2.0f);
    moversPtr->emplace_back(0.1, (float)canvas.GetWindowW(), canvas.GetWindowH() / 2.0f);
}

void MutiBallForce(Draw* draw) {
    if (!moversPtr) return;
    
    Vector wind = { 0.01f, 0.0f };
    Vector gravity = { 0, 0.1f };

    for (auto& m : *moversPtr) {
        m.applyForce(wind);
        m.applyForce(gravity);
        m.update();
        m.display(false);
        m.edgejudging();
    }
}







