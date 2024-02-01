#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "lexer.h"

uint8_t peek(Lexer* lexer);
static void peek_until(char* str, Lexer* lexer, uint8_t indentifier);
static void forward(Lexer* lexer);

Token next_token(Lexer* lexer) {
	Token token;

	if (lexer->position >= strlen(lexer->input)) {
		token.type = EOF_TYPE;
		return token;
	}
	
	switch (lexer->ch) {
		// TEXT
		case '\"':

			forward(lexer);
			size_t i = 0;
			while (lexer->ch != '\"') {
				token.content[i] = lexer->ch;
				forward(lexer);
				++i;
			}

			token.type = TEXT;
			forward(lexer);
			break;

		// START/END TAG
		case '<':

			forward(lexer);
			if (peek(lexer) == '/') token.type = TAG_END;
			else token.type = TAG_START;

			char str[32];
			peek_until(str, lexer, ' ');
			strcpy(token.content, str);
			token.type = TAG_END;
			break;
	}

	forward(lexer);

	return token;
}

uint8_t peek(Lexer* lexer) {
	return lexer->input[lexer->position + 1];
}


static void peek_until(char* str, Lexer* lexer, uint8_t indentifier) {
	forward(lexer);
	size_t i = 0;
	while (lexer->ch != indentifier) {
		str[i] = lexer->ch;
		forward(lexer);
		++i;		
	}

	str[i] = '\0';
}

static void forward(Lexer* lexer) {
	++lexer->position;
	lexer->ch = lexer->input[lexer->position];
}
