#include <array>
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

namespace tetris {
const int field_width = 22;
// field is 10(game area) + 2(borders) + 2(buffer) + 6(additional info) = 20
const int field_height = 24;
using array_2d = std::array<std::array<char, field_width>, field_height>;

enum class tetrominoes { I, J, L, Z, O, S, T };
enum class keys { up, down, left, right, exit, pause };
enum class game_state { win, lose, pause, play };
enum class movement { left, right, down, rotation };

class Tetromino {
	std::array<std::array<char, 4>, 4> tetromino;
	int pos_x = 4;
	int pos_y = 0;

  public:
	void spawn_tetromino(tetrominoes block);
	void rotate_tetromino(array_2d const& game_field);
	bool move_tetromino(keys key_pressed, array_2d const& game_field);
	bool will_fit(array_2d const& field, movement const& mov) const;
	void print_tetromino() const;
	inline char get_element(int const x, int const y) const {
		if (x >= 0 && x <= 4 && y >= 0 && y <= 4) {
			return tetromino[x][y];
		}
		return ' ';
	}
};
class Field {
	array_2d game_field;
	int level = 1;
	int score = 0;

  public:
	void render_game() const;
	// set an empty field with only borders
	void set_game_field();
	void clear_row(int const row);
	void update_tetromino(Tetromino const& block);
	void draw_next_block(Tetromino const& block);
	void update_info();
	void add_points(int const lines_cleared);
	inline void clear_screen() { std::cout << "\033[H\033[2J\033[3J"; }
	inline void next_level() { ++level; }
	inline array_2d get_field() const { return game_field; }
};

} // namespace tetris
