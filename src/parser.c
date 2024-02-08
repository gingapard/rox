#include <ctype.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "parser.h"
#include "utils.h"

/* temp return type as parser.h file not setup properly */
void parse(Token* tokens) {

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
    Tag* tags = (Tag*)malloc(sizeof(Tag*));
    if (tags == NULL) {
        fprintf(stderr, "Error during allocation");
        return;
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
