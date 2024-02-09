#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/lexer.h"
#include "../../src/utils.h"

int main(void) {

	char* input = "<div class=\"testtext\">Hello</div> JOIN</a>awdawd<a>";
	char* path = "gnu.html";
	
	
	size_t len;
	Token* tokens = lex(path, &len);
	for (int i = 0; i < len; ++i) {
		printf("%d: %s\n", tokens[i].type, tokens[i].content);
	}

	free(tokens);
	return 0;
}
