#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/lexer.h"

int main(int argc, char** argv) {

	char* input = "<div> </div>";
	
	// init lexer
	Lexer lexer;
	lexer.input = (char*)malloc(strlen(input) + 1);
	strncpy(lexer.input, input, strlen(input));
	lexer.input[strlen(input)] = '\0';

	lexer.position = 0;
	lexer.ch = lexer.input[lexer.position];
	// init lexer

	Token token;
	while ((token = next_token(&lexer)).type != EOF_TYPE) {
		printf("%s\n", token.content);
	}

	free(lexer.input);
	return 0;
}
