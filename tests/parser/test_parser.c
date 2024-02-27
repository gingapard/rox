#include <stdio.h>
#include <stdlib.h>

#include "../../src/ast.h"

/*
void test_get_keyword() {
    char str[] = "controls";
    AttributeType atr = get_attribute_type(str);
    printf("Attribute type: %d\n", atr);

}
*/

int main(void) {
	
    SyntaxTree st = parse("gnu");
    free_tree(st.root);

	return 0;
}
