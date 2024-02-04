#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>

enum TokenType {
	R_ANGLE,
	L_ANGLE,
	KEYWORD,
	QUOTE,
	EQUALS,
	F_SLASH,
	EOF_TYPE,
};

typedef struct {
	enum TokenType type;
	char* content;
} Token;

typedef struct {
	char* input;
	uint32_t position;
	uint8_t ch;
} Lexer;

Token next_token(Lexer *lexer);


#endif
