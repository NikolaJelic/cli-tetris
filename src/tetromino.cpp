#include "tetromino.hpp"
#include <cstring>
#include <string>

namespace tetris {
void Tetromino::spawn_tetromino(tetrominoes block) {
	switch (block) {
		pos_x = 5;
	case tetrominoes::I:
		tetromino = {{{' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' '},
					  {'I', 'I', 'I', 'I'},
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
		tetromino = {{{' ', ' ', ' ', ' '},
					  {' ', 'O', 'O', ' '},
					  {' ', 'O', 'O', ' '},
					  {' ', ' ', ' ', ' '}}};
		break;
	case tetrominoes::S:
		tetromino = {{{' ', ' ', ' ', ' '},
					  {' ', ' ', 'S', 'S'},
					  {' ', 'S', 'S', ' '},
					  {' ', ' ', ' ', ' '}}};
		break;
	case tetrominoes::T:
		tetromino = {{{' ', ' ', ' ', ' '},
					  {' ', ' ', 'T', ' '},
					  {' ', 'T', 'T', 'T'},
					  {' ', ' ', ' ', ' '}}};
		break;
	case tetrominoes::Z:
		tetromino = {{{' ', ' ', ' ', ' '},
					  {' ', 'Z', 'Z', ' '},
					  {' ', ' ', 'Z', 'Z'},
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
bool Tetromino::will_fit(array_2d const& field, movement const& mov) const { return true; }
bool Tetromino::move_tetromino(keys key_pressed, array_2d const& field) {
	if (key_pressed == keys::left && will_fit(field, movement::left)) {
		--pos_x;
		return true;
	} else if (key_pressed == keys::right && will_fit(field, movement::right)) {
		++pos_x;
		return true;
	}
	return false;
}

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
			if (i == top && j == left + 1) {
				std::strncpy(&game_field[i][j], "=NEXT=", 6);
			}
			if (i == bot - 1 || j == left || j == right - 1) {
				game_field[i][j] = '#';
			}
		}
	}
	top = 10;
	bot = 16;
	left = 12;
	right = field_width - 1;
	for (int i = top; i < bot; ++i) {
		for (int j = left; j < right; ++j) {
			if (i == top && j == left + 1) {
				std::strncpy(&game_field[i][j], "=INFO==", 7);
			}
			if (i == top + 1 && j == left + 1) {
				std::strncpy(&game_field[i][j], "PTS:", 4);
			}
			if (i == top + 3 && j == left + 1) {
				std::strncpy(&game_field[i][j], "LVL:", 4);
			}

			if (i == bot - 1 || j == left || j == right - 1) {
				game_field[i][j] = '#';
			}
		}
	}
}

void Field::add_points(int const lines_cleared) {
	switch (lines_cleared) {
	case 1: score += (40 * level); break;
	case 2: score += (100 * level); break;
	case 3: score += (300 * level); break;
	case 4: score += (1200 * level); break;
	}
}

void Field::update_tetromino(Tetromino const& block) {}
void Field::draw_next_block(Tetromino const& block) {
	int left = 13, right = 17, top = 3, bot = 7;
	for (int i = top; i < bot; ++i) {
		for (int j = left; j < right; ++j) {
			game_field[i][j] = block.get_element(i - top, j - left);
		}
	}
}
void Field::update_info() {
	int score_y = 12;
	int x_value = 13;
	int level_y = 14;
	std::string score_str = std::to_string(score);
	std::string level_str = std::to_string(level);
	score_str.copy(&game_field[score_y][x_value], 7);
	level_str.copy(&game_field[level_y][x_value], 4);
}

} // namespace tetris
