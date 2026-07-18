void editor (){
	char nome_file[16];
	char tipo_file[4];

	print(" nomeFile=", VGA_TEXT_BIANCO_NERO);
	input(nome_file, 0x1c, sizeof(nome_file), VGA_TEXT_BIANCO_NERO);
	print(" tipoFile=0x", VGA_TEXT_BIANCO_NERO);
	input(tipo_file, 0x1c, sizeof(tipo_file), VGA_TEXT_BIANCO_NERO);
	
	clear();

	print(nome_file, VGA_TEXT_BIANCO_NERO);
	printchar('\n', VGA_TEXT_BIANCO_NERO);

	unsigned char buffer[256];
	input(buffer, 0x01, sizeof(buffer), VGA_TEXT_BIANCO_NERO);

	crea_file(stringa_to_hex(tipo_file), nome_file, buffer);
}
