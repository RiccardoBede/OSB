//bool CLIparserGenerico(char *, Comando *, int);
//unsigned int multiInput(SelezioneComando *, unsigned int, char);
//Comando sotto_comando[] = {{}};

SelezioneComando porta_com[] = {{"COM1 (0x3f8)", VGA_TEXT_BIANCO_NERO}, {"Altra", VGA_TEXT_BIANCO_NERO}};

SelezioneComando bound_rate[] = {{"115200", VGA_TEXT_BIANCO_NERO}, {"57600", VGA_TEXT_BIANCO_NERO}, {"38400", VGA_TEXT_BIANCO_NERO}, {"28800", VGA_TEXT_BIANCO_NERO}};

SelezioneComando bit_parita[] = {{"000 (5 bit, no stop)", VGA_TEXT_BIANCO_NERO}, {"001 (5 bit, 1 bit stop", VGA_TEXT_BIANCO_NERO}, {"010 (6 bit, no stop)", VGA_TEXT_BIANCO_NERO}, {"011 (6 bit, 1 bit stop)", VGA_TEXT_BIANCO_NERO}, {"100 (7 bit, no stop)", VGA_TEXT_BIANCO_NERO}, {"101 (7 bit, 1 bit stop)", VGA_TEXT_BIANCO_NERO}, {"110 (8 bit, no stop)", VGA_TEXT_BIANCO_NERO}, {"111 (8 bit, 1 bit stop)", VGA_TEXT_BIANCO_NERO}};

void uartCli (){
	//com 
	char buffer_com[16];
	unsigned short com = multiInput("Porta COM:", porta_com, (sizeof(porta_com) / sizeof(porta_com[0])), VGA_TEXT_BIANCO_NERO); 
	if (com > 0){
		print("\nPorta: 0x", VGA_TEXT_BIANCO_NERO);
		input(buffer_com, 0x1c, sizeof(buffer_com), VGA_TEXT_BIANCO_NERO);
		com = stringa_to_hex(buffer_com);
	}else{
		com = 0x3f8;
	}
	//bound_rate
	unsigned short boundrate = multiInput("Bound rate:", bound_rate, (sizeof(bound_rate) / sizeof(bound_rate[0])), VGA_TEXT_BIANCO_NERO);
	//bit_parita
	unsigned short bitparita = multiInput("Bit di parita e bit di stop:", bit_parita, (sizeof(bit_parita) / sizeof(bit_parita[0])), VGA_TEXT_BIANCO_NERO);

	if (init_com(com, boundrate, bitparita)){
		terminale_uart_rw(com);
	}

}
