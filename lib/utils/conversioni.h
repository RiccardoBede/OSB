unsigned long int stringa_to_int (char *buffer){
	unsigned int contatore_cifre = 0;
	unsigned long int valore_finale = 0;
	while (buffer[contatore_cifre] != '\0'){	contatore_cifre++;}
	for (unsigned int contatore = 0; contatore < contatore_cifre; contatore++){
		valore_finale *= 10;
		if (buffer[contatore] >= '0' && buffer[contatore] <= '9'){
			valore_finale += buffer[contatore] - '0';
		}
	}
	return valore_finale;
}

unsigned short stringa_to_unsigned_short (char *buffer){
	unsigned int contatore_cifre = 0;
	unsigned long int valore_finale = 0;
	while (buffer[contatore_cifre] != '\0'){	contatore_cifre++;}
	for (unsigned int contatore = 0; contatore < contatore_cifre; contatore++){
		valore_finale *= 10;
		if (buffer[contatore] >= '0' && buffer[contatore] <= '9'){
			valore_finale += buffer[contatore] - '0';
		}
	}
	return valore_finale;
}

unsigned long int stringa_to_hex (char *buffer){
	unsigned int contatore_cifre = 0;
	unsigned long int valore_finale = 0;
	while (buffer[contatore_cifre] != '\0'){	contatore_cifre++;}
	for (unsigned int contatore = 0; contatore < contatore_cifre; contatore++){
		valore_finale *= 16;
		if (buffer[contatore] >= '0' && buffer[contatore] <= '9'){
			valore_finale += buffer[contatore] - '0';
		}
		if (buffer[contatore] >= 'a' && buffer[contatore] <= 'f'){
			valore_finale += buffer[contatore] - 'a' + 10;
		}
	}
	return valore_finale;
}

void stampa_num_in_bin (unsigned long int numero_decimale, char colore){
	unsigned long int numero_cifre_decimale = numero_decimale;
	unsigned int numero_cifre_bin = 0;
	while (numero_cifre_decimale > 0){
		numero_cifre_decimale /= 2;
		numero_cifre_bin++;
	}
	while (numero_cifre_bin != 0){
		numero_cifre_bin--;
		if ((numero_decimale >> numero_cifre_bin) & 1){
			printchar('1', colore);
		}else{
			printchar('0', colore);
		}	
	}
}

void unsigned_int_to_stringa (unsigned long int numero, char *buffer, int sizeof_buffer){
	unsigned int divisore = 1;
	unsigned int contatore_buffer = 0;
	while (numero / divisore >= 10){
		divisore *= 10;
	}
	while (divisore > 0){
		if (contatore_buffer <= sizeof_buffer){
			int cifra = numero / divisore;
			buffer[contatore_buffer++] = (char)(cifra + '0');
			numero %= divisore;
			divisore /= 10;
		}
	}
}

unsigned long int hex_to_dec (unsigned long int numero){
	unsigned int divisore = 1;
	unsigned long int valore_ritorno = 0;
	while (numero > 0){
		unsigned long int cifra = numero % 16;
	        valore_ritorno += cifra * divisore;
	        divisore *= 10;
	        numero /= 16;
	}
	return valore_ritorno;
}
