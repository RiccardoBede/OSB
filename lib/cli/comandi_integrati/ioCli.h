void printCli (){
	char tipo_print[8];
	print(" type<", VGA_TEXT_BIANCO_NERO);
	input(tipo_print, 0x1c, sizeof(tipo_print), VGA_TEXT_VERDE_NERO);
	printchar('>', VGA_TEXT_BIANCO_NERO);

	if (stringa_uguale_stringa("str", tipo_print)){
		char stringa[128];
		print(" \"", VGA_TEXT_MAGENTA_NERO);
		input(stringa, 0x1c, sizeof(stringa), VGA_TEXT_BIANCO_NERO);
		print("\"\n", VGA_TEXT_MAGENTA_NERO);
		print(stringa, VGA_TEXT_BIANCO_NERO);
	}
	if (stringa_uguale_stringa("ptr", tipo_print)){
		unsigned int contatore_size = 0;
		char indirizzo[16];
		print(" 0x", VGA_TEXT_VERDE_NERO);
		input(indirizzo, 0x1c, sizeof(indirizzo), VGA_TEXT_VERDE_NERO);

		char size[8];
		print(" fino=", VGA_TEXT_GIALLO_NERO);
		input(size, 0x1c, sizeof(size), VGA_TEXT_BIANCO_NERO);
		
		char *puntatore_zona = (char *)stringa_to_hex(indirizzo);
		
		if (char_in_stringa('x', size) != -1){
			char term[8];
			unsigned short contatore_term = 0;
			unsigned short contatore_carattere_end = char_in_stringa('x', size);
			while(size[contatore_carattere_end] != '\0' || contatore_carattere_end <= sizeof(size)){
				contatore_carattere_end++;
				term[contatore_term] = size[contatore_carattere_end];
				contatore_term++;
			}
			term[contatore_term++] = '\0';
			while (puntatore_zona[contatore_size] != stringa_to_hex(term)){
				printchar(puntatore_zona[contatore_size], VGA_TEXT_BIANCO_NERO);
				contatore_size++;
			}
		}
		printchar('\n', VGA_TEXT_BIANCO_NERO);
		while (contatore_size <= stringa_to_int(size)){
			printchar(puntatore_zona[contatore_size], VGA_TEXT_BIANCO_NERO);
			contatore_size++;
		}
		printchar('\n', VGA_TEXT_BIANCO_NERO);
	}

}

void inputCli (){
	char indirizzo[16];
	char size[8];
	print(" indir=", VGA_TEXT_BIANCO_NERO);
	print("0x", VGA_TEXT_MAGENTA_NERO);
	input(indirizzo, 0x1c, sizeof(indirizzo), VGA_TEXT_MAGENTA_NERO);

	print(" size=", VGA_TEXT_GIALLO_NERO);
	input(size, 0x1c, sizeof(size), VGA_TEXT_BIANCO_NERO);
	
	char *puntatore_zona = (char *)stringa_to_hex(indirizzo);
	unsigned int contatore_puntatore = 0;

	printchar(' ', VGA_TEXT_BIANCO_NERO);
	
	if (stringa_uguale_stringa("no", size)){
		while (1){
			if (inb(STATO_TASTIERA) & 1){
				char carattere = inputNoInterrup();
				if (carattere == 0x01){
					printchar('\n', VGA_TEXT_BIANCO_NERO);
					return;
				}
				if (carattere != 0x00){
					printchar(carattere, VGA_TEXT_BIANCO_NERO);
					puntatore_zona[contatore_puntatore] = carattere;
					contatore_puntatore++;
				}
			}
		}
	}else{
		while (contatore_puntatore < stringa_to_int(size)){
			if (inb(STATO_TASTIERA) & 1){
				char carattere = inputNoInterrup();
				if (carattere == 0x01){
					printchar('\n', VGA_TEXT_BIANCO_NERO);
					return;
				}
				if (carattere != 0x00){
					printchar(carattere, VGA_TEXT_BIANCO_NERO);
					puntatore_zona[contatore_puntatore] = carattere;
					contatore_puntatore++;
				}
			}
		}
	}
	printchar('\n', VGA_TEXT_BIANCO_NERO);
}

void inbCli (){
	char buffer_porta[12];
	print(" 0x", VGA_TEXT_VERDE_NERO);
	input(buffer_porta, 0x1c, sizeof(buffer_porta), VGA_TEXT_VERDE_NERO);
	print("\n0x", VGA_TEXT_BIANCO_NERO);
	printint((unsigned int)inb((unsigned short)stringa_to_hex(buffer_porta)), VGA_TEXT_BIANCO_NERO);
}

void outbCli (){
	char buffer_porta[12], buffer_comando[12];
	print(" 0x", VGA_TEXT_VERDE_NERO);
	input(buffer_porta, 0x39, sizeof(buffer_porta), VGA_TEXT_VERDE_NERO);
	print(", ", VGA_TEXT_BIANCO_NERO);
	print("0x", VGA_TEXT_MAGENTA_NERO);
	input(buffer_comando, 0x1c, sizeof(buffer_comando), VGA_TEXT_MAGENTA_NERO);
	printchar('\n', VGA_TEXT_BIANCO_NERO);
	outb((unsigned short)stringa_to_hex(buffer_porta), (char)stringa_to_hex(buffer_comando));
}

void clearCli (){
	clear();
}
