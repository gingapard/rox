#include <ctype.h>
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
    Tag* tags = (Tag*)malloc(sizeof(Tag));



}

static void push_tag(Tag* tag, Tag* head) {
    
}

static void pop_tag(Tag* tag, Tag* head) {

}
