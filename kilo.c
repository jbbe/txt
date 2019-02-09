//A simple text editor
// Written by jbbe
// Based on kilo by <antirez>
#include <unistd.h>

int main() {
	char c;
	while (read(STDIN_FILENO, &c, 1) == 1);
	return 0;
}
