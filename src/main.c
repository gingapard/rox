#include <ncurses.h>

int main(void) {
	initscr();

	int ch;
	while ((ch = getch()) != 27) {}
	endwin();
	return 0;
}
