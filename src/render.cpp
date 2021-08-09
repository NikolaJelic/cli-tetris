#include "render.hpp"
#include <string>
#include <curses.h>
void render_game(tetris::Field const& game_field, tetris::Tetromino const& next_tetromino) {
	WINDOW *game, *next_block, *info;
	tetris::array_2d field = game_field.get_field();
	game = newwin(26, 12, 1, 1);
	wborder(game, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER,
			ACS_LLCORNER, ACS_LRCORNER);
	for (int i = 0; i < 24; ++i) {
		for (int j = 0; j < 10; ++j) {
			mvwaddch(game, 1 + i, 1 + j, field[i][j]);
		}
	}
	wrefresh(game);

	next_block = newwin(7, 8, 4, 16);
	wborder(next_block, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER,
			ACS_LLCORNER, ACS_LRCORNER);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mvwaddch(next_block, 2 + i, 1 + j, next_tetromino.get_element(i, j));
		}
	}
	wrefresh(next_block);

	info = newwin(7, 8, 12, 16);
	wborder(info, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER,
			ACS_LLCORNER, ACS_LRCORNER);

	mvwprintw(info, 1, 1, "Score");
	mvwprintw(info, 2, 1, "%d", game_field.get_score());
	mvwprintw(info, 4, 1, "Level");
	mvwprintw(info, 5, 1, "%d", game_field.get_level());
	wrefresh(info);
}
