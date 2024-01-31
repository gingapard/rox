#include <stdint.h>
#include <string.h>

#include "lexer.h"

Token next_token(Lexer lexer) {
	Token token;
	
	return token;
}

uint8_t peek(Lexer lexer) {
	return lexer.input[lexer.position + 1];
}
