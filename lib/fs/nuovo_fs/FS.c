#include "../../io.h"
#include "../../io_interrup.h"
#include "../selettore_unita.h"
#include "../io_settore.h" 

//SIZEOF del settore * 4
#define SIZEOF_BLOCCO 4

extern long long settori_lba32;
extern long long settori_lba48_u;

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

