#include "struct.h"

#include "comandi_integrati/helpCli.h"
#include "comandi_integrati/ioCli.h"
#include "comandi_integrati/videoCli.h"
#include "comandi_integrati/allocCli.h"
#include "comandi_integrati/kernelCli.h"
#include "comandi/editor.h"

Comando comandi[] = {
	{"help", helpCli},
	{"inb", inbCli}, {"outb", outbCli}, {"clear", clearCli}, /*I/O*/
	{"sys", kernelCli}, /*Kernel*/
	{"alloc", allocCli}, {"free", freeCli}, {"alloctab", tabellaAllocatoreCli}, /*Alloc*/
	{"video", videoCli}, /*Video Mode*/
	{"editor", editor}
};

bool CLIparser(char *buffer){
	unsigned int contatore_buffer = 0;	
	while (buffer[contatore_buffer] != '\0'){	contatore_buffer++;}
	for (unsigned int contatore_comandi = 0; contatore_comandi < (sizeof(comandi) / sizeof(comandi[contatore_comandi])); contatore_comandi++){
			unsigned int caratteri_giusti = 0;
			while(comandi[contatore_comandi].nome_comando[caratteri_giusti] == buffer[caratteri_giusti]){
				if (caratteri_giusti == contatore_buffer){
					comandi[contatore_comandi].funzione();
					return true;
				}
				caratteri_giusti++;
			}	
	}
	print("\nCOMANDO INVALIDO", VGA_TEXT_ROSSO_NERO);
	return false;
}

bool CLIparserGenerico (char *buffer, Comando *comandi, int sizeComandi){
	unsigned int contatore_buffer = 0;	
	while (buffer[contatore_buffer] != '\0'){	contatore_buffer++;}
	for (unsigned int contatore_comandi = 0; contatore_comandi < sizeComandi; contatore_comandi++){
			unsigned int caratteri_giusti = 0;
			while(comandi[contatore_comandi].nome_comando[caratteri_giusti] == buffer[caratteri_giusti]){
				if (caratteri_giusti == contatore_buffer){
					comandi[contatore_comandi].funzione();
					return true;
				}
				caratteri_giusti++;
			}	
	}
	print("\nCOMANDO INVALIDO", VGA_TEXT_ROSSO_NERO);
	return false;
}
