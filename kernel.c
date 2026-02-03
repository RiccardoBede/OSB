#include "lib/io_interrup.h"
#include "lib/utils/math.h"
#include "lib/io.h"
#include "lib/alloc/allocatore.h"

void main (){
	//startVGA();
	infoAlloc();

	int *a = (int *)alloc(3);
	free(a);

	char buffer[128];
	input(buffer, 0x1c, sizeof(buffer), VGA_TEXT_BIANCO_NERO);
	while(1){	__asm__("hlt");};
}
