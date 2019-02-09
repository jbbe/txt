/*** 	A simple text editor
	Written by jbbe
	Based on kilo by <antirez>


/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

/*** data ***/

struct termios orig_termios;

/*** terminal ***/

void die(const char *s) {
	perror(s);
	exit(1);
}

void disableRawMode() {
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) 
			die("tcsetattr");
}

void enableRawMode() {
	if(tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcsetattr");
	atexit(disableRawMode);

	struct termios raw = orig_termios;
	// Flips bitflag for 00000000000000000000000000001000
	raw.c_iflag &= ~(ICRNL | IXON | INPCK | ISTRIP | BRKINT);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/*** init ***/

int main() {
	enableRawMode();

//	if(argc > 0) { file_in = fopen(*argv[0]); }

	while (1) {
		char c = '\0';
		if(read(STDIN_FILENO, &c, 1) == -1)  die("tcsetattr");
		if (iscntrl(c)) {
			//if(c == 13) {
				//printf("\n");
			//} else {
			printf("%d\r\n", c);
			//k}
		} else {
			printf("'%c'\r\n", c);
		}
		if (c == 'q') break;
	}
	return 0;
}
