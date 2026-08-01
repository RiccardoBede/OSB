#define COM 0x3f8

#define FREQ_CLOCK 115200

/*void init_com (){
	outb(COM + 1, 0x00);
	outb(COM + 3, (1 << 8) & 0xff);
	outb(COM, 0x03); //freq low
	outb(COM, 0x00); //freq high
	outb(COM + 3, (3 << 0) & 0xff); //110 = 11 per 8 bit e 0 no stop
	
	outb(COM + 2, 0xc7);

	outb(COM + 4, 0x0b);
	outb(COM + 4, 0x1e);
	outb(COM, 0xae);

	if (inb(COM) != 0xae){
		//panic("UART chip ERROR");
	}
	outb(COM + 4, 0x0f); //abilita com

	while (1){
		while ((inb(COM + 5) & 1) == 0);
		printchar(inb(COM), VGA_TEXT_BIANCO_NERO);
		while ((inb(COM + 5) & 0x20) == 0){
			char buffer[2];
			input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
			outb(COM, buffer[0]);
		}
	}

}*/

bool init_com (unsigned int com, unsigned long int frequenza_com, unsigned short bit_parita){
	outb(com + 1, 0x00); //disabilita interrup
	outb(com + 3, (1 << 8) & 0xff); //abilita DLAB per baund_rate

	if (frequenza_com == 0){ //bound_rate massimo 115200
		outb(com, 0x01);
	}else{
		outb(com, frequenza_com);
	}
	outb(com, 0x00);

	if (bit_parita <= 7){
		outb(com + 3, (bit_parita << 0) & 0xff); 
	}else{
		return false;
	}
	
	outb(com + 2, 0xc7); //fifo + 14 byte
	outb(com + 4, 0x0b); //interrup attivi
	outb(com + 4, 0x1e); //test chip
	outb(com, 0xae); //test
	
	if (inb(com) != 0xae){
		print("Errore test chip UART!\n", VGA_TEXT_ROSSO_NERO);
		if (monoInput("Continuare [y/n]: ", 0x15, 0x35, VGA_TEXT_GIALLO_NERO)){
			outb(com + 4, 0x0f); //abilita com
			return true;
		}else{
			return false;
		}
	}
	outb(com + 4, 0x0f);
	return true;
}

void terminale_uart_rw (unsigned int com){
	print("\nPer uscire <ESC>\n", VGA_TEXT_GIALLO_NERO);

	while (1){
		if ((inb(com + 5) & 0x01)){
			char output_uart = inb(com);
			switch (output_uart){
				case 0x7f:
					cancellachar();
					cursore();
					break;
				case 0xd:
					cancellaCursore();
					stampaAcapo();
					cursore();
				case 0x9:
					stampaTab();
					cursore();
					break;
				default:
					printchar(output_uart, VGA_TEXT_GRIGIO_SCURO_NERO);
					break;
			}
		}

		if (inb(STATO_TASTIERA) & 0x01){
			char input_uart = inputNoInterrup();
			if (input_uart != 0x00){ //TODO: return per ESC
				printchar(input_uart, VGA_TEXT_BIANCO_NERO);
				outb(com, input_uart);
			}
			if (input_uart == 0xff){
				return;
			}
		}
	}
}
