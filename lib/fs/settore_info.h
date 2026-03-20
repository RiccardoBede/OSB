extern bool lba48_attivo;
extern unsigned long int settori_lba32;
extern struct settori_lba48;
//extern typedef enum DISCO_MONTATO;
//extern typedef enum TIPO_SETTORE; //io_settore
//extern typedef struct ByteSettore; //io_settore
extern unsigned short porta_controller_default;

//ByteSettore firma_settore_info;
//firma_settore_info.primo_byte = 0xff;
//firma_settore_info.secondo_byte = 0xff;

bool cerca_settore_info (DISCO_MONTATO tipo_disco){
	if (tipo_disco > 0x00){
		tipo_disco -= 0x01;
	}else{	return false;}

	unsigned long int numero_settore = 1;
	unsigned char verifica_firma_settore[3];
	unsigned char settore_info[512];

	if (!lba48_attivo){
		while (numero_settore < settori_lba32){
			leggi_settore(tipo_disco, numero_settore, settore_info, sizeof(settore_info));

			print(settore_info, VGA_TEXT_GIALLO_NERO);	
			/*if (verifica_firma_settore[0] == 0xff){
				//leggi_settore(tipo_disco, numero_settore, settore_info, sizeof(settore_info));
				print("SETTORE <INFO> TROVATO", VGA_TEXT_GIALLO_NERO);
				return true;
			}
			*/numero_settore++;
			return true;
		}
	}else{

	}
}
