#define PORTA_CONF 0xcf8
#define PORTA_DATA 0xcfc

#define BIT_ABILITAZIONE 31
#define BIT_NUMERO_BUS 16
#define BIT_NUMERO_DIS 11
#define BIT_NUMERO_FUN 8
#define BIT_OFSET_REG 2

void outl (unsigned int porta, unsigned long int valore){
	__asm__ volatile ("outl %%eax, %%dx" :: "a"(valore), "Nd"(porta));
}

unsigned long int inl (unsigned int porta){
	unsigned long int valore;
	__asm__ volatile ("inl %%dx, %%eax" : "=a"(valore) : "Nd"(porta));
	return valore;
}

//PCI
//	Classe
//		Sottoclasse
//			ProgIF

typedef struct{
	unsigned char progif;
	char nome_progif[32];
}ProgIf;

typedef struct{
	unsigned char sottoclasse;
	char nome_sottoclasse[32];
	ProgIf progif[16];
}Sottoclasse;

typedef struct{
	unsigned char classe;
	char nome_classe[32];
	Sottoclasse sottoclasse[16];
}PCI_device;


PCI_device pci_device[] = {
    {0x00, "sconosciuto", {
        {0x00, "sconosciuto", {
            {0x00, "sconosciuto"}
        }}
    }},
    {0x01, "Archiviazione Massa", {
        {0x01, "IDE", {
            {0x00, "ISA"},
            {0x05, "PCI"},
            {0x0a, "ISA + PCI"},
            {0x0f, "PCI + ISA"},
            {0x80, "ISA (BUS master)"},
            {0x85, "PCI (BUS master"},
            {0x8a, "ISA + PCI (BUS master)"},
            {0x8f, "PCI + ISA (BUS master)"}
        }},
        {0x02, "Floppy Disk", {
            {0x00, ""}
        }},
        {0x03, "IPI", {
            {0x00, ""}
        }},
        {0x04, "RAID", {
            {0x00, ""}
        }},
        {0x05, "ATA", {
            {0x20, "DMA singolo"},
            {0x30, "DMA multi"}
        }},
        {0x06, "Serial ATA", {
            {0x00, "Normale"},
            {0x01, "AHCI 1"},
            {0x02, "Serial BUS"}
        }},
        {0x07, "SCSI", {
            {0x00, "SAS"},
            {0x01, "Serial BUS"}
        }},
        {0x08, "SSD", {
            {0x01, "NVMHCI"},
            {0x02, "NVMe"}
        }}, 
        {0x80, "Sconosciuto", {
            {0x00, ""}
        }}
    }},
	{0x02, "Network Controller", {
		{0x0, "Ethernet", {
			{0x00, ""}
		}},
		{0x01, "Token Ring", {
            {0x00, ""}
        }},
        {0x02, "FDDI", {
            {0x00, ""}
        }},
        {0x03, "ATM", {
            {0x00, ""}
        }},
        {0x04, "ISDN", {
            {0x00, ""}
        }},
        {0x05, "WorldFip", {
            {0x00, ""}
        }},
        {0x06, "PICMG 2.4 Multi", {
            {0x00, ""}
        }},
        {0x07, "Infinityband", {
            {0x00, ""}
        }},
        {0x08, "Fabric", {
            {0x00, ""}
        }}, 
		{0x80, "Sconosciuto", {
			{0x00, ""}
		}}
	}},
	{0x03, "Display Controller", {
		{0x00, "VGA Controller", {
			{0x00, "VGA"},
			{0x01, "8514"}
		}},
		{0x01, "XGA Controller", {
			{0x00, ""}
		}},	
		{0x02, "3D Controller", {
			{0x00, ""}
		}},	
		{0x80, "Sconosciuto", {
			{0x00, ""}
		}}
	}},
	{0x04, "Multimedia Controller", {
		{0x00, "Video Controller", {
			{0x00, ""}
		}},
		{0x01, "Audio Controller", {
			{0x00, ""}
		}},
		{0x02, "Telefono Controller", {
			{0x00, ""}
		}},
		{0x03, "Audio", {
			{0x00, ""}
		}},
		{0x80, "Sconosciuto", {
			{0x00, ""}
		}}
	}},
	{0x05, "Memory Controller", {
		{0x00, "RAM Controller", {
			{0x00, ""}
		}},
		{0x01, "Flash Controller", {
			{0x00, ""}
		}},
		{0x80, "Sconosciuto", {
			{0x00, ""}
		}}
	}},
	{0x06, "Bridge", {
		{0x00, "Host Bridge", {
			{0x00, ""}
		}},
		{0x01, "ISA Bridge", {
			{0x00, ""}
		}},
		{0x02, "EISA Bridge", {
			{0x00, ""}
		}},
		{0x03, "MCA Bridge", {
			{0x00, ""}
		}},
		{0x04, "PCI to PCI", {
			{0x00, "Normale"},
			{0x01, "Sottrattivo"}
		}},
		{0x05, "PCMCIA Bridge", {
			{0x00, ""}
		}},
		{0x06, "NuBUS Bridge", {
			{0x00, ""}
		}},
		{0x07, "CardBUS Bridge", {
			{0x00, ""}
		}},
		{0x08, "RACEway Bridge", {
			{0x00, "Transparent Mode"},
			{0x01, "Endpoint Mode"}
		}},
		{0x09, "PCI to PCI", {
			{0x40, "Primo BUS per CPU"},
			{0x80, "Secondo BUS per CPU"}
		}},
		{0x0a, "Infinityband PCI", {
			{0x00, ""}
		}},
		{0x80, "Sconosciuto", {
			{0x00, ""}
		}},
	}},
	{0x07, "Telecom. Controller", {
		{0x00, "Serial Controller", {
			{0x00, "8250 (XT)"},
			{0x01, "16450"},
			{0x02, "16550"},
			{0x03, "16650"},
			{0x04, "16750"},
			{0x05, "16850"},
			{0x06, "16950"}
		}},
		{0x01, "Parell Controller", {
			{0x00, "Standard Parallel"},
			{0x01, "Bi-Directional Parallel"},
			{0x02, "ECP 1.X Parallel"},
			{0x03, "IEEE 1284 Controller"},
			{0xFE, "IEEE 1284 Target Device"}
		}},
		{0x02, "Multiport Serial", {
			{0x00, ""}
		}},
		{0x03, "Modem", {
			{0x00, "Generic Modem"},
			{0x01, "Hayes 16450 Interface"},
			{0x02, "Hayes 16550 Interface"},
			{0x03, "Hayes 16650 Interface"},
			{0x04, "Hayes 16750 Interface"}
		}},
		{0x04, "IEEE 488.1/2 Controller", {
			{0x00, ""}
		}},
		{0x05, "Smart Card Controller", {
			{0x00, ""}
		}},
		{0x80, "Sconosciuto", {
			{0x00, ""}
		}}
	}},
	{0x08, "Periferiche Base", {{0x0, "", {}}}},
	{0x09, "Dispositivi Input", {{0x0, "", {}}}},
	{0x0a, "Docking Agg.", {{0x0, "", {}}}},
	{0x0b, "Processore", {{0x0, "", {}}}},
	{0x0c, "Serial BUS", {{0x0, "", {}}}},
	{0x0d, "Wireless Controller", {{0x0, "", {}}}},
	{0x0f, "Satellite Controller", {{0x0, "", {}}}},
	{0x10, "Crittograf. Controller", {{0x0, "", {}}}},
	{0x11, "Sig. Process. Controller", {{0x0, "", {}}}}
};

void lista_pci (){
	unsigned char numero_bus = 0;
	unsigned char numero_dispositivo = 0;
	unsigned char numero_funzione = 0;

	unsigned char pci_classe;
	unsigned char pci_sottoclasse;
	unsigned char pci_progif;

	for (numero_bus = 0; numero_bus <= 255; numero_bus++){
		for (numero_dispositivo = 0; numero_dispositivo <= 31; numero_dispositivo++){
			outl(PORTA_CONF,
					(1 << BIT_ABILITAZIONE) |
					(numero_bus << BIT_NUMERO_BUS) |
					(numero_dispositivo << BIT_NUMERO_DIS) |
					(0 << BIT_NUMERO_FUN) |
					(0x00 & 0xfc)
			);
			unsigned int pci = inl(PORTA_DATA);
			wait(1);
			if ((unsigned short)(pci) == 0xffff){	
				return;
			}

			outl(PORTA_CONF,
					(1 << BIT_ABILITAZIONE) |
					(numero_bus << BIT_NUMERO_BUS) |
					(numero_dispositivo << BIT_NUMERO_DIS) |
					(0 << BIT_NUMERO_FUN) |
					(0x08 & 0xfc)
			);
			
			pci = (inl(PORTA_DATA) >> 8);
			
			for (unsigned short int tipo_classe = 0; tipo_classe < (sizeof(pci_device) / sizeof(pci_device[0])); tipo_classe++){
				pci_classe = (unsigned char)(pci >> 16) & 0xff;
				if (pci_device[tipo_classe].classe == pci_classe){
					print(pci_device[tipo_classe].nome_classe, VGA_TEXT_BIANCO_NERO);
					printchar(' ', VGA_TEXT_BIANCO_NERO);

					for (unsigned short tipo_sottoclasse = 0; tipo_sottoclasse < (sizeof(pci_device[0].sottoclasse) / sizeof(pci_device[0].sottoclasse[0])); tipo_sottoclasse++){
						pci_sottoclasse = (unsigned char)(pci >> 8) & 0xff;
						if (pci_device[tipo_classe].sottoclasse[tipo_sottoclasse].sottoclasse == pci_sottoclasse){
							print(pci_device[tipo_classe].sottoclasse[tipo_sottoclasse].nome_sottoclasse, VGA_TEXT_BIANCO_NERO);
							printchar(' ', VGA_TEXT_BIANCO_NERO);

							for (unsigned short tipo_progif = 0; tipo_progif < (sizeof(pci_device[0].sottoclasse[0].progif) / sizeof(pci_device[0].sottoclasse[0].progif[0])); tipo_progif++){
								pci_progif = (unsigned char)(pci) & 0xff;
								if (pci_device[tipo_classe].sottoclasse[tipo_sottoclasse].progif[tipo_progif].progif == pci_progif){
									print(pci_device[tipo_classe].sottoclasse[tipo_sottoclasse].progif[tipo_progif].nome_progif, VGA_TEXT_BIANCO_NERO);
									break;
								}
							}
						}
					}
				}
			}
			printchar('\n', VGA_TEXT_BIANCO_NERO);
		}
	}
}
