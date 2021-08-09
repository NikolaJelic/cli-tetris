#include <chrono>
#include <iostream>
#include <thread>
#include <ncurses.h>
#include "render.hpp"
#include "tetris.hpp"
int main(void) {

	initscr();
	noecho();
	cbreak();
	curs_set(0);
	// nonl();
	keypad(stdscr, TRUE);
	// nodelay(stdscr, TRUE);
	halfdelay(2);
	tetris::game_state game_state = tetris::game_state::play;
	int i = 0;
	tetris::Field game_field;
	tetris::Tetromino block;
	game_field.set_game_field();
	block.spawn_tetromino(tetris::tetrominoes::J);
	int key;
	std::chrono::duration<double> lag{0.0f};
	auto previous = std::chrono::system_clock::now();
	while (game_state == tetris::game_state::play) {
		auto current = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = current - previous;
		previous = current;
		lag += elapsed;
		key = getch();
		switch (key) {
		case KEY_LEFT:
			block.move_left(game_field.get_field());
			game_field.update_tetromino(block);
			break;
		case KEY_RIGHT:
			block.move_right(game_field.get_field());
			game_field.update_tetromino(block);
			break;
		case KEY_UP:
			block.rotate_tetromino(game_field.get_field());
			game_field.update_tetromino(block);
			break;
		case KEY_DOWN:
			block.move_down(game_field.get_field());
			game_field.update_tetromino(block);
			break;
		case KEY_EXIT: return 0; break;
		case 'p': game_state = tetris::game_state::pause; break;
		}

		if (lag.count() >= 1.0f && block.is_dropped == false) {
			std::cout << lag.count();
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

			block.move_down(game_field.get_field());
			game_field.update_tetromino(block);
			lag = std::chrono::seconds(0);
		}
		if (block.is_dropped) {
			block.spawn_tetromino(tetris::tetrominoes::I);
		}

		render_game(game_field, block);
	}
	cbreak();
	endwin();
}
