#include "lib/io_interrup.h"

#include "lib/utils/conversioni.h"
#include "lib/utils/math.h"
#include "lib/utils/string.h"

#include "lib/io.h"

#include "lib/kernel/panic.h"
#include "lib/kernel/reboot.h"

#include "lib/alloc/allocatore.h"


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
#include "lib/fs/filesystem.h"

#include "lib/cli/shell.h"

void main (){
	clear();
//	startVGA();

	infoAlloc();

//	int *a = (int *)alloc(3);
//	free(a);

	unsigned int tipo_disco = tipo_unita_montata();
	/*char buffer[512];
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);	
	scrivi_settore(0x01, 9, buffer, 0x00);*/

	printchar('\n' ,VGA_TEXT_BIANCO_NERO);
	
	/*if (!cerca_settore_info(tipo_disco)){
		info_settore.tipo_filesystem = "seq";
		info_settore.visualizza_msg_allocatore = true;
		info_settore.ultimo_settore_scritto_lba28 = 10;
		info_settore.ultimo_settore_scritto_lba48_mrb = 0;
		info_settore.ultimo_settore_scritto_lba48_lrb = 100;

		crea_settore_info(tipo_disco);
	}*/
//	crea_bitmap();	
	//char buffer[10] = "ciao";
	//scrivi_settore(0x01, 1, buffer, 0xbb);
	
	/*for(;;){
		clear();
		printint(cerca_settore_libero(0, 0, 0), VGA_TEXT_BIANCO_NERO);
		char buffers[2];
		input(buffers, 0x1c, sizeof(buffers), VGA_TEXT_BIANCO_NERO);
		char buffer[512];
		input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
		crea_file(0xbb, "file.txt", buffer);
	}*/

	/*char buffer[512];
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
	crea_file(0xbb, "file.txt", buffer);*/
	/*print(settore, VGA_TEXT_BIANCO_NERO);*/

	/*scrivi_settore(0x01, 1, "ciao", 0xbb);
	char buffer_l[512];
	while (1){
		leggi_settore(0x01, 1, buffer_l, sizeof(buffer_l));
		print(buffer_l, VGA_TEXT_BIANCO_NERO);
		char buffers[2];
		input(buffers, 0x1c, sizeof(buffers), VGA_TEXT_BIANCO_NERO);
	}*/
//	printint('\n', VGA_TEXT_BIANCO_NERO);
//	printint(cerca_file(0xbb, "file\0"), VGA_TEXT_BIANCO_NERO);

	while (1){
		char buffer[128];
		printchar('#', VGA_TEXT_BIANCO_NERO);
		input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
		CLIparser(buffer);
	}

	while(1){	
		panic("Errore Fatale!");
		__asm__("hlt");
	};
}
