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

void logoutCli (){
	while (1){
		unsigned long int seed = cicloCPU_32();
		printcharat((seed % 0xff), (seed % ((80*25)+1)), (seed % 0xf+1)); 
		if (inputNoInterrup() == 0x01){	
			clear();
			break;
		}
	}
}

Comando sotto_comando_kernel [] = {{"reboot", rebootCli}, {"panic", panicCli}, {"pci", pciCli}, {"logout", logoutCli}};

void kernelCli (){
	char buffer[16];
	print(" ?", VGA_TEXT_ROSSO_CHIARO_ROSSO);
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
	CLIparserGenerico(buffer, sotto_comando_kernel, (sizeof(sotto_comando_kernel) / sizeof(sotto_comando_kernel[0])));
}
