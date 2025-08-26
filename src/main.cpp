#include "core/Event.hpp"
#include "core/Game.hpp"
#include <base/Canvas.hpp>
#include <base/Painter.hpp>

#include "Game/Draw.hpp"


int main(int argc, char* argv[]) {
	//画布
	auto& canvas = Canvas::getInstance();
	//画笔
	auto& painter = Painter::getInstance();

	//事件循环 和 GameLoop
	EventTrain train;
	Game game(train);

	//Draw
	Draw draw{};

	train.subscribeFrame([&draw](float deltaTime) {
		draw.draw();
		draw.present();
	});


	//渲染循环
	game.run();

	return 0;
}
