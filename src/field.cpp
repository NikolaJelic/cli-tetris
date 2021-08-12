#include "tetris.hpp"

namespace tetris {

void Field::set_game_field() {
	for (int i = 0; i < field_height; ++i) {
		for (int j = 0; j < field_width; ++j) {
			game_field[i][j] = ' ';
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
int Field::check_rows() {
	bool cleared = true;
	int rows = 0;
	for (int i = 0; i < field_height; ++i) {
		cleared = true;
		for (int j = 0; j < field_width; ++j) {
			if (game_field[i][j] == ' ') {
				cleared = false;
			}
		}
		if (cleared) {
			clear_row(i);
			++rows;
		}
	}
	rows_cleared += rows;
	return rows;
}

void Field::clear_row(const int row) {
	for (int i = row; i > 0; --i) {
		for (int j = 0; j < field_width; ++j) {
			game_field[i][j] = game_field[i - 1][j];
		}
	}
}

void Field::update_tetromino(Tetromino& block) {
	std::pair<int, int> block_position = block.get_position();
	std::pair<int, int> previous_position = block.get_previous_position();

	// first clear the previous position of the tetromino and then update the new one
	if (block.is_dropped == false) {
		array_2d temp_block;
		if (block.is_rotated) {
			temp_block = block.get_previous_state();
			previous_position = block_position;
			block.is_rotated = false;
		} else {
			temp_block = block.get_current_block();
		}

		for (int i = previous_position.second; i < previous_position.second + 4; ++i) {
			for (int j = previous_position.first; j < previous_position.first + 4; ++j) {
				if (temp_block[i - previous_position.second][j - previous_position.first] != ' ') {
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
}

} // namespace tetris
