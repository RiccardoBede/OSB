#define KERNEL_START 0x5000

static unsigned long int INIT_ALLOC = KERNEL_START;
static unsigned long int FINE_ALLOC = KERNEL_START;

//Tabella Allocazione Dinamica
void TAD (unsigned long int KbSizeTab){ //dimensione in KB
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
}

/*	TODO:
 *
 *	Alloc data la grandezza da allocare, restituisce l'indirizzo del primo byte 
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
}
