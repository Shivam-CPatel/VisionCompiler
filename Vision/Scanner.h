/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Jul 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */
#define FLT_LEN 10

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	TIM_T,		/*  5: Tab(\t) in method*/
	GTS_T,		/*  6: greater(>) than sign*/
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Integer Literal token */
	FLL_T,		/* 11: Float Literal token */
	ASP_T,      /* 12: Assignment operator token */
	SLC_T,		/* 13: Single line comment */
	MLC_T,		/* 13: Multi line comment */
	SEOF_T,		/* 14: Source end-of-file token */
	LTS_T,		/* 15: less(<) than sign*/
	NES_T		/* 16: not(!) than sign*/
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	vision_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	vision_intg intValue;						/* integer literal attribute (value) */
	vision_intg keywordIndex;					/* keyword index in the keyword table */
	vision_intg contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	vision_real floatValue;					/* floating-point literal attribute (value) */
	vision_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	vision_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	vision_byte flags;			/* Flags information */
	union {
		vision_intg intValue;				/* Integer value */
		vision_real floatValue;			/* Float value */
		vision_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	vision_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';',
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # ,
 *  .&., .|. , .!. , SEOF.
 */

 /* TO_DO: Define lexeme FIXED classes */
 /* These constants will be used on nextClass */
#define CHRCOL1 ' '
#define CHRCOL2 '\n'
#define CHRCOL3 ':'
#define CHRCOL4 '.'
#define CHRCOL5 'e'
#define CHRCOL6 '"'

/*
#define CHRCOL2 '_'
#define CHRCOL3 '&'
#define CHRCOL4 '\''
*/

/* These constants will be used on VID / MID function */
#define MNIDPREFIX ' '

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESWR	101		/* Error state with retract */
#define ESNR	102		/* Error state with no retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 15

/* TO_DO: Transition table - type of states defined in separate table */
static vision_intg transitionTable[][TABLE_COLUMNS] = {
	/*   [A-z] , [0-9],    _,    &,    ", SEOF, other
		          L(0),  D(1), S(2), C(3), M(4), P(5),  Q(6),  O(7),  U(8), F(9),  E(10) */
		   /*
		   */
			   {     1,     4, ESNR,   13, ESNR,   11,   11,   ESNR,  ESNR,  ESNR,	ESNR}, // S0: NOAS
			   {     1,		2,	  2,	2,    2,	2,	  2,      2,     2,     3,     1}, // S1: NOAS
			   {    FS,    FS,   FS,   FS,   FS,   FS,   FS,     FS,    FS,    FS,    FS}, // S2: ASWR (KEY)
			   {    FS,    FS,   FS,   FS,   FS,   FS,   FS,     FS,    FS,    FS,    FS}, // S3: ASNR (Method \ Variable)
			   {	 5,     4,	  5,    5,    5,    6,    5,      5,     5,     5,     5}, // S4: NOAS
			   {    FS,    FS,   FS,   FS,   FS,   FS,   FS,     FS,    FS,    FS,    FS}, // S5: ASNR (IL)
			   {  ESNR,     6, ESNR, ESNR, ESNR, ESNR, ESNR,      8,  ESNR,  ESNR,     7}, // S6: NOAS
			   {  ESNR,     7, ESNR, ESNR, ESNR, ESNR, ESNR,      9,  ESNR,  ESNR,  ESNR}, // S7: NOAS 
			   {    FS,    FS,   FS,   FS,   FS,   FS,   FS,     FS,    FS,    FS,    FS}, // S8: ASNR (FL)
			   {    FS,    FS,   FS,   FS,   FS,   FS,   FS,     FS,    FS,    FS,    FS}, // S9: ASNR (FL)
			   {  ESNR,     8, ESNR, ESNR, ESNR, ESNR, ESNR,      9,  ESNR,  ESNR,  ESWR}, // S10: NOAS
			   {    11,    11,   11,   11,   11,   11,   12,     11,    11,    11,    11}, // S11: NOAS
			   {    FS,    FS,   FS,   FS,   FS,   FS,   FS,     FS,    FS,    FS,    FS}, // S12: ASNR 
			   {    13,    13,   13,   14,   13,   13,   13,     13,    13,    13,    13}, // S13: NOAS
			   {    FS,    FS,   FS,   FS,   FS,   FS,   FS,     FS,    FS,    FS,    FS}, // S14: ASNR (Multi-line comment)
			   {    FS,    FS,   FS,   FS,   FS,   FS,   FS,     FS,    FS,    FS,    FS}  // S15: ASWR (ER)




			   /*   [A-z] , [0-9],    _,    &,    ", SEOF, other
				  L(0),  D(1), U(2), M(3), Q(4), E(5),  O(6) */
				  /*
					  {     1,  ESNR, ESNR, ESNR,    4, ESWR, ESNR}, // S0: NOAS
					  {     1,     1,    1,    2, ESNR, ESWR,    3}, // S1: NOAS
					  {    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S2: ASNR (MVID)
					  {    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S3: ASWR (KEY)
					  {     4,     4,    4,    4,    5, ESWR,    4}, // S4: NOAS
					  {    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S5: ASNR (SL)
					  {    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S6: ASNR (ES)
					  {    FS,    FS,   FS,   FS,   FS,   FS,   FS}  // S7: ASWR (ER)
				  */
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */



/* TO_DO: Define list of acceptable states */
static vision_intg stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSWR, /* 02 (KEY) */
	FSNR, /* 03 (MID) - Methods */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	NOFS, /* 06 */
	NOFS, /* 07 */
	FSNR, /* 08 */
	FSNR, /* 09 */
	NOFS, /* 10 */
	NOFS, /* 11 */
	FSNR, /* 12 */
	NOFS, /* 13 */
	FSNR, /* 14 Multi-line */
	FSWR  /* 15 Err */
};

/* TO_DO: Define list of acceptable states */
//static vision_intg stateType[] = {
//	NOFS, /* 00 */
//	NOFS, /* 01 */
//	FSNR, /* 02 (MID) - Methods */
//	FSWR, /* 03 (KEY) */
//	NOFS, /* 04 */
//	FSNR, /* 05 (SL) */
//	FSNR, /* 06 (Err1 - no retract) */
//	FSWR  /* 07 (Err2 - retract) */
//};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
vision_intg startScanner(ReaderPointer psc_buf);
static vision_intg nextClass(vision_char c);			/* character class function */
static vision_intg nextState(vision_intg, vision_char);		/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(vision_char* lexeme);

/* Declare accepting states functions */
Token funcSL(vision_char lexeme[]);
Token funcIL(vision_char lexeme[]);
Token funcFL(vision_char lexeme[]);
Token funcID(vision_char lexeme[]);
Token funcKEY(vision_char lexeme[]);
Token funcErr(vision_char lexeme[]);

/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */


 /* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcKEY,	/* KEY  [02] */
	funcID,		/* MNID	[03] */
	NULL,		/* -    [04] */
	funcIL,		/* IL	[05] */
	NULL,		/* -	[06] */
	NULL,		/* -	[07] */
	funcFL,		/* FL	[08] */
	funcFL,		/* FL	[09] */
	NULL,		/* -	[10] */
	NULL,		/* -	[11] */
	funcSL,		/* SL   [12] */
	NULL,		/* -	[13] */
	NULL,		/* -	[14] */
	funcErr		/* ERR2 [15] */
};
/* TO_DO: Define final state table */
//static PTR_ACCFUN finalStateTable[] = {
//	NULL,		/* -    [00] */
//	NULL,		/* -    [01] */
//	funcID,		/* MNID	[02] */
//	funcKEY,	/* KEY  [03] */
//	NULL,		/* -    [04] */
//	funcSL,		/* SL   [05] */
//	funcErr,	/* ERR1 [06] */
//	funcErr		/* ERR2 [07] */
// };

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

#define KWT_SIZE 7

/* TO_DO: Define the list of keywords */
static vision_char* keywordTable[KWT_SIZE] = {
	"if",
	"then",
	"else",
	"while",
	"do",
	"def",
	"class"
};

/* TO_DO: Define the number of Keywords from the language
#define KWT_SIZE 10
*/

/* TO_DO: Define the list of keywords
static vision_char* keywordTable[KWT_SIZE] = {
	"data",
	"code",
	"int",
	"real",
	"string",
	"if",
	"then",
	"else",
	"while",
	"do"
};
*/

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

 /* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	vision_char indentationCharType;
	vision_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

#endif
