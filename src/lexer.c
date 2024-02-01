#include <stdint.h>
#include <string.h>

#include "lexer.h"

uint8_t peek(Lexer* lexer);
void forward(Lexer* lexer);

Token next_token(Lexer* lexer) {
	Token token;

	if (lexer->position >= strlen(lexer->input)) {
		token.type = EOF_TYPE;
		return token;
	}
	
	// text token
	if (lexer->ch == '\"') {
		forward(lexer);
		size_t i = 0;
		while (lexer->ch != '\"') {
			token.content[i] = lexer->ch;
			forward(lexer);
			++i;
		}

		token.type = TEXT;
		forward(lexer);
	}

	// move one forward
	forward(lexer);

	return token;
}

uint8_t peek(Lexer* lexer) {
	return lexer->input[lexer->position + 1];
}

void forward(Lexer* lexer) {
	++lexer->position;
	lexer->ch = lexer->input[lexer->position];
}
