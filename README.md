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
> 3. `qemu-system-i386 -cdrom osb.iso -hda <disco.img> -device <tipo>,<id>`

## Filesystem
> [!WARNING] **Il filesystem è ancora in fase di sviluppo !**
> Presenta solo le operazioni di scrittura.
> Le operazioni di lettura sono presenti all'interno della libreria `io_settore.h` ma non sono ancora state implementate all'interno di `filesystem.h`
