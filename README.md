> [!WARNING] Ancora in Sviluppo !
> Il Sistema Operativo non è ancora perfettamente funzionante, ed è stato reso pubblico solo per l'esposizione del mio Esame di Stato!

# OSB
Sistema Operativo scritto in C per architetture a 32bit, sviluppato per gestire I/O su porte e periferiche (PCI e ATA/IDE). Presenta in oltre un filesystem.

#Specifiche OSB
OSB deriva dal precedente sistema operativo [BedeskOS](https://www.github.com/RiccardoBede/BedeskOS). Come il precedente il sistema è interamente scritto a mano senza l'utilizzo di nessuna libreria esterna/standard.

##Requisiti di Sistema
1. 100MB di RAM
2. 700MHz di CPU
> ![WARNING]
> Il filesystem presenta per ora solo la possibilità di lavorare con LBA28 quindi:
> 3. < 128GB di HDD/SSD/ATAPI
> ![INFO]
> Presto verrà introdotto il supporto per LBA48 portando la grandezza massima di lavoro fino a 2TB
