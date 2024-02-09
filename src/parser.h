#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

#include "lexer.h"
#include "utils.h"

typedef enum {
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
} TagType;

typedef enum {
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
	Token* input;
	uint32_t position;
	Token token;
} Parser;

typedef struct {
	AttributeType type;
	char* name;
	char* content;
} Attribute;

typedef struct {
	TagType type;
	Attribute* attributes;
	size_t attributes_count;
	uint8_t open;
} Tag;

typedef struct {
	TagType type;
	Attribute* attributes;
	size_t attributes_count;
	char* content;
} Element;

typedef struct {
	// to be defined.
} SyntaxTree;

SyntaxTree* parse(char* path);

#endif
