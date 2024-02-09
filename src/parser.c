#include <ctype.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "parser.h"
#include "utils.h"

static void free_tags(Tag* tags, size_t size);
static void pop_tag(Tag* tag, Tag* tags, size_t size);
static void push_tag(Tag* tag, Tag* tags, size_t size);

SyntaxTree* parse(char* path) {
    SyntaxTree* st;

    size_t token_count;
    Token* tokens = lex(path, &token_count);

    /* init parser, which will get tokens
    * provided by the lexer.
    */
    Parser parser;
    parser.input = tokens;
    parser.token = parser.input[0];
    parser.position = 0;
    

    /*storing the tags(parsed tokens).
     * Using allocation to heap as html documents
     * are not expected to be large 
     */
    size_t tag_count = 0;
    Tag* tags = (Tag*)malloc(sizeof(Tag*));
    if (tags == NULL) {
        fprintf(stderr, "Error during allocation");
        return st;
    }

    free(parser.input);
    free(tokens);
    free_tags(tags, tag_count);
    return st;
}

static void free_tags(Tag* tags, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (tags[i].attributes_count != 0) {
            for (size_t j = 0; j < tags[i].attributes_count; ++j) {
                free(tags[i].attributes[j].content); 
            }
            free(tags[i].attributes); 
        }
    }
}

static void push_tag(Tag* tag, Tag* tags, size_t size) {
    tags = (Tag*)realloc(tags, (size + 1) * sizeof(Tag));
    if (tags == NULL)
        return;

    tags[size] = *tag;
}

static void pop_tag(Tag* tag, Tag* tags, size_t size) {
    if (size > 0) {
        tags = (Tag*)realloc(tags, (size - 1) * sizeof(Tag));
        if (tags == NULL) 
            return;
    }   
}
