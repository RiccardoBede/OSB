#define SIZEOF_SETTORE 1024
#define SIZEOF_NOME_FILE 16
#define SIZEOF_FIRMA 2

#define FIRMA_JMP 0xfe

extern bool lba48_attivo;
extern unsigned long int settori_lba32;
extern struct settori_lba48;
extern unsigned short porta_controller_default;

extern struct info_settore;

//creare funzione di settore_info per indicizzare in ram i file
//per rendere i/o più veloce (tramite struct)

static unsigned char settore[1024];

bool crea_file (DISCO_MONTATO tipo_disco, char *nome_file, char *buffer, TIPO_SETTORE tipo_settore){
	//nome_file max 16
	//
	//firma_tipo_settore;nome_file;
	//	buffer;
	//ultimi 16 + 2 byte da mettre firma JMP e numero settore jmp

	//verificare la grandezza del buffer per immettere un jmp and un altro settore 
	//(firmaJMP;numero_settore) alla fine del settore inizializzato o meno.
	//
	unsigned int numero_caratteri_buffer = 0;
	unsigned int numero_caratteri_settore = 0;
	unsigned int numero_caratteri_nome_file = 0;
	static unsigned char buffer_settore[1024];
	
	while (buffer[numero_caratteri_buffer] != '\0'){	numero_caratteri_buffer++;}
	while (nome_file[numero_caratteri_nome_file] != '\0'){	numero_caratteri_nome_file++;}

	if (!lba48_attivo){
		leggi_settore(tipo_disco, info_settore.ultimo_settore_scritto_lba28 + 1, settore, sizeof(settore));

		if (settore[0] == 0x00 && settore[1] == 0x00){
			while (numero_caratteri_settore < 16 && nome_file[numero_caratteri_settore] != '\0'){
				buffer_settore[numero_caratteri_settore] = nome_file[numero_caratteri_settore];
				numero_caratteri_settore++;
			}

			if (numero_caratteri_buffer > (SIZEOF_SETTORE - (SIZEOF_NOME_FILE + SIZEOF_FIRMA) * 2)){
				while (numero_caratteri_settore < numero_caratteri_buffer && numero_caratteri_settore < (SIZEOF_SETTORE - (SIZEOF_NOME_FILE + SIZEOF_FIRMA) * 2)){
					buffer_settore[numero_caratteri_settore] = buffer_settore[numero_caratteri_settore];
					numero_caratteri_settore++;
				}
				buffer_settore[numero_caratteri_settore++] = FIRMA_JMP;
				buffer_settore[numero_caratteri_settore++] = FIRMA_JMP;
				
				unsigned long int settore_jmp = info_settore.ultimo_settore_scritto_lba28 + 2;

				while (settore_jmp < settori_lba32){
					leggi_settore(tipo_disco, settore_jmp, settore, sizeof(settore));
				
					if (settore[0] == 0x00 && settore[1] == 0x00){
						unsigned char stringa_settore_jmp[16];
						unsigned_int_to_stringa(settore_jmp, stringa_settore_jmp, sizeof(stringa_settore_jmp));
						for (unsigned int carattere_settore_jmp = 0; carattere_settore_jmp < sizeof(stringa_settore_jmp); carattere_settore_jmp++){
							buffer_settore[numero_caratteri_settore] = stringa_settore_jmp[carattere_settore_jmp];
							numero_caratteri_settore++;
						}
						break;
					}
					settore_jmp++;
				}
				scrivi_settore(tipo_disco, info_settore.ultimo_settore_scritto_lba28 + 1, buffer_settore, tipo_settore);

				static unsigned char buffer_continuo_file[512];
				unsigned int numero_caratteri_buffer_continuo_file = 0;

				while (buffer[numero_caratteri_settore] != '\0'){
					buffer_continuo_file[numero_caratteri_buffer_continuo_file] = buffer[numero_caratteri_settore];
					numero_caratteri_settore++;
				}
				buffer_continuo_file[numero_caratteri_settore++] = '\0';

				scrivi_settore(tipo_disco, settore_jmp, buffer_continuo_file, tipo_settore);
			}else{
				while (numero_caratteri_settore < numero_caratteri_buffer){
					buffer_settore[numero_caratteri_settore] = buffer_settore[numero_caratteri_settore];
					numero_caratteri_settore++;
				}
				buffer_settore[numero_caratteri_settore++] = '\0';
				scrivi_settore(tipo_settore, info_settore.ultimo_settore_scritto_lba28 + 1, buffer_settore, tipo_settore);
			}
		}
	}else{}

}

//creare funzione elimina file, formatta disco
