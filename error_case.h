/*"******************************* mman14 Project which resmbles an assembly compiler *************************************************
******************************************************10/02/23**********************************************************************
********************************************by Elay Levi & Binyamin Visotski********************************************************
*******************************************(id:206016511)*****(id:316513746)********************************************************
***********************************************************************************************************************************"*/
#ifndef MAMAN14_ERR_MESS_H
#define MAMAN14_ERR_MESS_H

#include "defined.h"

/* The assembler may detect errors in the syntax of the language, errors such as "Instruction does not exist" or "to many operands" and more. 
The assembler has to verify that all symbols are defined exactly once. 
Thus all errors detected by the assembler may be attributed to a particular line of input. 
If, for example, two addresses are assigned to instruction that should be assigned with only one address, then the assembler may respond with "To many addresses" error message. 
The following table contains information on legal addressing mode for the source and destination operands.*/


/* all of this functions are ERROR functions that print an error for the error coresponding to the name itself*/
void memoryError(void);
void chkNumArgs (int args);
FILE *fileNotCreated(FILE *fd, char *fileToOpen, char *mode, int *error);/*in case the fike was not created this function will take care of it with the error flag on*/
void badLabelName(int *error, int line);
void chkLineLen(int *error, int line);
void LabelToLong(int *error, int line);
void badMcr(int *error, int line);
void noSpace(int *error, int line);
void noParameter(int *error, int line);
void spacedLabel(int *error, int line);
void existingLabelName(int *error, int line);
void textOverBound(int *error, int line);
void unDefienedcommand(int *error, int line);
void undefinedInstruction(int *error, int line);
void badComma(int *error, int line);
void invalidDataParam(int *error, int line);
void badString(int *error, int line);
void toManyCommas(int *error, int line);
void noComma(int *error, int line);
void dumpLabel(int *error, int line);
void badValue(int *error, int line);
void badNumber(int *error, int line);
void badRegister(int *error, int line);
void dataOverbound(int *error);
void unDefienedLabel(int *error, int line);
void extCantBeEnt(int *error, int line);


#endif /*MAMAN14_ERR_MESS_H*/
