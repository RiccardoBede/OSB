typedef struct {
	unsigned int sizeof_zona;
	unsigned long int ptr_zona;
}Tabella_MMU __attribute__((packed));

static unsigned short int contatore_tabella_mmu = 0;
Tabella_MMU tabella_mmu[1024];

bool alloc_ptr_mmu (unsigned int sizeof_zona, void *puntatore){
	if ((contatore_tabella_mmu + 1) <= (sizeof(tabella_mmu) / sizeof(tabella_mmu[0]))){
		print("MMU->ALLOC (ptr:0x", VGA_TEXT_GIALLO_NERO);
		printhex((unsigned long int)puntatore, VGA_TEXT_GIALLO_NERO);
		print(", ", VGA_TEXT_GIALLO_NERO);
		printint(sizeof_zona, VGA_TEXT_GIALLO_NERO);
		print(") ", VGA_TEXT_GIALLO_NERO);
		tabella_mmu[contatore_tabella_mmu++] = (Tabella_MMU){sizeof_zona, (unsigned long int)puntatore};
		return true;
	}
	print("MMU->ALLOC/ERR", VGA_TEXT_GIALLO_NERO);
	return false;
}

bool free_ptr_mmu (void *puntatore){
	unsigned short int contatore_tabella = 0;
	unsigned int byte_pulizia = 0;
	for (contatore_tabella; contatore_tabella <= (sizeof(tabella_mmu) / sizeof(tabella_mmu[0])) || contatore_tabella <= contatore_tabella_mmu; contatore_tabella++){
		if ((unsigned long int)tabella_mmu[contatore_tabella].ptr_zona == (unsigned long int)puntatore){
			char **ptr_pulitore = (char **)tabella_mmu[contatore_tabella].ptr_zona;
			for (byte_pulizia; byte_pulizia <= tabella_mmu[contatore_tabella].sizeof_zona; byte_pulizia++){
				ptr_pulitore[byte_pulizia] = 0x00;
			}
			print("MMU->FREE (ptr:0x", VGA_TEXT_GIALLO_NERO);
			printhex((unsigned long int)puntatore, VGA_TEXT_GIALLO_NERO);
			print(", ", VGA_TEXT_GIALLO_NERO);
			printint(tabella_mmu[contatore_tabella].sizeof_zona, VGA_TEXT_GIALLO_NERO);
			print(") ", VGA_TEXT_GIALLO_NERO);
			return true;
		}
	}
	print("MMU->FREE/ERR", VGA_TEXT_GIALLO_NERO);
	return false;
}
