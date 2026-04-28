#define SIZEOF_SETTORE_CHAR 1024
#define SIZEOF_FIRMA 2
#define SIZEOF_NOME_FILE 16
#define SIZEOF_SETTORE_JMP_CHAR 16
#define SIZEOF_FLAG_SETTORE_LBA48_JMP 1
#define NUM_SEPARATORI_LBA28 4
#define NUM_SEPARATORI_LBA48 6

#define FIRMA_JMP 0xfe


extern unsigned long int settori_lba32;
extern bool lba48_attivo;
extern struct settori_lba48;
extern enum TIPO_SETTORE; //firme: avviabile 0x01, normale 0x00, info 0x02
//extern unsigned int tipo_disco;
unsigned int tipo_disco = 0x01;

typedef struct {
	TIPO_SETTORE tipo_file;
	char nome_file[16];
	char *contenuto_file;
	unsigned long int settore_lba28_JMP;
	struct{
		bool settore_lba48_attivo;
		unsigned long int settore_lba48_mrb_JMP;
		unsigned long int settore_lba48_lrb_JMP;
	}settore_lba48_JMP;
}File;

unsigned long int settore_lba28_libero;
unsigned long int settore_lba48_mrb_libero;
unsigned long int settore_lba48_lrb_libero;

unsigned long int cerca_settore_libero (unsigned long int settore_lba28, unsigned long int settore_lba48_mrb, unsigned long int settore_lba48_lrb){
	char verifica_firma_settore[2];
	if (!lba48_attivo){
		settore_lba28_libero = 1;
		while (settore_lba28_libero < settori_lba32){
			//ignora il settore
			if (settore_lba28 != -1){
				if (settore_lba28_libero == settore_lba28){
					settore_lba28_libero++;
				}
			}

			leggi_settore(tipo_disco, settore_lba28_libero, verifica_firma_settore, sizeof(verifica_firma_settore));
			if (verifica_firma_settore[0] == 0x00 && verifica_firma_settore[1] == 0x00){
				return settore_lba28_libero;
			}
			settore_lba28_libero++;
		}
		return 0;
	}else{
		//mettere l'ignora dei settori anche per lba48
	}
	return 0;
}

bool crea_file (TIPO_SETTORE tipo_file, char *nome_file, char *buffer){
	File file;
	unsigned short contatore_nome_file = 0;
	unsigned int contatore_buffer = 0;
	unsigned int contatore_buffer_primo_settore = 0;
	unsigned int contatore_buffer_rimanente_JMP = 0;
	
	static unsigned char buffer_settore[1024];

	char settore_lba28_stringa[16];
	char settore_lba48_mrb_stringa[16];
	char settore_lba48_lrb_stringa[16];
	unsigned short contatore_caratteri_lba_stringa = 0;

	file.tipo_file = tipo_file;
	while (contatore_nome_file < sizeof(nome_file) && nome_file[contatore_nome_file] != '\0'){	
		file.nome_file[contatore_nome_file] = nome_file[contatore_nome_file];
		contatore_nome_file++;
	}
	file.contenuto_file = buffer;
	while (buffer[contatore_buffer] != '\0'){	contatore_buffer++;}
		
	if (!lba48_attivo){
		unsigned long int settore_da_scrivere = cerca_settore_libero(-1, -1, -1);

		file.settore_lba48_JMP.settore_lba48_attivo = false;
		if (contatore_buffer > (SIZEOF_SETTORE_CHAR - (SIZEOF_FIRMA + contatore_nome_file + SIZEOF_FLAG_SETTORE_LBA48_JMP + SIZEOF_SETTORE_JMP_CHAR + NUM_SEPARATORI_LBA28))){
			//riuso contatore_buffer per contare il primo buffer da inserire nel primo settore del file
			contatore_buffer = 0;
			while (file.nome_file[contatore_buffer] != '\0'){
				buffer_settore[contatore_buffer] = file.nome_file[contatore_buffer];
				contatore_buffer++;
			}

			buffer_settore[contatore_buffer++] = ';';

			while (contatore_buffer < (SIZEOF_SETTORE_CHAR - (SIZEOF_FIRMA + contatore_nome_file + SIZEOF_FLAG_SETTORE_LBA48_JMP  + SIZEOF_SETTORE_JMP_CHAR + NUM_SEPARATORI_LBA28))){
				buffer_settore[contatore_buffer] = buffer[contatore_buffer_primo_settore];
				contatore_buffer++;
				contatore_buffer_primo_settore++;
				contatore_buffer_rimanente_JMP++;
			}

			buffer_settore[contatore_buffer++] = 0xfe;
			buffer_settore[contatore_buffer++] = 0; //flag lba48 attivo
			buffer_settore[contatore_buffer++] = ';';
			
			//cerca nuovo settore
			file.settore_lba28_JMP = cerca_settore_libero(settore_da_scrivere, -1, -1);
			unsigned_int_to_stringa(file.settore_lba28_JMP, settore_lba28_stringa, sizeof(settore_lba28_stringa));
			
			while (settore_lba28_stringa[contatore_caratteri_lba_stringa] != '\0' && contatore_caratteri_lba_stringa <= sizeof(settore_lba28_stringa)){
				buffer_settore[contatore_buffer++] = settore_lba28_stringa[contatore_caratteri_lba_stringa];
				contatore_caratteri_lba_stringa++;
			}
			
			if (contatore_buffer < sizeof(buffer_settore)){
				buffer_settore[contatore_buffer++] = '\0';
			}
				
			//prima parte del file
			scrivi_settore(tipo_disco, settore_da_scrivere, buffer_settore, tipo_file);

			unsigned int contatore_caratteri_buffer_settore = 0;
			while (contatore_caratteri_buffer_settore < sizeof(buffer_settore)){	buffer_settore[contatore_caratteri_buffer_settore] = 0x00;}
			
			contatore_buffer_primo_settore = 0;
			contatore_buffer = 0;
			while (buffer[contatore_buffer_primo_settore] != '\0'){	contatore_buffer_primo_settore++;}

			while (contatore_buffer_rimanente_JMP < contatore_buffer_primo_settore){
				buffer_settore[contatore_buffer] = buffer[contatore_buffer_rimanente_JMP];
				contatore_buffer++;
				contatore_buffer_rimanente_JMP++;
			}

			scrivi_settore(tipo_disco, file.settore_lba28_JMP, buffer_settore, tipo_file);
		}else{
			contatore_buffer = 0;
			while (file.nome_file[contatore_buffer] != '\0'){
				buffer_settore[contatore_buffer] = file.nome_file[contatore_buffer];
				contatore_buffer++;
			}

			buffer_settore[contatore_buffer++] = ';';

			while (contatore_buffer < (SIZEOF_SETTORE_CHAR - (SIZEOF_FIRMA + contatore_nome_file + SIZEOF_FLAG_SETTORE_LBA48_JMP  + SIZEOF_SETTORE_JMP_CHAR + NUM_SEPARATORI_LBA28))){
				buffer_settore[contatore_buffer] = buffer[contatore_buffer_primo_settore];
				contatore_buffer++;
				contatore_buffer_primo_settore++;
				contatore_buffer_rimanente_JMP++;
			}
			
			scrivi_settore(tipo_disco, settore_da_scrivere, buffer_settore, tipo_file);
		}
	}else{
	
	}
	return false;
}
