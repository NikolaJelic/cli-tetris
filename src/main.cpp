#include <chrono>
#include <random>
#include <thread>
#include <ncurses.h>
#include "render.hpp"
#include "tetris.hpp"

int random_number(int min, int max) {
	std::random_device r;
	std::default_random_engine re(r());
	std::uniform_int_distribution<int> uniform_dist(min, max);
	return uniform_dist(re);
}
int main(void) {
	// NCURSES INIT
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	halfdelay(2);
	// GAME INIT
	tetris::game_state game_state = tetris::game_state::play;
	tetris::Field game_field;
	tetris::Tetromino block;
	tetris::Tetromino next_block;

	game_field.set_game_field();
	block.spawn_tetromino(static_cast<tetris::tetrominoes>(random_number(0, 6)));
	next_block.spawn_tetromino(static_cast<tetris::tetrominoes>(random_number(0, 6)));

	int key;
	// TIME INIT
	std::chrono::duration<double> lag{0.0f};
	auto previous = std::chrono::system_clock::now();
	// GAME LOOP
	while (game_state == tetris::game_state::play) {
		// TIME
		auto current = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// INPUT
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
		case 'c': game_state = tetris::game_state::lose; break;
		}

		// AUTO FALL
		if (lag.count() >= 1.0f - game_field.get_level() * 0.1) {
			if (block.is_dropped == false) {
				block.move_down(game_field.get_field());
				game_field.update_tetromino(block);
			}
			lag = std::chrono::seconds(0);
		}

		// DROPPED TETROMINO
		if (block.is_dropped) {
			if (block.get_position().second <= 1) {
				game_state = tetris::game_state::lose;
			}
			game_field.add_points(game_field.check_rows());
			if (game_field.get_rows_cleared() % 10 == 0 && game_field.get_rows_cleared() > 1) {
				game_field.next_level();
			}
			block = next_block;
			next_block.spawn_tetromino(static_cast<tetris::tetrominoes>(random_number(0, 6)));
		}

		// RENDER
		render_game(game_field, next_block);
	}
	clear();
	while ((key = getch()) == ERR) {
		render_credits(game_field);
	}
	endwin();
}
