#ifndef AST_H 
#define AST_H

#include <stdint.h>

#include "lexer.h"
#include "utils.h"

typedef struct SyntaxTreeNode SyntaxTreeNode;

typedef enum {
    UNKNOWN_ELEMENT,
    A,
    ABBR,
    ADDRESS,
    AREA,
    ARTICLE,
    ASIDE,
    AUDIO,
    B,
    BASE,
    BDI,
    BDO,
    BLOCKQUOTE,
    BODY,
    BR,
    BUTTON,
    CANVAS,
    CAPTION,
    CITE,
    CODE,
    COL,
    COLGROUP,
    DATA,
    DATALIST,
    DD,
    DEL,
    DETAILS,
    DFN,
    DIALOG,
    DIV,
    DL,
    DT,
    EM,
    EMBED,
    FIELDSET,
    FIGCAPTION,
    FIGURE,
    FOOTER,
    FORM,
    H1,
    H2,
    H3,
    H4,
    H5,
    H6,
    HEAD,
    HEADER,
    HGROUP,
    HR,
    HTML,
    I,
    IFRAME,
    IMG,
    INPUT,
    INS,
    KBD,
    LABEL,
    LEGEND,
    LI,
    LINK,
    MAIN,
    MAP,
    MARK,
    META,
    METER,
    NAV,
    NOSCRIPT,
    OBJECT,
    OL,
    OPTGROUP,
    OPTION,
    OUTPUT,
    P,
    PARAM,
    PICTURE,
    PRE,
    PROGRESS,
    Q,
    RP,
    RT,
    RUBY,
    S,
    SAMP,
    SCRIPT,
    SECTION,
    SELECT,
    SMALL,
    SOURCE,
    SPAN,
    STRONG,
    STYLE,
    SUB,
    SUMMARY,
    SUP,
    SVG,
    TABLE,
    TBODY,
    TD,
    TEMPLATE,
    TEXTAREA,
    TFOOT,
    TH,
    THEAD,
    TIME,
    TITLE,
    TR,
    TRACK,
    U,
    UL,
    VAR,
    VIDEO,
    WBR,
} ElementType;

typedef enum {
    UNKNOWN_ATTRIBUTE,
	ACCESSKEY,
	ALIGN,
	ALT,
	ASYNC,
	AUTOCOMPLETE,
	AUTOPLAY,
	BORDER,
	CLASS,
	COLS,
	COLSPAN,
	CONTENT,
	CONTROLS,
	DISABLED,
	DOWNLOAD,
	ENCTYPE,
	FOR,
	HEIGHT,
	HREF,
	ID,
	MAX,
	MAXLENGTH,
	METHOD,
	MIN,
	MULTIPLE,
	NAME,
	PLACEHOLDER,
	READONLY,
	REL,
	REQUIRED,
	ROWSPAN,
	SRC,
	TARGET,
	TYPE,
	VALUE,
	WIDTH,
} AttributeType;

typedef struct {
	Token* tokens;
    size_t token_count;
	uint32_t position;
	Token token;
    int in_tag;
    ElementType tag;
} Parser;

typedef struct {
	AttributeType type;
	char* content;
} Attribute;

typedef struct {
	ElementType type;
	Attribute** attributes;
	size_t attributes_count;
	char* content;
} Element;

struct SyntaxTreeNode {
    SyntaxTreeNode* parent;
    Element element;
    SyntaxTreeNode** children;
    size_t children_count;
};

typedef struct {
    SyntaxTreeNode* root;
    size_t node_count;
} SyntaxTree;

typedef struct {
    ElementType type;
    SyntaxTreeNode* node;
} StackItem;

SyntaxTree parse(char* path);
void free_tree(SyntaxTreeNode* root);

#endif
