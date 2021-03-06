#pragma once
#include <array>
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>
namespace tetris {
const int field_width = 10;
const int field_height = 24;
using array_2d = std::array<std::array<char, field_width>, field_height>;

enum class tetrominoes { I, J, L, Z, O, S, T };
enum class keys { up, down, left, right, exit };
enum class game_state { lose, play };
enum class movement { left, right, down, rotation, stopped };

class Tetromino {
	array_2d tetromino;
	array_2d previous_state;
	std::pair<int, int> position{4, 0};
	std::pair<int, int> previous_position{position};

  public:
	bool is_dropped = false;
	bool is_rotated = false;
	void spawn_tetromino(tetrominoes block);
	void rotate_tetromino(array_2d const& game_field);
	bool move_down(array_2d const& field);
	bool move_left(array_2d const& field);
	bool move_right(array_2d const& field);
	bool will_fit(array_2d field, std::pair<int, int> pos, bool rotation) const;
	void check_level();
	inline std::pair<int, int> get_position() const { return position; }
	inline std::pair<int, int> get_previous_position() const { return previous_position; }
	inline array_2d get_previous_state() const { return previous_state; }
	inline array_2d get_current_block() const { return tetromino; }
	inline char get_element(int const i, int const j) const {
		if (i >= 0 && i < 4 && j >= 0 && j < 4) {
			return tetromino[i][j];
		}
		return ' ';
	}
};
class Field {
	array_2d game_field;
	int level = 1;
	int score = 0;
	int rows_cleared = 0;
	Tetromino current_block;
	Tetromino next_block;

  public:
	void set_game_field();
	int check_rows();
	void clear_row(int const row);
	void update_tetromino(Tetromino& block);
	void add_points(int const lines_cleared);
	inline void next_level() { ++level; }
	inline array_2d get_field() const { return game_field; }
	inline int get_level() const { return level; }
	inline int get_rows_cleared() const { return rows_cleared; }
	inline int get_score() const { return score; }
};

} // namespace tetris
