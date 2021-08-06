#pragma once
#include <array>
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

namespace tetris {
// field is 10(game area) + 2(borders) + 2(buffer) + 8(additional info) = 22
const int field_width = 10;
const int field_height = 24;
using array_2d = std::array<std::array<char, field_width>, field_height>;

enum class tetrominoes { I, J, L, Z, O, S, T };
enum class keys { up, down, left, right, exit, pause };
enum class game_state { win, lose, pause, play };
enum class movement { left, right, down, rotation, stopped };

class Tetromino {
	array_2d tetromino;
	std::pair<int, int> position{4, 0};
	std::pair<int, int> previous_position{position};

  public:
	bool is_dropped = false;
	void spawn_tetromino(tetrominoes block);
	void rotate_tetromino(array_2d const& game_field);
	bool move_down(array_2d const& field);
	bool move_left(array_2d const& field);
	bool move_right(array_2d const& field);
	bool will_fit(array_2d field, std::pair<int, int> pos, bool rotation) const;
	inline std::pair<int, int> get_position() const { return position; }
	inline std::pair<int, int> get_previous_position() const { return previous_position; }

	inline char get_element(int const x, int const y) const {
		if (x >= 0 && x < 4 && y >= 0 && y < 4) {
			return tetromino[x][y];
		}
		return ' ';
	}
};
class Field {
	array_2d game_field;
	int level = 1;
	int score = 0;
	Tetromino current_block;
	Tetromino next_block;

  public:
	// set an empty field with only borders
	void set_game_field();
	bool clear_row();
	void update_tetromino(Tetromino const& block);
	void add_points(int const lines_cleared);
	inline void next_level() { ++level; }
	inline array_2d get_field() const { return game_field; }
	inline int get_level() const { return level; }
	inline int get_score() const { return score; }
};

} // namespace tetris
