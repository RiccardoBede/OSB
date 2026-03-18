__attribute__((destructor)) __attribute__((noreturn)) void panic (char *msg){
	print(msg, VGA_TEXT_ROSSO_CHIARO_ROSSO);
	
	unsigned int eax, ebx, ecx, edx;

	__asm__ ("mov %%eax, %0" : "=r" (eax));
	__asm__ ("mov %%ebx, %0" : "=r" (ebx));
	__asm__ ("mov %%ecx, %0" : "=r" (ecx));
	__asm__ ("mov %%edx, %0" : "=r" (edx));

	print("\nEAX: 0x", VGA_TEXT_BIANCO_NERO);
	printhex(eax, VGA_TEXT_BIANCO_NERO);
	print(" ; EBX: 0x", VGA_TEXT_BIANCO_NERO);
	printhex(ebx, VGA_TEXT_BIANCO_NERO);
	print("\nECX: 0x", VGA_TEXT_BIANCO_NERO);
	printhex(ecx, VGA_TEXT_BIANCO_NERO);
	print(" ; EDX: 0x", VGA_TEXT_BIANCO_NERO);
	printhex(edx, VGA_TEXT_BIANCO_NERO);

	for(;;){
		__asm__("hlt;cli");
	}
}
