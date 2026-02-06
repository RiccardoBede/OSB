#define VGA_LUNGHEZZA_CARATTERE 8
#define VGA_ALTEZZA_CARATTERE 8

unsigned int bios_font[256][VGA_ALTEZZA_CARATTERE];

void carica_font_bios() {
    unsigned long int es_bp_segment, es_bp_offset;

    asm volatile(
        "mov $0x1130, %%ax \n"  // funzione BIOS: load font
        "mov $0x00, %%bh \n"    // font 8x8
        "int $0x10 \n"          // chiamata BIOS
        "mov %%es, %0 \n"       // salva ES
        "mov %%bp, %1 \n"       // salva BP
        : "=r"(es_bp_segment), "=r"(es_bp_offset)
        :
        : "ax", "bx", "es", "bp"
    );

    unsigned int *font_ptr = (unsigned int*)((es_bp_segment << 4) + es_bp_offset);

    for (unsigned int c = 0; c < 256; c++) {
        for (unsigned int row = 0; row < VGA_ALTEZZA_CARATTERE; row++) {
            bios_font[c][row] = font_ptr[c * VGA_ALTEZZA_CARATTERE + row];
        }
    }
}

void draw_char_13h(char c, int x, int y, uint8_t color) {
    unsigned int* glyph = bios_font[(unsigned int)c];
    for (unsigned int row = 0; row < VGA_ALTEZZA_CARATTERE; row++) {
        unsigned int bits = glyph[row];
        for (unsigned int col = 0; col < VGA_LUNGHEZZA_CARATTERE; col++) {
            if (bits & (1 << (7 - col))) {
                VGA[y * 320 + x] = color;
            }
        }
    }
}
