#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

#include "lexer.h"
#include "utils.h"

enum TagType {
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
};

enum AttributeType {
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
	LABEL,
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
	STYLE,
	TARGET,
	TYPE,
	VALUE,
	WIDTH,
};

typedef struct {
	Token* input;
	uint32_t position;
	Token token;
} Parser;

typedef struct {
	AttributeType type;
	char* content;
} Attribute;

typedef struct {
	enum TagType type;
	Attribute* attributes;
	uint8_t open;
} Tag;

#endif