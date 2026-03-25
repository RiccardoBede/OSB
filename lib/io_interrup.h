#define BUFFER_TASTIERA 0x60
#define STATO_TASTIERA 0x64

char inb (unsigned short porta){
	char buffer;
	__asm__ ("in %%dx, %%al" : "=a" (buffer) : "d" (porta));
	return buffer;
}

void outb (unsigned short porta, char comando){
	__asm__ ("outb %0, %1" : : "a" (comando), "dN" (porta));
}

void outw (unsigned short porta, unsigned short buffer){
	__asm__ ("outw %0, %1" : : "a" (buffer), "dN" (porta));
}

char inw (unsigned short porta){
	char buffer;
	__asm__ ("inw %%dx, %%ax" : "=a" (buffer) : "dN" (porta));
	return buffer;
}

char outb_set (unsigned short porta, char index, int comando){
	outb(porta, index);
	outb(porta, comando);
}

typedef struct{
	char carattere_ascii;
	char carattere_shift;
	char codice_tastiera;
}MappaTastiera;

MappaTastiera tastiera[] = {
	{'\\', '|', 0x2b},{'1', '!', 0x02},{'2', '\"', 0x03},{'3', '£', 0x04},{'4', '$', 0x05},{'5', '%', 0x06},{'6', '&', 0x07},{'7', '/', 0x08},{'8', '(', 0x09},{'9', ')', 0x0a},{'0', '=', 0x0b},{'\'', '?', 0x0c},{'\b', '\b', 0x0e},{'ì', '^', 0x0d},
	{'\t', '\t', 0x0f},{'q', 'Q', 0x10},{'w', 'W', 0x11},{'e', 'E', 0x12},{'r', 'R', 0x13},{'t', 'T', 0x14},{'y', 'Y', 0x15},{'u', 'U', 0x16},{'i', 'I', 0x17},{'o', 'O', 0x18},{'p', 'P', 0x19},{'[', ']', 0x1a},{'+', '*', 0x1b},
	{'a', 'A', 0x1e},{'s', 'S', 0x1f},{'d', 'D', 0x20},{'f', 'F', 0x21},{'g', 'G', 0x22},{'h', 'H', 0x23},{'j', 'J', 0x24},{'k', 'K', 0x25},{'l', 'L', 0x26},{'{', '@', 0x27},{'}', '#', 0x28},{'\n', '\n', 0x1c},
	{'z', 'Z', 0x2c},{'x', 'X', 0x2d},{'c', 'C', 0x2e},{'v', 'V', 0x2f},{'b', 'B', 0x30},{'n', 'N', 0x31},{'m', 'M', 0x32},{',', ';', 0x33},{'.', ':', 0x34},{'-', '_', 0x35},
	{' ', ' ', 0x39},{'<', '>', 0x56},
};

void input (char *buffer, char interrup, int sizeof_buffer, char colore){
	unsigned int contatore_char = 0;
	bool shift = false, caps = false, alt = false;
	while (contatore_char < (sizeof_buffer - 1)){
		while(!(inb(STATO_TASTIERA) & 0x01));
		char char_tastiera = inb(BUFFER_TASTIERA);

		if (char_tastiera == interrup){
			buffer[contatore_char] = '\0';
			return;
		}

		if (char_tastiera == 0x2a || char_tastiera == 0x36){ //shift
			shift = !(shift);
		}
		/*if (char_tastiera == 0xaa || char_tastiera == 0xb6){
			shift = !(shift);
		}*/

		if (char_tastiera == 0x38){
			alt = !(alt);
			print("<Alt>", colore-1);
		}

		if (char_tastiera == 0x4b){
			print("<Sin>", colore-1);
		}
		if (char_tastiera == 0x4d){
			print("<Des>", colore-1);
		}
		if (char_tastiera == 0x48){
			print("<Su>", colore-1);
		}
		if (char_tastiera == 0x50){
			print("<Giu>", colore-1);
		}

		for (int contatore_tastiera = 0; contatore_tastiera < sizeof(tastiera) / sizeof(tastiera[0]); contatore_tastiera++){
			if (char_tastiera == tastiera[contatore_tastiera].codice_tastiera){
				/*if (contatore_char == 0 && tastiera[contatore_tastiera].carattere_ascii == '\b'){
					break;
				}*/
				if (shift){
					switch (tastiera[contatore_tastiera].carattere_shift){
						case '\n':
							stampaAcapo();
							cursore();
							break;
						case '\t':
							stampaTab();
							cursore();
							break;
						case '\b':
							if (contatore_char == 0){	break;}
							cancellachar();
							cursore();	
							buffer[contatore_char-=2] == 0x00;	
							break;
						default:
							buffer[contatore_char] = tastiera[contatore_tastiera].carattere_shift;
							printchar(tastiera[contatore_tastiera].carattere_shift, colore);	
							break;
					}
					contatore_char++;
					break;
				}
				switch (tastiera[contatore_tastiera].carattere_ascii){
					case '\n':
						stampaAcapo();
						cursore();
						break;
					case '\t':
						stampaTab();
						cursore();
						break;
					case '\b':
						if (contatore_char == 0){	break;}
						cancellachar();
						cursore();	
						buffer[contatore_char-=2] == 0x00;	
						break;
					default:
						buffer[contatore_char] = tastiera[contatore_tastiera].carattere_ascii;
						printchar(tastiera[contatore_tastiera].carattere_ascii, colore);
						break;
				}
				contatore_char++;
				break;
			}
		}
		//shift = false;
	}
	buffer[contatore_char] = '\0';
}

bool monoInput (char *msg, char rispostaTrue, char rispostaFalse, char colore){
	print(msg, colore);
	while(1){
		while(!(inb(STATO_TASTIERA) & 0x01));
		char char_tastiera = inb(BUFFER_TASTIERA);
		for (int contatore_tastiera = 0; contatore_tastiera < sizeof(tastiera) / sizeof(tastiera[0]); contatore_tastiera++){
			if (char_tastiera == tastiera[contatore_tastiera].codice_tastiera){
				printchar(tastiera[contatore_tastiera].carattere_ascii, colore);
				if (char_tastiera == rispostaTrue){
					return true;
				}else{
					return false;
				}
			}
		}
	}
}

typedef struct{
	char msg[77];
	char colore;
}SelezioneComando;

unsigned int multiInput(SelezioneComando *buffer, unsigned int sizeof_buffer, char colore){
	clear();
	unsigned int voce = 0;
	unsigned int selzione_voce = 0;
	while(voce < sizeof_buffer){
		print("[ ]", colore);
		print(buffer[voce].msg, buffer[voce].colore);
		printchar('\n', colore);
		voce++;
	}
	printcharat('*', (80 * selzione_voce + 1), colore);
	while (1){
		while(!(inb(STATO_TASTIERA) & 0x01));
		char char_tastiera = inb(BUFFER_TASTIERA);

		if (char_tastiera == 0x48){ //freccia su
			if (selzione_voce > 0){
				printcharat(' ', (80 * selzione_voce + 1), 0x0);
				selzione_voce--;
				printcharat('*', (80 * selzione_voce + 1), colore);
			}
		}
		if (char_tastiera == 0x50){ //freccia giu
			if (selzione_voce < voce){
				printcharat(' ', (80 * selzione_voce + 1), 0x0);
				selzione_voce++;
				printcharat('*', (80 * selzione_voce + 1), colore);
			}else{
				printcharat(' ', (80 * selzione_voce + 1), 0x0);
				selzione_voce = 0;
				printcharat('*', (80 * selzione_voce + 1), colore);
			}
		}
		if (char_tastiera == 0x1c){
			return selzione_voce;
		}	
	}
}
