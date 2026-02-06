bool CLIparserGenerico(char *, Comando *, int);

Comando sotto_comando[] = {{"13h", startVGA}};

void videoCli (){
	char buffer[5];
	print(" mode=", VGA_TEXT_BIANCO_NERO);
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
	CLIparserGenerico(buffer, sotto_comando, (sizeof(sotto_comando) / sizeof(sotto_comando[0])));
}
