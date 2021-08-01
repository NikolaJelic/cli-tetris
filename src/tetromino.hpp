#include <array>
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

namespace tetris {
const int field_width = 20;
// field is 10(game area) + 2(borders) + 2(buffer) + 6(additional info) = 20
const int field_height = 24;
enum class tetrominoes { I, J, L, Z, O, S, T };
enum class keys { up, down, left, right, exit, pause };
enum class game_state { win, lose, pause };

class Tetromino {
	std::array<std::array<char, 4>, 4> tetromino;
	int pos_x = 4;
	int pos_y = 0;

  public:
	void spawn_tetromino(tetrominoes block);
	void rotate_tetromino(int const direction);
	void move_tetromino(keys key_pressed);
	bool will_fit(char field[field_height][field_width]) const;
	void print_tetromino() const;
};
class Field {
	std::array<std::array<char, field_width>, field_height> game_field;
	int level = 1;

  public:
	void render_game() const;
	// todo pass it the current and next blocks, level and score
	// todo store important ascii escape sequences in an array of strings/enums
	void set_game_field();
	void clear_row(int const row);
	inline void clear_screen() { std::cout << "\033[H\033[2J\033[3J"; }
	inline void next_level() { ++level; }
};

} // namespace tetris
