/*#include "../../io.h"
#include "../../io_interrup.h"
#include "../../utils/conversioni.h"
#include "../../utils/math.h"
#include "../../alloc/allocatore.h"
*/
bool init_scheda (){
	outb(0x3f9, 0x00);
	outb(0x3fb, 0x80);
	outb(0x3f8, 0x03);
	outb(0x3f9, 0x00);
	outb(0x3fb, 0x03);
	outb(0x3fa, 0xc7);
	outb(0x3fc, 0x0b);
	outb(0x3fc, 0x1e);
	outb(0x3f8, 0xae);

	if (inb(0x3fd) != 0xae){	return false;}

	outb(0x3fc, 0xf);
	return true;
}
