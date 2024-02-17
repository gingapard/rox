#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "lexer.h"
#include "utils.h"

#define ELMNT_KWORD_COUNT 115
#define ATRBT_KWORD_COUNT 160

const char* element_keywords[ELMNT_KWORD_COUNT] = {
    "a", "abbr", "address", "area", "article", "aside", "audio",
    "b", "base", "bdi", "bdo", "blockquote", "body", "br", "button", "canvas", "caption", "cite", "code", "col", "colgroup", "data", "datalist", "dd", "del", "details", "dfn", "dialog", "div", "dl", "dt", "em", "embed",
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
const char* attribute_keywords[ATRBT_KWORD_COUNT] = {
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

Token next_token(Lexer* lexer);
static void skip_whitespace(Lexer* lexer);
static char* capture_token(Lexer* lexer); 
static uint8_t bpeek(Lexer* lexer);
static uint8_t fpeek(Lexer* lexer);
static void forward(Lexer* lexer);
static void backward(Lexer* lexer);

Token next_token(Lexer* lexer) {
    Token token;
    char current_ch = lexer->ch;

    if (lexer->position >= strlen(lexer->input)) {
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
            break;
        case '\"':
            token.type = D_QUOTE;
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
        default:
            token.type = ALPHNUM;
    }
    
    if (token.type == ALPHNUM) {
        token.content = capture_token(lexer);
        token.type = lexer->last_type;
    }
    else {
        size_t content_length = 1; 
        token.content = (char*)malloc(content_length + 1); 
        if (token.content == NULL) {
            perror("could not allocate memory");
            exit(EXIT_FAILURE);
        }
        token.content[0] = current_ch; 
        token.content[1] = '\0'; 
    }

    lexer->last_type = token.type;
    forward(lexer);
    return token;
}

static void skip_whitespace(Lexer* lexer) {
    while (isspace(lexer->ch) && lexer->position < lexer->length)
        forward(lexer);
}

static char* capture_token(Lexer* lexer) {
    size_t len = 0;

    while (lexer->position + len < lexer->length && isalnum(lexer->input[lexer->position + len])) {
        ++len;
    }

    /* allocate the needed memory */
    char* str = (char*)malloc(len + 1);

    if (str == NULL) {
        perror("could not allocate memory");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < len; ++i) {
        str[i] = lexer->input[lexer->position + i];
    }

    str[len] = '\0';

    // Check element keywords
    // bugged stuff goin on here!
    /*
    for (size_t i = 0; i < ELMNT_KWORD_COUNT; ++i) {
        if (strcmp(str, element_keywords[i]) == 0) {
            lexer->last_type = ELEMENT_KWORD;
            return str;
        }
    }


    // Check attribute keywords
    for (size_t i = 0; i < ATRBT_KWORD_COUNT; ++i) {
        if (strcmp(str, attribute_keywords[i]) == 0) {
            lexer->last_type = ATTRIBUTE_KWORD;
            return str;
        }
    } 

    printf("Captured token: %s\n", str); 

    for (size_t i = 0; i < len; ++i) {
        forward(lexer);
    }
    */
    
    lexer->last_type = OTHER;
    lexer->position += len;
    lexer->ch = lexer->input[lexer->position];
    return str;
}

static uint8_t fpeek(Lexer* lexer) {
    if (lexer->position + 1 < lexer->length) {
        return lexer->input[lexer->position + 1];
    }

    return '\0';
}

static uint8_t bpeek(Lexer* lexer) {
    if (lexer->position > 0) {
        return lexer->input[lexer->position - 1];
    } 

    return '\0';
}

static void forward(Lexer* lexer) {
    if (lexer->ch != '\0' && lexer->position < lexer->length) {
        lexer->ch = lexer->input[++lexer->position];
    }
}

static void backward(Lexer* lexer) {
    if (lexer->position > 0 && lexer->ch != '\0') {
        lexer->ch = lexer->input[--lexer->position];
    }
}
