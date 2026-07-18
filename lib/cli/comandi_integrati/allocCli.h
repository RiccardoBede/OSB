void allocCli (){
	char buffer[8];
	print(" size=", VGA_TEXT_GIALLO_NERO);
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
	print("\ninit:", VGA_TEXT_GIALLO_NERO);
	printhex((unsigned long int)alloc(stringa_to_int(buffer)), VGA_TEXT_BIANCO_NERO);
}

void freeCli (){
	char buffer[8];
	print(" 0x", VGA_TEXT_GIALLO_NERO);
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_GIALLO_NERO);
	printchar('\n', VGA_TEXT_BIANCO_NERO);
	char *ptr = (char *)stringa_to_hex(buffer);
	free(ptr);
}

void tabellaAllocatoreCli (){
	printchar('\n', VGA_TEXT_GIALLO_NERO);
	printTabellaAllocatore();
}
