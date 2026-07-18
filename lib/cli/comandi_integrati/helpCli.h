void helpCli (){
	print("\nhelp     : lista dei comandi\n", VGA_TEXT_BIANCO_NERO);
	print("clear    : pulisce lo schermo\n", VGA_TEXT_BIANCO_NERO);
	print("inb      : (porta) leggi il valore di una porta\n", VGA_TEXT_BIANCO_NERO);
	print("outb     : (porta, comando) inserisci comando in una porta\n", VGA_TEXT_BIANCO_NERO);
	print("alloc    : (size) alloca dinamicamente (size)byte\n", VGA_TEXT_BIANCO_NERO);
	print("free     : (puntatore) dealloca la zona di ram allocata\n", VGA_TEXT_BIANCO_NERO);
	print("alloctab : mostra la tabella di allocazione\n", VGA_TEXT_BIANCO_NERO);
	print("video    : [13h] imposta la modalita video\n", VGA_TEXT_BIANCO_NERO);
	print("sys      : [reboot, panic (msg), pci] richiama funzioni di sistema\n", VGA_TEXT_BIANCO_NERO);
	print("disco    : [cambia (porta disco), info] interroga il disco\n", VGA_TEXT_BIANCO_NERO);
}
