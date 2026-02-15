#include "lib/io_interrup.h"

#include "lib/utils/conversioni.h"
#include "lib/utils/math.h"

#include "lib/io.h"
#include "lib/alloc/allocatore.h"

#include "lib/cli/shell.h"

//SelezioneComando selez[] = {{"ciao", VGA_TEXT_BIANCO_NERO}, {"ciao2", VGA_TEXT_ROSSO_NERO}};

void main (){
	clear();
//	startVGA();

//	infoAlloc();

//	int *a = (int *)alloc(3);
//	free(a);
	
	//printint(multiInput(selez, (sizeof(selez) / sizeof(selez[0])),VGA_TEXT_BIANCO_NERO), 0x7);

	while (1){
		char buffer[128];
		printchar('#', VGA_TEXT_BIANCO_NERO);
		input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
		CLIparser(buffer);
	}

	while(1){	__asm__("hlt");};
}
