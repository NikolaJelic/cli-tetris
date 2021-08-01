#include "tetromino.hpp"
#include <cstring>

namespace tetris {
void Tetromino::spawn_tetromino(tetrominoes block) {
	switch (block) {
		pos_x = 5;
	case tetrominoes::I:
		tetromino = {{{'.', '.', '.', '.'},
					  {'.', '.', '.', '.'},
					  {'I', 'I', 'I', 'I'},
					  {'.', '.', '.', '.'}}};
		break;
	case tetrominoes::J:
		tetromino = {{{'.', 'J', '.', '.'},
					  {'.', 'J', 'J', 'J'},
					  {'.', '.', '.', '.'},
					  {'.', '.', '.', '.'}}};
		break;
	case tetrominoes::L:
		tetromino = {{{'.', '.', '.', 'L'},
					  {'.', 'L', 'L', 'L'},
					  {'.', '.', '.', '.'},
					  {'.', '.', '.', '.'}}};
		break;
	case tetrominoes::O:
		tetromino = {{{'.', '.', '.', '.'},
					  {'.', 'O', 'O', '.'},
					  {'.', 'O', 'O', '.'},
					  {'.', '.', '.', '.'}}};
		break;
	case tetrominoes::S:
		tetromino = {{{'.', '.', '.', '.'},
					  {'.', '.', 'S', 'S'},
					  {'.', 'S', 'S', '.'},
					  {'.', '.', '.', '.'}}};
		break;
	case tetrominoes::T:
		tetromino = {{{'.', '.', '.', '.'},
					  {'.', '.', 'T', '.'},
					  {'.', 'T', 'T', 'T'},
					  {'.', '.', '.', '.'}}};
		break;
	case tetrominoes::Z:
		tetromino = {{{'.', '.', '.', '.'},
					  {'.', 'Z', 'Z', '.'},
					  {'.', '.', 'Z', 'Z'},
					  {'.', '.', '.', '.'}}};
		break;
	}
}
void Tetromino::print_tetromino() const {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << tetromino[i][j];
		}
		std::cout << '\n';
	}
}
void Tetromino::rotate_tetromino(int const direction) {
	for (int i = 0; i < 4; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			char tmp = tetromino[i][j];
			tetromino[i][j] = tetromino[j][i];
			tetromino[j][i] = tmp;
		}
	}
}
bool Tetromino::will_fit(char field[field_height][field_width]) const { return false; }

void Field::render_game() const {
	for (int i = 0; i < field_height; ++i) {
		for (int j = 0; j < field_width; ++j) {
			if (game_field[i][j] == '#' || game_field[i][j] == '.') {
				std::cout << "\033[1m\033[37m" << game_field[i][j] << "\033[0m";
			} else {
				std::cout << "\033[1m\033[31m" << game_field[i][j] << "\033[0m";
			}
		}
		std::cout << '\n';
	}
}
void Field::set_game_field() {
	// draw main field box, score field and next tetromino box

	for (int i = 0; i < field_height; ++i) {
		for (int j = 0; j < field_width; ++j) {
			game_field[i][j] = ' ';
		}
	}
	// game field
	for (int i = 0; i < field_height; ++i) {
		for (int j = 0; j < 11; ++j) {
			if (i == 0 || i == field_height - 1 || j == 0 || j == 10) {
				game_field[i][j] = '#';
			}
		}
	}

	int top = 2;
	int bot = 8;
	int left = 12;
	int right = field_width - 2;
	for (int i = top; i < bot; ++i) {
		for (int j = left; j < right; ++j) {
			if (i == top && j == 13) {
				std::strncpy(&game_field[i][j], "NEXT", 4);
			}
			if (i == bot - 1 || j == left || j == field_width - 3) {
				game_field[i][j] = '#';
			}
		}
	}

	top = 10;
	bot = 17;
	for (int i = top; i < bot; ++i) {
		for (int j = left; j < right; ++j) {
			if (i == top && j == 13) {
				std::strncpy(&game_field[i][j], "INFO", 4);
			}
			if (i == top + 1 && j == 13) {
				std::strncpy(&game_field[i][j], "PTS:", 4);
			}
			if (i == top + 3 && j == 13) {
				std::strncpy(&game_field[i][j], "LVL:", 4);
			}

			if (i == bot - 1 || j == left || j == field_width - 3) {
				game_field[i][j] = '#';
			}
		}
	}
}

} // namespace tetris
