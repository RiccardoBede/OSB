#define ALLOC_START 0x00
#define KERNEL_INIT 0x1000

static unsigned long int INIT_ALLOC = ALLOC_START;
static bool verbose = false;

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

void infoAlloc (){
	verbose = true;
}

unsigned long int alloc(unsigned long int sizeAlloc){
	char *ptr = (char *)INIT_ALLOC;
	int byte_liberi = 0;
	while (byte_liberi < sizeAlloc + 1){
		if (*ptr != 0x00){
			byte_liberi = 0;
			INIT_ALLOC++;
		}
		byte_liberi++;
		INIT_ALLOC++;
		ptr = (char *)INIT_ALLOC;
	}
	ptr[0] = sizeAlloc;

	if (verbose){
		print("ALLOC (init: 0x", VGA_TEXT_GIALLO_NERO);
		printhex((int)ptr, VGA_TEXT_GIALLO_NERO);
		print(", byte: ", VGA_TEXT_GIALLO_NERO);
		printint(ptr[0], VGA_TEXT_GIALLO_NERO);
		print(")\n", VGA_TEXT_GIALLO_NERO);
	}

	return (char)ptr;
}

void free (void *puntatore){
	char *ptr = (char *)puntatore;
	unsigned long int contatoreZone = 1;
	while (contatoreZone < ptr[0]){
		ptr[contatoreZone] = 0x00;
		contatoreZone++;
	}
	ptr[0] = 0x00;

	if (verbose){
		print("FREE (init: 0x", VGA_TEXT_GIALLO_NERO);
		printhex((int)puntatore, VGA_TEXT_GIALLO_NERO);
		print(")\n", VGA_TEXT_GIALLO_NERO);
	}
}
