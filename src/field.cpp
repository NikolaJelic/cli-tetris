#include "tetris.hpp"

namespace tetris {
void Field::render_game() const {
	for (int i = 0; i < field_height; ++i) {
		for (int j = 0; j < field_width; ++j) {
			if (game_field[i][j] == '#' || game_field[i][j] == '.') {
				std::cout << "\033[1m\033[37m" << game_field[i][j] << "\033[0m";
			} else if (j < 12 || (i > 2 && i < 10)) {
				switch (game_field[i][j]) {
				case 'I':
					// cyan
					std::cout << "\033[1m\033[36m"
							  << "█"
							  << "\033[0m";
					break;
				case 'J':
					// blue
					std::cout << "\033[1m\033[34m"
							  << "█"
							  << "\033[0m";
					break;
				case 'T':
					// magenta
					std::cout << "\033[1m\033[35m"
							  << "█"
							  << "\033[0m";
					break;

				case 'S':
					// green
					std::cout << "\033[1m\033[32m"
							  << "█"
							  << "\033[0m";
					break;
				case 'Z':
					// red
					std::cout << "\033[1m\033[31m"
							  << "█"
							  << "\033[0m";
					break;
				case 'O':
					// yellow
					std::cout << "\033[1m\033[33;1m"
							  << "█"
							  << "\033[0m";
					break;
				case 'L':
					// orange
					std::cout << "\033[1m\033[31;1m"
							  << "█"
							  << "\033[0m";
					break;
				case ' ': std::cout << ' '; break;
				}
			} else {
				std::cout << "\033[1m\033[37;1m" << game_field[i][j] << "\033[0m";
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
		for (int j = 0; j < 12; ++j) {
			if (i == 0 || i == field_height - 1 || j == 0 || j == 11) {
				game_field[i][j] = '#';
			}
		}
	}

	int top = 2;
	int bot = 8;
	int left = 13;
	int right = field_width - 1;
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
	previous_state = game_field;
}

void Field::add_points(int const lines_cleared) {
	switch (lines_cleared) {
	case 1: score += (40 * level); break;
	case 2: score += (100 * level); break;
	case 3: score += (300 * level); break;
	case 4: score += (1200 * level); break;
	}
}
// TODO check last movement of the block and update with it
// ! keep track of the previous position, turn all of the old blocks into ' ' and then redraw the
// !tetromino at the new position

//! problem is that the tetromino gets deleted when it stops moving/ a new one spawns
void Field::update_tetromino(Tetromino const& block) {
	std::pair<int, int> block_position = block.get_position();
	std::pair<int, int> previous_position = block.get_previous_position();

	// first clear the previous position of the tetromino and then update the new one
	for (int i = previous_position.second; i < previous_position.second + 4; ++i) {
		for (int j = previous_position.first; j < previous_position.first + 4; ++j) {
			if (block.get_element(i - previous_position.second, j - previous_position.first) !=
					' ' &&
				block.move != movement::stopped) {
				game_field[i][j] = ' ';
			}
		}
	}

	for (int i = block_position.second; i < block_position.second + 4; ++i) {
		for (int j = block_position.first; j < block_position.first + 4; ++j) {
			if (block.get_element(i - block_position.second, j - block_position.first) != ' ') {
				game_field[i][j] =
					block.get_element(i - block_position.second, j - block_position.first);
			}
		}
	}
}
void Field::draw_next_block(Tetromino const& block) {
	int left = 14, right = 18, top = 3, bot = 7;
	for (int i = top; i < bot; ++i) {
		for (int j = left; j < right; ++j) {
			game_field[i][j] = block.get_element(i - top, j - left);
		}
	}
}
void Field::update_info() {
	int score_y = 12;
	int x_value = 14;
	int level_y = 14;
	std::string score_str = std::to_string(score);
	std::string level_str = std::to_string(level);
	score_str.copy(&game_field[score_y][x_value], 7);
	level_str.copy(&game_field[level_y][x_value], 4);
}
} // namespace tetris
