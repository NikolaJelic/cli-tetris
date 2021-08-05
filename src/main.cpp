#include <chrono>
#include <iostream>
#include <thread>
#include <ncurses.h>
#include "tetris.hpp"
int main(void) {

	initscr();
	noecho();
	// cbreak();
	// nonl();
	keypad(stdscr, TRUE);

	endwin();
	tetris::game_state game_state = tetris::game_state::play;
	int i = 0;
	tetris::Field game_field;
	game_field.set_game_field();
	tetris::Tetromino block;
	block.spawn_tetromino(tetris::tetrominoes::J);
	while (i < 300) {
		// timing
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 - game_field.get_level() * 40));

		game_field.clear_screen();
		// game_field.draw_next_block(block);
		if (!block.move_tetromino(tetris::keys::down, game_field.get_field())) {
			block.spawn_tetromino(tetris::tetrominoes::L);
		}
		if (char ch = getch() == 'l') {
			block.move_tetromino(tetris::keys::left, game_field.get_field());
		}
		game_field.add_points(2);
		game_field.update_info();
		game_field.update_tetromino(block);
		game_field.render_game();
		++i;
	}
}
