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
	
	switch (bit_parita){
		case 0:
			outb(com + 3, (0 << 0) & 0xff); //000 = 5 bit no stop
			break;
		case 1:
			case (com +3, (1 << 0) & 0xff); //001 = 5 bit 1 bit stop
			break;
		
		//TODO: tutte le casistiche fino a 111
	}
}
