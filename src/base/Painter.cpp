#include "SDL3/SDL_render.h"
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

void Painter::DrawLine(Vector v1,Vector v2,Color color){
	SDL_SetRenderDrawColor(GetRenderer(), color.r,color.g,color.b,color.a);
	SDL_RenderLine(GetRenderer(), v1.x, v1.y, v2.x, v2.y);
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




void Painter::DrawFilledCircle(int centerX, int centerY, int radius, Color color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        // 绘制水平扫描线（填充圆内部）
        DrawHorizontalLine(centerX - x, centerX + x, centerY + y, color);
        DrawHorizontalLine(centerX - x, centerX + x, centerY - y, color);
        DrawHorizontalLine(centerX - y, centerX + y, centerY + x, color);
        DrawHorizontalLine(centerX - y, centerX + y, centerY - x, color);
        
        // 更新 Bresenham 算法参数
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

// 辅助函数：绘制水平线
void Painter::DrawHorizontalLine(int startX, int endX, int y, Color color) {
    if (startX > endX) std::swap(startX, endX);
    for (int x = startX; x <= endX; x++) {
        PutPixel(x, y, color);
    }
}
