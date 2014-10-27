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
#include "print.h"

void print_board(char board[8][8], int possibility, options *op) {
  int i;

  printf("Possibility number %d\n", possibility);
  if (op->color) {
    static char *colors[] = {
      "\033[33;1m",
      "\033[37;1m",
      "\033[0m"
    };

    for (i = 0; i < 8; ++i) {
      int j;

      printf("%s-----------------\n", colors[1]);
      for (j = 0; j < 8; ++j) {
        if (board[i][j] < 10) {
          printf("|%s%d%s", colors[0], board[i][j], colors[1]);
        } else {
          printf("| ");
        }
      }
      printf("|\n");
    }
    printf("-----------------%s\n", colors[2]);
    return;
  }
  for (i = 0; i < 8; ++i) {
    int j;

    printf("-----------------\n");
    for (j = 0; j < 8; ++j) {
      if (board[i][j] < 10) {
        printf("|%d", board[i][j]);
      } else {
        printf("| ");
      }
    }
    printf("|\n");
  }
  printf("-----------------\n");
}
