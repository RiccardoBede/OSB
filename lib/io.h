#include "video/driverVGA_frame13H.h"

#define VGA 0xa0000

#define VGA_RIGHE_PIXEL 320
#define VGA_COLONNE_PIXEL 200

#define VGA_ALTEZZA_CARATTERE 8
#define VGA_LUNGHEZZA_CARATTERE 8

#define VGA_TEXT 0xb8000

#define VGA_TEXT_RIGHE 80
#define VGA_TEXT_COLONNE 25

#define VGA_TEXT_NERO_NERO 0x0
#define VGA_TEXT_BLU_NERO 0x1
#define VGA_TEXT_VERDE_NERO 0x2
#define VGA_TEXT_CIANO_NERO 0x3
#define VGA_TEXT_ROSSO_NERO 0x4
#define VGA_TEXT_MAGENTA_NERO 0x5
#define VGA_TEXT_GIALLO_NERO 0x6
#define VGA_TEXT_BIANCO_NERO 0x7
#define VGA_TEXT_GRIGIO_SCURO_NERO 0x8
#define VGA_TEXT_CIANO_BLU 0x9
#define VGA_TEXT_VERDE_CHIARO_VERDE 0xa
#define VGA_TEXT_CIANO_CIANO 0xb
#define VGA_TEXT_ROSSO_CHIARO_ROSSO 0xc
#define VGA_TEXT_MAGENTA_CHIARO_MAGENTA 0xd
#define VGA_TEXT_GIALLO_CHIARO_GIALLO 0xe
#define VGA_TEXT_BIANCO_CHIARO_BIANCO 0xf

static bool vga = false;

void startVGA (){
	vga = true;
	VGA_13h();
	char *vga = (char *)VGA;
	for (unsigned long int pixel = 0; pixel < (VGA_RIGHE_PIXEL * VGA_COLONNE_PIXEL); pixel++){	vga[pixel] = 0x00;}
	//chiamata driver FRAME buffer
}

typedef struct{
	char carattere;
	char colore;
}CarattereColore;

//VGA TEXT MODE
static unsigned int carattere_corrente_vga_text = 0;

//VGA
static unsigned int x = 0;
static unsigned int y = 0;

void cursore(){
	if (!vga){
		CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
		vga_text[carattere_corrente_vga_text] = (CarattereColore){219, VGA_TEXT_BIANCO_NERO};
	}else{
		char *vga = (char *)VGA;
		for (int cerca_carattere_ascii = 0; cerca_carattere_ascii < 99; cerca_carattere_ascii++) {
			if (mappaVGA[cerca_carattere_ascii].carattere_ascii == 219) {
				unsigned int x_base = x;
				unsigned int y_base = y;
				for (int carattere_pixel = 0; carattere_pixel < (VGA_ALTEZZA_CARATTERE * VGA_LUNGHEZZA_CARATTERE); carattere_pixel++) {
					vga[((y_base + (carattere_pixel / VGA_LUNGHEZZA_CARATTERE)) * VGA_RIGHE_PIXEL) + (x_base + (carattere_pixel % VGA_LUNGHEZZA_CARATTERE))] = mappaVGA[cerca_carattere_ascii].carattere_pixel[carattere_pixel];
				}
			}
		}
	}
}

void cancellaCursore (){
	if (!vga){
		CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
		vga_text[carattere_corrente_vga_text] = (CarattereColore){' ', VGA_TEXT_NERO_NERO};
	}else{
		char *vga = (char *)VGA;
		for (int carattere_pixel = 0; carattere_pixel < (VGA_ALTEZZA_CARATTERE * VGA_LUNGHEZZA_CARATTERE); carattere_pixel++) {
			vga[((y + (carattere_pixel / VGA_LUNGHEZZA_CARATTERE)) * VGA_RIGHE_PIXEL) + (x + (carattere_pixel % VGA_LUNGHEZZA_CARATTERE))] = 0x00;
		}	
	}
}

void stampaAcapo (){
	CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
	for (int caratteri_acapo = (carattere_corrente_vga_text % VGA_TEXT_RIGHE); caratteri_acapo < VGA_TEXT_RIGHE; caratteri_acapo++){
		CarattereColore carattere = {' ', VGA_TEXT_NERO_NERO};
		vga_text[carattere_corrente_vga_text] = carattere;
		carattere_corrente_vga_text++;
		y += VGA_ALTEZZA_CARATTERE;
	}
	if (carattere_corrente_vga_text % VGA_TEXT_RIGHE != 0){
		carattere_corrente_vga_text += VGA_TEXT_RIGHE - (carattere_corrente_vga_text % VGA_TEXT_RIGHE);
		y += ((VGA_TEXT_RIGHE) - (carattere_corrente_vga_text % VGA_TEXT_RIGHE)) * VGA_ALTEZZA_CARATTERE;
	}	
}

void cancellachar (){
	CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
	char *vga = (char *)VGA;
	vga_text[carattere_corrente_vga_text--] = (CarattereColore){' ', VGA_TEXT_NERO_NERO};
	x -= VGA_LUNGHEZZA_CARATTERE;
	unsigned int x_base = x;
	unsigned int y_base = y;
	for (int carattere_pixel = 0; carattere_pixel < (VGA_ALTEZZA_CARATTERE * VGA_LUNGHEZZA_CARATTERE); carattere_pixel++) {
		vga[((y_base + (carattere_pixel / VGA_LUNGHEZZA_CARATTERE)) * VGA_RIGHE_PIXEL) + (x_base + (carattere_pixel % VGA_LUNGHEZZA_CARATTERE))] = 0x00;
	}

}

void stampaTab (){
	CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
	for (int caratteri_tab = 0; caratteri_tab < 4; caratteri_tab++){
		vga_text[carattere_corrente_vga_text] = (CarattereColore){' ', VGA_TEXT_NERO_NERO};
		carattere_corrente_vga_text++;
		x += VGA_LUNGHEZZA_CARATTERE;
	}

}

void print (char *buffer, char colore){
	cancellaCursore();
	if (!vga){
		CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
		for (int carattere_corrente = 0; buffer[carattere_corrente] != '\0'; carattere_corrente++){
			switch (buffer[carattere_corrente]){
				case '\n':
					stampaAcapo();
					break;
				case '\t':
					stampaTab();
					break;
				case '\b':
					cancellachar();
					break;
				default:
					CarattereColore carattere = {buffer[carattere_corrente], colore};
					vga_text[carattere_corrente_vga_text] = carattere;
					carattere_corrente_vga_text++;
					x += VGA_LUNGHEZZA_CARATTERE;
					break;
			}
		}
	}else{
		char *vga = (char *)VGA;
		for (int carattere_corrente = 0; buffer[carattere_corrente] != '\0'; carattere_corrente++) {
			if (buffer[carattere_corrente] == '\n') {
				x = 0;
				y += VGA_ALTEZZA_CARATTERE;
			}	
			for (int cerca_carattere_ascii = 0; cerca_carattere_ascii < 99; cerca_carattere_ascii++) {
				if (mappaVGA[cerca_carattere_ascii].carattere_ascii == buffer[carattere_corrente]) {
					unsigned int x_base = x;
					unsigned int y_base = y;
					for (int carattere_pixel = 0; carattere_pixel < (VGA_ALTEZZA_CARATTERE * VGA_LUNGHEZZA_CARATTERE); carattere_pixel++) {
						vga[((y_base + (carattere_pixel / VGA_LUNGHEZZA_CARATTERE)) * VGA_RIGHE_PIXEL) + (x_base + (carattere_pixel % VGA_LUNGHEZZA_CARATTERE))] = mappaVGA[cerca_carattere_ascii].carattere_pixel[carattere_pixel];
					}
					x += VGA_LUNGHEZZA_CARATTERE;
					carattere_corrente_vga_text++;
					if (x + VGA_LUNGHEZZA_CARATTERE > VGA_RIGHE_PIXEL) {
						x = 0;
						y += VGA_ALTEZZA_CARATTERE;
					}
					if (y + VGA_ALTEZZA_CARATTERE > VGA_COLONNE_PIXEL) {
						for (unsigned long int pixel = 0; pixel < (VGA_RIGHE_PIXEL * VGA_COLONNE_PIXEL); pixel++) {
							vga[pixel] = 0x00;
						}
						x = 0;
						y = 0;
					}
				}
			}
		}

	}
	cursore();
}

void printchar (char carattere, char colore){
	cancellaCursore();
	if (!vga){
		CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
		switch (carattere){
			case '\n':
				stampaAcapo();
				break;
			case '\t':
				stampaTab();
				break;
			case '\b':
				cancellachar();
				break;
			default:
				vga_text[carattere_corrente_vga_text++] = (CarattereColore){carattere, colore};
				break;
		}
	}else{
		char *vga = (char *)VGA;
		if (carattere == '\n') {
			x = 0;
			y += VGA_ALTEZZA_CARATTERE;
		}	
		for (int cerca_carattere_ascii = 0; cerca_carattere_ascii < 99; cerca_carattere_ascii++) {
			if (mappaVGA[cerca_carattere_ascii].carattere_ascii == carattere) {
				unsigned int x_base = x;
				unsigned int y_base = y;
				for (int carattere_pixel = 0; carattere_pixel < (VGA_ALTEZZA_CARATTERE * VGA_LUNGHEZZA_CARATTERE); carattere_pixel++) {
					vga[((y_base + (carattere_pixel / VGA_LUNGHEZZA_CARATTERE)) * VGA_RIGHE_PIXEL) + (x_base + (carattere_pixel % VGA_LUNGHEZZA_CARATTERE))] = mappaVGA[cerca_carattere_ascii].carattere_pixel[carattere_pixel];
				}
				x += VGA_LUNGHEZZA_CARATTERE;
				carattere_corrente_vga_text++;
			}
		}
	}
	cursore();
}

void printint(long int numero, char colore) {
    if (numero == 0) {
        printchar('0', colore);
        return;
    }
    if (numero < 0) {
        printchar('-', colore);
        numero = -numero;
    }
    unsigned long n = (unsigned long)numero;
    unsigned long divisore = 1;
    while (n / divisore >= 10) {
        divisore *= 10;
    }
    while (divisore > 0) {
        int cifra = n / divisore;
        printchar(cifra + '0', colore);
        n %= divisore;
        divisore /= 10;
    }
}

void printhex(long int numero, char colore) {
    if (numero == 0) {
        printchar('0', colore);
        return;
    }
    unsigned long n = (unsigned long)numero;
    unsigned long divisore = 1;
    while (n / divisore >= 16) {
        divisore *= 16;
    }
    while (divisore > 0) {
        int cifra = n / divisore;
        if (cifra < 10) {
            printchar(cifra + '0', colore);
        } else {
            printchar(cifra - 10 + 'A', colore);
        }
        n %= divisore;
        divisore /= 16;
    }
}
