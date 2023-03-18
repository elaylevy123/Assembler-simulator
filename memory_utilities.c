/*"******************************* mman14 Project which resmbles an assembly compiler *************************************************
******************************************************10/02/23**********************************************************************
********************************************by Elay Levi & Binyamin Visotski********************************************************
*******************************************(id:206016511)*****(id:316513746)********************************************************
***********************************************************************************************************************************"*/
#include "memory_utilities.h"

mcrHead *createMcrList(){

    mcrHead *list = malloc(sizeof(mcrHead));

    if(list == NULL)
        memoryError();

    list->head = NULL;
    return list;
}

data_base *definedMemory(){

    data_base *asmValues = malloc(sizeof(data_base));

    if(asmValues == NULL)
        memoryError();

    asmValues->DC = 0;
    asmValues->IC = 100;

    return asmValues;
}

symbolLine *createSymbolLine(){

    symbolLine *list = malloc(sizeof(symbolLine));

    if(list == NULL)
        memoryError();

    list->head = NULL;
    return list;
}

headLine *createHeadLine(){

    headLine *list = malloc(sizeof(headLine));

    if(list == NULL)
        memoryError();

    list->head = NULL;
    return list;
}

void addMcrList(mcrHead *headMcr, char name[MAX_LINE], int firstLineLocation, int amountOfLines){

    mcrList *pointer = malloc(sizeof(mcrList));
    mcrList *temp = headMcr->head;

    if (!pointer)
        memoryError();

    /* save all the values of the macro we want to save */
    strcpy(pointer->mcrName, name) ;
    pointer->mcrLocation = firstLineLocation;
    pointer->numberOfLines = amountOfLines;
    pointer->next = NULL;
	/* first macro spread */
    if(!(headMcr->head)) 
        headMcr->head = pointer;

    else{
		/* set pointer to last macro */
        while (temp->next != NULL) 
            temp = temp->next;

        temp->next = pointer;
    } /* end */
}

void addSymbolList(symbolLine *symbol, char *labelName, char *type, int IC){

    symbolList *pointer = malloc(sizeof(symbolList));
    symbolList  *temp ;

    if (!pointer)
        memoryError();

    /* save all label values */
    strcpy(pointer->symbolName, labelName) ;
    strcpy(pointer->mark, type);
    pointer->value = IC;
    pointer->next = NULL;
/* in case first label aint set */
    if(!(symbol->head)) 
        symbol->head = pointer;

    else{

        temp = symbol->head;
	/* set pointer to last label in list */
        while (temp->next != NULL) 
            temp = temp->next;

        temp->next = pointer;
    } /* end */
}

void addDataLine(headLine *headLineStart, int num, int IC){

    dataList *pointer = malloc(sizeof(dataList));
    dataList *temp = headLineStart->head;

    if(pointer == NULL)
        memoryError();

    /* save all values of data line  */
    pointer->data =  resultList();
    addDataValues(pointer->data, num);
    pointer->ic_start = IC;
    pointer->next = NULL;

    if (!headLineStart->head) /* set first data line if not set */
        headLineStart->head = pointer;

    else{

        while(temp->next != NULL)  /* set pointer to data line in the input */ 
            temp = temp->next;

        temp->next = pointer;
    } /* end else */
}

void addDataValues(opCode *opCoded, int num){

    int i;

    for(i = 0; i < 14; i++){

        if(num & (1<< i))
            opCoded->value |= (1 << i);
    } /* end for loop */
}

void setOpCode(opCode *opCoded){

    opCoded->value = 0;
}

opCode *resultList(){

    opCode *pointer = malloc(sizeof(opCode));

    if(!pointer)
        memoryError();

    pointer->value = 0;

    return pointer;
}

int badName(char *name){

    int i ;
    /* name of instructors, directives and registers */
    char *directives [MAX_DIRECTIVES] = {".data", ".string", ".entry", ".extern"};
    char *instructions [MAX_INSTRUCTIONS] = {"mov", "cmp", "add", "sub", "lea", "not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
    char *registers [MAX_REGISTERS] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

    for (i = 0 ; i < MAX_INSTRUCTIONS ; i++){

        if(!strcmp(name, instructions[i]))
            return 1;
    } /* end loop */

    for (i = 0 ; i < MAX_DIRECTIVES ; i++){

        if(!strcmp(name, directives[i]))
            return 1;
    } /* end loop */

    for (i = 0 ; i < MAX_REGISTERS; i++){

        if(!strcmp(name, registers[i]))
            return 1;
    } /* end loop */

    return 0;
}

void freeheadLineStart(headLine *list){

    dataList *temp = list->head;

    while(list->head != NULL){

        list->head = list->head->next;
        free(temp->data);
        free(temp);
        temp = list->head;
    } /* end  loop */

    free(list);
}

void freeMcrTbl(mcrHead *list){

    mcrList *temp = list->head;

    while(list->head != NULL){

        list->head = list->head->next;
        free(temp);
        temp = list->head;
    } /* end loop */

    free(list);
}

void freeSymbolLine(symbolLine *list){

    symbolList *temp = list->head;

    while(list->head != NULL){

        list->head = list->head->next;
        free(temp);
        temp = list->head;
    } /* end loop */

    free(list);
}
