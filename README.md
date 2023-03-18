# Assembler-simulator

******************************* mman14 Project which resmbles an assembly compiler *************************************************
******************************************************10/02/23**********************************************************************
********************************************by Elay Levi & Binyamin Visotski********************************************************
*******************************************(id:206016511)*****(id:316513746)********************************************************
************************************************************************************************************************************
### Instruction:
To run this project
step1: open the folder containing the Makefile and run the ubuntu prompt in it NOTE:you can run "make clean" to clean all(".am",".ob",".ent",".ext") files .
step2: write the command make in prompt to compile the project and get the execute file its namme should be assembler.
step3: to run the executable file correctly choose your ".as" file of choice with the assembly code written in it and write 
in prompt "./assembler ".as file name" "
step4:now u have the result outputs of the assembler HAVE FUN! :D.

------------------
   Information
------------------

### The Assembler:

our assembler first step is to define and initialise all the output files which are of (".am",".ob",".ent",".ext")

###".am":
output will result with the code that the user has inputed after it been proccesed by preassembler.c which spreades the macros written in the code to the code itself for example:

MAIN: mov r3 ,LENGTH				output we get from code above:
LOOP: jmp L1(#-1,r6)				MAIN: mov r3 ,LENGTH
mcr m1						LOOP: jmp L1(#-1,r6)				
sub r1, r4						prn #-5
bne END						bne LOOP(r4,r3)
endmcr						sub r1, r4
prn #-5						bne END
bne LOOP(r4,r3)					L1: inc K
m1							bne LOOP(K,STR)
L1: inc K						END: stop
bne LOOP(K,STR)					STR: .string "abcdef"
END: stop						LENGTH: .data 6,-9,15
STR: .string "abcdef"				K: .data 22
LENGTH: .data 6,-9,15
K: .data 22


###".ent":

this output file saves all the labels that are marked under the ".entry" in the first_pass.c .
and result with:

example:

; file a.as					output:
    .entry LENGTH				LENGTH	130
    .extern W					LOOP		103
MAIN: 	mov r3 ,LENGTH
LOOP: 	jmp L1(#-1,r6)
        prn #-5
        bne W(r4,r5)
        sub r1, r4
        bne L3
L1: 	inc K
    .entry LOOP
        bne LOOP(K,W)
END: 	stop
STR: 	.string "abcdef"
LENGTH: .data 6,-9,15
K: 	    .data 22
    .extern L3



###".ext":
this output file saves all the labels that are marked under the ".extern" in the first_pass.c .
and result with:
example:

; file a.as					output:
    .entry LENGTH				W		110
						L3		115
    .extern W				W		121
MAIN: 	mov r3 ,LENGTH
LOOP: 	jmp L1(#-1,r6)
        prn #-5
        bne W(r4,r5)
        sub r1, r4
        bne L3
L1: 	inc K
    .entry LOOP
        bne LOOP(K,W)
END: 	stop
STR: 	.string "abcdef"
LENGTH: .data 6,-9,15
K: 	    .data 22
    .extern L3

###".ob":
this output file will have the code without the macro lines translated to "," and "/" based on the opcode of the commands that the user inputed and will look like this:

	; file a.as
    .entry LENGTH
    .extern W
MAIN: 	mov r3 ,LENGTH
LOOP: 	jmp L1(#-1,r6)
        prn #-5
        bne W(r4,r5)
        sub r1, r4
        bne L3
L1: 	inc K
    .entry LOOP
        bne LOOP(K,W)
END: 	stop
STR: 	.string "abcdef"
LENGTH: .data 6,-9,15
K: 	    .data 22
    .extern L3

###output:

	0100		........//./..
	0101		....//........
	0102		..../....././.
	0103		..///../../...
	0104		.....///./../.
	0105		////////////..
	0106		.........//...
	0107		....//........
	0108		/////////.//..
	0109		/////./.../...
	0110		............./
	0111		.../....././..
	0112		......//////..
	0113		...../.../....
	0114		...././..../..
	0115		............./
	0116		.....///.../..
	0117		..../...././/.
	0118		././/./.../...
	0119		.....//..////.
	0120		..../...././/.
	0121		............./
	0122		....////......
	0123		.......//..../
	0124		.......//.../.
	0125		.......//...//
	0126		.......//../..
	0127		.......//.././
	0128		.......//..//.
	0129		..............
	0130		...........//.
	0131		//////////.///
	0132		..........////
	0133		........././/.

---------------------------------------------------
      general explanation of project functions
---------------------------------------------------

$$$assembler.c$$$
this part of the program is in charge of:
1)creation of files .
2)calling all other steps in the program in alignment
for further proccesing steps .

$$$preassembler.c$$$
this part of the program is in charge of:
1)searching for macros in the from the ".as" file .
2)spreading the macro in the of the original code.
3)writing to the ".am" the wanted out put of ".as" without macros shortcuts.

$$$preassemblerUtilities.c$$$
most of the calculations of preassembler will happen here.


$$$first_step.c$$$
this part of the program is in charge of:
1)proccessing the ".am" file to check for ".entry" and ".extern" labels in the code and save them 
in the designated files in ".ent" and ".ext"
2)save all labels in the designated files 

$$$onePassUtilities.c$$$
most of the calculations of first step will happen here.


$$$second_step.c$$$
1)check if the assembly code is written correctly
2)call for a function to turn it to the opcode following the mman 14 instructions with 14 bits of opcode in binary
3)turn the opcode to the "," "/" schematic and save it in the ".ob" file

$$$secondPassUtilities.c$$$
has few process for second pass.


$$$error_case.c$$$
is accountable for all the error cases in the code when we spot an error in one of the steps it will jump
to this program file and result with the error of the particular case in the steps that called it.

$$$memory_utilities$$$
is accountable for all data saves and further usfull functions of calculating different values
 that we use in the different steps of the code.


$$$opcode.c$$$
as the name says this part of the code is where we calculate the opcode for 14 bit as asked in mman14 

-----------------------------
       ".h" files 
-----------------------------
$$$defined.h$$$
is the most important ".h" file which contanes all the defined values that we use in the code and is used in all parts of the code
it contanes the c librarys that we use in the code as well.
------
all other .h files have a more indepth explanation of which functions we use in the code
and theyre coorolation.





PS: now that you read all the README file you can start compiling GoodLuck.










