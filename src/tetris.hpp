#include <array>
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

namespace tetris {
// field is 10(game area) + 2(borders) + 2(buffer) + 8(additional info) = 22
const int field_width = 22;
const int field_height = 24;
using array_2d = std::array<std::array<char, field_width>, field_height>;

enum class tetrominoes { I, J, L, Z, O, S, T };
enum class keys { up, down, left, right, exit, pause };
enum class game_state { win, lose, pause, play };
enum class movement { left, right, down, rotation, stopped };

class Tetromino {
	array_2d tetromino;
	std::pair<int, int> position{4, 1};
	std::pair<int, int> previous_position{position};

  public:
	tetrominoes tetromino_type;
	movement move = movement::down;
	void spawn_tetromino(tetrominoes block);
	void rotate_tetromino(array_2d const& game_field);
	bool move_tetromino(keys key_pressed, array_2d const& game_field);
	//! NEEDS REWORK
	bool will_fit(array_2d const& field, movement const& mov) const;
	void print_tetromino() const;
	inline std::pair<int, int> get_position() const { return position; }
	inline std::pair<int, int> get_previous_position() const { return previous_position; }

	inline char get_element(int const x, int const y) const {
		if (x >= 0 && x <= 4 && y >= 0 && y <= 4) {
			return tetromino[x][y];
		}
		return ' ';
	}
};
class Field {
	array_2d game_field;
	array_2d previous_state;
	int level = 1;
	int score = 0;
	Tetromino current_block;
	Tetromino next_block;

  public:
	void render_game() const;
	// set an empty field with only borders
	void set_game_field();
	bool clear_row();
	void update_tetromino(Tetromino const& block);
	void draw_next_block(Tetromino const& block);
	void update_info();
	void add_points(int const lines_cleared);
	inline void clear_screen() { std::cout << "\033[H\033[2J\033[3J"; }
	inline void next_level() { ++level; }
	inline array_2d get_field() const { return game_field; }
	inline int get_level() const { return level; }
};

} // namespace tetris
