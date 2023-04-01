#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// function names

void clearboard(char board[6][7]);
void printboard(char board[6][7]);
void readplayernames(char player1, char player2);
void playgame(char board[6][7], char player1, char player2, int movesplayed);
void showmenu();
int makemove(char board[6][7], int movesplayed, char player1, char player2);
int checkforwinner(char board[6][7]);

// main function

int main() {

  int endofprogram = 0;

  while (endofprogram == 0) {
    char board[6][7];
    char player1 = 'X';
    char player2 = 'O';
    int movesplayed = 0;

    showmenu();

    int choice;
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      clearboard(board);
      readplayernames(player1, player2);
      playgame(board, player1, player2, movesplayed);
      break;
    case 2:
      printf("goodbye!\n");
      endofprogram = 1;
      break;
    default:
      printf("Wrong choice, try again!\n");
    }
  }

  return 0;
}

// functions definitions

void clearboard(char board[6][7]) {
  int i;
  int j;

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 7; j++) {
      board[i][j] = ' ';
    }
  }
}

void printboard(char board[6][7]) {
  int i;
  int j;

  char line1[] = "  1   2   3   4   5   6   7  ";
  char lines[] = "|---|---|---|---|---|---|---|";
  system("cls");
  printf("%s\n", line1);
  printf("%s\n", lines);

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 7; j++) {
      printf("| %c ", board[i][j]);
    }
    printf("|\n");
    printf("%s\n", lines);
  }
}

void readplayernames(char player1, char player2) {
  player1 = 'X';
  player2 = 'O';
}

void playgame(char board[6][7], char player1, char player2, int movesplayed) {
  while (1) {
    printboard(board);

    if (makemove(board, movesplayed, player1, player2) == 1) {
      break;
    }

    movesplayed++;

    int result = checkforwinner(board);
    if (result != 0) {
      printboard(board);

      if (result == 1) {
        printf("\nX wins\n\n");
      }

      else if (result == 2) {
        printf("\nO wins\n\n");
      }

      break;
    }

    if (movesplayed == 42) {
      printboard(board);
      printf("\nTie!\n\n");
      break;
    }
  }
}

void showmenu() {
  printf("\n\n1.New Game\n");
  printf("2.Exit\n");
  printf("choose: ");
}

int makemove(char board[6][7], int movesplayed, char player1, char player2) {
  char sign = 'X';

  if (movesplayed % 2 == 1) {
    sign = 'O';
  }

  int column, i, j;

  while (1) {
    printf("\nplayer %c's turn(1/2/3/4/5/6/7): ", sign);

    scanf("%d", &column);

    if (column >= 0) {
      break;
    }
    printf("\nMove not allowed!\n");
  }

  if (column != 0) {
    for (i = 6; i >= 0; i--) {
      if (board[i][column - 1] == ' ') {
        board[i][column - 1] = sign;
        printf("\n\n");
        break;
      }
    }
  }

  else {
    return 1;
  }

  return 0;
}

int checkforwinner(char board[6][7]) {
  // check rows
  int i;
  int j;

  for(i  = 0; i < 6; i++) {
    for(j = 0; j < 7; j++) {
      if( (board[i][j] == board[i][j+1]) && (board[i][j] == board[i][j+2]) && (board[i][j] == board[i][j+3])) {
          if(board[i][j] == 'X') return 1;
          else if(board[i][j] == 'O') return 2;
      }
      else if( (board[i][j] == board[i+1][j]) && (board[i][j] == board[i+2][j]) && (board[i][j] == board[i+3][j])) {
          if(board[i][j] == 'X') return 1;
          else if(board[i][j] == 'O') return 2;
      }
      else if( (board[i][j] == board[i+1][j+1]) && (board[i][j] == board[i+2][j+2]) && (board[i][j] == board[i+3][j+3])) {
          if(board[i][j] == 'X') return 1;
          else if(board[i][j] == 'O') return 2;
      }
      else if( (board[i][j] == board[i+1][j-1]) && (board[i][j] == board[i+2][j-2]) && (board[i][j] == board[i+3][j-3])) {
            if(board[i][j] == 'X') return 1;
            else if(board[i][j] == 'O') return 2;
      }
      else if( (board[i][j] == board[i-1][j+1]) && (board[i][j] == board[i-2][j+2]) && (board[i][j] == board[i-3][j+3])) {
            if(board[i][j] == 'X') return 1;
            else if(board[i][j] == 'O') return 2;
      }
      else if( (board[i][j] == board[i-1][j-1]) && (board[i][j] == board[i-2][j-2]) && (board[i][j] == board[i-3][j-3])) {
            if(board[i][j] == 'X') return 1;
            else if(board[i][j] == 'O') return 2;
      }
    }
  }
  return 0;
}