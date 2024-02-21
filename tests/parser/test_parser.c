#include <stdio.h>
#include <stdlib.h>

#include "../../src/parser.h"

int main(void) {
	
    SyntaxTree st = parse("gnu");
    free_tree(st.root);

	return 0;
}
