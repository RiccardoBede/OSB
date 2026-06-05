#define FREQUENZA_PIT 1193182

void wait (unsigned long int tempo){
	
	unsigned long int cicli = 0;

	outb(0x43, 0x36);
	outb(0x40, 255 & 0xff);
	outb(0x40, (255 >> 8) & 0xff);

	outb (0x43, 0x00);
	while (cicli != (tempo * 5 *  potenza(10, 3))){
		if (inb(0x40) == 122){	cicli++;}
	}
}
