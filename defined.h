/*"******************************* mman14 Project which resmbles an assembly compiler *************************************************
******************************************************10/02/23**********************************************************************
********************************************by Elay Levi & Binyamin Visotski********************************************************
*******************************************(id:206016511)*****(id:316513746)********************************************************
***********************************************************************************************************************************"*/

#ifndef MAMAN14_CONSTANT_H
#define MAMAN14_CONSTANT_H
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/* this part of the code has all the defined paramaters that will be used in the steps of 
proccessing in the code*/

/* max number of cells */
#define MAX_LENGTH 255
/* max number of chars */
#define MAX_LINE 82
/* max number of symbols */
#define MAX_SYMBOL 31
/* 9 bits of opcode */
#define MAX_TYPE 9
/* 4 bits of directives */
#define MAX_DIRECTIVES 4
/* number of instruction */
#define MAX_INSTRUCTIONS 16
/* number of registers */
#define MAX_REGISTERS 8
/* opcode length */
#define OP1_LENGTH 9
#define OP2_LENGTH 5

#endif /*MAMAN14_CONSTANT_H*/
