#include <ctype.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "parser.h"
#include "utils.h"

const char* element_keywords[115] = {
    "a", "abbr", "address", "area", "article", "aside", "audio",
    "b", "base", "bdi", "bdo", "blockquote", "body", "br", "button",
    "canvas", "caption", "cite", "code", "col", "colgroup",
    "data", "datalist", "dd", "del", "details", "dfn", "dialog", "div", "dl", "dt",
    "em", "embed",
    "fieldset", "figcaption", "figure", "footer", "form",
    "h1", "h2", "h3", "h4", "h5", "h6", "head", "header", "hr", "html",
    "i", "iframe", "img", "input", "ins",
    "kbd", "keygen",
    "label", "legend", "li", "link",
    "main", "map", "mark", "menu", "menuitem", "meta", "meter",
    "nav", "noscript",
    "object", "ol", "optgroup", "option", "output",
    "p", "param", "pre", "progress",
    "q",
    "rp", "rt", "ruby",
    "s", "samp", "script", "section", "select", "small", "source", "span", "strong", "style", "sub", "summary", "sup",
    "table", "tbody", "td", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "track",
    "u", "ul",
    "var", "video",
    "wbr"
};

const char* attribute_keywords[160] = {
    "accept", "accept-charset", "accesskey", "action", "align", "alt", "async",
    "autocomplete", "autofocus", "autoplay",
    "bgcolor", "border",
    "challenge", "charset", "checked", "cite", "class", "code", "codebase", "color", "cols", "colspan", "content", "contenteditable", "contextmenu", "controls", "coords",
    "data", "data-*", "datetime", "default", "defer", "dir", "dirname", "disabled", "download", "draggable",
    "enctype",
    "for", "form", "formaction", "headers", "height", "hidden", "high", "href", "hreflang", "http-equiv",
    "icon", "id", "ismap",
    "keytype", "kind",
    "label", "lang", "list", "loop", "low",
    "manifest", "max", "maxlength", "media", "method", "min", "multiple", "muted",
    "name", "novalidate",
    "open", "optimum",
    "pattern", "ping", "placeholder", "poster", "preload",
    "radiogroup", "readonly", "rel", "required", "reversed", "rows", "rowspan",
    "sandbox", "scope", "scoped", "seamless", "selected", "shape", "size", "sizes", "span", "spellcheck", "src", "srcdoc", "srclang", "srcset", "start", "step", "style", "subject", "summary",
    "tabindex", "target", "title", "type",
    "usemap",
    "value"
};

static void free_tokens(Token* tokens, size_t count);
static void free_elements(Element* elements, size_t size);
static void pop_element(Element* element, Element** elements, size_t* size);
static void push_element(Element* element, Element** elements, size_t* size);

SyntaxTree* parse(char* path) {
    SyntaxTree* st = (SyntaxTree*)malloc(sizeof(SyntaxTree));

    size_t token_count = 0;
    Token* tokens = lex(path, get_file_size(path), &token_count);

    /* init parser, which will get tokens
    * provided by the lexer.
    */

    Parser parser;
    parser.tokens = tokens;
    parser.token = parser.tokens[0];
    parser.position = 0;

    /*storing the elements(parsed tokens).
     * Using allocation to heap as html documents
     * are not expected to be large 
     */

    size_t element_count = 0;
    Element* elements = (Element*)malloc(sizeof(Element));
    if (elements == NULL) {
        fprintf(stderr, "Error during allocation");
        return st;
    }

    /* read & parse tokens */

    
    

    free_tokens(parser.tokens, token_count);
    free(parser.tokens);
    free_elements(elements, element_count);
    return st;
}

static void free_tokens(Token* tokens, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        free(tokens[i].content);
    }
}

static void free_elements(Element* elements, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (elements[i].attributes_count != 0) {
            for (size_t j = 0; j < elements[i].attributes_count; ++j) {
                free(elements[i].attributes[j].content); 
            }
            free(elements[i].attributes);
        }
    }
}

static void push_element(Element* element, Element** elements, size_t* size) {
    Element* temp = (Element*)realloc(*elements, (*size + 1) * sizeof(Element));
    if (temp == NULL) {
        fprintf(stderr, "Error during allocation");
        return;
    }

    *elements = temp;
    (*elements)[*size] = *element;
    (*size)++;
}

static void pop_element(Element* element, Element** elements, size_t* size) {
    if (*size > 0) {
        Element* temp = (Element*)realloc(*elements, (*size - 1) * sizeof(Element));
        if (temp == NULL) {
            fprintf(stderr, "Error during allocation");
            return;
        }

        *elements = temp;
        (*size)--;
    }
}
