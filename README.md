> [!WARNING] Ancora in Sviluppo !
> Il Sistema Operativo non è ancora perfettamente funzionante, ed è stato reso pubblico solo per l'esposizione del mio Esame di Stato!

# OSB
Sistema Operativo scritto in C per architetture a 32bit, sviluppato per gestire I/O su porte e periferiche (PCI e ATA/IDE). Presenta in oltre un filesystem.

# Specifiche OSB
OSB deriva dal precedente sistema operativo [BedeskOS](https://www.github.com/RiccardoBede/BedeskOS). Come il precedente il sistema è interamente scritto a mano senza l'utilizzo di nessuna libreria esterna/standard.

## Requisiti di Sistema
1. 100MB di RAM
2. 700MHz di CPU
> ![WARNING]
> Il filesystem presenta per ora solo la possibilità di lavorare con LBA28 quindi:
> 3. < 128GB di HDD/SSD/ATAPI
> ![INFO]
> Presto verrà introdotto il supporto per LBA48 portando la grandezza massima di lavoro fino a 2TB

## Compilazione
### Pacchetti necessari
Arch e derivate: `base-devel` `nasm` `gcc` `ld` `grub` `grub-mkrescue` `xorriso` `mtools`
<br><br>
Debian e derivate: `build-essential` `nasm` `gcc` `grub-mkrescue` `ld` `grub-pc-bin` `grub-common` `xorriso` `mtools`
### Compilazione
1. `make clean`
2. `make`
3. `qemu-system-i386 -cdrom osb.iso -hda <disco.img>`
> [!NOTE] Harware periferico PCI
> Se si vuole inserire hardware periferico tramite QEMU

3. `qemu-system-i386 -cdrom osb.iso -hda <disco.img> -device <tipo>,<id>`

## Filesystem
> [!WARNING] **Il filesystem è ancora in fase di sviluppo !**
> Presenta solo le operazioni di scrittura.
> Le operazioni di lettura sono presenti all'interno della libreria `io_settore.h` ma non sono ancora state implementate all'interno di `filesystem.h`

Presenta la possibilità di: creare, ~~modificare~~, ~~eliminare~~, ~~leggere~~

## Allocatore di memoria
> [!WARNING] **Non presenta nessun controllo !**
> Non è presente il blocco nel caso il deallocatore provi ad azzerare la zona di memoria `0x1000` (Kernel INIT)!
> [!INFO] L'algoritmo è ancora in fase di sviluppo e nelle prossime versioni del sistema, verrà introdotta la possibilità di allocare zone della RAM con flag DMA.

L'allocatore dinamico presenta la possibilità di allocare/liberare zone della RAM (comprese tra `0x0000`~`0x1000`). In oltre presenta anche la possibilità di riutilizzare zone precedentemente liberate come spazio **riallocabile**.

## Comandi di Sistema
OSB presenta ache una shell di sistema che presenta alcuni comandi:
| Nome comando | Argomenti | Sottocomandi | Funzionalità | Funzionante |
| --- | --- | --- | --- | --- |
| `help` | `` | `` | lista dei comandi | `true` |
| `clear` | `` | pulisce lo schermo | `true` |
| `inb` | `porta` | `` | legge il valore di una porta | `true` |
| `outb` | `porta, comando` | `` | invia un comando ad una porta | `true` |
| `alloc` | `size` | `` | restituisce l'indirizzo della zona di dimensione `size` allocata  | `parziale` |
| `free` | `indirizzo zona` | `` | dealloca la zona designata (`0x00`) e la marca come allocabile | `true` |
| `alloctab` | `` | `` | mostra la tabella con gli indirizzi e le grandezze precedentemente deallocate, e rialloca la zona qual'ora la grandezza richiesta sia compatibile con la grandezza | `true` |
