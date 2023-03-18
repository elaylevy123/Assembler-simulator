

#ifndef MAMAN14_PRE_ASM_H
#define MAMAN14_PRE_ASM_H

#include "memory_utilities.h"
#include "error_case.h"
#include "assembler.h"

/* skip spaces and tabs */
void no_tabs(char *pointer);
/* remove all spaces  */
void no_spaces(char *pointer);
/* process to open the macros */
void openMcr(char *amFileName, char *asFileName, int *error);
/* check the code for macro instances to spread the code */
int checkMcr(mcrHead *mcr, char *line, FILE *asFile, FILE *source);
/* check if we are in the macro */
int goodMcr (char *line, char *word);

#endif /*MAMAN14_PRE_ASM_H*/
