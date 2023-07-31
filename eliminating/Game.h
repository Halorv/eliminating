#include "Board.h"

class Game {
private:
	Board board;

public:
	Game();
	void Run();
};

Game::Game() {
	board.load(); // 加载初始地图
	board.draw(); // 绘制初始地图
	board.window.display(); // 显示已渲染的内容
	board.Check_board();
}

void Game::Run() {
	while (board.window.isOpen()) {
		board.window.clear();
		board.draw();
		board.Control_mouse_events(board.window);
		board.window.display();
	}
}