Relazioni_Binarie: relazioni_binarie_composizione_differenza.c makefile
	gcc -ansi -Wall -O relazioni_binarie_composizione_differenza.c -o relazioni_binarie_composizione_differenza
pulisci:
	rm -f relazioni_binarie_composizione_differenza.o
pulisci_tutto:
	rm -f relazioni_binarie_composizione_differenza relazioni_binarie_composizione_differenza.o
