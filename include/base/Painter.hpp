#pragma once
#include "SDL3/SDL_render.h"
#include <Tools/Color.hpp>
#include <base/Canvas.hpp>

inline static constexpr Color Black = {0,0,0,255};
inline static constexpr Color White = {255,255,255,255};

class Painter {
public:
	static Painter& getInstance() {
		static Painter instance;
		return instance;
	}
	Painter(const Painter&) = delete;
	Painter& operator=(const Painter&) = delete;
	SDL_Renderer* GetRenderer() { return renderer.get(); }

	//SDL Setting Painter
	//设置颜色
	void SetColor(Color color) { SDL_SetRenderDrawColor(GetRenderer(), color.r, color.g, color.b, color.a); }
	void Clear(Color color) {
		SetColor(color);
		SDL_RenderClear(GetRenderer());
	}
	void Present() { SDL_RenderPresent(GetRenderer()); }

	//RunPixelPen
	void PutPixel(float x, float y, Color color);
	void DrawRect(float x, float y, float width, float height, Color color);
	void DrawRectOutline(float x, float y, float width, float height, Color color);
	void DrawCircle(int centerX, int centerY, int radius);


private:
	Painter();
	~Painter();

private:
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
};