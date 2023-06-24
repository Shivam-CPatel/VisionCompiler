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
* File name: mainBuffer.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

vision_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
//	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
vision_void matchToken(vision_intg tokenCode, vision_intg tokenAttribute) {
	vision_intg matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:

		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
vision_void syncErrorHandler(vision_intg syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
vision_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case GTS_T:
		printf("GTS_T\n");
		break;
	case LTS_T:
		printf("LTS_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
vision_void program() {
	vision_intg endParser = 1;
	while (endParser == 1) {

	
	switch (lookahead.code) {
	case MLC_T:
		matchToken(MLC_T, NO_ATTR);
		break;
	case SLC_T:
		matchToken(SLC_T, NO_ATTR);
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 5) == 0) {
			matchToken(MNID_T, NO_ATTR);
			matchToken(STR_T, NO_ATTR);
			matchToken(RPR_T, NO_ATTR);
			if (lookahead.code == SEOF_T) {
				;
				break;
			}
			break;
		}
		else {
			vision_intg otherThanVariable = 1;
			while (otherThanVariable == 1)
			{
				matchToken(MNID_T, NO_ATTR);
				matchToken(ASP_T, NO_ATTR);
				
				if (lookahead.code == TIM_T) {
					matchToken(TIM_T, NO_ATTR);
				}
				
				if (lookahead.code == INL_T) {
					matchToken(INL_T, NO_ATTR);
				}else if (lookahead.code == FLL_T) {
					matchToken(FLL_T, NO_ATTR);
				}else if (lookahead.code == STR_T) {
					matchToken(STR_T, NO_ATTR);
				}else if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 5) == 0) {
					matchToken(MNID_T, NO_ATTR);
					matchToken(STR_T, NO_ATTR);
					matchToken(RPR_T, NO_ATTR);
				}
				if (lookahead.code == MLC_T || lookahead.code == SLC_T 
					|| lookahead.code == KW_T) {
					otherThanVariable = 2;
				}

			}
		}
	case KW_T:
		if (lookahead.attribute.codeType == 6) {
			matchToken(KW_T, KW_CLASS);
			matchToken(MNID_T, NO_ATTR);
			//dataSession();
			codeSession();
			//matchToken(RBR_T, NO_ATTR);
			break;
		}
		else if (lookahead.attribute.codeType == 5) {
			matchToken(KW_T, KW_DEF);
			matchToken(MNID_T, NO_ATTR);
			//dataSession();
			codeSession();
			//matchToken(RBR_T, NO_ATTR);
			break;
		}
		else if (lookahead.attribute.codeType == 4) {

		}
		else if (lookahead.attribute.codeType == 3) {

		}
		else if (lookahead.attribute.codeType == 2) {

		}
		else if (lookahead.attribute.codeType == 1) {

		}
		else if (lookahead.attribute.codeType == 0) {
			matchToken(KW_T, KW_if);
			matchToken(MNID_T, NO_ATTR);
			if (lookahead.code == GTS_T) {
				matchToken(GTS_T, NO_ATTR);
				
				if (lookahead.code == ASP_T) {
					matchToken(ASP_T, NO_ATTR);
				}
				
				if (lookahead.code == TIM_T) {
					matchToken(TIM_T, NO_ATTR);
				}

				if (lookahead.code == INL_T) {
					matchToken(INL_T, NO_ATTR);
				}
				else if (lookahead.code == FLL_T) {
					matchToken(FLL_T, NO_ATTR);
				}
			}
			else if (lookahead.code == LTS_T) {
				matchToken(LTS_T, NO_ATTR);

				if (lookahead.code == ASP_T) {
					matchToken(ASP_T, NO_ATTR);
				}

				if (lookahead.code == TIM_T) {
					matchToken(TIM_T, NO_ATTR);
				}

				if (lookahead.code == INL_T) {
					matchToken(INL_T, NO_ATTR);
				}
				else if (lookahead.code == FLL_T) {
					matchToken(FLL_T, NO_ATTR);
				}
			} 
			else if (lookahead.code == ASP_T) {
				matchToken(ASP_T, NO_ATTR);
				matchToken(ASP_T, NO_ATTR);
				
				if (lookahead.code == TIM_T) {
					matchToken(TIM_T, NO_ATTR);
				}

				if (lookahead.code == INL_T) {
					matchToken(INL_T, NO_ATTR);
				}
				else if (lookahead.code == FLL_T) {
					matchToken(FLL_T, NO_ATTR);
				}
			}
			else if (lookahead.code == NES_T) {
				matchToken(NES_T, NO_ATTR);
				matchToken(ASP_T, NO_ATTR);

				if (lookahead.code == TIM_T) {
					matchToken(TIM_T, NO_ATTR);
				}

				if (lookahead.code == INL_T) {
					matchToken(INL_T, NO_ATTR);
				}
				else if (lookahead.code == FLL_T) {
					matchToken(FLL_T, NO_ATTR);
				}
			}
			codeSession();
			break;
		}
		else {
			printError();
		}
	case SEOF_T:
		endParser = 2;
		; // Empty
		break;
	default:
		printError();
	}

	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
vision_void dataSession() {
	//matchToken(KW_T, KW_data);
	//matchToken(LBR_T, NO_ATTR);
	optVarListDeclarations();
	//matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
}

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
vision_void optVarListDeclarations() {
	switch (lookahead.code) {
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
vision_void codeSession() {
	while (lookahead.code == TIM_T || lookahead.code != SEOF_T) {
		while (lookahead.code == TIM_T) {
			matchToken(TIM_T, NO_ATTR);
		}

		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 5) == 0) {
			matchToken(MNID_T, NO_ATTR);
			matchToken(STR_T, NO_ATTR);
			matchToken(RPR_T, NO_ATTR);
		}
		else if (lookahead.code == MLC_T)
		{
			matchToken(MLC_T, NO_ATTR);
		}
		else if (lookahead.code == SLC_T)
		{
			matchToken(SLC_T, NO_ATTR);
		}
		else
		{
			vision_intg otherThanVariable = 1;
			if (lookahead.code == KW_T) {
				if (lookahead.attribute.codeType == 5) {
					matchToken(KW_T, KW_DEF);
				}


				matchToken(MNID_T, NO_ATTR);
				matchToken(RPR_T, NO_ATTR);
				codeSession();
			}
			if (lookahead.code == SEOF_T) {
				matchToken(SEOF_T, NO_ATTR);
				break;
			}
			matchToken(MNID_T, NO_ATTR);
			if (lookahead.code == ASP_T) {
				matchToken(ASP_T, NO_ATTR);

				if (lookahead.code == TIM_T) {
					matchToken(TIM_T, NO_ATTR);
				}

				if (lookahead.code == INL_T) {
					matchToken(INL_T, NO_ATTR);
				}
				else if (lookahead.code == FLL_T) {
					matchToken(FLL_T, NO_ATTR);
				}
				else if (lookahead.code == STR_T) {
					matchToken(STR_T, NO_ATTR);
				}
				else if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 5) == 0) {
					matchToken(MNID_T, NO_ATTR);
					matchToken(STR_T, NO_ATTR);
					matchToken(RPR_T, NO_ATTR);
				}

				if (lookahead.code == MLC_T || lookahead.code == SLC_T) {
					otherThanVariable = 2;
				}
			}
		}
	}
	//matchToken(KW_T, KW_code);
	//matchToken(LBR_T, NO_ATTR);
	//optionalStatements();
	//matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
vision_void optionalStatements() {
	switch (lookahead.code) {
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
vision_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
vision_void statementsPrime() {
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
vision_void statement() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		default:
			printError();
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
vision_void outputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
vision_void outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}
