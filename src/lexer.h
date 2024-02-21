#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>

enum TokenType {
    LITERAL,
    ELMNT,
    ATRBT,
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
    ADD,
    ASTERISK,
    SUBTRACT,
	F_SLASH,
	HASH,
	DOT,
	AT,
	AND,
	NEW_LINE,
    OTHER,
	EOF_TYPE,
};

typedef struct {
	enum TokenType type;
	char* content;
} Token;

typedef struct {
	char* input;
    enum TokenType last_type;
	uint32_t position;
    size_t length;
	uint8_t ch;
} Lexer;

Token* lex(char* path, intmax_t file_size, size_t* len);
Token next_token(Lexer* lexer);
void free_tokens(Token* tokens, size_t count);

#endif
