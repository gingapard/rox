#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "lexer.h"
#include "utils.h"

static Token next_token(Lexer* lexer);
static void skip_whitespace(Lexer* lexer);
static char* capture_token(Lexer* lexer); 
static uint8_t fpeek(Lexer* lexer);
static void forward(Lexer* lexer);
static void backward(Lexer* lexer);

Token* lex(char* path, size_t* len) {
    FILE* fp = fopen(path, "r");
    if (fp == NULL)
        return NULL;

    long file_size = get_file_size(path);
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(fp);
        perror("could not allocate memory");
        return NULL;
    }

    size_t read_size = fread(buffer, 1, file_size, fp); 

    /* Making sure the read size is the same as 
     * the size of the file 
     */
    if (read_size != file_size) {
        fclose(fp);
        free(buffer);
        perror("could not read file");
        return NULL;
    }

    buffer[file_size] = '\0';

    // initiate lexer
    Lexer lexer;
    lexer.input = (char*)malloc(strlen(buffer) + 1);
    strcpy(lexer.input, buffer);
    lexer.position = 0;
    lexer.ch = lexer.input[lexer.position];

    free(buffer);

    /* creating pointer to the stored tokens and keeping
     * track of the size 
     */
    Token* tokens = NULL;
    Token token;

    while ((token = next_token(&lexer)).type != EOF_TYPE) {
        tokens = (Token*)realloc(tokens, sizeof(Token) * (*len + 1)); 
        tokens[*len] = token; 
        ++(*len);
    }

    fclose(fp);
    free(lexer.input); 
    return tokens;
}

Token next_token(Lexer* lexer) {
    Token token;
    char current_ch = lexer->ch;

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
        case '{':
            token.type = L_BRACKET;
            break;
        case '}':
            token.type = R_BRACKET;
            break;
        case '[':
            token.type = L_SQ_BRACKET;
            break;  
        case ']':
            token.type = R_SQ_BRACKET;
            break;  
        case '(':
            token.type = R_PARENT;
            break;
        case ')':
            token.type = L_PARENT;
            break;
        case '!':
            token.type = BANG;
            break;
        case '\'':
            token.type = S_QUOTE;
            token.content = capture_token(lexer);
            break;
        case '\"':
            token.type = D_QUOTE;
            token.content = capture_token(lexer);
            break;
        case ':':
            token.type = COLON;
            break;
        case ';':
            token.type = SEMI_COLON;
            break;
        case ',':
            token.type = COMMA;
            break;
        case '=':
            token.type = EQUALS;
            break;
        case '%':
            token.type = MOD;
            break;
        case '/':
            token.type = F_SLASH;
            break;
        case '#':
            token.type = HASH;
            break;
        case '.':
            token.type = DOT;
            break;
        case '@':
            token.type = AT;
            break;
        case '&':
            token.type = AND;
            break;
        case '\n':
            skip_whitespace(lexer);
            return next_token(lexer);
        default:
            token.type = KEYWORD;
            token.content = capture_token(lexer);
            return token;
    }
    
    /* allocating lexer->ch to a string and assigning token.content
     * unless lexer->ch is ' or "  
     */
    if (current_ch != '\"' && current_ch != '\'') {
        char token_content[2] = {lexer->ch, '\0'};
        token.content = str_x_dup(token_content);
    }

    forward(lexer);
    return token;
}

static void skip_whitespace(Lexer* lexer) {
    while (isspace(lexer->ch) && lexer->position < strlen(lexer->input))
        forward(lexer);
}

/* The thought for this function is to find if a collection of characters
 * are valid. (This is for use outside of "" or '')
 */
static uint8_t is_valid(uint8_t ch) {
    if (is_in(ch, "<>\"\' "))
        return 0;
    return 1;
}

static char* capture_token(Lexer* lexer) {
    size_t len = 0;

    /* finding how much memory needs to be allocted as 
     * token.content is heap allocated
     */
    if (lexer->ch == '\"' || lexer->ch == '\'') {
        /* Allocating two extra bytes for 
         * start and end quote 
         */
        ++len;
        while (lexer->input[lexer->position + len] != lexer->ch && lexer->input[lexer->position + len] != '\0')
            ++len;
        ++len;
    }
    else {
        while (is_valid(lexer->input[lexer->position + len]) && lexer->input[lexer->position + len] != '\0')
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

// frontpeek
static uint8_t fpeek(Lexer* lexer) {
    return lexer->input[lexer->position + 1];
}

// backpeek
static uint8_t bpeek(Lexer* lexer) {
    return lexer->input[lexer->position - 1];
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
