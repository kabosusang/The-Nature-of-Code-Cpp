#pragma once
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <memory>

class Canvas {
public:
	static Canvas& getInstance() {
		static Canvas instance;
		return instance;
	}
	Canvas(const Canvas&) = delete;
	Canvas& operator=(const Canvas&) = delete;

	SDL_Window* GetWindow() { return window.get(); }

	//Window WH
    int GetWindowW(){return WindowW;}
    int GetWindowH(){return WindowH;}
	void pollevent(SDL_Event& event);
private:
	Canvas();
	~Canvas();
	SDL_Window* CreateSDLWindow();

private:
	int WindowW = 1200;
	int WindowH = 800;
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
};