#include "lib/io_interrup.h"

#include "lib/utils/conversioni.h"
#include "lib/utils/math.h"
#include "lib/utils/string.h"

#include "lib/io.h"

#include "lib/kernel/panic.h"

#include "lib/alloc/allocatore.h"

#include "lib/cli/shell.h"

#include "lib/fs/selettore_unita.h"
#include "lib/fs/io_settore.h"

struct{
	char *tipo_filesystem;
	bool visualizza_msg_allocatore;
	unsigned long int ultimo_settore_scritto_lba28;
	
	unsigned long int ultimo_settore_scritto_lba48_mrb;
	unsigned long int ultimo_settore_scritto_lba48_lrb;
}info_settore;

#include "lib/fs/settore_info.h"



void main (){
	clear();
//	startVGA();

	infoAlloc();

//	int *a = (int *)alloc(3);
//	free(a);

	tipo_unita_montata();
/*	char buffer[512];
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);	
	scrivi_settore(0x01, 1, buffer, 0x02);*/

	printchar('\n' ,VGA_TEXT_BIANCO_NERO);
	
	bool settore_info = cerca_settore_info(0x01);
	if (!settore_info){
		info_settore.tipo_filesystem = "seq";
		info_settore.visualizza_msg_allocatore = true;
		info_settore.ultimo_settore_scritto_lba28 = 100;
		info_settore.ultimo_settore_scritto_lba48_mrb = 0;
		info_settore.ultimo_settore_scritto_lba48_lrb = 100;

		//crea_settore_info(0x01);
	}

	printint(settore_info, VGA_TEXT_BIANCO_NERO);

	//print(info_settore.tipo_filesystem, VGA_TEXT_BIANCO_NERO);

	char settore[512];
	leggi_settore(0x01, 1, settore, sizeof(settore));
	for (unsigned int carattere_settore = 0; carattere_settore < 512; carattere_settore++){
		printhex(settore[carattere_settore], VGA_TEXT_BIANCO_NERO);
		print(", ", VGA_TEXT_BIANCO_NERO);
	}

	/*char settore[512];
	leggi_settore(0x01, 1, settore, sizeof(settore));
	print(settore, VGA_TEXT_BIANCO_NERO);*/

	while (1){
		char buffer[128];
		printchar('#', VGA_TEXT_BIANCO_NERO);
		input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
		CLIparser(buffer);
	}

	while(1){	__asm__("hlt");};
}
