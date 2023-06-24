/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Patel Shivam & Chen Nathan
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ....... VISION LANGUAGE ....... |
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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: 012
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /*
 ***********************************************************
 * Function name: readerCreate
 * Purpose: Creates the buffer reader according to capacity, increment
	 factor and operational mode ('f', 'a', 'm')
 * Author: Patel Shivam & Chen Nathan
 * History/Versions: S22
 * Called functions: calloc(), malloc()
 * Parameters:
 *   size = initial capacity
 *   increment = increment factor
 *   mode = operational mode
 * Return value: bPointer (pointer to reader)
 * Algorithm: Allocation of memory according to inicial (default) values.
 * TODO ......................................................
 *	- Adjust datatypes for your LANGUAGE.
 *   - Use defensive programming
 *	- Check boundary conditions
 *	- Check flags.
 *************************************************************
 */

ReaderPointer readerCreate(vision_intg size, vision_intg increment, vision_intg mode) {
	ReaderPointer readerPointer;
	/* TO_DO: Defensive programming */
	if ((size < 0) || (increment < 0) || ((mode != MODE_FIXED) && (mode != MODE_ADDIT) && (mode != MODE_MULTI)))
		return NULL;
	/* TO_DO: Adjust the values according to parameters */
	size = READER_DEFAULT_SIZE;
	increment = READER_DEFAULT_INCREMENT;
	if (mode == MODE_FIXED) {
		mode = MODE_FIXED;
	}
	else if (mode == MODE_ADDIT) {
		mode = MODE_ADDIT;
	}
	else if (mode == MODE_MULTI) {
		mode = MODE_MULTI;
	}
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	else {
		readerPointer->content = (vision_char*)malloc(size);
		/* TO_DO: Defensive programming */
		if (!readerPointer->content) {
			return NULL;
		}
		/* TO_DO: Initialize the histogram */
		readerPointer->histogram[size];
		readerPointer->size = size;
		readerPointer->increment = increment;
		readerPointer->mode = mode;
		/* TO_DO: Initialize flags */
		readerPointer->flags = READER_DEFAULT_FLAG | READER_EMP_FLAG;
		/* TO_DO: The created flag must be signalized as EMP */
		return readerPointer;
	}
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, vision_char ch) {
	vision_char* tempReader = NULL;
	vision_intg newSize = 0;
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return NULL;
	}
	/* TO_DO: Reset Realocation */
	// readerPointer->content = (vision_char*)malloc(newSize);
	/* TO_DO: Test the inclusion of chars */
	vision_intg realAdd = (&(readerPointer->content));
	if (readerPointer->position.wrte * (vision_intg)sizeof(vision_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
//		readerPointer->flags = READER_EMP_FLAG | readerPointer->flags;
		readerPointer->flags = READER_REL_FLAG | readerPointer->flags;
	}
	else {
		/* TO_DO: Reset Full flag */
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Defensive programming (DONE) */
			if ((newSize < 0) || (newSize > READER_MAX_SIZE)) {
				return NULL;
			}
			else {
				/* TO_DO: Adjust new size (DONE) */
				newSize = readerPointer->size + readerPointer->increment;
			}
			break;
		case MODE_MULTI:
			/* TO_DO: Defensive programming (DONE) */
			if ((newSize < 0) || (newSize > READER_MAX_SIZE)) {
				return NULL;
			}
			else {
				/* TO_DO: Adjust new size (DONE) */
				newSize = readerPointer->size * readerPointer->increment;
			}
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		tempReader = (vision_char*)realloc(readerPointer->content, newSize);
		readerPointer->content = tempReader;
		/* TO_DO: Defensive programming */
		if (!tempReader)
			return NULL;
		/* TO_DO: Check Relocation */
		if (readerPointer) {
			readerPointer->size = newSize;
		}
	}
	/* TO_DO: Add the char (DONE) */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
//	if ((readerPointer != realAdd) && (&(readerPointer->content) != realAdd)) {
//		readerPointer->flags = READER_REL_FLAG | readerPointer->flags;
//	}

	readerPointer->histogram[newSize];
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer) {
		/* TO_DO: Adjust flags original */
		free(readerPointer->content);
		readerPointer->size = READER_DEFAULT_SIZE;
		readerPointer->content = (vision_char*)calloc(1, readerPointer->size);
		readerPointer->flags = READER_DEFAULT_FLAG;
		return VISION_TRUE;
	}
	return VISION_FALSE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return VISION_FALSE;
	/* TO_DO: Free pointers */
	free(readerPointer->content);
	free(readerPointer);
	return VISION_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return VISION_FALSE;
	}
	/* TO_DO: Check flag if buffer is FUL */
	if (readerPointer->flags == READER_FUL_FLAG) {
		return VISION_TRUE;
	}
	return VISION_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return VISION_FALSE;
	}
	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer->flags == READER_EMP_FLAG) {
		return VISION_TRUE;
	}
	return VISION_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_boln readerSetMark(ReaderPointer const readerPointer, vision_intg mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark < 0 || mark > readerPointer->position.wrte) {
		return VISION_FALSE;
	}
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return VISION_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_intg readerPrint(ReaderPointer const readerPointer) {
	vision_intg cont = 0;
	vision_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Check flag if buffer EOB has achieved */
	if (readerPointer->flags == READER_EMP_FLAG) {
		return VISION_FALSE;
	}
	c = readerGetChar(readerPointer);
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	vision_intg size = 0;
	vision_char c;
	/* TO_DO: Defensive programming */
	if (!readerPointer || !fileDescriptor) {
		return READER_ERROR;
	}
	c = (vision_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
	if (readerPointer->size != size) {
		return readerPointer->size;
	}
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return VISION_FALSE;
	}
	/* TO_DO: Recover positions */
	readerPointer->position.read = VISION_FALSE;
	readerPointer->position.mark = VISION_FALSE;
	return VISION_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return VISION_FALSE;
	/* TO_DO: Retract (return 1 pos read) (DONE) */
	readerPointer->position.read--;
	return VISION_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return VISION_FALSE;
	/* TO_DO: Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return VISION_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return VISION_FALSE;
	/* TO_DO: Check condition to read/wrte */
	/* TO_DO: Set EOB flag */
	/* TO_DO: Reset EOB flag */
	if (readerPointer->content[readerPointer->position.read] == READER_TERMINATOR) {
		readerPointer->flags = READER_END_FLAG;
	}
	return readerPointer->content[readerPointer->position.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_char* readerGetContent(ReaderPointer const readerPointer, vision_intg pos) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || pos < 0)
		return VISION_FALSE;
	/* TO_DO: Return content (string) */
	return readerPointer->content + pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return read (DONE) */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return wrte (DONE) */
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return mark (DONE) */
	return readerPointer->position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_intg readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return VISION_FALSE;
	/* TO_DO: Return size (DONE) */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return VISION_FALSE;
	/* TO_DO: Return increment (DONE) */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return VISION_FALSE;
	/* TO_DO: Return mode (DONE) */
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return VISION_FALSE;
	/* TO_DO: Return flags (DONE) */
	return readerPointer->flags;
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
vision_intg readerShowStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return VISION_FALSE;
	/* TO_DO: Updates the histogram */
//	readerPointer->histogram[];
	return VISION_TRUE;
}