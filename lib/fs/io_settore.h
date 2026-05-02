#define SIZE_SETTORE 512

extern bool lba48_attivo;
extern unsigned long int settori_lba32;
extern struct settori_lba48;
extern unsigned short porta_controller_default;

typedef struct{
	char primo_byte;
	char secondo_byte;
}ByteSettore __attribute__((packed));

void outw_d (unsigned short porta, ByteSettore buffer){
	__asm__ ("outw %0, %1" :: "a" (buffer), "dN" (porta));
}

ByteSettore inw_d (unsigned short porta){
	ByteSettore buffer;
	unsigned short valore;
	__asm__ ("inw %%dx, %%ax" : "=a" (valore) : "dN" (porta));

	buffer.primo_byte = valore & 0xff;
        buffer.secondo_byte = (valore >> 8) & 0xff;

	return buffer;
}

typedef enum{
	SETTORE_NORMALE = 0x00,
	SETTORE_AVVIABILE = 0x01,
	SETTORE_INFO = 0x02,
	SETTORE_BITMAP = 0x03
}TIPO_SETTORE;

bool scrivi_settore (DISCO_MONTATO tipo_disco, unsigned long int numero_settore, unsigned char *buffer, TIPO_SETTORE tipo_settore){
	//magari fare un extern da selettore_unita e fare verifca se 
	//il tipo_disco è uguale, altrimenti scrivi su tipo_disco
	bool firma = false;
	if (tipo_disco > 0x00){	
		tipo_disco -= 0x01;
	}else{
		return false;
	}

	unsigned long int caratteri_buffer = 0;
	ByteSettore carattere_buffer_per_settore;
	unsigned short int conta_carattere_settore = 0;

	while (buffer[caratteri_buffer] != '\0'){	caratteri_buffer++;}

	if (!lba48_attivo){
		while(inb(porta_controller_default) & ATA_BUSY);

		while(!(inb(porta_controller_default) & ATA_DEVICE_READY));

		outb((porta_controller_default - 0x05), numero_settore);

		outb((porta_controller_default - 0x04), (numero_settore << 0) & 0xff);
		outb((porta_controller_default - 0x03), (numero_settore << 8) & 0xff);
		outb((porta_controller_default - 0x02), (numero_settore << 16) & 0xff);

		outb((porta_controller_default - 0x01), ATA_ACCESSO_DISCO | ((tipo_disco & 1) << 4) | ((numero_settore >> 24) & 0x0f));
	
		outb(porta_controller_default, ATA_SCRIVI_SETTORE);

		while(!(inb(porta_controller_default)) & ATA_BUSY);
		
		while (conta_carattere_settore < SIZE_SETTORE * 1){

			if (tipo_settore == SETTORE_INFO && firma == false){
				carattere_buffer_per_settore.primo_byte = 0xff;
				carattere_buffer_per_settore.secondo_byte = 0xff;

				outw_d((porta_controller_default - 0x07), carattere_buffer_per_settore);
				firma = true;
			}

			if (tipo_settore == SETTORE_NORMALE && firma == false){
				carattere_buffer_per_settore.primo_byte = 0xbb;
				carattere_buffer_per_settore.secondo_byte = 0xbb;

				outw_d((porta_controller_default - 0x07), carattere_buffer_per_settore);
				firma = true;
			}

			if (tipo_settore == SETTORE_BITMAP && firma == false){
				carattere_buffer_per_settore.primo_byte = 0xbf;
				carattere_buffer_per_settore.secondo_byte = 0xbf;

				outw_d((porta_controller_default - 0x07), carattere_buffer_per_settore);
				firma = true;
			}

			if (conta_carattere_settore <  (caratteri_buffer - 0)){
				carattere_buffer_per_settore.primo_byte = buffer[conta_carattere_settore];
				carattere_buffer_per_settore.secondo_byte = buffer[conta_carattere_settore+=1];

				outw_d((porta_controller_default - 0x07), carattere_buffer_per_settore);
			}else{
				carattere_buffer_per_settore.primo_byte = 0x00;
				carattere_buffer_per_settore.secondo_byte = 0x00;

				outw_d((porta_controller_default - 0x07), carattere_buffer_per_settore);	
			}
			conta_carattere_settore++;
		}
		outb(porta_controller_default, ATA_FLUSH_CACHE);
	}else{
	
	}
}

bool leggi_settore (DISCO_MONTATO tipo_disco, unsigned long int numero_settore, unsigned char *buffer, int sizeof_buffer){
	if (tipo_disco > 0x00){
		tipo_disco -= 0x01;
	}else{
		return false;
	}
	
	ByteSettore carattere_buffer_per_settore;
	unsigned short int conta_carattere_settore = 0;
	
	if (!lba48_attivo){
		while(inb(porta_controller_default) & ATA_BUSY);

		while(!(inb(porta_controller_default) & ATA_DEVICE_READY));

		outb((porta_controller_default - 0x05), numero_settore);

		outb((porta_controller_default - 0x04), (numero_settore << 0) & 0xff);
		outb((porta_controller_default - 0x03), (numero_settore << 8) & 0xff);
		outb((porta_controller_default - 0x02), (numero_settore << 16) & 0xff);

		outb((porta_controller_default - 0x01), ATA_ACCESSO_DISCO | ((tipo_disco & 1) << 4) | ((numero_settore >> 24) & 0x0f));
	
		outb(porta_controller_default, ATA_LEGGI_SETTORE);

		while(!(inb(porta_controller_default)) & 0x08);
		
		while (conta_carattere_settore < SIZE_SETTORE * 2){
			ByteSettore carattere_settore = inw_d((porta_controller_default - 0x07));
			
			printhex(carattere_settore.primo_byte, VGA_TEXT_VERDE_NERO);
			printhex(carattere_settore.secondo_byte, VGA_TEXT_ROSSO_NERO);
			
			if (conta_carattere_settore < sizeof_buffer){
				buffer[conta_carattere_settore] = carattere_settore.primo_byte;
			}
			
			conta_carattere_settore++;

			if (conta_carattere_settore < sizeof_buffer){
				buffer[conta_carattere_settore] = carattere_settore.secondo_byte;
			}
			conta_carattere_settore++;
		}
		outb(porta_controller_default, ATA_FLUSH_CACHE);
		buffer[sizeof_buffer-1] = '\0';
	}else{
	
	}
}
