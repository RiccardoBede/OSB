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
