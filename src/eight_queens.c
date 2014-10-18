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

typedef struct solution {
  char solution[8][8];
  struct solution *next;
} solution;

void print_board(char board[8][8], int possibility) {
  int i;

  printf("Possibility number: %d\n", possibility);
  for (i = 0; i < 8; ++i) {
    int j;

    printf("------------------\n");
    for (j = 0; j < 8; ++j) {
      if (board[i][j] < 10) {
	printf("|%d", board[i][j]);
      } else {
      	printf("| ");
      }
    }
    printf("|\n");
  }
  printf("------------------\n");
}

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

int put_queen(int nb_queen, char board[8][8], int possibility, solution **s) {
  int posy = 0;
  int posx = 0;

  for (; posy < 8; ++posy) {
    for (posx = 0; posx < 8; ++posx) {
      if (!board[posy][posx]) {
	set_queen(nb_queen, board, posx, posy);
	if (nb_queen == 8) {
	  if (add_solution(board, s)) {
	    possibility += 1;
	    print_board(board, possibility);
	  }
	}
	else
	  possibility = put_queen(nb_queen + 1, board, possibility, s);
	unset_queen(nb_queen, board);
      }
    }
  }
  return possibility;
}

int main() {
  char board[8][8] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
  int i;
  solution *s = 0;

  printf("\nFor a total of %d possibilities\n", put_queen(1, board, 0, &s));
  while (s) {
    solution *tmp = s->next;

    free(s);
    s = tmp;
  }
  return 0;
}
