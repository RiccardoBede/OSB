#include "lib/io_interrup.h"
#include "lib/io.h"
#include "lib/alloc/allocatore.h"

void main (){
	//startVGA();
	TAD();
	print("CIAO\tciao\b\n\tciao", VGA_TEXT_BIANCO_NERO);
	
	char buffer[128];
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
	while(1){	__asm__("hlt");};
}
