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
#define ATAPI_IDENTIFICA 0xa1
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

bool lba48_attivo = false;
unsigned long int settori_lba32 = 0;
struct {
	unsigned long int mrb_settori_lba48; //most relevant bit
	unsigned long int lrb_settori_lba48; //less relevant bit
}settori_lba48;

//porta default del controller
unsigned short porta_controller_default = 0x1f7;

DISCO_MONTATO monta_unita (){
	unsigned int tentativi_lettura = 0;
	while (tentativi_lettura < 10){
		unsigned int attesa_busy = 0;
		while (attesa_busy < 256){
			if (!(inb(porta_controller_default) & ATA_BUSY)){
				//ATA_IDE
				outb(porta_controller_default, ATA_INDENTIFICA);

				if (inb(0x1f2) == 0x01 && inb(0x1f3) == 0x01 && inb(0x1f4) == 0x14 && inb(0x1f5) == 0xeb){	return 0x02;}	

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
		monta_unita();
	}else{
		printchar('\n', VGA_TEXT_BIANCO_NERO);
		return 0x00;
	}
}

void identifica_unita (){
	//monta_unita();
	unsigned char lista_identify[256];
	unsigned int carattere = 0;

	for (carattere; carattere < 256; carattere++){
		lista_identify[carattere] = inw(porta_controller_default - 0x07);
	}
	carattere = 0;
	while (carattere < sizeof(lista_identify)){
		if (carattere >= 10 && carattere < 19){	
			if (carattere == 10){	print("Numero disco: ", VGA_TEXT_BIANCO_NERO);}
			printchar(lista_identify[carattere], VGA_TEXT_BIANCO_NERO);
		}
		if (carattere >= 23 && carattere < 26){	
			if (carattere == 23){	print("\nVersione firmware: ", VGA_TEXT_BIANCO_NERO); carattere++;}
			printint(lista_identify[carattere], VGA_TEXT_BIANCO_NERO);
		}
		if (carattere >= 26 && carattere < 46){
			if (carattere == 26){	print("\nModello: ", VGA_TEXT_BIANCO_NERO); carattere++;}
			printchar(lista_identify[carattere], VGA_TEXT_BIANCO_NERO);
		}
		if (carattere == 60){
			print("\nSettori (LBA28): ", VGA_TEXT_BIANCO_NERO);
			settori_lba32 = (unsigned long int)(((unsigned long)lista_identify[61] << 16) | (unsigned long)lista_identify[60]);
			printint(settori_lba32, VGA_TEXT_BIANCO_NERO);			
			//funzione per alloc della grandezza dell'unita	
		}
		if (carattere == 84){
			print("\nSupporto (LBA48): ", VGA_TEXT_BIANCO_NERO);
			if (lista_identify[carattere] == 0x00){
				print("<NO SUPP>", VGA_TEXT_ROSSO_NERO);
			}else{
				print("<SUPP>", VGA_TEXT_VERDE_NERO);
				lba48_attivo = true;
				//mettere bool per flag da allegare alla funzione per trovare la grandezza
				//del disco (che fa sia lba28 che lba48)
			}
		}
		if (carattere == 100){
			print("\nSettori (LBA48): ", VGA_TEXT_BIANCO_NERO);
			if (lista_identify[carattere] == 0x00){
				print("<NO SUPP>", VGA_TEXT_ROSSO_NERO);
			}else{
				//funzione per alloc della granedzza dell'unita (103-102 101-100)
				settori_lba48.mrb_settori_lba48 = (unsigned long int)(((unsigned long)lista_identify[103] << 16) | (unsigned long)lista_identify[102]), VGA_TEXT_BIANCO_NERO;
				settori_lba48.lrb_settori_lba48 = (unsigned long int)(((unsigned long)lista_identify[101] << 16) | (unsigned long)lista_identify[100]), VGA_TEXT_BIANCO_NERO;

				printint(settori_lba48.mrb_settori_lba48, VGA_TEXT_BIANCO_NERO);
				if (settori_lba48.mrb_settori_lba48 != settori_lba48.lrb_settori_lba48){
					printint(settori_lba48.lrb_settori_lba48, VGA_TEXT_BIANCO_NERO);
				}

			}
			printchar('\n', VGA_TEXT_BIANCO_NERO);
			break;
		}
		carattere++;
	}
	
}

void tipo_unita_montata (){
	DISCO_MONTATO tipo_unita = monta_unita();
	print("UNITA' ARCHIVIAZIONE ", VGA_TEXT_BIANCO_NERO);
	switch (tipo_unita){
		case NESSUN_DISCO:
			print("<NULL>\n", VGA_TEXT_ROSSO_NERO);
			break;
		case DISCO_ATA:
			print("<ATA/IDE>\n", VGA_TEXT_VERDE_NERO);
			identifica_unita();
			break;
		case DISCO_ATAPI:
			print("<ATAPI>\n", VGA_TEXT_VERDE_NERO);
			break;
	}
}
