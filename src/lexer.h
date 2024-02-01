#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>

enum TokenType;

typedef struct {
	char* input;
	size_t position;
	uint8_t ch;
} Lexer;

enum TokenType {
	TAG_START,
	TAG_END,
	TEXT,
	ATTRIBUTE,
	EQUALS,
	OTHER,
	EOF_TYPE,
};

typedef struct {
	enum TokenType type;
	char content[16];
} Token;

Token next_token(Lexer *lexer);


#endif
