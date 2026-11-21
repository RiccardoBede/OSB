#include "../../io.h"
#include "../../io_interrup.h"
#include "../selettore_unita.h"
#include "../io_settore.h" 

//SIZEOF del settore * 4
#define SIZEOF_BLOCCO 4

extern unsigned long long int settori_lba32;
extern unsigned long long int settori_lba48_u;
extern bool lba48_attivo;

static unsigned long long int settore_BITMAP = 0;

/*	VALUTARE di fare firme a 32/64 bit per evitare che nell'inserimento dei file vengano inseriti dei blob che possano
 *	far scattare le funzioni con dei falsi positivi
 *
 *	[
 *		creare struct inode, con puntatori a cartella e file, size dei file partizione di appartenenza
 *	]
 *
 *	disco_inizializzato () -> bool
 *
 *	crea_bitmap ()
 *		con firma per essere riconosciuto (0xff)
 *		ogni blocco per bit delle word (2 * char)
 *		e tabella indirizzi degli inode
 *		e firma terminazione della bitmap (0xef)
 *
 * 	crea_part (int settore_inizio, int settore_fine)
 * 		con firma per essere riconosciuto (0xd0)
 * 		partizione logica con lista indode per ogni file
 *
 * 	[
 * 		metto l'indirizzo della partizione LOGICA di base dentro alla BITMAP per evitare di salvare nel superblocco della bitmap
 * 		tutti gli indirizzi degli inode ed evitare che la size della bitmap vada a corrompere dei settori contigui che contengono
 * 		degli inode
 * 	]
 *
 * 	crea_inode (struct struttura_inode)
 * 		con firma per essere riconosciuto (0x1f)
 *		lista dei file e cartelle contenute
 * 		e firma terminazione dell'inode (0xf1)
 * 		
 * 	crea_file e crea_cartella (partizione di appartenenza, nome, tipologia_file)
 * 		con firma per tipologia di file o cartella
 * 		per la cartella VALUTARE di fare una struct da mette per fare una tabella con i file di appartenenza
 *
 * 	EVENTUALI 
 *
 * 	formattazione_disco (bool zeri)
 * 		con zeri per formattazione di zeri
 * 		e senza bool con rimozione o ripristino della bitmap con tutti 0 per bit
 *
 *
 */


//prototipi
void ripara_fs();
bool disco_inizializzato();
void crea_bitmap (DISCO_MONTATO);

//inserire la funzione appena dopo tipo_unita_montata() per passare il DISCO_MONTATO
void INIT_fs (DISCO_MONTATO tipo_disco){
	print("\nINIT FS", VGA_TEXT_BIANCO_NERO);
	unsigned long long int cerca_bitmap = 1;
	unsigned char firma_bitmap[2];
	
	if (SETTORE_BITMAP != 0){	return;}

	while (((cerca_bitmap < settori_lba32) && !lba48_attivo) || ((cerca_bitmap < settori_lba48_u) && lba48_attivo)){
		leggi_settore(tipo_disco, cerca_bitmap, firma_bitmap, sizeof(firma_bitmap));
		if ((firma_bitmap[0] == firma_bitmap[1]) && firma_bitmap[0] == 0xff){ //accorciare il tempo di attesa perchè se esp1 è falsa in and non vengono controllati gli altri esp 
			settore_BITMAP = cerca_bitmap;
			return;
		}
	}
	
	SelezioneComando bitmap_non_trovata[] = {{"Ripara filesystem", VGA_TEXT_VERDE_NERO}, {"Ricrea BITMAP (FORMATTAZIONE DISCO)!", VGA_TEXT_ROSSO_CHIARO_ROSSO}, {"Esci", VGA_TEXT_GIALLO_NERO}};
	switch (multiInput("Superblocco BITMAP non trovato!", bitmap_non_trovata, (sizeof(bitmap_non_trovata) / sizeof(bitmap_non_trovata[0]), VGA_TEXT_BIANCO_NERO))){
		case 0:
			clear();
			print("RIPARAZIONE FILESYSTEM\n", VGA_TEXT_VERDE_NERO);
			ripara_fs();
			break;
		case 1:
			clear();
			print("INIZIALIZZAZIONE DISCO\n", VGA_TEXT_GIALLO_NERO);
			crea_bitmap(tipo_disco);
			break;
		case 2:
			print("NUSSUNA OPZIONE E\' STATA ESEGUITA!\n", VGA_TEXT_GIALLO_NERO);
			break;
		default:
			print("NUSSUNA OPZIONE E\' STATA ESEGUITA!\n", VGA_TEXT_GIALLO_NERO);
			break;
	}
	return;
}


void crea_bitmap(DISCO_MONTATO tipo_disco){
	unsigned long long int sizeof_blocchi = 0;
	/*
	 *Per mettere bit a bit da sinistra a destra dentro ad un char devo fare
	 *uno shift bit a bit << e la formula è 0x80 che è l'ottavo bit del char 
	 *e per aggiungere il bit prima quindi quello contiguo più a destra
	 *		devo fare 0x80 + (0x80 / 2)
	 *
	 *L'unico accorgimemto è per 0xff quindi char saturo e a quel punto 
	 *devo fare 0x80 * 2 + (0x80 * 2 / 2)
	 *
	 *Dimensione massima accetta da lba48 è 2tb quidi 2 000 000 000 000
	 *2 tb -> 2 000 000 000 000 * 2 -> settore (512 byte) -> 4 000 000 000 000
	 *
	 * settore (512 byte) / 4 -> 1 000 000 000 000 bit,
	 * quidi la dimensione massima è di circa 125 MB
	 *
	 *quindi o faccio un array di char con 64 bit quindi 8 oppure multiplo per
	 *fare tutto in meno accessi al disco possibili
	 *
	 *quindi o si fa un accesso unico altrimenti ciclata con while oppure
	 *ciclo di azzeramento bit dell'array e unica scrittura
	*/

	print("CREAZIONE BITMAP", VGA_TEXT_BIANCO_NERO);
	
	(!lba48_attivo) ? sizeof_blocchi = (settori_lba32 / SIZEOF_BLOCCO) : sizeof_blocchi = (settori_lba48_u / SIZEOF_BLOCCO);

	settore_BITMAP = 1;
	scrivi_settore(tipo_disco, settore_BITMAP, , SETTORE_BITMAP);
}
