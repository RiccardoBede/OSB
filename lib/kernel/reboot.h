#ifndef REBOOT_H
#define REBOOT_H

__attribute__((destructor)) __attribute__((noreturn)) void reboot (){
	outb(0x64, 0xfe);
}

#endif // REBOOT_H
