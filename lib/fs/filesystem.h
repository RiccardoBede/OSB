extern bool lba48_attivo;
extern unsigned long int settori_lba32;
extern struct settori_lba48;
extern unsigned short porta_controller_default;

//creare funzione di settore_info per indicizzare in ram i file
//per rendere i/o più veloce (tramite struct)


bool crea_file (DISCO_MONTATO tipo_disco, char *nome_file, char *buffer, TIPO_SETTORE tipo_settore){
	//nome_file max 16
	//
	//firma_tipo_settore;nome_file;
	//	buffer;
	//ultimi 16 + 2 byte da mettre firma JMP e numero settore jmp

	//verificare la grandezza del buffer per immettere un jmp and un altro settore 
	//(firmaJMP;numero_settore) alla fine del settore inizializzato o meno.
	//
}

//creare funzione elimina file, formatta disco
