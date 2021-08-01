#include <iostream>
#include "tetromino.hpp"

int main(void) {
	tetris::Tetromino block;
	block.spawn_tetromino(tetris::tetrominoes::J);
	block.print_tetromino();
	block.rotate_tetromino(1);
	std::cout << '\n';
	block.print_tetromino();
	tetris::Field game_field;
	game_field.set_game_field();
	game_field.render_game();
}
