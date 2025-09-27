#pragma once
#include "Game/Utils/Vector.hpp"
#include "SDL3/SDL_render.h"
#include <Tools/Color.hpp>
#include <base/Canvas.hpp>

inline static constexpr Color Black = {0,0,0,255};
inline static constexpr Color White = {255,255,255,255};
inline static constexpr Color Red = {255,0,0,255};
inline static constexpr Color Green = {0,255,0,255};
inline static constexpr Color Blue = {0,0,255,255};
inline static constexpr Color Gray = {220,220,220,255};




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
	void DrawLine(Vector v1,Vector v2,Color color);
	void DrawRect(float x, float y, float width, float height, Color color);
	void DrawRectOutline(float x, float y, float width, float height, Color color);
	void DrawCircle(int centerX, int centerY, int radius);
	void DrawFilledCircle(int centerX, int centerY, int radius, Color color);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_FColor color);


private:
	Painter();
	~Painter();
	void DrawHorizontalLine(int startX, int endX, int y, Color color);

private:
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
};