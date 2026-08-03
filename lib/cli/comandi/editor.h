void editor (){
	char nome_file[16];
	char tipo_file[4];

	print(" nomeFile=", VGA_TEXT_BIANCO_NERO);
	input(nome_file, 0x1c, sizeof(nome_file), VGA_TEXT_BIANCO_NERO);
	print(" tipoFile=0x", VGA_TEXT_BIANCO_NERO);
	input(tipo_file, 0x1c, sizeof(tipo_file), VGA_TEXT_BIANCO_NERO);

	if (monoInput(" modalita=[l/s]: ", 0x26, 0x1f, VGA_TEXT_BIANCO_NERO)){
		if (cerca_file(stringa_to_hex(tipo_file), nome_file) != 0){
			clear();

			static char buffer[1024];
			char num_parte[8];
				
			print("Parte file: ", VGA_TEXT_BIANCO_NERO);
			input(num_parte, 0x1c, sizeof(num_parte), VGA_TEXT_BIANCO_NERO);
			
			clear();

			leggi_file(stringa_to_hex(tipo_file), nome_file, buffer, sizeof(buffer), stringa_to_int(num_parte));

			print(nome_file, VGA_TEXT_BIANCO_NERO);
			printchar('\n', VGA_TEXT_BIANCO_NERO);
			print(buffer, VGA_TEXT_BIANCO_NERO);
		}else{
			print("File inesistente!", VGA_TEXT_ROSSO_NERO);
		}
	}else{
		clear();

		print(nome_file, VGA_TEXT_BIANCO_NERO);
		printchar('\n', VGA_TEXT_BIANCO_NERO);

		unsigned char buffer[256];
		input(buffer, 0x01, sizeof(buffer), VGA_TEXT_BIANCO_NERO);

		crea_file(stringa_to_hex(tipo_file), nome_file, buffer);
	}
}
