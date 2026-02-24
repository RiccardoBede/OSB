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

char* num_to_char_bin (unsigned long int numero_decimale){
	char buffer_char[32];
	unsigned long int numero_cifre_decimale = numero_decimale;
	unsigned int numero_cifre_bin = 0;
	while (numero_cifre_decimale > 0){
		numero_cifre_decimale /= 2;
		numero_cifre_bin++;
	}
	unsigned int cifra = 0;
	while (cifra < (sizeof(numero_decimale) - numero_cifre_bin)){
		buffer_char[cifra] = 0x30;
		cifra++;
	}
	while (cifra < numero_cifre_bin){
		buffer_char[cifra] = ((numero_decimale << cifra) & 1) ? 0x31 : 0x30;
		cifra++;
	}
	return buffer_char;
}
