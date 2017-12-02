#include <stdio.h>
#include <string.h>
#include "McodeMod.h"

int main(void) {

	char *stringParse = "Test String";
	int size = strlen(stringParse);
	int i = 0;

	while (stringParse[i] != '\0' ) {

		char *letter = mcodestring(stringParse[i]);

		printf("Vale of letter:%s  in i: %d\n", letter, i);

		i++;
	}

	//for (i=0; i<size; i++) {}


	return 0;
}