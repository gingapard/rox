#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../../src/lexer.h"
#include "../../src/utils.h"

void test_lex() {

    char* input = xfread_full("gnu");
    size_t token_count = 0;
    Token* tokens = (Token*)lex(input, strlen(input), &token_count);

    int i = 0;
    while (tokens[i].type != EOF_TYPE) {
        printf("%s\n", tokens[i].content);
        ++i;
    }

    free_tokens(tokens, token_count);
    free(tokens);    
    free(input);
}

void test_next_token() {

    char* input = "=<= divclass=\"test\">TestElement</div>";

    // initiate lexer
    Lexer lexer;
    lexer.input = (char*)malloc(strlen(input) + 1);
    strcpy(lexer.input, input);
    lexer.position = 0;
    lexer.length = strlen(lexer.input);
    lexer.ch = lexer.input[lexer.position];

    /* creating pointer to the stored tokens and keeping
     * track of the size 
     */
    Token token;
    while ((token = next_token(&lexer)).type != EOF_TYPE) {
        printf("%d: %s\n", token.type, token.content);
        free(token.content);
    }

    free(lexer.input); 
}

int main(void) {
    test_lex();
    // test_next_token();
    return 0;
}
