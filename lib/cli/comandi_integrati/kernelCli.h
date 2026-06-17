bool CLIparserGenerico(char *, Comando *, int);

void rebootCli (){
	reboot();
}

void panicCli (){
	char buffer[128];
	print(" msg=", VGA_TEXT_ROSSO_CHIARO_ROSSO);
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
	panic(buffer);
}

void pciCli (){
	printchar('\n', VGA_TEXT_BIANCO_NERO);
	lista_pci();
}

Comando sotto_comando_kernel [] = {{"reboot", rebootCli}, {"panic", panicCli}, {"pci", pciCli}};

void kernelCli (){
	char buffer[16];
	print(" ?", VGA_TEXT_ROSSO_CHIARO_ROSSO);
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
	CLIparserGenerico(buffer, sotto_comando_kernel, (sizeof(sotto_comando_kernel) / sizeof(sotto_comando_kernel[0])));
}
