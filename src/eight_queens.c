/*
 * eight-queens - Copyright (c) 2014 Gomez Guillaume.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim
 *    that you wrote the original software. If you use this software in a product,
 *    an acknowledgment in the product documentation would be appreciated but is
 *    not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include "list.h"

void set_queen(int nb_queen, char board[8][8], int posx, int posy) {
  int x = 0;
  int y = 0;

  board[posy][posx] = nb_queen;
  for (; x < 8; ++x) {
    if (!board[posy][x]) {
      board[posy][x] = nb_queen + 10;
    }
  }
  for (; y < 8; ++y) {
    if (!board[y][posx]) {
      board[y][posx] = nb_queen + 10;
    }
  }
  for (x = posx + 1, y = posy + 1; x < 8 && y < 8; ++x, ++y) {
    if (!board[y][x])
      board[y][x] = nb_queen + 10;
  }
  for (x = posx - 1, y = posy - 1; x >= 0 && y >= 0; --x, --y) {
    if (!board[y][x])
      board[y][x] = nb_queen + 10;
  }
  for (x = posx - 1, y = posy + 1; x >= 0 && y < 8; --x, ++y) {
    if (!board[y][x])
      board[y][x] = nb_queen + 10;
  }
  for (x = posx + 1, y = posy - 1; x < 8 && y >= 0; ++x, --y) {
    if (!board[y][x])
      board[y][x] = nb_queen + 10;
  }
}

void unset_queen(int nb_queen, char board[8][8]) {
  int x, y;

  for (x = 0; x < 8; ++x) {
    for (y = 0; y < 8; ++y) {
      if (board[y][x] == nb_queen || board[y][x] == nb_queen + 10) {
	board[y][x] = 0;
      }
    }
  }
}

int put_queen(int nb_queen, char board[8][8], int possibility, solution **s, options *op) {
  int posy = 0;
  int posx = 0;

  for (; posy < 8; ++posy) {
    for (posx = 0; posx < 8; ++posx) {
      if (!board[posy][posx]) {
	set_queen(nb_queen, board, posx, posy);
	if (nb_queen == 8) {
	  if (add_solution(board, s)) {
	    possibility += 1;
	    print_board(board, possibility, op);
	    if (possibility == 92 && op->stop_before_end)
	      op->end = 1;
	  }
	}
	else
	  possibility = put_queen(nb_queen + 1, board, possibility, s, op);
	unset_queen(nb_queen, board);
	if (op->end)
	  return possibility;
      }
    }
  }
  return possibility;
}

int main(int ac, char **av) {
  char board[8][8] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
  int i;
  solution *s = 0;
  options op;

  if (!check_options(ac, av, &op))
    return 0;
  printf("%d %d\n", op.color, op.stop_before_end);
  printf("\nFor a total of %d possibilities\n", put_queen(1, board, 0, &s, &op));
  clear_list(&s);
  return 0;
}
