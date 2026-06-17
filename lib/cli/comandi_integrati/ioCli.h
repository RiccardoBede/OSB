void inbCli (){
	char buffer_porta[12];
	print(" 0x", VGA_TEXT_VERDE_NERO);
	input(buffer_porta, 0x1c, sizeof(buffer_porta), VGA_TEXT_VERDE_NERO);
	print("\n0x", VGA_TEXT_BIANCO_NERO);
	printint((unsigned int)inb((unsigned short)stringa_to_hex(buffer_porta)), VGA_TEXT_BIANCO_NERO);
}

void outbCli (){
	char buffer_porta[12], buffer_comando[12];
	print(" 0x", VGA_TEXT_VERDE_NERO);
	input(buffer_porta, 0x39, sizeof(buffer_porta), VGA_TEXT_VERDE_NERO);
	print(", ", VGA_TEXT_BIANCO_NERO);
	print("0x", VGA_TEXT_MAGENTA_NERO);
	input(buffer_comando, 0x1c, sizeof(buffer_comando), VGA_TEXT_MAGENTA_NERO);
	printchar('\n', VGA_TEXT_BIANCO_NERO);
	outb((unsigned short)stringa_to_hex(buffer_porta), (char)stringa_to_hex(buffer_comando));
}

void clearCli (){
	clear();
}
