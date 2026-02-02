#include "lib/io_interrup.h"
#include "lib/utils/math.h"
#include "lib/io.h"
#include "lib/alloc/allocatore.h"

void main (){
	//startVGA();
//	alloc(2*1024);
//	alloc(3*2048);
//	alloc(1);
//	alloc(3);
//	print("CIAO\tciao\b\n\tciao", VGA_TEXT_BIANCO_NERO);
	printint(12, VGA_TEXT_BIANCO_NERO);

	char buffer[128];
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
	while(1){	__asm__("hlt");};
}
