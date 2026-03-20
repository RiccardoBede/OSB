extern bool lba48_attivo;
extern unsigned long int settori_lba32;
extern struct settori_lba48;
//extern typedef enum DISCO_MONTATO;
//extern typedef enum TIPO_SETTORE; //io_settore
//extern typedef struct ByteSettore; //io_settore
extern unsigned short porta_controller_default;

const ByteSettore firma_settore_info = {.primo_byte = 0xff, .secondo_byte = 0xff};

const TIPO_SETTORE tipo_settore = SETTORE_NORMALE;

bool cerca_settore_info (DISCO_MONTATO tipo_disco){
	if (tipo_disco > 0x00){
		tipo_disco -= 0x01;
	}else{	return false;}

	unsigned long int numero_settore = 1;
	char verifica_firma_settore[2];
	char settore_info[1024];
	
	if (!lba48_attivo){
		while (numero_settore < settori_lba32){
			leggi_settore(tipo_disco, numero_settore, verifica_firma_settore, sizeof(verifica_firma_settore));
			if (verifica_firma_settore[0] == firma_settore_info.primo_byte && verifica_firma_settore[1] == firma_settore_info.secondo_byte){
				leggi_settore(tipo_disco, numero_settore, settore_info, sizeof(settore_info));
				print(settore_info, VGA_TEXT_GIALLO_NERO);
				return true;
			}
			numero_settore++;
		}
	}else{

	}
}
