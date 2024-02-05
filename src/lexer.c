#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "utils.h"

static void skip_whitespace(Lexer* lexer);
static char* capture_token(Lexer* lexer); 
static uint8_t peek(Lexer* lexer);
static void forward(Lexer* lexer);
static void backward(Lexer* lexer);

Token next_token(Lexer* lexer) {
    Token token;

    if (lexer->position >= strlen(lexer->input) && lexer->ch == '\0') {
        token.type = EOF_TYPE;
        token.content = NULL;
        return token;
    }
    
    skip_whitespace(lexer);

    switch (lexer->ch) {
        case '<':
            token.type = L_ANGLE;
            break;
        case '>':
            token.type = R_ANGLE;
            break; 
        case '\"':
            token.type = QUOTE;
            token.content = capture_token(lexer);
            break;
        case '=':
            token.type = EQUALS;
            break;
        case '/':
            token.type = F_SLASH;
            break;
        default:
            token.type = KEYWORD;
            token.content = capture_token(lexer);
            return token;
    }
    
    char token_content[2] = {lexer->ch, '\0'};
    token.content = str_x_dup(token_content);
    forward(lexer);
    return token;
}

static void skip_whitespace(Lexer* lexer) {
    while (lexer->ch == ' ' && lexer->position <= strlen(lexer->input)) 
        forward(lexer);
}

static uint8_t is_valid(uint8_t ch) {
    if (isalpha(ch) || isdigit(ch) || ch == '_' || ch == '-') 
        return 1;
    return 0;
}

static char* capture_token(Lexer* lexer) {
    size_t len = 0;


    if (lexer->ch != '\"') {
        while (is_valid(lexer->input[lexer->position + len])) ++len; 
    }
    else {
        ++len;
        while (lexer->input[lexer->position + len] != '\"') ++len;
        ++len;
    }
    
    char* str = (char*)malloc(len + 1);
    for (int i = 0; i < len; ++i) {
        str[i] = lexer->input[lexer->position + i];
    }

    str[len] = '\0';

    for (int i = 0; i < len; ++i) {
        forward(lexer);
    }

    return str;
}

static uint8_t peek(Lexer* lexer) {
    return lexer->input[lexer->position + 1];
}

static void forward(Lexer* lexer) {
    if (lexer->ch != '\0' && lexer->position < strlen(lexer->input)) {
        lexer->ch = lexer->input[++lexer->position];
    }
}

static void backward(Lexer* lexer) {
    if (lexer->position > 0 && lexer->ch != '\0') {
        lexer->ch = lexer->input[--lexer->position];
    }
}
