#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/lexer.h"
#include "../../src/utils.h"

void test_next_token() {
    char* path = "gnu";
    FILE* fp = fopen(path, "r");
    if (fp == NULL)
        return;

    long file_size = get_file_size(path);
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(fp);
        perror("could not allocate memory");
        return;
    }

    size_t read_size = fread(buffer, 1, file_size, fp); 

    /* Making sure the read size is the same as 
     * the size of the file 
     */
    if (read_size != file_size) {
        fclose(fp);
        free(buffer);
        perror("could not read file");
        return;
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
    Token token;
    while ((token = next_token(&lexer)).type != EOF_TYPE) {
        printf("%d: %s\n", token.type, token.content);
        free(token.content);
    }

    fclose(fp);
    free(lexer.input); 
}

void test_lex() {
    size_t token_count;
    Token* tokens = lex("gnu.html", &token_count);

    for (int i = 0; i < token_count; ++i) {
        printf("%s\n", tokens[i].content);
    }
    
    free(tokens);
}


int main(void) {
    //test_lex();
    test_next_token();

    return 0;
}
