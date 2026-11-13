#ifndef STRUCT_H
#define STRUCT_H

typedef struct{
	char nome_comando[16];
	void (*funzione)();
}Comando;

#endif // STRUCT_H
