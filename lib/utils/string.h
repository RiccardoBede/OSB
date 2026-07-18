int stringa_in_stringa (char *regex, char *buffer){
	unsigned int sizeof_regex = 0;
	unsigned int sizeof_buffer = 0;

	unsigned int conta_carattere_regex = 0;
	unsigned int conta_carattere_buffer = 0;

	unsigned int corrispondenza = 0;

	while (regex[sizeof_regex] != '\0'){	sizeof_regex++;}
	while (buffer[sizeof_buffer] != '\0'){	sizeof_buffer++;}
	
	if (sizeof_regex > sizeof_buffer){	return -1;}

	for (conta_carattere_buffer; buffer[conta_carattere_buffer] != '\0'; conta_carattere_buffer++){
		if (corrispondenza == sizeof_regex){
			return (conta_carattere_buffer - sizeof_regex);
		}
		if (regex[conta_carattere_regex] == buffer[conta_carattere_buffer]){
			corrispondenza++;
			conta_carattere_regex++;
		}else{
			corrispondenza = 0;
			conta_carattere_regex = 0;
		}
	}
	return -1;
}

int char_in_stringa (char regex, char *buffer){
	unsigned int sizeof_buffer = 0;
	unsigned int carattere_buffer = 0;

	while (buffer[sizeof_buffer] != '\0'){	sizeof_buffer++;}

	for (carattere_buffer; carattere_buffer < sizeof_buffer; carattere_buffer++){
		if(buffer[carattere_buffer] == regex){
			return carattere_buffer;
		}
	}
	return -1;
}

bool stringa_uguale_stringa (char *buffer1, char *buffer2){
	unsigned int sizeof_buffer1 = 0;
	unsigned int sizeof_buffer2 = 0;

	unsigned int corrispondenza = 0;

	unsigned int conta_carattere = 0;

	while (buffer1[sizeof_buffer1] != '\0'){	sizeof_buffer1++;}
	while (buffer2[sizeof_buffer2] != '\0'){	sizeof_buffer2++;}

	if (sizeof_buffer1 != sizeof_buffer2){	return false;}

	while (buffer1[conta_carattere] != '\0'){
		if (buffer1[conta_carattere] == buffer2[conta_carattere]){	
			corrispondenza++;
		}else{
			return false;
		}
		conta_carattere++;
	}
	return true;
}
