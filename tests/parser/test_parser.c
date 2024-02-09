#include <stdio.h>
#include <stdlib.h>

#include "../../src/parser.h"

int main(void) {
	
	SyntaxTree* st = parse("gnu.html");

	free(st);
	return 0;
}
