#include "lib/io_interrup.h"
#include "lib/utils/math.h"
#include "lib/io.h"
#include "lib/alloc/allocatore.h"

#include "lib/cli/shell.h"

void main (){
	//startVGA();
//	infoAlloc();

//	int *a = (int *)alloc(3);
//	free(a);

	while (1){
		char buffer[128];
		printchar('#', VGA_TEXT_BIANCO_NERO);
		input(buffer, 0x39, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
		CLIparser(buffer);
	}
	while(1){	__asm__("hlt");};
}
