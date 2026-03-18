#include "lib/io_interrup.h"

#include "lib/utils/conversioni.h"
#include "lib/utils/math.h"

#include "lib/io.h"

#include "lib/kernel/panic.h"

#include "lib/alloc/allocatore.h"

#include "lib/cli/shell.h"

#include "lib/fs/selettore_unita.h"
#include "lib/fs/io_settore.h"

void main (){
	clear();
//	startVGA();

	infoAlloc();

//	int *a = (int *)alloc(3);
//	free(a);

	tipo_unita_montata();
/*	char buffer[512];
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
	scrivi_settore(0x01, 1, buffer, 0x00);

	printchar('\n' ,VGA_TEXT_BIANCO_NERO);

	char settore[512];
	leggi_settore(0x01, 1, buffer, sizeof(buffer));
	print(buffer, VGA_TEXT_BIANCO_NERO);
*/
	while (1){
		char buffer[128];
		printchar('#', VGA_TEXT_BIANCO_NERO);
		input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
		CLIparser(buffer);
	}

	while(1){	__asm__("hlt");};
}
