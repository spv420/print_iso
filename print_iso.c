#include <stdio.h>
#include <stdlib.h>
#include "iso_font.c"

/* based on https://github.com/Billy-Ellis/framebuffer_write */
char* generate_char(char c, char white, char black) {
	char* write_to = malloc(16 * 9);

	for (int y = 0; y < 15; y += 1){
		int value = iso_font[c * 16 + y];

		for (int x = 0; x < 8; x++){
			if ((value & (1 << (x)))) {
				write_to[(y * 9) + x] = white;
			}

			else {
				write_to[(y * 9) + x] = black;
			}
		}
		write_to[(y * 9) + 8] = '\n';
	}
	return write_to;
}

int main(int argc, char* argv[]) {
	char gen_char;
	char fg;
	char bg;
	if (argc < 2) {
		printf("usage: %s [character to generate] (character to use, default is the character itself) (background character, default is space)\n", argv[0]);
		return -1;
	}
	else if (argc == 2) {
		gen_char = argv[1][0];
		fg = gen_char;
		bg = ' ';
	}
	else if (argc == 3) {
		gen_char = argv[1][0];
		fg = argv[2][0];
		bg = ' ';
	}
	else if (argc >= 4) {
		gen_char = argv[1][0];
		fg = argv[2][0];
		bg = argv[3][0];
	};
	char* s = generate_char(gen_char, fg, bg);
	printf("%s", s);
	free(s);
	return 0;
}
