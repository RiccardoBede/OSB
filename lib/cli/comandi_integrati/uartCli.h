//bool CLIparserGenerico(char *, Comando *, int);
//unsigned int multiInput(SelezioneComando *, unsigned int, char);
//Comando sotto_comando[] = {{}};

SelezioneComando bound_rate[] = {{"115200", VGA_TEXT_BIANCO_NERO}, {"57600", VGA_TEXT_BIANCO_NERO}, {"38400", VGA_TEXT_BIANCO_NERO}, {"28800", VGA_TEXT_BIANCO_NERO}};

void uartCli (){
	//bound_rate
	multiInput(bound_rate, (sizeof(bound_rate) / sizeof(bound_rate[0])), VGA_TEXT_BIANCO_NERO);
}
