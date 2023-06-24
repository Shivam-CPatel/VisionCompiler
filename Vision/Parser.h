/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ........ BOA LANGUAGE ......... |
|     __    __    __    __        |
|    /  \  /  \  /  \  /  \       |
| __/  __\/  __\/  __\/  __\__    |
| _/  /__/  /__/  /__/  /_____|   |
|  \_/ \   / \   / \   / \  \___  |
|       \_/   \_/   \_/   \___o_> |
|                                 |
| .. ALGONQUIN COLLEGE - 2022F .. |
|_________________________________|

*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern vision_intg line;
extern Token tokenizer();
extern vision_char* keywordTable[];
vision_intg syntaxErrorNumber = 0;

#define STR_LANGNAME	"Vision"
#define LANG_WRTE		"print"
#define LANG_READ		"input"
#define LANG_CLASS		"class"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_if,
	KW_then,
	KW_else,
	KW_while,
	KW_do,
	KW_DEF,
	KW_CLASS
};

/* Function definitions */
vision_void startParser();
vision_void matchToken(vision_intg, vision_intg);
vision_void syncErrorHandler(vision_intg);
vision_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
vision_void codeSession();
vision_void dataSession();
vision_void optVarListDeclarations();
vision_void optionalStatements();
vision_void outputStatement();
vision_void outputVariableList();
vision_void program();
vision_void statement();
vision_void statements();
vision_void statementsPrime();

#endif
