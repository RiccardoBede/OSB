#ifndef CPU_H
#define CPU_H

unsigned long int cicloCPU_32 (){
	unsigned long int ciclo;
	__asm__("rdtsc" : "=a"(ciclo));
	return ciclo;
}

#endif // CPU_H
