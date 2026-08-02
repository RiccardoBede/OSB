//bool CLIparserGenerico(char *, Comando *, int);
//unsigned int multiInput(SelezioneComando *, unsigned int, char);
//Comando sotto_comando[] = {{}};

SelezioneComando porta_com[] = {{"COM1 (0x3f8)", VGA_TEXT_BIANCO_NERO}, {"Altra", VGA_TEXT_BIANCO_NERO}};

SelezioneComando bound_rate[] = {{"115200", VGA_TEXT_BIANCO_NERO}, {"57600", VGA_TEXT_BIANCO_NERO}, {"38400", VGA_TEXT_BIANCO_NERO}, {"28800", VGA_TEXT_BIANCO_NERO}};

SelezioneComando bit_parita[] = {{"000 (5 bit, no stop)", VGA_TEXT_BIANCO_NERO}, {"001 (5 bit, 1 bit stop", VGA_TEXT_BIANCO_NERO}, {"010 (6 bit, no stop)", VGA_TEXT_BIANCO_NERO}, {"011 (6 bit, 1 bit stop)", VGA_TEXT_BIANCO_NERO}, {"100 (7 bit, no stop)", VGA_TEXT_BIANCO_NERO}, {"101 (7 bit, 1 bit stop)", VGA_TEXT_BIANCO_NERO}, {"110 (8 bit, no stop)", VGA_TEXT_BIANCO_NERO}, {"111 (8 bit, 1 bit stop)", VGA_TEXT_BIANCO_NERO}};

SelezioneComando tipo_uart[] = {{"Terminale (r/w)", VGA_TEXT_BIANCO_NERO}, {"Lettura (r)", VGA_TEXT_BIANCO_NERO}, {"Scrittura (w) disco/manuale", VGA_TEXT_BIANCO_NERO}};

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

	switch (multiInput("Tipo UART:", tipo_uart, (sizeof(tipo_uart) / sizeof(tipo_uart[0])), VGA_TEXT_BIANCO_NERO)){
		case 0:
			if (init_com(com, boundrate, bitparita)){
				terminale_uart_rw(com);
			}
			break;
		case 1:
			char buffer_fine[8];
			char buffer_sizeof[8];
			print("\nCarattere fine: 0x", VGA_TEXT_BIANCO_NERO);
			input(buffer_fine, 0x1c, sizeof(buffer_fine), VGA_TEXT_BIANCO_NERO);
			
			print("\nSize buffer: ", VGA_TEXT_BIANCO_NERO);
			input(buffer_sizeof, 0x1c, sizeof(buffer_sizeof), VGA_TEXT_BIANCO_NERO);
			char *buffer = (char *)alloc(stringa_to_int(buffer_sizeof));
			
			int contatore_carattere_buffer = 1;
			while (contatore_carattere_buffer <= stringa_to_int(buffer_sizeof)+1){
				char input_buffer = inputNoInterrup();
				if (input_buffer == 0x01){
					buffer[contatore_carattere_buffer++] = stringa_to_hex(buffer_fine);		
				}
				if (input_buffer != 0x00){
					buffer_fine[contatore_carattere_buffer++] = input_buffer;
				}
			}
			buffer[contatore_carattere_buffer] = stringa_to_hex(buffer_fine);
			break;
		case 2:
			if (monoInput("Disco/Manuale [d/m]: ", 0x20, 0x32, VGA_TEXT_BIANCO_NERO)){
				printchar('\n', VGA_TEXT_BIANCO_NERO);
				//TODO: selettore file o numero settore
				return;
			}else{
				printchar('\n', VGA_TEXT_BIANCO_NERO);
				if (init_com(com, boundrate, bitparita)){
					terminale_uart_rw(com);
				}
			}
			break;
		default:
			if (init_com(com, boundrate, bitparita)){
				terminale_uart_rw(com);
			}
			break;
	}
}
