__attribute__((destructor)) __attribute__((noreturn)) void reboot (){
	outb(0x64, 0xfe);
}
