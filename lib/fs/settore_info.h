extern bool lba48_attivo;
extern unsigned long int settori_lba32;
extern struct settori_lba48;
//extern typedef enum DISCO_MONTATO;
//extern typedef enum TIPO_SETTORE; //io_settore
//extern typedef struct ByteSettore; //io_settore
extern unsigned short porta_controller_default;
extern struct info_settore;

static unsigned char settore_info[1024];
unsigned char array_flag[][16] = {"filesystem", "allocator", "UsettoreLBA28", "UsettoreLBA48MRB", "UsettoreLBA48LRB"}; 

void applica_settore_info (unsigned char *buffer_settore, unsigned int sizeof_buffer_settore){
	unsigned short int numero_flag = 0;
	unsigned short int contatore_carattere_flag = 0;
	unsigned short int sizeof_flag_corrente = 0;

	char buffer_flag_corrente[16];
	unsigned short int contatore_buffer_flag_corrente = 0;

	for (numero_flag; numero_flag < (sizeof(array_flag) / sizeof(array_flag[0])); numero_flag++){
		contatore_carattere_flag = 0;
		sizeof_flag_corrente = 0;
		while (array_flag[numero_flag][sizeof_flag_corrente] != '\0'){	sizeof_flag_corrente++;}	

		for (unsigned short int contatore_carattere_buffer = 0; contatore_carattere_buffer < sizeof_buffer_settore; contatore_carattere_buffer++){
			if (buffer_settore[contatore_carattere_buffer] == array_flag[numero_flag][contatore_carattere_flag]){
				if (contatore_carattere_flag == sizeof_flag_corrente - 1){
					print("\t*", VGA_TEXT_GIALLO_NERO);
					print(array_flag[numero_flag], VGA_TEXT_GIALLO_NERO);
					printchar(' ', VGA_TEXT_GIALLO_NERO);
				
					contatore_carattere_buffer++;

					while (buffer_settore[contatore_carattere_buffer] != ';'){
						printchar(buffer_settore[contatore_carattere_buffer], VGA_TEXT_GIALLO_NERO);
						buffer_flag_corrente[contatore_buffer_flag_corrente++] = buffer_settore[contatore_carattere_buffer];
						contatore_carattere_buffer++;
					}
					contatore_buffer_flag_corrente = 0;

					switch(numero_flag){
						case 0:
							if (stringa_uguale_stringa("all", buffer_flag_corrente)){
								info_settore.tipo_filesystem = "all";
							}else{
								info_settore.tipo_filesystem = "seq";
							}
							break;
						case 1:
							if (stringa_uguale_stringa("true", buffer_flag_corrente)){
								info_settore.visualizza_msg_allocatore = true;
							}else{
								info_settore.visualizza_msg_allocatore = false;	 
							}
							break;
						case 2:
							info_settore.ultimo_settore_scritto_lba28 = stringa_to_int(buffer_flag_corrente);
							break;
						case 3:
							info_settore.ultimo_settore_scritto_lba48_mrb = stringa_to_int(buffer_flag_corrente);
							break;
						case 4:
							info_settore.ultimo_settore_scritto_lba48_lrb = stringa_to_int(buffer_flag_corrente);
							break;
						default:
							break;
					}

					printchar('\n', VGA_TEXT_GIALLO_NERO);
					contatore_carattere_flag = 0;
				}
				contatore_carattere_flag++;
			}else{	contatore_carattere_flag = 0;}	
		}
	}
}

void crea_settore_info(DISCO_MONTATO tipo_disco){
	unsigned long int numero_settore = 1;
	
	unsigned int contatore_buffer_settore_info = 0;

	unsigned int contatore_flag = 0;
	unsigned int contatore_caratteri_flag = 0;

	unsigned char buffer_numero_settore[16];
	unsigned int contatore_cifra_buffer_numero_settore = 0;

	unsigned char buffer_settore_info[512];

	for (contatore_flag; contatore_flag < sizeof(array_flag) / sizeof(array_flag[0]); contatore_flag++){
		while (array_flag[contatore_flag][contatore_caratteri_flag] != '\0'){
			buffer_settore_info[contatore_buffer_settore_info] = array_flag[contatore_flag][contatore_caratteri_flag];
			contatore_caratteri_flag++;
			contatore_buffer_settore_info++;
		}		
		
		switch(contatore_flag){
			case 0:
				if (stringa_uguale_stringa("all", info_settore.tipo_filesystem)){
					buffer_settore_info[contatore_buffer_settore_info++] = 'a';
					buffer_settore_info[contatore_buffer_settore_info++] = 'l';
					buffer_settore_info[contatore_buffer_settore_info++] = 'l';
				}else{	
					buffer_settore_info[contatore_buffer_settore_info++] = 's';
					buffer_settore_info[contatore_buffer_settore_info++] = 'e';
					buffer_settore_info[contatore_buffer_settore_info++] = 'q';
				}
				break;
			case 1:
				if (info_settore.visualizza_msg_allocatore){
					buffer_settore_info[contatore_buffer_settore_info++] = 't';
					buffer_settore_info[contatore_buffer_settore_info++] = 'r';
					buffer_settore_info[contatore_buffer_settore_info++] = 'u';
					buffer_settore_info[contatore_buffer_settore_info++] = 'e';
				}else{
					buffer_settore_info[contatore_buffer_settore_info++] = 'f';
					buffer_settore_info[contatore_buffer_settore_info++] = 'a';
					buffer_settore_info[contatore_buffer_settore_info++] = 'l';
					buffer_settore_info[contatore_buffer_settore_info++] = 's';
					buffer_settore_info[contatore_buffer_settore_info++] = 'e';
				}
				break;
			case 2:
				unsigned_int_to_stringa(info_settore.ultimo_settore_scritto_lba28, buffer_numero_settore, sizeof(buffer_numero_settore));
					while (contatore_cifra_buffer_numero_settore < sizeof(buffer_numero_settore) && buffer_numero_settore[contatore_cifra_buffer_numero_settore] != '\0'){
					buffer_settore_info[contatore_buffer_settore_info++] = buffer_numero_settore[contatore_cifra_buffer_numero_settore];
					contatore_cifra_buffer_numero_settore++;
				}
				break;
			case 3:
				unsigned_int_to_stringa(info_settore.ultimo_settore_scritto_lba48_mrb, buffer_numero_settore, sizeof(buffer_numero_settore));
				while (contatore_cifra_buffer_numero_settore < sizeof(buffer_numero_settore) && buffer_numero_settore[contatore_cifra_buffer_numero_settore] != '\0'){
					buffer_settore_info[contatore_buffer_settore_info++] = buffer_numero_settore[contatore_cifra_buffer_numero_settore];
					contatore_cifra_buffer_numero_settore++;
				}
				break;
			case 4:
				unsigned_int_to_stringa(info_settore.ultimo_settore_scritto_lba48_lrb, buffer_numero_settore, sizeof(buffer_numero_settore));
				while (contatore_cifra_buffer_numero_settore < sizeof(buffer_numero_settore) && buffer_numero_settore[contatore_cifra_buffer_numero_settore] != '\0'){
					buffer_settore_info[contatore_buffer_settore_info++] = buffer_numero_settore[contatore_cifra_buffer_numero_settore];
					contatore_cifra_buffer_numero_settore++;
				}
				break;
			default:
				break;
		}
		buffer_settore_info[contatore_buffer_settore_info++] = ';';
		buffer_settore_info[contatore_buffer_settore_info++] = ';';
	
		contatore_caratteri_flag = 0;
		contatore_cifra_buffer_numero_settore = 0;
		
	}
	buffer_settore_info[contatore_buffer_settore_info++] = '\0';

	if (!lba48_attivo){
		while(numero_settore < settori_lba32){
			leggi_settore(tipo_disco, numero_settore, settore_info, sizeof(settore_info));	
			if (settore_info[0] == 0x00 && settore_info[1] == 0x00){		
				print(buffer_settore_info, VGA_TEXT_GIALLO_NERO);
				scrivi_settore(tipo_disco, numero_settore, buffer_settore_info, 0x02);
				break;
			}
			numero_settore++;
		}
	}else{
	
	}

}

void aggiorna_settore_info (DISCO_MONTATO tipo_disco, char *tipo_filesystem, char *visualizza_msg_allocatore, unsigned long int ultimo_settore_scritto_lba28, unsigned long int ultimo_settore_scritto_lba48_mrb, unsigned long int ultimo_settore_scritto_lba48_lrb){
	unsigned long int numero_settore = 1;

	if (!lba48_attivo){
		while(numero_settore < settori_lba32){
			leggi_settore(0x01, numero_settore, settore_info, sizeof(settore_info));
			if (settore_info[0] = 0xff && settore_info[1] == 0xff){	
				unsigned int contatore_buffer_settore_info = 0;

				unsigned int contatore_flag = 0;
				unsigned int contatore_caratteri_flag = 0;

				unsigned char buffer_numero_settore[16];
				unsigned int contatore_cifra_buffer_numero_settore = 0;

				unsigned char buffer_settore_info[512];

				for (contatore_flag; contatore_flag < sizeof(array_flag) / sizeof(array_flag[0]); contatore_flag++){
					while (array_flag[contatore_flag][contatore_caratteri_flag] != '\0'){
						buffer_settore_info[contatore_buffer_settore_info] = array_flag[contatore_flag][contatore_caratteri_flag];
						contatore_caratteri_flag++;
						contatore_buffer_settore_info++;
					}		
		
					switch(contatore_flag){
						case 0:
							if (stringa_uguale_stringa("all", tipo_filesystem)){
								buffer_settore_info[contatore_buffer_settore_info++] = 'a';
								buffer_settore_info[contatore_buffer_settore_info++] = 'l';
								buffer_settore_info[contatore_buffer_settore_info++] = 'l';
							}else{	
								buffer_settore_info[contatore_buffer_settore_info++] = 's';
								buffer_settore_info[contatore_buffer_settore_info++] = 'e';
								buffer_settore_info[contatore_buffer_settore_info++] = 'q';
							}
							break;
						case 1:
							if (visualizza_msg_allocatore){
								buffer_settore_info[contatore_buffer_settore_info++] = 't';
								buffer_settore_info[contatore_buffer_settore_info++] = 'r';
								buffer_settore_info[contatore_buffer_settore_info++] = 'u';
								buffer_settore_info[contatore_buffer_settore_info++] = 'e';
							}else{
								buffer_settore_info[contatore_buffer_settore_info++] = 'f';
								buffer_settore_info[contatore_buffer_settore_info++] = 'a';
								buffer_settore_info[contatore_buffer_settore_info++] = 'l';
								buffer_settore_info[contatore_buffer_settore_info++] = 's';
								buffer_settore_info[contatore_buffer_settore_info++] = 'e';
							}
							break;
						case 2:
							unsigned_int_to_stringa(ultimo_settore_scritto_lba28, buffer_numero_settore, sizeof(buffer_numero_settore));
							while (contatore_cifra_buffer_numero_settore < sizeof(buffer_numero_settore) && buffer_numero_settore[contatore_cifra_buffer_numero_settore] != '\0'){
								buffer_settore_info[contatore_buffer_settore_info++] = buffer_numero_settore[contatore_cifra_buffer_numero_settore];
								contatore_cifra_buffer_numero_settore++;
							}
							break;
						case 3:
							unsigned_int_to_stringa(ultimo_settore_scritto_lba48_mrb, buffer_numero_settore, sizeof(buffer_numero_settore));
							while (contatore_cifra_buffer_numero_settore < sizeof(buffer_numero_settore) && buffer_numero_settore[contatore_cifra_buffer_numero_settore] != '\0'){
								buffer_settore_info[contatore_buffer_settore_info++] = buffer_numero_settore[contatore_cifra_buffer_numero_settore];
								contatore_cifra_buffer_numero_settore++;
							}
							break;
						case 4:
							unsigned_int_to_stringa(ultimo_settore_scritto_lba48_lrb, buffer_numero_settore, sizeof(buffer_numero_settore));
							while (contatore_cifra_buffer_numero_settore < sizeof(buffer_numero_settore) && buffer_numero_settore[contatore_cifra_buffer_numero_settore] != '\0'){
								buffer_settore_info[contatore_buffer_settore_info++] = buffer_numero_settore[contatore_cifra_buffer_numero_settore];
								contatore_cifra_buffer_numero_settore++;
							}
							break;
						default:
							break;		
					}
					buffer_settore_info[contatore_buffer_settore_info++] = ';';
					buffer_settore_info[contatore_buffer_settore_info++] = ';';
	
					contatore_caratteri_flag = 0;
					contatore_cifra_buffer_numero_settore = 0;
		
				}
				buffer_settore_info[contatore_buffer_settore_info++] = '\0';
				scrivi_settore(tipo_disco, numero_settore, buffer_settore_info, 0x02);
			}
		}
	}else{}
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
