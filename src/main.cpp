#include <chrono>
#include <iostream>
#include <thread>
#include "tetromino.hpp"
int main(void) {

	tetris::game_state game_state = tetris::game_state::play;
	int i = 0;
	tetris::Field game_field;
	game_field.set_game_field();
	while (i < 300 /* game_state == tetris::game_state::play */) {

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		game_field.clear_screen();
		tetris::Tetromino block;
		block.spawn_tetromino(tetris::tetrominoes::J);
		block.rotate_tetromino(game_field.get_field());
		game_field.update_info();
		game_field.add_points(4);
		game_field.render_game();
		++i;
	}
}
