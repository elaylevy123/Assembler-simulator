/*"******************************* mman14 Project which resmbles an assembly compiler *************************************************
******************************************************10/02/23**********************************************************************
********************************************by Elay Levi & Binyamin Visotski********************************************************
*******************************************(id:206016511)*****(id:316513746)********************************************************
***********************************************************************************************************************************"*/
#include "error_case.h"

void memoryError(void){

    printf("ERROR : You have memory allocation error.\n");
    exit(0);
}

void chkNumArgs (int args){
    if (args < 2){
        printf("ERROR : You should have a file name.\n ");
        exit(0);
    } /* end if */
}

FILE *fileNotCreated(FILE *fd, char *fileToOpen, char *mode, int *error){

    if (!(fd = fopen(fileToOpen, mode))) {

        printf("ERROR : the file %s does'nt exist.\n", fileToOpen);
        *error = 1;
        return NULL;
    } /* end if */
    return fd;
}

void badLabelName(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("can't use registers, commands, instruction and any other character except (A-Z or a-z or 0-9) in labels \n\n\n");
    *error = 1;
}

void chkLineLen(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("The line is to long.\n NOTE: max is 81 charachters.\n\n");
    *error = 1;
}

void LabelToLong(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("The label is to long.\n NOTE: max is 30 charachters.\n\n");
    *error = 1;
}

void badMcr(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("can't use registers, commands, instruction and any other character except (A-Z or a-z or 0-9) in macros \n\n\n");
    *error = 1;
}

void noSpace(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("No spaces after instruction.\n\n");
    *error = 1;
}

void noParameter(int * error, int line){

    printf("Error in line : %d\n", line);
    printf("Should be a register defined after instruction.\n\n");
    *error = 1;
}

void spacedLabel(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("Cant have spaces in the label name.\n\n");
    *error = 1;
}

void existingLabelName(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("label name already exsisting and defined.\n\n");
    *error = 1;
}

void textOverBound(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("Text overbound.\n\n");
    *error = 1;
}

void unDefienedcommand(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("Undefined command.\n\n");
    *error = 1;
}

void undefinedInstruction(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("Undefined instruction .\n\n");
    *error = 1;
}

void badComma(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("bad comma spot.\n\n");
    *error = 1;
}

void invalidDataParam(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("Only positive and negative integers allowed.\n\n");
    *error = 1;
}

void badString(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("bad string NOTE: whould start with \" and end with \" .\n \n");
    *error = 1;
}

void toManyCommas(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("To many commas.\n\n");
    *error = 1;
}

void noComma(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("no comma.\n\n");
    *error = 1;
}

void dumpLabel(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("Dumped Label \n NOTE: needs to be within .extrn or .entry .\n\n");
    *error = 1;
}

void badValue(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("bad value.\n\n");
    *error = 1;
}

void badNumber(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("Bad number definment should start with '#' and should be any negative or positive integer number and \n");
    *error = 1;
}

void badRegister(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("Bad Register should start with an 'r' and max 8 registers 0-7.\n\n");
    *error = 1;
}

void dataOverbound(int *error){

    printf("ERROR : Program data is overbound the program is to large.\n\n");
    *error = 1;
}

void unDefienedLabel(int *error, int line){

    printf("Error in line : %d\n", line);
    printf("Wrong definment of label or does'nt exist in the list  \n\n\n");
    *error = 1;
}

void extCantBeEnt(int *error, int line){

    printf("Error in line : %d\n", line);
    printf(".extern can't be .entry  .\n\n");
    *error = 1;
}
