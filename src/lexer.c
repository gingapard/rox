#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "lexer.h"

static char* capture_token(Lexer* lexer, char* identifiers);
static uint8_t peek(Lexer* lexer);
static int isin(uint8_t ch, char* identifiers);
static void peek_until(char* str, Lexer* lexer, char* identifier);
static void forward(Lexer* lexer);
static void backward(Lexer* lexer);

Token next_token(Lexer* lexer) {
    Token token;

    if (lexer->position >= strlen(lexer->input)) {
        token.type = EOF_TYPE;
        return token;
    }

    char* token_content;
    char* identifiers = NULL;

    switch (lexer->ch) {
        case '\"':

            token.type = TEXT;
            token_content = capture_token(lexer, "\"");
            strcpy(token.content, token_content);
            free(token_content);
            break;

        // START/END TAG
        case '<':
            lexer->in_tag = 1;

            if (peek(lexer) == '/') {
                forward(lexer);
                token.type = TAG_END;
            } else {
                token.type = TAG_START;
            }

            identifiers = strdup(" >\"");
            token_content = capture_token(lexer, identifiers); 
            strcpy(token.content, token_content);
            free(token_content);

            if (lexer->ch == '>') {
                lexer->in_tag = 0;
            }
            else if (lexer->ch == '\"') {
                forward(lexer);
                token.type = ATTRIBUTE;
                token_content = capture_token(lexer, "\"");
                strcat(token.content, token_content);
                free(token_content);
            }

            break;

        case '=':

            token.type = EQUALS;
            strcpy(token.content, "=");
            break;

        default:
            
            if (lexer->in_tag == 1) {
                token.type = ATTRIBUTE;
                identifiers = strdup("=\"<");
            }
            else {
                token.type = OTHER;
                identifiers = strdup("<");
            }

            token_content = capture_token(lexer, identifiers);
            strcpy(token.content, token_content);
            free(token_content);
            backward(lexer);
    }

    free(identifiers);
    forward(lexer);
    return token;
}

static char* capture_token(Lexer* lexer, char* identifiers) {
    // finding token size
    size_t len = 0;
    while (isin(lexer->input[lexer->position - len], identifiers) == 0 && len < strlen(lexer->input)) {
        ++len;
    }

    char* str = (char*)malloc(len + 1);
    peek_until(str, lexer, identifiers);

    return str;
}


static uint8_t peek(Lexer* lexer) {
    if (lexer->position + 1 < strlen(lexer->input)) {
        return lexer->input[lexer->position + 1];
    } else {
        return '\0';  
    }
}

static void peek_until(char* str, Lexer* lexer, char* identifiers) {
    forward(lexer);
    size_t i = 0;
    while (isin(lexer->ch, identifiers) == 0 && i < strlen(lexer->input)) {
        str[i] = lexer->ch;
        forward(lexer);
        ++i;
    }

    str[i] = '\0';
}

static int isin(uint8_t ch, char* identifiers) {
    for (size_t i = 0; i < strlen(identifiers); ++i) {
        if (ch == identifiers[i]) return 1;
    }

    return 0;
}

static void forward(Lexer* lexer) {
    lexer->ch = lexer->input[++lexer->position];
}

static void backward(Lexer* lexer) {
    lexer->ch = lexer->input[--lexer->position];
}
