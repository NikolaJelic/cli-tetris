#include "tetris.hpp"

namespace tetris {
void Tetromino::spawn_tetromino(tetrominoes block) {
	position.first = 4;
	position.second = 1;
	tetromino_type = block;
	switch (block) {
	case tetrominoes::I:
		tetromino = {{{'I', 'I', 'I', 'I'},
					  {' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' '}}};
		break;
	case tetrominoes::J:
		tetromino = {{{' ', 'J', ' ', ' '},
					  {' ', 'J', 'J', 'J'},
					  {' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' '}}};
		break;
	case tetrominoes::L:
		tetromino = {{{' ', ' ', ' ', 'L'},
					  {' ', 'L', 'L', 'L'},
					  {' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' '}}};
		break;
	case tetrominoes::O:
		tetromino = {{{' ', 'O', 'O', ' '},
					  {' ', 'O', 'O', ' '},
					  {' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' '}}};
		break;
	case tetrominoes::S:
		tetromino = {{{' ', ' ', 'S', 'S'},
					  {' ', 'S', 'S', ' '},
					  {' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' '}}};
		break;
	case tetrominoes::T:
		tetromino = {{{' ', ' ', 'T', ' '},
					  {' ', 'T', 'T', 'T'},
					  {' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' '}}};
		break;
	case tetrominoes::Z:
		tetromino = {{{' ', 'Z', 'Z', ' '},
					  {' ', ' ', 'Z', 'Z'},
					  {' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' '}}};
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
//! rotation doesn't work
void Tetromino::rotate_tetromino(array_2d const& game_field) {
	if (will_fit(game_field, movement::rotation)) {
		for (int i = 0; i < 4; ++i) {
			for (int j = i + 1; j < 4; ++j) {
				char tmp = tetromino[i][j];
				tetromino[i][j] = tetromino[j][i];
				tetromino[j][i] = tmp;
			}
		}
	}
}
bool Tetromino::will_fit(array_2d const& field, movement const& mov) const {
	if (mov == movement::down) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (tetromino[i][j] != ' ' && tetromino[(i == 3) ? i : i + 1][j] == ' ' &&
					field[position.second + i + 1][position.first + j] != ' ') {
					return false;
				}
			}
		}
	}

	if (mov == movement::left) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (tetromino[i][j] != ' ' && tetromino[(j == 0) ? j : j - 1][j] == ' ' &&
					field[position.second + i][position.first + j - 1] != ' ') {
					return false;
				}
			}
		}
	}

	if (mov == movement::right) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (tetromino[i][j] != ' ' && tetromino[(j == 3) ? j : j + 1][j] == ' ' &&
					field[position.second + i + 1][position.first + j + 1] != ' ') {
					return false;
				}
			}
		}
	}

	if (mov == movement::rotation) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (field[position.second + i][position.first + j + 1] != ' ') {
					return false;
				}
			}
		}
	}
	return true;
}

bool Tetromino::move_tetromino(keys key_pressed, array_2d const& field) {
	if (key_pressed == keys::left && will_fit(field, movement::left)) {
		previous_position.first = position.first;
		--position.first;
		move = movement::left;
		return true;
	} else if (key_pressed == keys::right && will_fit(field, movement::right)) {
		previous_position.first = position.first;
		++position.first;
		move = movement::right;

		return true;
	} else if (key_pressed == keys::down && will_fit(field, movement::down)) {
		previous_position.second = position.second;
		++position.second;
		move = movement::down;

		return true;
	}
	move = movement::stopped;

	return false;
}

} // namespace tetris
