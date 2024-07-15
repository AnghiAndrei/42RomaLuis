if [ ! -d "Assets_tester" ]; then
	git clone https://github.com/AnghiAndrei/Assets_tester_42RomaLuis.git Assets_tester 
fi

echo '
test-leaks: re
	@clear
	@echo Senza parametri
	-valgrind ./so_long
	@echo
	@echo Piu parametri
	-valgrind ./so_long Assets_tester/So_Long/1.ber Assets_tester/So_Long/2.ber
	@echo
	@echo File inesistente
	-valgrind ./so_long Assets_tester/So_Long/no_exist.ber
	@echo
	@echo File con estenzione non .ber
	-valgrind ./so_long Assets_tester/So_Long/1.aanghi
	@echo
	@echo File vuoto
	-valgrind ./so_long Assets_tester/So_Long/error1.ber
	@echo
	@echo Nessuna uscita nella mappa
	-valgrind ./so_long Assets_tester/So_Long/error2.ber
	@echo
	@echo Nessun collezionabile nella mappa
	-valgrind ./so_long Assets_tester/So_Long/error3.ber
	@echo
	@echo Nessun player nella mappa
	-valgrind ./so_long Assets_tester/So_Long/error4.ber
	@echo
	@echo Carattere estraneo nella mappa
	-valgrind ./so_long Assets_tester/So_Long/error5.ber
	@echo
	@echo Mappa aperta con lo ' '
	-valgrind ./so_long Assets_tester/So_Long/error6.ber
	@echo
	@echo Mappa aperta con lo 0
	-valgrind ./so_long Assets_tester/So_Long/error7.ber
	@echo
	@echo Mappa incompletabile [Nota se non da errore va bene lo stesso]
	-valgrind ./so_long Assets_tester/So_Long/error8.ber
	@echo
	@echo Mappa quadrata
	-valgrind ./so_long Assets_tester/So_Long/error9.ber
	@echo
	@echo Piu uscite nella mappa
	-valgrind ./so_long Assets_tester/So_Long/error10.ber
	@echo
	@echo Piu player nella mappa
	-valgrind ./so_long Assets_tester/So_Long/error11.ber
	@echo
	@echo Linea vuota nella mappa
	-valgrind ./so_long Assets_tester/So_Long/error12.ber
	@echo
	@echo Mappa incompletabile, uscita irraggiungibile
	-valgrind ./so_long Assets_tester/So_Long/error13.ber
	@echo
	@echo Mappa incompletabile, moneta irraggiungibile
	-valgrind ./so_long Assets_tester/So_Long/error14.ber
	@echo
	@echo Righe vuote sopra la mappa
	-valgrind ./so_long Assets_tester/So_Long/error15.ber
	@echo
	@echo File con solo riga vuota
	-valgrind ./so_long Assets_tester/So_Long/error16.ber
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks: re
	@clear
	@echo Senza parametri
	-./so_long
	@echo
	@echo Piu parametri
	-./so_long Assets_tester/So_Long/1.ber Assets_tester/So_Long/2.ber
	@echo
	@echo File inesistente
	-./so_long Assets_tester/So_Long/no_exist.ber
	@echo
	@echo File con estenzione non .ber
	-./so_long Assets_tester/So_Long/1.aanghi
	@echo
	@echo File vuoto
	-./so_long Assets_tester/So_Long/error1.ber
	@echo
	@echo Nessuna uscita nella mappa
	-./so_long Assets_tester/So_Long/error2.ber
	@echo
	@echo Nessun collezionabile nella mappa
	-./so_long Assets_tester/So_Long/error3.ber
	@echo
	@echo Nessun player nella mappa
	-./so_long Assets_tester/So_Long/error4.ber
	@echo
	@echo Carattere estraneo nella mappa
	-./so_long Assets_tester/So_Long/error5.ber
	@echo
	@echo Mappa aperta con lo ' '
	-./so_long Assets_tester/So_Long/error6.ber
	@echo
	@echo Mappa aperta con lo 0
	-./so_long Assets_tester/So_Long/error7.ber
	@echo
	@echo Mappa incompletabile [Nota se non da errore va bene lo stesso]
	-./so_long Assets_tester/So_Long/error8.ber
	@echo
	@echo Mappa quadrata
	-./so_long Assets_tester/So_Long/error9.ber
	@echo
	@echo Piu uscite nella mappa
	-./so_long Assets_tester/So_Long/error10.ber
	@echo
	@echo Piu player nella mappa
	-./so_long Assets_tester/So_Long/error11.ber
	@echo
	@echo Linea vuota nella mappa
	-./so_long Assets_tester/So_Long/error12.ber
	@echo
	@echo Mappa incompletabile, uscita irraggiungibile
	-./so_long Assets_tester/So_Long/error13.ber
	@echo
	@echo Mappa incompletabile, moneta irraggiungibile
	-./so_long Assets_tester/So_Long/error14.ber
	@echo
	@echo Righe vuote sopra la mappa
	-./so_long Assets_tester/So_Long/error15.ber
	@echo
	@echo File con solo riga vuota
	-./so_long Assets_tester/So_Long/error16.ber
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-norm:
	@echo Errori di norma:
	@norminette *.c *.h | grep Error! | wc -l
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]
' >> Makefile

clear
echo "! Tester installato !"
echo
echo "Istruzioni:"
echo "make test-leaks: per testare l'input con controllo leaks"
echo "make test-nleaks: per testare l'input senza controllo leaks"
echo "make test-norm: per testare la norma"