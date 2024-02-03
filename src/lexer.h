#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>

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
	char content[256];
} Token;

typedef struct {
	char* input;
	uint32_t position;
	uint8_t in_tag;
	uint8_t ch;
} Lexer;

Token next_token(Lexer *lexer);


#endif
