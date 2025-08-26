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

void Painter::PutPixel(float x, float y,Color color) {
    auto& canvas = Canvas::getInstance();
	SetColor(color);
	SDL_RenderPoint(GetRenderer(), x, y);
}

void Painter::DrawRect(float x, float y, float width, float height, Color color) {
    SetColor(color);
    
    SDL_FRect rect = {
        x,          // x 位置
        y,          // y 位置
        width,      // 宽度
        height      // 高度
    };
    
    SDL_RenderFillRect(GetRenderer(), &rect);
}

void Painter::DrawRectOutline(float x, float y, float width, float height, Color color) {
    SetColor(color);
    
    SDL_FRect rect = {
        x,          // x 位置
        y,          // y 位置
        width,      // 宽度
        height      // 高度
    };
    
    SDL_RenderRect(GetRenderer(), &rect);
}
