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
/*	vga = true;
	VGA_13h();
	char *vga = (char *)VGA;
	for (unsigned long int pixel = 0; pixel < (VGA_RIGHE_PIXEL * VGA_COLONNE_PIXEL); pixel++){	vga[pixel] = 0x00;}*/
}

typedef struct{
	char carattere;
	char colore;
}CarattereColore;

//VGA TEXT MODE
static unsigned int carattere_corrente_vga_text = 0;

//VGA
//static unsigned int VGA_X = 0;
//static unsigned int VGA_Y = 0;

void scroll(){
	if (carattere_corrente_vga_text > (VGA_TEXT_RIGHE * VGA_TEXT_COLONNE)){
		CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
		CarattereColore *vga_text_nonStamp = (CarattereColore *)VGA_TEXT;
		unsigned int caratteri_spostare = 0;
		while (caratteri_spostare < VGA_TEXT_RIGHE){
			vga_text_nonStamp[(VGA_TEXT_RIGHE * VGA_TEXT_COLONNE) + caratteri_spostare] = vga_text[caratteri_spostare];
			vga_text[caratteri_spostare] = (CarattereColore){0x00, VGA_TEXT_NERO_NERO};
			caratteri_spostare++;
		}
		unsigned int copia_index_vga_text = 0;
		while (caratteri_spostare < (VGA_TEXT_RIGHE * VGA_TEXT_COLONNE)){
			vga_text[copia_index_vga_text] = vga_text[caratteri_spostare++];
			copia_index_vga_text++;	
		}
		carattere_corrente_vga_text -= VGA_TEXT_RIGHE + (carattere_corrente_vga_text - (VGA_TEXT_RIGHE * VGA_TEXT_COLONNE));
	}
}

void clear (){
	if (!vga){
		CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
		for (unsigned int carattere = 0; carattere < (VGA_TEXT_RIGHE * VGA_TEXT_COLONNE); carattere++){
			vga_text[carattere] = (CarattereColore){0x00, VGA_TEXT_NERO_NERO};
		}
		carattere_corrente_vga_text = 0;
	}else{
	
	}
}

void cursore(){
	if (!vga){
		CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
		vga_text[carattere_corrente_vga_text] = (CarattereColore){219, VGA_TEXT_BIANCO_NERO};
	}else{
	
	}
	scroll();
}

void cancellaCursore (){
	if (!vga){
		CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
		vga_text[carattere_corrente_vga_text] = (CarattereColore){' ', VGA_TEXT_NERO_NERO};
	}else{

	}
}

void stampaAcapo (){
	CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
	for (int caratteri_acapo = (carattere_corrente_vga_text % VGA_TEXT_RIGHE); caratteri_acapo < VGA_TEXT_RIGHE; caratteri_acapo++){
		CarattereColore carattere = {' ', VGA_TEXT_NERO_NERO};
		vga_text[carattere_corrente_vga_text] = carattere;
		carattere_corrente_vga_text++;
	}
	if (carattere_corrente_vga_text % VGA_TEXT_RIGHE != 0){
		carattere_corrente_vga_text += VGA_TEXT_RIGHE - (carattere_corrente_vga_text % VGA_TEXT_RIGHE);
	}	
	scroll();
}

void cancellachar (){
	CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
	char *vga = (char *)VGA;
	vga_text[carattere_corrente_vga_text--] = (CarattereColore){' ', VGA_TEXT_NERO_NERO};
}

void stampaTab (){
	CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
	for (int caratteri_tab = 0; caratteri_tab < 4; caratteri_tab++){
		vga_text[carattere_corrente_vga_text] = (CarattereColore){' ', VGA_TEXT_NERO_NERO};
		carattere_corrente_vga_text++;	
	}
	scroll();
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
					break;
			}
		}
	}else{
	
	}
	cursore();
	scroll();
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
		
	}
	cursore();
	scroll();
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

void printcharat (char carattere, unsigned int pos, char colore){//mettere if che se pos > (VGA altezza * VGA lunghezza) il carattere deve metterlo a vga_text_char + la differenza tra altezza*lunghezza e pos
	if (!vga){
		CarattereColore *vga_text = (CarattereColore *)VGA_TEXT;
		vga_text[pos] = (CarattereColore){carattere, colore};	
	}else{
	
	}
}
