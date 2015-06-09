/*
 *
 * TICTACTOE -- human vs. computer
 *
 * Author: Ian Welch
 * Date: May 2015
 *
 * CHANGE LOG:
 *
 * 26.05 modified the user prompt to say (row,col) instead of x,y
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"

int check(TicTacToe* game);
void init_game(TicTacToe* game, int size);
int player_move(TicTacToe* game);
void computer_move(TicTacToe* game);
void print_game(TicTacToe game);
char tokenstr(int token);
void print_result(TicTacToe game);

int main(void) {
	int size = 0;
	TicTacToe game;

	setbuf(stdout, NULL);
	printf("This is the game of Tic Tac Toe.\n");
	printf("You will be playing against the computer.\n");

	//Get the size of the board from user
	printf("Enter in the size of the board:\n");
	scanf("%d", &size);

	printf("Size is %d ", size);

	init_game(&game, size); // initialise the board

	printf("The game board is %d by %d.\n", size, size);

	int done;
	do {
		print_game(game);
		do {
			done = player_move(&game);
		} while (!done); // loop until valid move
		if (check(&game) != FALSE)
			break; // was a winner or a draw
		computer_move(&game);
		if (check(&game) != FALSE)
			break; // was a winner or a draw
	} while (TRUE);

	print_result(game);
	print_game(game); /* show final positions */

	return 0;
}

/* Initialize the matrix. */
void init_game(TicTacToe* game, int size) {
	int i, j;

	//Create the game board and allocate memory for it
	int **board = (int **) malloc(sizeof(int *) * size); // our tic tac toe board

	for (i = 0; i < size; i++) {
		board[i] = (int *) malloc(sizeof(int *) * size);
	}

	// now initialise it
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			// set to empty of tokens
			board[i][j] = NONE;

	game->board = board;
	game->size = size;
}

/* Get a player's move. */
int player_move(TicTacToe* game) {
	int x, y;
	int valid;

	// changed the print statement so it is clear that it is row,col (Ian 26.05)
	printf("Enter coordinates (row,column) for your move: ");
	scanf("%d%*c%d", &x, &y);

	x--;
	y--;

	if (game->board[x][y] != NONE) {
		printf("Invalid move, try again.\n");
		valid = FALSE;
	} else {
		game->board[x][y] = HUMAN;
		valid = TRUE;
	}
	return valid;
}

/* Get a move from the computer. */
void computer_move(TicTacToe* game) {
	int done = FALSE;
	int i, j, cx, cy;
	cx = cy = -1;
	for (i = 0; i < game->size; i++) {
		for (j = 0; j < game->size; j++)
			if (game->board[i][j] == NONE) {
				cx = i;
				cy = j;
				break;
			}
		if (cx != -1) {
			game->board[cx][cy] = COMPUTER;
			break;
		}
	}
}

/* Map the board token ID to a character. */
char tokenstr(int t) {
	if (t == HUMAN)
		return 'X';
	else if (t == COMPUTER)
		return 'O';
	return '.';
}

/* Display the game board. */
void print_game(TicTacToe game) {
	int i, j;

	// read and print the board one character at a time
	for (i = 0; i < game.size; i++) {
		for (j = 0; j < game.size; j++) {
			printf("%d", game.board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* See if there is a winner. */
/* return true (0) if so otherwise false */
int check(TicTacToe* game) {
	int i, j;
	int count = 1;

	//Check rows
	for (i = 0; i < game->size; i++) {
		count = 1;
		for (j = 1; j < game->size; j++) {
			if (game->board[i][j] != NONE
					&& game->board[i][j] == game->board[i][j - 1]) {
				count++;
			}
		}
		if (count == game->size) {
			game->winner = game->board[i][j-1];
			return TRUE;
		}
	}

	//Check columns
	for (i = 0; i < game->size; i++) {
		count = 1;
		for (j = 1; j < game->size; j++) {
			if (game->board[j][i] != NONE
					&& game->board[j][i] == game->board[j - 1][i]) {
				count++;
			}
		}
		if (count == game->size) {
			game->winner = game->board[j-1][i];
			return TRUE;
		}
	}

	/* test diagonals */
	if (game->board[0][0] != NONE && game->board[0][0] == game->board[1][1]
			&& game->board[1][1] == game->board[2][2]) {
		game->winner = game->board[0][0];
		return TRUE;
	}

	if (game->board[0][2] != NONE && game->board[0][2] == game->board[1][1]
			&& game->board[1][1] == game->board[2][0]) {
		game->winner = game->board[0][2];
		return TRUE;
	}

	/* test if out of space on the game->board */
	count = 0;
	for (i = 0; i < game->size; i++) {
		for (j = 0; j < game->size; j++) {
			if (game->board[i][j] == NONE)
				count++;
		}
	}
	if (count == 0) {
		game->winner = DRAW;
		return TRUE;
	}

	// no-one and nor was there a draw
	return FALSE;
}

/* Print the result */
void print_result(TicTacToe game) {
	if (game.winner == HUMAN)
		printf("You won!\n");
	else if (game.winner == COMPUTER)
		printf("I won!!!!\n");
	else
		printf("Draw :(\n");
}
