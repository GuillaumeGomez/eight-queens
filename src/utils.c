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

#include <string.h>
#include <stdio.h>
#include "utils.h"

int compare_boards(char board1[8][8], char board2[8][8]) {
  int i = 0;

  for (; i < 8; ++i) {
    int j = 0;

    for (; j < 8; ++j) {
      if (board1[i][j] < 10 && (board2[i][j] == 0 || board2[i][j] > 10))
	return 0;
      if (board2[i][j] < 10 && (board1[i][j] == 0 || board1[i][j] > 10))
	return 0;
    }
  }
  return 1;
}

int check_options(int ac, char **av, options *op) {
  int i = 0;

  if (!op)
    return 1;
  op->end = 0;
  op->color = 0;
  op->stop_before_end = 0;
  if (ac < 2)
    return 1;
  for (; i < ac; ++i) {
    if (!strcmp(av[i], "-h") || !strcmp(av[i], "--help")) {
      printf("eight-queens' options:\n");
      printf(" -h, --help : display this help.\n");
      printf(" -s         : stop before ends, the execution will stop when 92 possibilities will be found.\n");
      printf(" -c         : activate color display.\n");
      return 0;
    } else if (av[i][0] == '-') {
      int x;

      for (x = 1; av[i][x]; ++x) {
	if (av[i][x] == 'c')
	  op->color = 1;
	else if (av[i][x] == 's')
	  op->stop_before_end = 1;
	else {
	  printf("Error: '%c': unknown option, please use -h to get the full options list.\n",
		 av[i][x]);
	  return 0;
	}
      }
    }
  }
  return 1;
}
