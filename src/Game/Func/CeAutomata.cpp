#include "Game/Func/CeAutomata.hpp"
#include "Game/Draw.hpp"
#include "Game/Nature/CA.hpp"
#include "Game/Nature/GameLife.hpp"

CA ca;
std::string Wolframestatus;
std::vector<int> CA::ruleset = { 0, 1, 0, 1, 1, 0, 1, 0 };
void Wolframe_Init() {
	ca.Clear();
	CA newca = CA();
	ca = newca;
}

void Wolframe(Draw* draw) {
	auto& canvas = Canvas::getInstance();
	ca.display();

	// 空格键暂停/继续
	static bool paused = false;
	if (draw->blankPressed_) {
		paused = !paused;
	}

	// 如果没暂停且没完成，生成下一代
	if (!paused && !ca.finished) {
		ca.generate();
	}

	// 按鼠标重置
	if (draw->mousePressed_) {
		CA newCA;
		ca = newCA;
		paused = false;
	}

	// 显示状态信息
	auto& painter = Painter::getInstance();
	Wolframestatus = "Gen: " + std::to_string(ca.currentGeneration) +
			" | " + (ca.finished ? "Finished" : "Running") +
			" | " + (paused ? "Paused" : "Playing");
}

GameOfLife gol;
void ClearCA() {
	ca.Clear();
	//gol.Clear();
}

void GameOfLife_Init() {
	ClearCA();
	GameOfLife newgl = GameOfLife{};
	gol = newgl;
	gol.randomize(0.3f);
}

void GameOfLifeUpdate(Draw* draw) {
	auto& canvas = Canvas::getInstance();
    
    // 更新游戏状态
    gol.generate();
    
    // 处理鼠标交互
    gol.handleMouse(draw->mouse_.x, draw->mouse_.y, draw->mousePressed_);
    
    // 显示网格
    gol.display();
    // 键盘控制
    // if (draw->keyPressed_[SDLK_SPACE]) {
    //     gol.isRunning = !gol.isRunning;
    // }
    // if (draw->keyPressed_[SDLK_r]) {
    //     gol.randomize(0.3f);
    // }
    // if (draw->keyPressed_[SDLK_c]) {
    //     gol.clear();
    // }
}
