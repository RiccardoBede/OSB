#define KERNEL_START 0x1000

static unsigned long int INIT_ALLOC = KERNEL_START;
static unsigned long int FINE_ALLOC = KERNEL_START;

//Tabella Allocazione Dinamica
void TAD (unsigned long int KbSizeTab){ //dimensione in KB
	unsigned char *valoreZona = (char *)INIT_ALLOC;
	while (((KbSizeTab * 1024) - (FINE_ALLOC - INIT_ALLOC)) > 0){
		while (*valoreZona != 0x00){
			*valoreZona &= INIT_ALLOC + 1;
			INIT_ALLOC++;
		}
		while ((FINE_ALLOC - INIT_ALLOC) <= (KbSizeTab * 1024)){
			if (*valoreZona != 0x00){
				INIT_ALLOC = &valoreZona;	
			}
			*valoreZona &= (INIT_ALLOC + 1);
			FINE_ALLOC = (INIT_ALLOC++);
		}
	}
}

void alloc(unsigned long int sizeAlloc){
	
}
