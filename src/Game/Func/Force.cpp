#include "Game/Func/Force.hpp"

#include "Game/Draw.hpp"
#include "Game/Mover.hpp"
#include "Game/Utils/Vector.hpp"
#include "Game/Nature/Liquid.hpp"
#include "base/Painter.hpp"

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
    moversPtr.reset();
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
        m.acceleration = {};
        m.applyForce(wind);
        m.applyForce(gravity);
        m.update();
        m.display(false);
        m.edgejudging();
    }
}

void FirctionForce(Draw* draw){
    if (!moversPtr) return;
    
    Vector wind = { 0.01f, 0.0f };
    Vector gravity = { 0, 0.1f };

    float c = 0.03f;
    for (auto& m : *moversPtr) {
        m.acceleration = {};
        auto firction = m.velocity;
        firction.mult(-1);
        firction.normalize();
        firction.mult(c);
        
        m.applyForce(firction);
        m.applyForce(wind);
        m.applyForce(gravity);
        m.update();
        m.display(false);
        m.edgejudging();
    }
}


Liquid liquid;
void DragMagnitude_Init(Draw* draw){
    auto& canvas = Canvas::getInstance();
    liquid = {0,(float)canvas.GetWindowH() / 2,(float)canvas.GetWindowW(),(float)canvas.GetWindowH()/2,0.1};
    
    moversPtr.reset();
    moversPtr = std::make_unique<std::vector<Mover>>();
    moversPtr->reserve(100);
    
    for (int i = 0; i < 5; i++) {
        moversPtr->emplace_back((float)Random(0.1, 5).get(), 0, 0);
    }
}

void DragMagnitude(Draw* draw){
    liquid.display();
    
    for (auto& m : *moversPtr) {
        m.acceleration = {};
        if (m.IsInside(liquid)){
            m.drag(liquid);
            std::cout << "In Liquid";
        }
        float m1 = 0.1 * m.mass;
        Vector gravity = { 0, m1 };
        m.applyForce(gravity);
        m.update();
        m.display(false);
        m.edgejudging();
    }

}









