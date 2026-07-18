> [!WARNING] 
> **Ancora in fase di sviluppo !** <br>
> Il Sistema Operativo presenta alcune sezioni ancora in fase di sviluppo, a breve diventerà completamente operativo.

# OSB
Sistema Operativo scritto in C per architetture a 32bit, sviluppato per gestire I/O su porte e periferiche (ATA/IDE, PCI). Presenta inoltre un filesystem.

# Specifiche OSB
OSB deriva dal precedente sistema operativo [BedeskOS](https://www.github.com/RiccardoBede/BedeskOS). Come il precedente, questo sistema è interamente scritto a mano senza l'utilizzo di librerie esterne/standard.

## Requisiti di Sistema
1. 100MB di RAM
2. 700MHz di CPU
> [!WARNING]
> Il filesystem presenta per ora solo la possibilità di lavorare con LBA28 quindi:
> <br> 3. < 128GB di HDD/SSD/ATAPI

> [!NOTE]
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
> [!NOTE]
> **Hardware periferico PCI**
> Comando per montare hardware periferico tramite QEMU

3. `qemu-system-i386 -cdrom osb.iso -hda <disco.img> -device <tipo>,<id>`

## PCI (Peripheral Component Interconnect)
Il sistema consente la mappatura delle periferiche PCI (PnP) e ne mostra l'indirizzo di base (BAR - Base Address Register) e tipologia di trasmissione dati I/O (MMIO, VirtIO).

## Filesystem
> [!WARNING] 
> **Il filesystem è ancora in fase di sviluppo !**
> Presenta solo le operazioni di scrittura.
> Le operazioni di lettura sono presenti all'interno della libreria `io_settore.h` ma non sono ancora state implementate all'interno di `filesystem.h`

Permette di: creare (in futuro anche modificare, eliminare, leggere) files su diversi dispositivi di archiviazione: ATA/IDE, ATAPI, PCI solo se VirtIO.
Il filesystem presenta una sequenza di scrittura e ricerca **sequenziale** quindi è sconsigliato per dischi di grandi dimensioni.
> [!NOTE] 
> Verrà implementato un'algoritmo di indicizzazione.

Il filesystem presenta diverse intestazioni (primi 16 byte di ogin settore) per i file.
| Intestazione | Funzione |
| --- | --- |
| `0xbb` | file di testo normale |
| `0xaa` | file avviabile |
| `0xff` | **settore info** |
| `0xbf` | **settore bitmap** |

#### 0xbb
Il settore contiene solo testo.

#### 0xaa
> [!NOTE]
> Non ancora implementato!

Il settore contiene codice (binario) che verrà allocato in una zona di memoria con flag avviabile.

#### 0xff
> [!NOTE] 
> Temporaneamente disabilitato. In fase di sviluppo ottimizzazione del tempo di indicizzazione del primo avvio.

Questa intestazione serve al file `settore_info.h` per caricare le preferenze di sistema scelte dall'utente.

#### 0xbf
> [!NOTE] 
> Non ancora implementato!

Questa intesazione indica che il settore coincide con la tabella di indicizzazione dei file presenti sul disco.

## Allocatore di memoria
> [!WARNING] 
> **Non presenta nessun controllo !** <br>
> Non è presente il blocco nel caso il deallocatore provi ad azzerare la zona di memoria `0x1000` (Kernel INIT)!

> [!NOTE]
> L'algoritmo è ancora in fase di sviluppo e nelle prossime versioni del sistema, verrà introdotta la possibilità di allocare zone della RAM con flag DMA.

L'allocatore dinamico offre la possibilità di allocare o liberare zone della RAM (comprese tra `0x0000`~`0x1000`). Inoltre offre la possibilità di riutilizzare zone precedentemente liberate come spazio nuovamente allocabile.

## Comandi di Sistema
OSB presenta ache una shell di sistema che presenta alcuni comandi:
| Nome comando | Argomenti | Sottocomandi | Funzionalità | Funzionante |
| --- | --- | --- | --- | --- |
| `help` | `/` | `/` | lista dei comandi | `true` |
| `clear` | `/` | `/` | pulisce lo schermo | `true` |
| `inb` | `porta` | `/` | legge il valore di una porta | `true` |
| `outb` | `porta, comando` | `/` | invia un comando ad una porta | `true` |
| `alloc` | `size` | `/` | restituisce l'indirizzo della zona di dimensione `size` allocata  | `parziale` |
| `free` | `indirizzo zona` | `/` | dealloca la zona designata (`0x00`) e la marca come allocabile | `true` |
| `alloctab` | `/` | `/` | mostra la tabella con gli `indirizzi` e le `size` precedentemente deallocate, e rialloca la zona qualora la grandezza richiesta sia compatibile con la grandezza | `true` |
| `video` | `13h`| `/` | imposta la modalità video | `disattivato` |
| `sys` | `/` | `reboot`, `panic <msg>`, `pci` | esegue comandi di sistema | `true` |
| `disco` | `/` | `cambia`, `info` | cambia/richiede le variabili di stato relative al dispositivo di archiviazione | `true` |
| `editor` | `nomefile`, `tipo file` | `/` | permette di utlizzare le funzioni del filesystem sul dispositivo di archiviazione | `parziale` |
