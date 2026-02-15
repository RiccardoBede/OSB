//DEFINE STATI UNITA IDE_ATA
#define ATA_BUSY 0x80
#define ATA_DEVICE_READY 0x40
#define ATA_ERROR 0x01
#define ATA_RICHIESTA_COMANDO_OK 0x08

//DEFINE COMANDI IDE_ATA DISCO
#define ATA_INDENTIFICA 0xec
#define ATA_LEGGI_SETTORE 0x20
#define ATA_SCRIVI_SETTORE 0x30
#define ATA_FLUSH_CACHE 0xe7

//DEFINE COMANDI IDE_ATAPI (CD, DVD)
#define ATAPI_IDENTIFICA 0x51
#define ATAPI_READY 0x00

#define ATAPI_MONTA_SMONTA 0xa6
#define ATPI_VELOCITA_DISCO 0xbb


#define ATAPI_LEGGI_BUFFER 0x3c
#define ATAPI_SCRIVI_BUFFER 0x3b

typedef enum {
	NESSUN_DISCO = 0x00,
	DISCO_ATA = 0x01,
	DISCO_ATAPI = 0x02
}DISCO_MONTATO; //per poi vedere quali set di funzioni unsare per scrivere sui dischi

struct ATA_IDENTIFICA {
	char numeroSerie[10];
	char versioneFirmware[4];
	char modello[20];
	//settori totali LBA32 FARE ALLOC
	bool falgLBA48;
	//settori totali LBA48 FARE ALLOC
};

struct ATAPI_IDENTIFICA {};

//porta default del controller
unsigned short porta_controller_default = 0x1f7;

DISCO_MONTATO cambia_unita (){
	unsigned int tentativi_lettura = 0;
	while (tentativi_lettura < 10){
		unsigned int attesa_busy = 0;
		while (attesa_busy < 256){
			if (!(inb(porta_controller_default) & ATA_BUSY)){
				//ATA_IDE
				outb(porta_controller_default, ATA_INDENTIFICA);
				if (inb(porta_controller_default) & ATA_RICHIESTA_COMANDO_OK){	return 0x01;}
				//ATAPI
				outb(porta_controller_default, ATAPI_IDENTIFICA);
				if (inb(porta_controller_default) & ATAPI_READY){	return 0x02;}
			}
			attesa_busy++;
		}
		tentativi_lettura++;
	}
	print("UNITA' DISCO (ATA/IDE) NON TROVATO ALLA PORTA DEFAULT (0x1f7)\n", VGA_TEXT_GIALLO_NERO);
	if (monoInput("Cambiare porta [y/n]?", 0x15, 0x31, VGA_TEXT_GIALLO_NERO)){
		print("\nPorta: 0x", VGA_TEXT_BIANCO_NERO);
		char porta[8];
		input(porta, 0x1c, sizeof(porta), VGA_TEXT_BIANCO_NERO);
		porta_controller_default = stringa_to_unsigned_short(porta);
		printchar('\n', VGA_TEXT_BIANCO_NERO);
		cambia_unita();
	}else{
		return 0x00;
	}
}

void identifica_unita (){
	DISCO_MONTATO tipo_unita = cambia_unita();
	print("UNITA' ARCHIVIAZIONE ", VGA_TEXT_BIANCO_NERO);
	switch (tipo_unita){
		case NESSUN_DISCO:
			print("<NULL>\n", VGA_TEXT_ROSSO_NERO);
			break;
		case DISCO_ATA:
			print("<ATA/IDE>\n", VGA_TEXT_VERDE_NERO);
			break;
		case DISCO_ATAPI:
			print("<ATAPI>\n", VGA_TEXT_VERDE_NERO);
			break;
	}
}
