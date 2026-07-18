long int potenza (long int base, long int esponente){
	long int risul = 1;
	for (int contatore_moltiplicazioni = 0; contatore_moltiplicazioni < esponente; contatore_moltiplicazioni++){
		risul *= base;
	}
	return risul;
}
