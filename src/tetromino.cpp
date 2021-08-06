#include <utility>
#include "tetris.hpp"

namespace tetris {
void Tetromino::spawn_tetromino(tetrominoes block) {
	position.first = 4;
	position.second = 1;
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

//! rotation doesn't work
void Tetromino::rotate_tetromino(array_2d const& game_field) {}
bool Tetromino::will_fit(array_2d field, std::pair<int, int> pos, bool rotation) const {

	for (int i = position.second; i < position.second + 4; ++i) {
		for (int j = position.first; j < position.first + 4; ++j) {
			if (tetromino[i - position.second][j - position.first] != ' ') {
				field[i][j] = ' ';
			}
		}
	}
	for (int i = pos.second; i < pos.second + 4; ++i) {
		for (int j = pos.first; j < pos.first + 4; ++j) {
			if (tetromino[i - pos.second][j - pos.first] != ' ' &&
				(field[i][j] != ' ' || i > 23 || j < 0 || j > 9)) {
				return false;
			}
		}
	}
	return true;
}

bool Tetromino::move_down(array_2d const& field) {
	previous_position.first = position.first;
	previous_position.second = position.second;
	if (will_fit(field, {position.first, position.second + 1}, false)) {
		++position.second;
		return true;
	}
	is_dropped = true;
	return false;
}

bool Tetromino::move_left(array_2d const& field) {
	previous_position.first = position.first;
	previous_position.second = position.second;
	if (will_fit(field, {position.first - 1, position.second}, false)) {
		--position.first;
		return true;
	}
	move_down(field);
	return false;
}
bool Tetromino::move_right(array_2d const& field) {
	previous_position.first = position.first;
	previous_position.second = position.second;
	if (will_fit(field, {position.first + 1, position.second}, false)) {
		++position.first;
		return true;
	}
	move_down(field);
	return false;
}

} // namespace tetris
