#pragma once
#include <ncurses.h>
#include "tetris.hpp"

void render_game(tetris::Field const& game_field, tetris::Tetromino const& next_tetromino);
void render_credits(tetris::Field const& game_field);
int color_indice(char shape);
