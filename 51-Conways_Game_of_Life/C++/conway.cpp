#include <stdio.h>
#include <curses.h>
#include <cstring>
#include <ctype.h>

using namespace std;

template <size_t arr_x, size_t arr_y>
int neighborCheck(int x, int y, char (&board)[arr_x][arr_y][2]){
	int count = 0;
	if(board[x-1][y][0] == 1) count++;
	if(board[x-1][y-1][0] == 1) count++;
	if(board[x][y-1][0] == 1) count++;
	if(board[x+1][y-1][0] == 1) count++;
	if(board[x+1][y][0] == 1) count++;
	if(board[x+1][y+1][0] == 1) count++;
	if(board[x][y+1][0] == 1) count++;
	if(board[x-1][y+1][0] == 1) count++;

	return count;
}

template <size_t arr_x, size_t arr_y>
void fillArray(char (&board)[arr_x][arr_y][2], int layer){
	for(size_t i = 0; i < arr_x; i++){
		for(size_t j = 0; j < arr_y; j++){
			board[i][j][layer] = 0;
		}
	}
}

int main(){
	int ch;
	int x, y;
	int doSession = 1;
	char board[64][64][2] = {0};


	initscr();					// Initialize curses.
	start_color();
	raw();						// Disable line buffering.
	nonl();
	keypad(stdscr, TRUE);		// Enable keypad.
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);


	noecho();					// Don't echo() when getch() is called.

	int row, col;
	getmaxyx(stdscr, row, col);

	int menuPos = 0;

	mainMenu:

	fillArray(board, 0);
	fillArray(board, 1);

	clear();
	curs_set(0);
	attron(COLOR_PAIR(2));
	mvprintw(row/2-7, (col - 21) / 2, "CONWAY'S GAME OF LIFE");
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(1));
	mvprintw(row/2 - 3, (col-11) / 2, "Start Session");
	attroff(COLOR_PAIR(1));
	mvprintw(row/2, (col-4) / 2, "Exit");


	while(true){
		getmaxyx(stdscr, row, col);
		ch = getch();

		if(ch == KEY_UP) menuPos++;
		else if(ch == KEY_DOWN) menuPos--;
		else if(ch == '\r'){
			if(~menuPos & 1){
				doSession = 1;
				clear();
				break;
			} else if(menuPos & 1){
				doSession = 0;
				break;
			}
		}


		if(~menuPos & 1){
			attron(COLOR_PAIR(2));
			mvprintw(row/2-7, (col - 21) / 2, "CONWAY'S GAME OF LIFE");
			attroff(COLOR_PAIR(2));
			attron(COLOR_PAIR(1));
			mvprintw(row/2 - 3, (col-11) / 2, "START SESSION");
			attroff(COLOR_PAIR(1));
			mvprintw(row/2, (col-4) / 2, "EXIT");
		} else if(menuPos & 1) {
			attron(COLOR_PAIR(2));
			mvprintw(row/2-7, (col - 21) / 2, "CONWAY'S GAME OF LIFE");
			attroff(COLOR_PAIR(2));
			mvprintw(row/2 - 3, (col-11) / 2, "START SESSION");
			attron(COLOR_PAIR(1));
			mvprintw(row/2, (col-4) / 2, "EXIT");
			attroff(COLOR_PAIR(1));
		}
	}

	mousemask(BUTTON1_CLICKED | BUTTON3_CLICKED, NULL);

	while(doSession){
		while(true){
			ch = getch();
			MEVENT event;

			if(ch == KEY_END) goto end;
			if(ch == '\r') break;
			if(ch == KEY_MOUSE){
				if(nc_getmouse(&event) == OK){
					if(event.x < 64 || event.y < 64){
						if(event.bstate & BUTTON1_CLICKED){
							board[event.x][event.y][0] = 1;
							mvaddch(event.y, event.x, '#');
							refresh();
						} else if(event.bstate & BUTTON3_CLICKED){
							board[event.x][event.y][0] = 0;
							mvaddch(event.y, event.x, ' ');
							refresh();
						}
					}
				}
			}
		}


		while(true){
			for(int i = 0; i < 64; i++){
				for(int j = 0; j < 64; j++){
					int neighbors = neighborCheck(i, j, board);
					if(neighbors < 2 || neighbors > 3) board[i][j][1] = 0;
					if(neighbors == 3) board[i][j][1] = 1;
					if(neighbors == 2) board[i][j][1] = board[i][j][0];
				}
			}

			for(int i = 0; i < 64; i++){
				for (int j = 0; j < 64; j++){
					board[i][j][0] = board[i][j][1];
					board[i][j][1] = 0;

					if(board[i][j][0] == 1) mvaddch(j, i, '#');
					if(board[i][j][0] == 0) mvaddch(j, i, ' ');
				}
			}

			int ch2 = getch();
			if(ch2 == KEY_END) goto end;
			if(ch2 == KEY_HOME) goto mainMenu;
		}
	}

	end:

	curs_set(1);

	clear();
	refresh();
	endwin();
	return 0;
}

