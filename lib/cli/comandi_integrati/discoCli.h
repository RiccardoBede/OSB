bool CLIparserGenerico(char *, Comando *, int);
extern unsigned short porta_controller_default;

void cambia_unitaCli (){
	print("\nPorta: 0x", VGA_TEXT_BIANCO_NERO);
	char porta[8];
	input(porta, 0x1c, sizeof(porta), VGA_TEXT_BIANCO_NERO);

	if(stringa_uguale_stringa("abort", porta)){
		print("\nPorta non cambiata!", VGA_TEXT_ROSSO_NERO);
		return;
	}

	porta_controller_default = stringa_to_unsigned_short(porta);
	printchar('\n', VGA_TEXT_BIANCO_NERO);
	tipo_unita_montata();
}

void info_discoCli (){
	printchar('\n', VGA_TEXT_BIANCO_NERO);
	tipo_unita_montata();
}

Comando sotto_comando_disco[] = {{"cambia", cambia_unitaCli}, {"info", info_discoCli}};

void discoCli (){
	char buffer[16];
	print(" -", VGA_TEXT_GIALLO_NERO);
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_GIALLO_NERO);
	CLIparserGenerico(buffer, sotto_comando_disco, (sizeof(sotto_comando_disco) / sizeof(sotto_comando_disco[0])));
}
