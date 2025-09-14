#include "core/Event.hpp"
#include "core/Game.hpp"
#include <base/Canvas.hpp>
#include <base/Painter.hpp>

#include "Game/Draw.hpp"
#include "Game/editor/editor.hpp"


int main(int argc, char* argv[]) {
	//画布
	auto& canvas = Canvas::getInstance();
	//画笔
	auto& painter = Painter::getInstance();

	//事件循环 和 GameLoop
	EventTrain train;
	Game game(train);

	//Editor
	Editor editor{};

	//Draw
	Draw draw;

	//Logic
	train.subscribeFrame([&draw,&editor,&painter](float deltaTime) {
		painter.Clear(Black);
		draw.draw();
		editor.draw();

		draw.present();
	});

	//Editor
	train.subscribeEvent([&](SDL_Event& e){
		canvas.pollevent(e);
		draw.pollevent(e);
		editor.pollevent(e);
	});



	// train.publishEvent(SDL_Event &event){

	// }


	//渲染循环
	game.run();

	return 0;
}
