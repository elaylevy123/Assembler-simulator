/*"******************************* mman14 Project which resmbles an assembly compiler *************************************************
******************************************************10/02/23**********************************************************************
********************************************by Elay Levi & Binyamin Visotski********************************************************
*******************************************(id:206016511)*****(id:316513746)********************************************************
***********************************************************************************************************************************"*/
#include "preassembler.h"

void no_spaces(char *pointer);
void no_tabs(char *pointer);

void openMcr(char *amFileName, char *asFileName, int *error){

    FILE *amFile = NULL;
    FILE *asFile = NULL;
    char line [MAX_LINE]= {'\0'};
    char mcrName[MAX_LINE] = {'\0'};
    char copyLine [MAX_LINE]= {'\0'};
    int firstString = -1 ; /* the position of amFile using ftell() */
    int numberOfLines = 0; /* number of lines in macro */
    int inMcr = 0, skipMcr = 0; /* when we in the macro flag will be up */
    int countLines = 0;
    mcrHead *mcr = createMcrList(); /* head of macro */

    if(!(amFile = fileNotCreated(amFile, amFileName, "w+", error)))
        return;

    if(!(asFile = fileNotCreated(asFile, asFileName, "r+", error)))
        return;

    while (fgets(line, MAX_LINE, asFile) != NULL) { /* check all the .as file till the end */

        char *ptrLine = line;
        fpos_t pos;
        fgetpos(asFile, &pos);
        strcpy(copyLine, line);
        countLines++;

        no_tabs(ptrLine);
        /* if we get to macro  */
        if (goodMcr (ptrLine, "mcr")) {

            ptrLine += 3;
            no_spaces(ptrLine); /* take the name of the macro */

            if (!badName(ptrLine)){

                inMcr = 1;
                skipMcr = 1;

                if (firstString == -1)
                    firstString = (int) ftell(asFile); /* save all the file code which is not the macro  */

                strcpy(mcrName, ptrLine);
                continue;
            } /* end */

            badMcr(error, countLines);
            continue;
        } /* end */

        /* end of macro */
        if (goodMcr (ptrLine, "endmcr") && inMcr) {

            inMcr = 0;
            addMcrList(mcr, mcrName, firstString, numberOfLines);
            numberOfLines = 0;
            firstString = -1 ;
            continue;
        } /* end */

        /* in found macro */
        if (inMcr) {

            numberOfLines++;
            continue;
        } /* end */

        if (skipMcr) {

            if (checkMcr(mcr, ptrLine, amFile, asFile)) {

                fsetpos(asFile, &pos);
                continue;
            } /* end */
        } /* end */

        fputs(copyLine, amFile);
    } /* end loop */

    freeMcrTbl(mcr);
    fclose(amFile);
    fclose(asFile);

}

int checkMcr(mcrHead *mcr, char *line, FILE *amFile, FILE *source){

    int i = 0;
    char copyLine[MAX_LINE] = {'\0'};
    mcrList *temp = mcr->head;

    while(temp != NULL){

        if(goodMcr(line, temp->mcrName)){

            fseek(source, temp->mcrLocation, SEEK_SET); /* pointer to start of macro */

            while(i < temp->numberOfLines){

                fgets(copyLine, MAX_LINE, source);
                fputs(copyLine, amFile);
                i++ ;
            } /* end loop */
            return 1;
        } /* end */
        temp = temp->next;
    } /* end loop */

    return 0;
}

int goodMcr (char *line, char *word){

    int i = 0;
    int charCount = 0;
    int nameLength = strlen(word);

    while((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z') || (line[i] >= '0' && line[i] <= '9') || line[i] == '#' || line[i] == '.' ){

        charCount++;
        i++;
    } /* end loop */

    if(nameLength != charCount)
        return 0;

    if(strncmp(line, word, charCount) == 0)
        return 1;

    return 0;
}




