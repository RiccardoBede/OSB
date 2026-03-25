extern bool lba48_attivo;
extern unsigned long int settori_lba32;
extern struct settori_lba48;
//extern typedef enum DISCO_MONTATO;
//extern typedef enum TIPO_SETTORE; //io_settore
//extern typedef struct ByteSettore; //io_settore
extern unsigned short porta_controller_default;

static unsigned char settore_info[1024];
unsigned char array_flag[][10] = {"filesystem"/*, "allocator"*/}; 

void applica_settore_info (unsigned char *buffer_settore, unsigned int sizeof_buffer_settore){
	unsigned short int numero_flag = 0;
	unsigned short int contatore_carattere_flag = 0;
	unsigned short int sizeof_flag_corrente = 0;

	for (unsigned short int contatore_carattere_buffer = 0; contatore_carattere_buffer < sizeof_buffer_settore; contatore_carattere_buffer++){
		while (array_flag[numero_flag][sizeof_flag_corrente] != '\0'){	sizeof_flag_corrente++;}

		if (buffer_settore[contatore_carattere_buffer] == array_flag[numero_flag][contatore_carattere_flag] && (numero_flag < (sizeof(array_flag) / sizeof(array_flag[numero_flag])))){
			if (contatore_carattere_flag == sizeof_flag_corrente - 1){
				print("\t*", VGA_TEXT_GIALLO_NERO);
				print(array_flag[numero_flag], VGA_TEXT_GIALLO_NERO);
				printchar(' ', VGA_TEXT_GIALLO_NERO);
				
				contatore_carattere_buffer++;
				while (buffer_settore[contatore_carattere_buffer] != ';'){
					printchar(buffer_settore[contatore_carattere_buffer], VGA_TEXT_GIALLO_NERO);
					contatore_carattere_buffer++;
				}

				printchar('\n', VGA_TEXT_GIALLO_NERO);
				numero_flag++;
				contatore_carattere_flag = 0;
				sizeof_flag_corrente = 0;
			}
			contatore_carattere_flag++;
		}else{
			/*if (numero_flag < (sizeof(array_flag) / sizeof(array_flag[0]))){
				numero_flag++;
			}else{
				numero_flag = 0;
			}*/
			contatore_carattere_flag = 0;
		}
		sizeof_flag_corrente = 0;
	}
}

bool cerca_settore_info (DISCO_MONTATO tipo_disco){
	if (tipo_disco > 0x00){
		tipo_disco -= 0x01;
	}else{	return false;}

	unsigned long int numero_settore = 1;
	//static unsigned char settore_info[1024];

	if (!lba48_attivo){
		while (numero_settore < settori_lba32){
			leggi_settore(0x01, numero_settore, settore_info, sizeof(settore_info));
			if (settore_info[0] == 0xff && settore_info[1] == 0xff){
				print("SETTORE <INFO> TROVATO\n", VGA_TEXT_GIALLO_NERO);
				//leggi_settore(0x01, 2, settore_info, sizeof(settore_info));
				applica_settore_info(settore_info, sizeof(settore_info));
				return true;
			}
			numero_settore++;
		}
	}else{

	}
	return false;
}
