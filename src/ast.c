#include <ctype.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ast.h"
#include "lexer.h"
#include "utils.h"

const char* element_keywords[111] = {
    "UNKNOWN_ELEMENT",
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

const char* attribute_keywords[108] = {
    "UNKNOWN_ATTRIBUTE",
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

static void _ignore_comments(Parser* parser);
static ElementType get_element_type(char* literal);
static AttributeType get_attribute_type(char* literal);
static Token* _peek(Parser* parser);
static void _forward(Parser* parser);
static void _free_element(Element element);
static Element _init_element(ElementType type, size_t attributes_count, char* content);
static SyntaxTreeNode* _init_node(SyntaxTreeNode* parent, ElementType type, size_t attributes_count, char* content);
static void _push_node(SyntaxTreeNode* parent, SyntaxTreeNode* node);

SyntaxTree parse(char* path) {
    SyntaxTree st;

    char* input = xfread_full(path);
    size_t token_count = 0;

    /* Note to Myself:
     * DONT FREE tokens!
     */
    Token* tokens = lex(input, get_file_size(path), &token_count);
    free(input);

    /* print token content test
    for (int i = 0; i < token_count; ++i) {
        printf("%s\n", tokens[i].content);
    }

    init parser, which will get tokens
     provided by the lexer.
    */

    Parser* parser = (Parser*)malloc(sizeof(Parser));
    if (parser == NULL) {
        fprintf(stderr, "could not allocate memory\n");
        exit (1);
    }

    parser->tokens = tokens;
    parser->token = parser->tokens[0];
    parser->token_count = token_count;
    parser->position = 0;
    parser->in_tag = 0;
    
    /* allocate root node */
    st.root = (SyntaxTreeNode*)malloc(sizeof(SyntaxTreeNode));
    if (st.root == NULL) {
        fprintf(stderr, "Error allocating root node\n");
        free_tokens(parser->tokens, token_count);
        free(parser->tokens);
        return st;
    }


    /*              - child
     *      - child - child
     * root - child - child
     *      - child - child
     *              - child
     */
    
    /* init root node */
    st.root->parent = NULL;
    st.root->element = _init_element(UNKNOWN_ELEMENT, 0, NULL);
    st.root->children = NULL;
    st.root->children_count = 0;

    /* parse */
    /* note: use stack data structure for parsing */
    /* Root node will be UNKNOWN_TAG.
     * Stack will keep track of where we are currently.
     * Not sure if this will be the final solution.
     *
     * Example (1): [html, div, p] stack_ptr = 2;
     * <html>
     *      <div>
     *          <p>Hello <- current position</p>
     *      </div>
     * </html>
     * 
     * Example (2): [html] stack_ptr = 0;
     * <html>
     *      <div>
     *          <p>Hello</p>
     *      </div>
     *      # <- current position
     * </html>
     */

    // Stack for parsing tokens
    SyntaxTreeNode* current_parent = st.root;
    StackItem stack[100];
    int top = -1;

    // note: remember handle selfclosing tags different
    while (parser->position < parser->token_count && parser->token.type != EOF_TYPE) {
        _ignore_comments(parser);

        switch (parser->token.type) {
            case L_ANGLE:
                if (_peek(parser)->type == LITERAL) {
                    /* TODO: check type of element,
                     * collect element attributes && check type,
                     * collect element content,
                     * init node (&& element),
                     * push node,
                     * push to stack,
                     */

                    // Move to to-be-defined parse_element function
                    // _peek and get element_type
                    ElementType type = get_element_type(_peek(parser)->content);
                    size_t attributes_count = 0;
                    /* 1. PARSE element attributes,
                     * NB: Call get_attribute_type,
                     * 2. collect content to string,
                     */
                    Element element = _init_element(type, attributes_count, "");
                    
                }
            // TODO: add more cases

                break;
            default:
                break;

        }
        printf("%s\n", parser->token.content);
        _forward(parser);
    }
      
    free_tokens(parser->tokens, token_count);
    free(parser->tokens);
    free(parser);
    return st;
}

static ElementType get_element_type(char* literal) {
    // literal to lowercase
    for (int i = 0; i < strlen(literal); ++i) {
        literal[i] = tolower(literal[i]);
    }

    size_t len = sizeof(element_keywords) / sizeof(element_keywords[0]);

    for (int i = 0; i < len; ++i) {
        if (strcmp(literal, element_keywords[i]) == 0) {
            return (ElementType)i;
        }
    }

    return UNKNOWN_ELEMENT;
}

static AttributeType get_attribute_type(char* literal) {
    // literal to lowercase
    for (int i = 0; literal[i]; ++i) {
        literal[i] = tolower(literal[i]);
    }

    size_t len = sizeof(attribute_keywords) / sizeof(attribute_keywords[0]);

    for (int i = 0; i < len; ++i) {
        if (strcmp(literal, attribute_keywords[i]) == 0) {
            return (AttributeType)i;
        }
    }

    return UNKNOWN_ATTRIBUTE;
}

static void _ignore_comments(Parser* parser) {
    // check if the token sequence represents a comment
    if (parser->token.type == L_ANGLE &&
        parser->position + 1 < parser->token_count &&
        parser->tokens[parser->position + 1].type == BANG) {
        // Skip until the end of the comment
        while (!(parser->token.type == R_ANGLE)) {
            _forward(parser);
            if (parser->position >= parser->token_count)
                break;
        }
        if (parser->position >= parser->token_count)
            return;
        // move past the closing '>'
        _forward(parser);
        return;
    }

    // otherwise, continue skipping other types of comments as before
    // ignore HTML comments = <!-- -->
    while (parser->position < parser->token_count - 1 &&
           parser->token.type == L_ANGLE &&
           parser->tokens[parser->position + 1].type == BANG) {
        while (!(parser->token.type == R_ANGLE &&
                 parser->tokens[parser->position - 1].type == SUBTRACT &&
                 parser->tokens[parser->position - 2].type == SUBTRACT)) {
            _forward(parser);
            if (parser->position >= parser->token_count)
                break;
        }
        if (parser->position >= parser->token_count)
            break;
        _forward(parser); // move past the closing -->
    }

    // ignore JavaScript and CSS multi-line comments = /* */
    while (parser->position < parser->token_count - 1 &&
           parser->token.type == F_SLASH &&
           parser->tokens[parser->position + 1].type == ASTERISK) {
        while (!(parser->token.type == ASTERISK &&
                 parser->tokens[parser->position + 1].type == F_SLASH)) {
            _forward(parser);
            if (parser->position >= parser->token_count)
                break;
        }
        if (parser->position >= parser->token_count)
            break;
        _forward(parser); // move past the closing */
        _forward(parser);
    }
}

static Token* _peek(Parser* parser) {
    if (parser->position + 1 < parser->token_count) {
        return &parser->tokens[parser->position + 1];
    } else {
        // return NULL if none remaining
        return NULL;
    }
}

static void _forward(Parser* parser) {
    if (parser->position < parser->token_count && parser->token.type != EOF_TYPE) {
        parser->token = parser->tokens[++parser->position];
    }
}


static Element _init_element(ElementType type, size_t attributes_count, char* content) {
    Element element;
    element.type = type;

    element.attributes = (Attribute**)malloc(attributes_count * sizeof(Attribute*));
    if (element.attributes == NULL) {
        fprintf(stderr, "could not allocate memory\n");
        exit(EXIT_FAILURE);
    }

    element.attributes_count = attributes_count;

    // content should be allocated already
    element.content = content;  

    return element;
}

static SyntaxTreeNode* _init_node(SyntaxTreeNode* parent, ElementType type, size_t attributes_count, char* content) {
    SyntaxTreeNode* node = (SyntaxTreeNode*)malloc(sizeof(SyntaxTreeNode));
    if (node == NULL) {
        fprintf(stderr, "could not allocate memory\n");
        exit(EXIT_FAILURE);
    }

    node->parent = parent;

    // initialize children fields (if necessary)
    node->children = NULL;
    node->children_count = 0;

    return node;
}

static void _push_node(SyntaxTreeNode* parent, SyntaxTreeNode* node) {
    if (parent == NULL) {
        fprintf(stderr, "parent is NULL\n");
        return;
    }

    // allocate for childless parents
    if (parent->children == NULL) {
        parent->children = (SyntaxTreeNode**)malloc(sizeof(SyntaxTreeNode*));
        if (parent->children == NULL) {
            fprintf(stderr, "could not allocate memory\n");
            return;
        }
        parent->children[0] = node;
        parent->children_count = 1;
    } else {
        // allocate for new child
        parent->children = (SyntaxTreeNode**)realloc(parent->children, (parent->children_count + 1) * sizeof(SyntaxTreeNode*));
        if (parent->children == NULL) {
            fprintf(stderr, "could not allocate memory\n");
            return;
        }
        parent->children[parent->children_count] = node;
        ++parent->children_count;
    }

    // set parent
    node->parent = parent;
}

static void _free_element(Element element) {
    if (element.attributes != NULL) {
        for (size_t i = 0; i < element.attributes_count; ++i) {
            free(element.attributes[i]->content);
        }
        free(element.attributes);
    }

    free(element.content);
}

void free_tree(SyntaxTreeNode* root) {
    if (root == NULL) {
        return;
    }

    for (size_t i = 0; i < root->children_count; ++i) {
        free_tree(root->children[i]);
    }

    _free_element(root->element);
    free(root->children);
    free(root);
}
