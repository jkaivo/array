#define _POSIX_C_SOURCE 2
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define CHARS_PER_LINE 8

int make_array(const char *path, int include_size)
{
	FILE *f = stdin;

	if (path && strcmp(path, "-") != 0) {
		f = fopen(path, "rb");
		if (f == NULL) {
			perror(path);
			return 1;
		}
	} else {
		path = "stdin";
	}

	size_t plen = strlen(path);
	char id[plen + 1];
	for (size_t i = 0; i < plen; i++) {
		id[i] = isalnum(path[i]) ? path[i] : '_';
	}
	id[plen] = '\0';

	printf("unsigned char %s[] = {\n", id);

	int c;
	int i = 0;
	while ((c = fgetc(f)) != EOF) {
		if (i == 0) {
			putchar('\t');
		}
		printf("0x%02hhx, ", c);
		if (++i == CHARS_PER_LINE) {
			putchar('\n');
			i = 0;
		}
	}

	if (i != 0) {
		putchar('\n');
	}

	printf("};\n");

	if (include_size) {
		printf("size_t %s_size = sizeof(%s);\n", id, id);
	}

	if (f != stdin) {
		fclose(f);
	}

	return 0;
}


int main(int argc, char *argv[])
{
	int include_size = 0;
	int c;

	while ((c = getopt(argc, argv, "s")) != -1) {
		switch (c) {
		case 's':
			include_size = 1;
			break;

		default:
			return 1;
		}
	}

	int ret = 0;
	do {
		ret |= make_array(argv[optind++], include_size);
	} while (optind < argc);

	return ret;
}
