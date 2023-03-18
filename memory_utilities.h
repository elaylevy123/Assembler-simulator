/*"******************************* mman14 Project which resmbles an assembly compiler *************************************************
******************************************************10/02/23**********************************************************************
********************************************by Elay Levi & Binyamin Visotski********************************************************
*******************************************(id:206016511)*****(id:316513746)********************************************************
***********************************************************************************************************************************"*/
#ifndef MAMAN14_AUXILIARY_STRUCTURES_H
#define MAMAN14_AUXILIARY_STRUCTURES_H

#include "error_case.h"
/*in this part of the code we are using all the memory and data functions to save in the designated structure we created for it in alingment without 
going overbounds in case of going overbound the corresponding error will show in prompt also this part of the code edits and checks for valid and invalid types of proccesssed memory that it saves here we have most of the adjusments to the listsw and files we create for output  */

/* macro values */
typedef struct macro{
    char mcrName[MAX_LINE];
    int mcrLocation;
    int numberOfLines;
    struct macro *next;
} mcrList;
/* macro list head */
typedef struct mcrTblHead{
    mcrList *head;
}mcrHead;
/* symbol values */
typedef struct symbol{
    char symbolName[MAX_SYMBOL];
    int value;
    char mark[MAX_TYPE];
    struct symbol *next;
}symbolList;
/* symbol list head */
typedef struct symTblHead{
    symbolList *head;
}symbolLine;
/* opcode 14 bits */
typedef struct opCode{
    unsigned int value:14;
}opCode;
/* data list values */
typedef struct dataList{
    opCode *data;
    int ic_start;
    struct dataList *next;
}dataList;
/* data list head */
typedef struct dataTblHead{
    dataList *head;
}headLine;
/* assembler values */
typedef struct esnParam{
    int IC;
    int DC;
} data_base;
/* allocate memory for macros */
mcrHead *createMcrList();
/* allocate memory fo IC and DC */
data_base *definedMemory();
/* allocate memory for symbol list */
symbolLine *createSymbolLine();
/*allocate memory for head data lines */
headLine *createHeadLine();
/* in case of wrong allocation of macro result in error else add the macro to the list*/
void addMcrList(mcrHead *headMcr, char *name, int firstLineLocation, int amountOfLines);
/* in case of wrong allocation of symbol result in error else add the symbol to the list */
void addSymbolList(symbolLine *symbol, char *labelName, char *type, int IC);
/* add data line */
void addDataLine(headLine *headLineStart, int num, int IC);
/* add data value */
void addDataValues(opCode *opCoded, int num);
/* initilize opCode value to 0 */
void setOpCode(opCode *opCoded);
/* in case of wrong allocation result in error els initialize all the data line values and return the pointer to this line */
opCode *resultList();
/* check if the names are of register,instruction, etc.. else return error */
int badName(char *name);
/* free the data list */
void freeheadLineStart(headLine *list);
/* free the macro list */
void freeMcrTbl(mcrHead *list);
/* free the symbol list */
void freeSymbolLine(symbolLine *list);


#endif /*MAMAN14_AUXILIARY_STRUCTURES_H*/
