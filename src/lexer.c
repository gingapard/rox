#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "lexer.h"

static char* capture_token(Lexer* lexer, uint8_t identifier);
uint8_t peek(Lexer* lexer);
static void peek_until(char* str, Lexer* lexer, uint8_t identifier);
static void forward(Lexer* lexer);

Token next_token(Lexer* lexer) {
    Token token;

    if (lexer->position >= strlen(lexer->input)) {
        token.type = EOF_TYPE;
        return token;
    }

    switch (lexer->ch) {

        case '\"':
			forward(lexer);
            token.type = TEXT;
			strcpy(token.content, capture_token(lexer, '\"'));
            break;

        // START/END TAG
        case '<':
            if (peek(lexer) == '/') {
                token.type = TAG_END;
            } else {
                token.type = TAG_START;
            }

			strcpy(token.content, capture_token(lexer, '\"'));
            break;

		default:

			token.type = OTHER;
			break;
    }

    forward(lexer);
    return token;
}

static char* capture_token(Lexer* lexer, uint8_t identifier) {
	size_t len = 0;
	while (lexer->input[lexer->position - len] != identifier && len < strlen(lexer->input)) {
		++len;
	}
	
	char* str = (char*)malloc(len + 1);
	peek_until(str, lexer, identifier);

	return str;
}


uint8_t peek(Lexer* lexer) {
    if (lexer->position + 1 < strlen(lexer->input)) {
        return lexer->input[lexer->position + 1];
    } else {
        return '\0';  
    }
}

static void peek_until(char* str, Lexer* lexer, uint8_t identifier) {
    forward(lexer);
    size_t i = 0;
    while (lexer->ch != identifier && lexer->position < strlen(lexer->input)) {
        str[i] = lexer->ch;
        forward(lexer);
        ++i;
    }

    forward(lexer);
    str[i] = '\0';
}

static void forward(Lexer* lexer) {
    ++lexer->position;
    lexer->ch = lexer->input[lexer->position];
}

