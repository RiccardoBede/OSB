extern bool lba48_attivo;
extern unsigned long int settori_lba32;
extern struct settori_lba48;
//extern typedef enum DISCO_MONTATO;
//extern typedef enum TIPO_SETTORE; //io_settore
//extern typedef struct ByteSettore; //io_settore
extern unsigned short porta_controller_default;

unsigned char info_flags[][10] = {"filesystem"}; 

void applica_settore_info (unsigned char *info, unsigned int sizeof_info){
	//unsigned char info[1024];
	//leggi_settore(tipo_disco, numero_settore_info, info, sizeof(info));

	unsigned short int carattere_flag = 0;
	unsigned short int flag_corrente = 0;
	for (unsigned short int flag = 0; flag < sizeof_info; flag++){
		if (info[flag] == info_flags[flag_corrente][carattere_flag]){
			if (carattere_flag == sizeof(info_flags[flag_corrente])){
				printchar('*', VGA_TEXT_GIALLO_NERO);
				print(info_flags[flag_corrente], VGA_TEXT_GIALLO_NERO);
				printchar(' ', VGA_TEXT_GIALLO_NERO);

				while (info[flag] != ';'){
					printchar(info[flag], VGA_TEXT_GIALLO_NERO);
					flag++;
				}
				printchar('\n', VGA_TEXT_GIALLO_NERO);
				flag_corrente++;
			}
			carattere_flag++;
		}else{
			carattere_flag = 0;
		}
	}
}

bool cerca_settore_info (DISCO_MONTATO tipo_disco){
	if (tipo_disco > 0x00){
		tipo_disco -= 0x01;
	}else{	return false;}

	unsigned long int numero_settore = 1;
	unsigned char settore_info[1024];

	if (!lba48_attivo){
		while (numero_settore < settori_lba32){
			leggi_settore(0x01, numero_settore, settore_info, sizeof(settore_info));
			if (settore_info[0] == 0xff && settore_info[1] == 0xff){
				print("SETTORE <INFO> TROVATO\n", VGA_TEXT_GIALLO_NERO);
				leggi_settore(0x01, 2, settore_info, sizeof(settore_info));
				applica_settore_info(settore_info, sizeof(settore_info));
				return true;
			}
			numero_settore++;
		}
	}else{

	}
	return false;
}
