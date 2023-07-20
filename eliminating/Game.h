#include "Board.h"

class Game {
private:
	Board board;

public:
	Game();
	void Run();
};

Game::Game() {
	board.load();
	board.draw();
	board.window.display();
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