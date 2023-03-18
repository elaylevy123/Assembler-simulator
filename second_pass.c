/*"******************************* mman14 Project which resmbles an assembly compiler *************************************************
******************************************************10/02/23**********************************************************************
********************************************by Elay Levi & Binyamin Visotski********************************************************
*******************************************(id:206016511)*****(id:316513746)********************************************************
***********************************************************************************************************************************"*/
#define _CRT_SECURE_NO_WARNINGS
#include "second_pass.h"

int lastLabelChecks(symbolLine *symbolLine, char *firstLabelName, int type, int *error, int countLines);

void editDotEnt(FILE *entFile, symbolLine *symbolLine, char *firstLabelName, int countLines, int *error) {

    symbolList *temp = symbolLine->head;
    char line[MAX_LINE] = {'\0'};

    while (temp) {
        if (!strcmp(firstLabelName, temp->symbolName)) {

            if (!strcmp("ext", temp->mark)) {

                extCantBeEnt(error, countLines);
                return;
            } /* end */

            sprintf(line, "%s\t\t%d\n", firstLabelName, temp->value);
            fputs(line, entFile);
            break;
        } /* end */
        temp = temp->next;
    } /* end loop */
}

void editDotExt(FILE *extFile, char *firstLabelName, int IC){

    char line[MAX_LINE] = {'\0'};

    sprintf(line, "%s\t\t%d\n", firstLabelName, IC);
    fputs(line, extFile);

}
void second(data_base *asmValues, symbolLine *symbolLineStart, headLine *headLineStart, char *amFileName, char *extFileName, char *entFileName, char *obFileName, int *error, int *ext_Flag, int *ent_Flag){

    FILE *amFile = NULL;
    FILE *extFile = NULL;
    FILE *entFile = NULL;
    FILE *obFile = NULL;
    char line[MAX_LINE] ={'\0'};
    char *ptrLine = NULL;
    char *op1[OP1_LENGTH] = {"not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr"};
    char *op2[OP2_LENGTH] = {"mov", "cmp", "add", "sub", "lea"};
    int countLines = 0;
    asmValues->IC = 100;

    if(!(amFile = fileNotCreated(amFile, amFileName, "r+", error)))
        return;

    if(ext_Flag) {

        if (!(extFile = fileNotCreated(extFile, extFileName, "w+", error)))
            return;
    } /* end */

    if(ent_Flag) {

        if (!(entFile = fileNotCreated(entFile, entFileName, "w+", error)))
            return;
    } /* end */

    if(!(obFile = fileNotCreated(obFile, obFileName, "w+", error)))
        return;

    while(fgets(line, MAX_LINE, amFile) != NULL) { /*check all the lines in the file*/

        char firstLabelName[MAX_SYMBOL] = {'\0'};
        int firstLabelFlag;
        int op1Flag = 0;
        int op2Flag = 0;
        int i;
        ptrLine = line;
        countLines++;

        no_tabs(ptrLine); /* point to start of line */

        /* skip empty line */
        if(*ptrLine == '\n' || *ptrLine == '\0')
            continue;

        /* skip comment */
        if(*ptrLine == ';') \
            continue;

        firstLabelFlag = label(ptrLine);

        if(firstLabelFlag) {

            saveLabel(ptrLine,firstLabelName);
            ptrLine += strlen(firstLabelName); /* after label name position */
            no_tabs(ptrLine);
        } /* end */

        if (*ptrLine == '.') { /* when in .data .extrn .entry .string zone */

            /*check for good .entry data */
            if (checkWord(ptrLine,".entry")) {

                ptrLine += 6;
                no_tabs(ptrLine);
                saveLabelToSymbol(ptrLine, firstLabelName);

                if(lastLabelChecks(symbolLineStart, firstLabelName, 1, error, countLines)) /* check if label name already exists in list */
                    editDotEnt(entFile, symbolLineStart, firstLabelName, countLines, error);

                continue;
            } /* end */

            if (checkWord(ptrLine,".extern"))
                continue;


            /*in case we already have the symbol in the list  */
            if(checkWord(ptrLine, ".data") || checkWord(ptrLine, ".string")){

                editDotObFile(obFile, asmValues, headLineStart, asmValues->IC);
                continue;
            } /* end */
        } /* end */

        /* calculate for instructions with 0 operands  */
        if(checkWord(ptrLine, "rts")){

            opCode *tempLine = resultList();
            addOp(14, tempLine);
            printOpToDotObj(obFile, asmValues, tempLine);
            asmValues->IC += 1;
            continue;
        } /* end */

        if(checkWord(ptrLine, "stop")){

            opCode *tempLine = resultList();
            addOp(15, tempLine);
            printOpToDotObj(obFile, asmValues, tempLine);
            asmValues->IC += 1;
            continue;
        } /* end */

        /* calculate for instructions with 1 operand */
        for(i = 0 ; i < OP1_LENGTH ; i++){

            if(checkWord(ptrLine, op1[i])){

                ptrLine += strlen(op1[i]);
                getOp1(obFile, extFile, asmValues, symbolLineStart, ptrLine, i, error, countLines);
                op1Flag = 1;
                break;
            } /* end */
        } /* end loop  */

        if(op1Flag)
            continue;


        /* calculate for instructions with 2 operansds*/
        for(i = 0 ; i < OP2_LENGTH ; i++){

            if(checkWord(ptrLine, op2[i])){

                ptrLine += strlen(op2[i]);
                getOp2(obFile, extFile, asmValues, symbolLineStart, ptrLine, i, error, countLines);
                op2Flag = 1;
                break;
            } /* end */
        } /* end loop */

        if(op2Flag)
            continue;
    }

    if(asmValues->IC - 100 > MAX_LENGTH){

        dataOverbound(error);
    } /* end */

    fclose(amFile);
    fclose(obFile);

    if(ext_Flag)
        fclose(extFile);

    if(ent_Flag)
        fclose(entFile);
}

void editDotObFile(FILE *obFile, data_base *asmValues, headLine *headLineStart, int currentIC){

    dataList *temp = headLineStart->head;

    while(temp != NULL && temp->ic_start == currentIC){

        printOpToDotObj(obFile,asmValues, temp->data);
        asmValues->IC += 1;
        headLineStart->head = headLineStart->head->next;
        free(temp->data);
        free(temp);
        temp = headLineStart->head;
    } /* end loop*/
}

void saveLabelToSymbol(char *line, char *firstLabelName);
void jumpToLabelAddress(char *firstLabelName, int *flag);

void getOp1(FILE *obFile, FILE *extFile, data_base *asmValues, symbolLine *symbolLineStart, char *ptrLine, int commandIndex, int *error, int countLines){

    enum{not = 0, clr, inc, dec, jmp, bne, red, prn, jsr};
    enum{IMMEDIATE = 0, PATH, JUMP, DIRECT_REGISTER}; /* addresses */
    enum{SOURCE = 1, DESTINATION}; /* which starting value  */
    enum{LABEL = 1, REGISTER}; /* which label parameter */
    enum {E = 1, R}; /* which classify */

    int num = 0;
    int ext_Flag = 0; /* equal to 1 if we reach to external file */
    int jumpToAddress = 0; /* equal to 1 if we reach '(' after label name */
    int firstParam = 0;
    int registerFlag = 0; /* equal to 1 if the first parameter in the jump address is register */
    char firstLabelName[MAX_SYMBOL] = {'\0'};
    opCode *tempLine = resultList();

    switch (commandIndex) {

        case not:
            addOp(4, tempLine);
            break;

        case clr:
            addOp(5, tempLine);
            break;

        case inc:
            addOp(7, tempLine);
            break;

        case dec:
            addOp(8, tempLine);
            break;

        case jmp:
            addOp(9, tempLine);
            break;

        case bne:
            addOp(10, tempLine);
            break;

        case red:
            addOp(11, tempLine);
            break;

        case prn:
            addOp(12, tempLine);
            break;

        case jsr:
            addOp(13, tempLine);
            break;

        default:
            break;
    } /* end */

    no_tabs(ptrLine);

    if(*ptrLine == 'r'){

        if(checkRegister(ptrLine[1]) != -1) {

            num = checkRegister(ptrLine[1]);
            addAddress(DESTINATION, DIRECT_REGISTER, tempLine);
            printOpToDotObj(obFile, asmValues, tempLine);
            asmValues->IC += 1;
            setOpCode(tempLine);
            editOpCodeNumbers(tempLine, num, 1);
            printOpToDotObj(obFile, asmValues, tempLine);
            asmValues->IC += 1;
            free(tempLine);
            return;
        } /* end */
    } /* end */

    else if(*ptrLine == '#'){

        ptrLine += 1; /* point to number */
        num = atoi(ptrLine);
        printOpToDotObj(obFile, asmValues, tempLine);
        asmValues->IC += 1;
        setOpCode(tempLine);
        addNumEncode(tempLine, num);
        printOpToDotObj(obFile, asmValues, tempLine);
        asmValues->IC += 1;
        free(tempLine);
        return;
    } /* end else if */

    else {

        saveLabelToSymbol(ptrLine, firstLabelName);
        jumpToLabelAddress(firstLabelName, &jumpToAddress);

        if (!lastLabelChecks(symbolLineStart, firstLabelName, 0, error, countLines)) {

            free(tempLine);
            return;
        } /* end */

        if (jumpToAddress) {

            skipChars(ptrLine);
            ptrLine++;
	    opCode *secondString;
            secondString = resultList();
            opCode *thirdString; 
	    thirdString = resultList();

            addAddress(DESTINATION, JUMP, tempLine);
            editLabelOpcode(symbolLineStart, secondString, firstLabelName, &ext_Flag);

            if(ext_Flag) {

                editDotExt(extFile, firstLabelName, asmValues->IC + 1);
                ext_Flag = 0;
            } /* end */

            while (*ptrLine != '\n' && *ptrLine != '\0') {

                if (*ptrLine == 'r') {

                    if (checkRegister(ptrLine[1]) != -1) {

                        num = checkRegister(ptrLine[1]);

                        if (registerFlag || firstParam) {

                            editValues(REGISTER, 2, tempLine);
                            printOpToDotObj(obFile, asmValues, tempLine);
                            asmValues->IC += 1;
                            printOpToDotObj(obFile, asmValues, secondString);
                            asmValues->IC += 1;

                            if (firstParam) {

                                printOpToDotObj(obFile, asmValues, thirdString);
                                asmValues->IC += 1;
                                setOpCode(thirdString);
                            } /* end */

                            editOpCodeNumbers(thirdString, num, 2);
                            printOpToDotObj(obFile, asmValues, thirdString);
                            asmValues->IC += 1;
                            free(tempLine);
                            free(secondString);
                            free(thirdString);
                            return;
                        } /* end */

                        editValues(REGISTER, 1, tempLine);
                        editOpCodeNumbers(thirdString, num, 1);
                        registerFlag = 1;
                        skipChars(ptrLine); /* skip register */
                        no_tabs(ptrLine);
                        ptrLine += 1; /* skip comma */
                        no_tabs(ptrLine);
                    } /* end */
                } /* end */

                else if (*ptrLine == '#') {

                    ptrLine += 1;
                    num = atoi(ptrLine); /* point to number */

                    if (registerFlag || firstParam) {

                        printOpToDotObj(obFile, asmValues, tempLine);
                        asmValues->IC += 1;
                        printOpToDotObj(obFile, asmValues, secondString);
                        asmValues->IC += 1;
                        printOpToDotObj(obFile, asmValues, thirdString);
                        asmValues->IC += 1;
                        setOpCode(thirdString);
                        addNumEncode(thirdString, num);
                        printOpToDotObj(obFile, asmValues, thirdString);
                        asmValues->IC += 1;
                        free(tempLine);
                        free(secondString);
                        free(thirdString);
                        return;
                    } /* end */

                    addNumEncode(thirdString, num);
                    firstParam = 1;
                    skipChars(ptrLine); /* skip number */
                    no_tabs(ptrLine);
                    ptrLine += 1; /* skip comma */
                    no_tabs(ptrLine);
                } /* end */

                else {

                    saveLabelToSymbol(ptrLine, firstLabelName);

                    if (!lastLabelChecks(symbolLineStart, firstLabelName, 0, error, countLines)) {

                        free(tempLine);
                        free(secondString);
                        free(thirdString);
                        return;
                    } /* end */

                    if (registerFlag || firstParam) {

                        editValues(LABEL, 2, tempLine);
                        printOpToDotObj(obFile, asmValues, tempLine);
                        asmValues->IC += 1;
                        printOpToDotObj(obFile, asmValues, secondString);
                        asmValues->IC += 1;
                        printOpToDotObj(obFile, asmValues, thirdString);
                        asmValues->IC += 1;
                        setOpCode(thirdString);
                        editLabelOpcode(symbolLineStart, thirdString, firstLabelName, &ext_Flag);

                        if(ext_Flag)
                            editDotExt(extFile, firstLabelName, asmValues->IC);

                        printOpToDotObj(obFile, asmValues, thirdString);
                        asmValues->IC += 1;
                        free(tempLine);
                        free(secondString);
                        free(thirdString);
                        return;
                    } /* end */

                    editValues(LABEL, 1, tempLine);
                    editLabelOpcode(symbolLineStart, thirdString, firstLabelName, &ext_Flag);

                    if(ext_Flag) {

                        editDotExt(extFile, firstLabelName, asmValues->IC + 2);
                        ext_Flag = 0;
                    } /* end */

                    firstParam = 1;
                    skipChars(ptrLine); /* skip label */
                    no_tabs(ptrLine);
                    ptrLine += 1; /* skip comma */
                    no_tabs(ptrLine);
                } /* end */
            } /* end loop*/
        } /* end */

        addAddress(DESTINATION, PATH, tempLine);
        printOpToDotObj(obFile, asmValues, tempLine);
        asmValues->IC += 1;
        setOpCode(tempLine);
        editLabelOpcode(symbolLineStart, tempLine, firstLabelName, &ext_Flag);

        if(ext_Flag) {

            editDotExt(extFile, firstLabelName, asmValues->IC);
            ext_Flag = 0;
        } /* end */

        printOpToDotObj(obFile, asmValues, tempLine);
        asmValues->IC += 1;
        free(tempLine);
    } /* end */
}

void getOp2(FILE *obFile, FILE *extFile, data_base *asmValues, symbolLine *symbolLineStart, char *ptrLine, int commandIndex, int *error, int countLines) {

    enum {mov = 0, cmp, add, sub, lea};
    enum {IMMEDIATE = 0, PATH, JUMP, DIRECT_REGISTER}; /* addresses */
    enum {SOURCE = 1, DESTINATION}; /* which starting value*/
    enum {LABEL = 1, REGISTER}; /* which label parameter */

    int num = 0;
    int ext_Flag = 0; /* flag=1 if we in extrn */
    int firstParam = 0;
    int registerFlag = 0; /* flag=1 if register */
    char firstLabelName[MAX_SYMBOL] = {'\0'};
    opCode *firstString = resultList();
    opCode *tempLine = resultList();


    switch (commandIndex) {

        case mov:
            break;

        case cmp:
            addOp(1, firstString);
            break;

        case add:
            addOp(2, firstString);
            break;

        case sub:
            addOp(3, firstString);
            break;

        case lea:
            addOp(6, firstString);
            break;

        default:
            break;
    } /* end */

    no_tabs(ptrLine); /* point to first value */

    while (*ptrLine != '\n' && *ptrLine != '\0') {

        if (*ptrLine == 'r') {

            if (checkRegister(ptrLine[1]) != -1) {

                num = checkRegister(ptrLine[1]);

                if (registerFlag || firstParam) {

                    addAddress(DESTINATION, DIRECT_REGISTER, firstString);
                    printOpToDotObj(obFile, asmValues, firstString);
                    asmValues->IC += 1; /* first value address */

                    if (firstParam) {

                        printOpToDotObj(obFile, asmValues, tempLine);
                        asmValues->IC += 1;
                        setOpCode(tempLine);
                    } /* end */

                    editOpCodeNumbers(tempLine, num, 2);
                    printOpToDotObj(obFile, asmValues, tempLine);
                    asmValues->IC += 1;
                    free(firstString);
                    free(tempLine);
                    return;
                } /* end */

                addAddress(SOURCE, DIRECT_REGISTER, firstString);
                editOpCodeNumbers(tempLine, num, 1);

                registerFlag = 1;
                skipChars(ptrLine); /* skip register */
                no_tabs(ptrLine);
                ptrLine += 1; /* skip comma */
                no_tabs(ptrLine);
            } /* end */
        } /* end */

        else if (*ptrLine == '#') {

            ptrLine += 1; /* point to number */
            num = atoi(ptrLine);

            if (registerFlag || firstParam) {

                printOpToDotObj(obFile, asmValues, firstString);
                asmValues->IC += 1;
                printOpToDotObj(obFile, asmValues, tempLine);
                asmValues->IC += 1;
                setOpCode(tempLine);
                addNumEncode(tempLine, num);
                printOpToDotObj(obFile, asmValues, tempLine);
                asmValues->IC += 1;
                free(tempLine);
                free(firstString);
                return;
            } /* end */

            addNumEncode(tempLine, num);
            firstParam = 1;
            skipChars(ptrLine); /* skip number */
            no_tabs(ptrLine);
            ptrLine += 1; /* skip comma */
            no_tabs(ptrLine);
        } /* end */

        else {

            saveLabelToSymbol(ptrLine, firstLabelName);

            if (!lastLabelChecks(symbolLineStart, firstLabelName, 0, error, countLines)) {

                free(firstString);
                free(tempLine);
                return;
            } /* end */

            if (registerFlag || firstParam) {

                addAddress(DESTINATION, PATH, firstString);
                printOpToDotObj(obFile, asmValues, firstString);
                asmValues->IC += 1;
                printOpToDotObj(obFile, asmValues, tempLine);
                asmValues->IC += 1;
                setOpCode(tempLine);
                editLabelOpcode(symbolLineStart, tempLine, firstLabelName, &ext_Flag);

                if(ext_Flag) {

                    editDotExt(extFile, firstLabelName, asmValues->IC);
                    ext_Flag = 0;
                } /* end */

                printOpToDotObj(obFile, asmValues, tempLine);
                asmValues->IC += 1;
                free(tempLine);
                free(firstString);
                return;
            } /* end */

            addAddress(SOURCE, PATH, firstString);
            editLabelOpcode(symbolLineStart, tempLine, firstLabelName, &ext_Flag);

            if(ext_Flag) {

                editDotExt(extFile, firstLabelName, asmValues->IC + 1);
                ext_Flag = 0;
            } /* end */

            firstParam = 1;
            skipChars(ptrLine); /* skip number */
            no_tabs(ptrLine);
            ptrLine += 1; /* skip comma */
            no_tabs(ptrLine);
        } /* end */
    } /* end loop */
}

