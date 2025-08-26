#include "Tools/Color.hpp"
#include <base/Canvas.hpp>
#include <base/Painter.hpp>

Painter::Painter() :
		renderer(SDL_CreateRenderer(Canvas::getInstance().GetWindow(), NULL), SDL_DestroyRenderer) {
	if (!renderer) {
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		SDL_Quit();
	}
}

Painter::~Painter() {
	renderer.reset();
}

void Painter::PutPixel(float x, float y, Color color) {
	auto& canvas = Canvas::getInstance();
	SetColor(color);
	SDL_RenderPoint(GetRenderer(), x, y);
}

void Painter::DrawRect(float x, float y, float width, float height, Color color) {
	SetColor(color);

	SDL_FRect rect = {
		x, // x 位置
		y, // y 位置
		width, // 宽度
		height // 高度
	};

	SDL_RenderFillRect(GetRenderer(), &rect);
}

void Painter::DrawRectOutline(float x, float y, float width, float height, Color color) {
	SetColor(color);

	SDL_FRect rect = {
		x, // x 位置
		y, // y 位置
		width, // 宽度
		height // 高度
	};

	SDL_RenderRect(GetRenderer(), &rect);
}

void Painter::DrawCircle(int centerX, int centerY, int radius) {
	int x = radius;
	int y = 0;
	int err = 0;
	Color color{ 255, 255, 255, 255 };

	while (x >= y) {
		PutPixel(centerX + x, centerY + y, color);
		PutPixel(centerX + y, centerY + x, color);
		PutPixel(centerX - y, centerY + x, color);
		PutPixel(centerX - x, centerY + y, color);
		PutPixel(centerX - x, centerY - y, color);
		PutPixel(centerX - y, centerY - x, color);
		PutPixel(centerX + y, centerY - x, color);
		PutPixel(centerX + x, centerY - y, color);
		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}
