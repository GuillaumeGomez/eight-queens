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

#include <stdlib.h>
#include "list.h"

void copy_solution(solution *n, char board[8][8]) {
  int i;

  if (!n)
    return;
  for (i = 0; i < 8; ++i) {
    int j;

    for (j = 0; j < 8; ++j) {
      n->solution[i][j] = board[i][j];
    }
  }
}

int add_solution(char board[8][8], solution **head) {
  if (*head) {
    solution *n;
    solution *tmp = *head;

    while (tmp) {
      if (compare_boards(board, tmp->solution))
	return 0;
      tmp = tmp->next;
    }
    if (!(n = malloc(sizeof(*n)))) {
      return 0;
    }
    tmp = *head;
    while (tmp->next)
      tmp = tmp->next;
    tmp-> next = n;
    n->next = 0;
    copy_solution(n, board);
    return 1;
  }
  if (!(*head = malloc(sizeof(solution))))
    return 0;
  (*head)->next = 0;
  copy_solution(*head, board);
  return 1;
}

void clear_list(solution **s) {
  while (*s) {
    solution *tmp = (*s)->next;

    free(*s);
    *s = tmp;
  }
}
