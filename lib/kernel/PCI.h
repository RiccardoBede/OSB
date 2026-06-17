#define PORTA_CONF 0xcf8
#define PORTA_DATA 0xcfc

#define BIT_ABILITAZIONE 31
#define BIT_NUMERO_BUS 16
#define BIT_NUMERO_DIS 11
#define BIT_NUMERO_FUN 8
#define BIT_OFSET_REG 2

#define OFSET_ID 0x00
#define OFSET_CLASSE 0x08
#define OFSET_COMANDO 0x04

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
	{0x08, "Periferiche Base", {
		{0x00, "PCI", {
			{0x00, "Generic 8259"},
			{0x01, "ISA-Compatible"},
			{0x02, "EISA-Compatible"},
			{0x10, "I/O APIC Interrupt Controller"},
			{0x20, "I/O(x) APIC Interrupt Controller"}
		}},
		{0x01, "DMA", {
			{0x00, "Generic 8237-Compatible"},
    		{0x01, "ISA-Compatible"},
    		{0x02, "EISA-Compatible"}
		}},
		{0x02, "Timer", {
			{0x00, "Generic 8254-Compatible"},
			{0x01, "ISA-Compatible"},
			{0x02, "EISA-Compatible"},
			{0x03, "HPET (High Precision Event Timer)"}
		}},
		{0x03, "RTC", {
			{0x00, "Generic RTC"},
    		{0x01, "ISA-Compatible"}
		}},
		{0x04, "PCI Controller", {
			{0x00, ""}
		}},
		{0x05, "SD Host Controller", {
			{0x00, ""}
		}},
		{0x06, "IOMMU", {
			{0x00, ""}
		}},
		{0x80, "Sconosciuto", {
			{0x00, ""}
		}}
	}},
	{0x09, "Dispositivi Input", {
		{0x00, "Tastiera", {
			{0x00, ""}
		}},
		{0x01, "Penna", {
			{0x00, ""}
		}},
		{0x02, "Mouse", {
			{0x00, ""}
		}},
		{0x03, "Scanner", {
			{0x00, ""}
		}},
		{0x04, "Game Port", {
			{0x00, "Generico"},
			{0x10, "Esteso"}
		}},
		{0x80, "Sconosciuto", {
			{0x00, ""}
		}}
	}},
	{0x0a, "Docking Agg.", {
		{0x00, "Generico", {
			{0x00, ""}
		}},
		{0x80, "Sconosciuto", {
			{0x00, ""}
		}}
	}},
	{0x0b, "Processore", {
		{0x00, "386", {
			{0x00, ""}
		}},
		{0x01, "486", {
			{0x00, ""}
		}},
		{0x02, "Pentium", {
			{0x00, ""}
		}},
		{0x03, "Pentium Pro", {
			{0x00, ""}
		}},
		{0x10, "Alpha", {
			{0x00, ""}
		}},
		{0x20, "PowerPC", {
			{0x00, ""}
		}},
		{0x30, "MIPS", {
			{0x00, ""}
		}},
		{0x40, "Co-Processor", {
			{0x00, ""}
		}},
		{0x80, "Sconosciuto", {
			{0x00, ""}
		}}
	}},
	{0x0C, "Serial BUS", {
        {0x00, "FireWire (IEEE 1394)", {
            {0x00, "Generic"},
            {0x10, "OHCI (Open Host Controller Interface)"},
        }},
        {0x01, "ACCESS Bus Controller", {
			{0x00, ""}
		}},
        {0x02, "SSA", {
			{0x00, ""}
		}},
        {0x03, "USB Controller", {
            {0x00, "UHCI Controller (USB 1.0/1.1 Intel)"},
            {0x10, "OHCI Controller (USB 1.0/1.1 Compaq)"},
            {0x20, "EHCI Controller (USB 2.0)"},
            {0x30, "XHCI Controller (USB 3.0)"},
            {0x80, "Unspecified Controller"},
            {0xFE, "USB Device (Not a Host Controller)"}
        }},
        {0x04, "Fibre Channel", {
			{0x00, ""}
		}},
        {0x05, "SMBus Controller", {
			{0x00, ""}
		}},
        {0x06, "InfiniBand Controller", {
			{0x00, ""}
		}},
        {0x07, "IPMI Interface", {
            {0x00, "SMIC"},
            {0x01, "Keyboard Controller"},
            {0x02, "Block Transfer"}
        }},
        {0x08, "SERCOS (IEC 61491)", {
			{0x00, ""}
		}},
        {0x09, "CANbus Controller", {
			{0x00, ""}
		}},
        {0x80, "Sconosciuto", {
			{0x00, ""}
		}}
    }},
	{0x0D, "Wireless Controller", {
        {0x00, "iRDA Compatible Controller", {
			{0x00, ""}
		}},
        {0x01, "Consumer IR Controller", {
			{0x00, ""}
		}},
        {0x10, "RF Controller", {
			{0x00, ""}
		}},
        {0x11, "Bluetooth Controller", {
			{0x00, ""}
		}},
        {0x12, "Broadband Controller", {
			{0x00, ""}
		}},
        {0x20, "Ethernet Controller (802.1a)", {
			{0x00, ""}
		}},
        {0x21, "Ethernet Controller (802.1b)", {
			{0x00, ""}
		}},
        {0x80, "Other Wireless Controller", {
			{0x00, ""}
		}}
    }},
	{0x0F, "Satellite Controller", {
        {0x01, "Satellite TV Controller", {
			{0x00, ""}
		}},
        {0x02, "Satellite Audio Controller", {
			{0x00, ""}
		}},
        {0x03, "Satellite Voice Controller", {
			{0x00, ""}
		}},
        {0x04, "Satellite Data Controller", {
			{0x00, ""}
		}}
    }},
	{0x10, "Crittograf. Controller", {
        {0x00, "Network/Computing Encryption", {
			{0x00, ""}
		}},
        {0x10, "Entertainment Encryption", {{
			0x00, ""}
		}},
        {0x80, "Sconosciuto", {
			{0x00, ""}
		}}
    }},
	{0x11, "Sig. Process. Controller", {
		{0x00, "DPIO", {
			{0x00, ""}
		}},
        {0x01, "Performance Counters", {
			{0x00, ""}
		}},
        {0x10, "Communication Synchronizer", {
			{0x00, ""}
		}},
        {0x20, "Signal Processing Management", {
			{0x00, ""}
		}},
        {0x80, "Sconosciuto", {
			{0x00, ""}
		}}
	}}
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
					(OFSET_ID & 0xfc)
			);
			unsigned int pci = inl(PORTA_DATA);
			//wait(1);
			if ((unsigned short)(pci) == 0xffff){	
				return;
			}

			outl(PORTA_CONF,
					(1 << BIT_ABILITAZIONE) |
					(numero_bus << BIT_NUMERO_BUS) |
					(numero_dispositivo << BIT_NUMERO_DIS) |
					(0 << BIT_NUMERO_FUN) |
					(OFSET_CLASSE & 0xfc)
			);
			
			pci = (inl(PORTA_DATA) >> 8);
			
			for (unsigned short int tipo_classe = 0; tipo_classe < (sizeof(pci_device) / sizeof(pci_device[0])); tipo_classe++){
				pci_classe = (unsigned char)(pci >> 16) & 0xff;
				if (pci_device[tipo_classe].classe == pci_classe){
					print(pci_device[tipo_classe].nome_classe, VGA_TEXT_BIANCO_NERO);
					print(" -> ", VGA_TEXT_GIALLO_NERO);					

					for (unsigned short tipo_sottoclasse = 0; tipo_sottoclasse < (sizeof(pci_device[0].sottoclasse) / sizeof(pci_device[0].sottoclasse[0])); tipo_sottoclasse++){
						pci_sottoclasse = (unsigned char)(pci >> 8) & 0xff;
						if (pci_device[tipo_classe].sottoclasse[tipo_sottoclasse].sottoclasse == pci_sottoclasse){
							print(pci_device[tipo_classe].sottoclasse[tipo_sottoclasse].nome_sottoclasse, VGA_TEXT_BIANCO_NERO);
							printchar(' ', VGA_TEXT_BIANCO_NERO);	

							for (unsigned short tipo_progif = 0; tipo_progif < (sizeof(pci_device[0].sottoclasse[0].progif) / sizeof(pci_device[0].sottoclasse[0].progif[0])); tipo_progif++){
								pci_progif = (unsigned char)(pci) & 0xff;
								if (pci_device[tipo_classe].sottoclasse[tipo_sottoclasse].progif[tipo_progif].progif == pci_progif){
									print(pci_device[tipo_classe].sottoclasse[tipo_sottoclasse].progif[tipo_progif].nome_progif, VGA_TEXT_BIANCO_NERO);
								
									print(" (0x", VGA_TEXT_GIALLO_NERO);
									printhex(pci_device[tipo_classe].classe, VGA_TEXT_GIALLO_NERO);
									print(", 0x", VGA_TEXT_GIALLO_NERO);
									printhex(pci_device[tipo_classe].sottoclasse[tipo_sottoclasse].sottoclasse, VGA_TEXT_GIALLO_NERO);
									print(", 0x", VGA_TEXT_GIALLO_NERO);
									printhex(pci_device[tipo_classe].sottoclasse[tipo_sottoclasse].progif[tipo_progif].progif, VGA_TEXT_GIALLO_NERO);
									printchar(')', VGA_TEXT_GIALLO_NERO);

									bar_pci(numero_bus, numero_dispositivo);

									break;
								}
							}
							break;
						}
					}
				}
			}
			printchar('\n', VGA_TEXT_BIANCO_NERO);
		}
	}
}

void bar_pci (unsigned short int numero_bus, unsigned short int numero_dispositivo){
	outl(PORTA_CONF, 
		(1 << BIT_ABILITAZIONE) |
		(numero_bus << BIT_NUMERO_BUS) |
		(numero_dispositivo << BIT_NUMERO_DIS) |
		(0 << BIT_NUMERO_FUN) |
		((0x10 + 2) & 0xfc)	
	);
	
	print("\n\tBAR: 0x", VGA_TEXT_GIALLO_NERO);

	if (inl(PORTA_DATA) & 0x1){
		printhex((inl(PORTA_DATA) & 0xfffffffc), VGA_TEXT_GIALLO_NERO);
	}else{
		printhex((inl(PORTA_DATA) & 0xfffffff0), VGA_TEXT_GIALLO_NERO);
	}
}
