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
	halfdelay(2);

	tetris::game_state game_state = tetris::game_state::play;
	int i = 0;
	tetris::Field game_field;
	// game_field.set_game_field();
	tetris::Tetromino block;
	game_field.set_game_field();
	block.spawn_tetromino(tetris::tetrominoes::J);
	int key;
	tetris::keys key_pressed = tetris::keys::down;
	while (game_state == tetris::game_state::play) {
		// std::this_thread::sleep_for(std::chrono::milliseconds(500 - game_field.get_level() *
		// 50));
		key = getch();
		switch (key) {
		case KEY_LEFT: block.move_left(game_field.get_field()); break;
		case KEY_RIGHT: block.move_right(game_field.get_field()); break;
		case KEY_UP: block.rotate_tetromino(game_field.get_field()); break;
		case KEY_DOWN: block.move_down(game_field.get_field()); break;
		case ERR: block.move_down(game_field.get_field()); break;
		case KEY_EXIT: return 0; break;
		case 'p': game_state = tetris::game_state::pause; break;
		}
		game_field.update_tetromino(block);
		render_game(game_field, block);
		++i;
	}
	endwin();
}
