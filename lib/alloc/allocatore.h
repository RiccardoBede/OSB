#define KERNEL_START 0x1000

static unsigned long int INIT_ALLOC = KERNEL_START;
//static unsigned long int FINE_ALLOC = KERNEL_START;

//Tabella Allocazione Dinamica
/*void TAD (unsigned long int KbSizeTab){ //dimensione in KB
	print("TAD inizializzato", VGA_TEXT_GIALLO_NERO);
	unsigned char *valoreZona = (char *)INIT_ALLOC;
	while (((KbSizeTab * 1024) - (FINE_ALLOC - INIT_ALLOC)) > 0){
		while (*valoreZona != 0x00){
			*valoreZona &= (unsigned long int)INIT_ALLOC + 1;
			INIT_ALLOC++;
		}
		while ((KbSizeTab * 1024) < (FINE_ALLOC - INIT_ALLOC)){
			if (*valoreZona != 0x00){
				INIT_ALLOC = (unsigned long int)&valoreZona;	
			}
			*valoreZona &= (unsigned long int)(INIT_ALLOC + 1);
			FINE_ALLOC += (INIT_ALLOC)+1;
		}
	}
	print("\nTAD eseguito", VGA_TEXT_GIALLO_NERO);
}*/

/*	Alloc data la grandezza da allocare, restituisce l'indirizzo del primo byte 
 *	es. x -> sizeof (32bit) alloc(sizeof(x)) -> 0Xxx
 *
 *	Allocazione di variabili a lunghezza variabile, se la lunghezza viene superata, 
 *	viene allocato altro spazio in memoria.
 *
 *	Puntatori esterni alla TAD.
 *
 *	Se la TAD si esaurisce, incrementarne la capienza.
 */

void alloc(unsigned long int sizeAlloc){
	char *valoreZona = (char *)INIT_ALLOC;
	unsigned long int byteLiberi = 0;
	if (byteLiberi != sizeAlloc){
		while (*valoreZona != 0x00){
			byteLiberi = 0;
			*valoreZona &= (unsigned long int)(INIT_ALLOC)++;
		}
		byteLiberi++;
		*valoreZona &= (unsigned long int)(INIT_ALLOC)++;
		*valoreZona = 0xff;
	}
	print("ALLOCATO(", VGA_TEXT_GIALLO_NERO);
	printhex((int)((unsigned long int)&valoreZona - sizeAlloc), VGA_TEXT_GIALLO_NERO);
	printchar(',', VGA_TEXT_GIALLO_NERO);
	printhex((int)&valoreZona, VGA_TEXT_GIALLO_NERO);
	print(")\n", VGA_TEXT_GIALLO_NERO);
	INIT_ALLOC = (unsigned long int)&valoreZona;
}
