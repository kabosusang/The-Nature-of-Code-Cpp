#pragma once
#include "base/Canvas.hpp"


struct Editor {
	Editor();
	void init();
	void draw();

    void pollevent(SDL_Event& event);

private:
	void DemoWindowWidgetsListBoxes();
	SDL_Window* window_;
	SDL_Renderer* renderer_;
};