/*"******************************* mman14 Project which resmbles an assembly compiler *************************************************
******************************************************10/02/23**********************************************************************
********************************************by Elay Levi & Binyamin Visotski********************************************************
*******************************************(id:206016511)*****(id:316513746)********************************************************
***********************************************************************************************************************************"*/

#ifndef MAMAN14_SECOND_H
#define MAMAN14_SECOND_H

#include "first_pass.h"
#include "opcode.h"
/*the second pass is accountable to take all the data we proccesed until now and by using opcode.c/.h we assmble the wanted .ob file 
with the wanted output in "," and "/" by calculating the results of opcode with our 
diffrerent types of checks as instructed below and in previous parts of the code.
*/


/* edit the .entry file with the label names */
void editDotEnt(FILE *entfile, symbolLine *symbolLine, char *firstLabelName, int countLines, int *error);
/* edit the .extrn file with the label names */
void editDotExt(FILE *extfile, char *firstLabelName, int IC);
/* check if label names exist in the list */
int lastLabelChecks(symbolLine *symbolLine, char *firstLabelName, int type, int *error, int countLines);
/* in second we build all the data needed to edit the .ob file with the ending result */
void second(data_base *asmValues, symbolLine *symbolLineStart, headLine *headLineStart, char *asFileName, char *extFileName, char *entFileName, char *obFileName, int *error, int *ext_Flag, int *ent_Flag);
/* adds all data to the .ob file */
void editDotObFile(FILE *obFile, data_base *asmValues, headLine *headLineStart, int currentIC);
/* save the symbol name in the label name */
void saveLabelToSymbol(char *line, char *firstLabelName);
/* chechk where we landed in the jump address */
void jumpToLabelAddress(char *firstLabelName, int *flag);
/*check the opcode for the label instruction and command of the first half of the code and for the first operand */
void getOp1(FILE *obFile, FILE *extFile, data_base *asmValues, symbolLine *symbolLineStart, char *ptrLine, int commandIndex, int *error, int countLines);
/* checks the second half of opcode respinsible for the second operand and */
void getOp2(FILE *obFile, FILE *extFile, data_base *asmValues, symbolLine *symbolLineStart, char *ptrLine, int commandIndex, int *error, int countLines);

#endif /*MAMAN14_SECOND_H*/
