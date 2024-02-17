#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>

enum TokenType {
    ELEMENT_KWORD,
    ATTRIBUTE_KWORD,
    TEXT,
    OTHER,
    ALPHNUM,
	L_ANGLE,
	R_ANGLE,
	L_BRACKET,
	R_BRACKET,
	L_SQ_BRACKET,
	R_SQ_BRACKET,
	L_PARENT,
	R_PARENT,
	BANG,
	D_QUOTE,
	S_QUOTE,
	COMMA,
	COLON,
	SEMI_COLON,
	EQUALS,
	MOD,
	F_SLASH,
	HASH,
	DOT,
	AT,
	AND,
	NEW_LINE,
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

extern const char* element_keywords[];
extern const char* attribute_keywords[];

Token* lex(char* str, size_t* len);
Token next_token(Lexer* lexer);

#endif
