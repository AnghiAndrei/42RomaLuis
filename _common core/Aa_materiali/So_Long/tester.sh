mkdir maps_tester
echo "" > maps_tester/error1.ber
echo "
11111
10CP1
11111" > maps_tester/error2.ber
echo "
11111
1E0P1
11111" > maps_tester/error3.ber
echo "
11111
1EC01
11111" > maps_tester/error4.ber
echo "
111111
1ECPX1
111111" > maps_tester/error5.ber
echo "
111111
1ECP0
111111" > maps_tester/error6.ber
echo "
111111
1ECP00
111111" > maps_tester/error7.ber
echo "
111111
1CEP01
111111" > maps_tester/error8.ber
echo "
11111
1ECP1
10001
10001
11111" > maps_tester/error9.ber
echo "
11111
1ECP1
1E001
11111" > maps_tester/error10.ber
echo "
11111
1ECP1
10P01
11111" > maps_tester/error11.ber
echo "
11111
1ECP1

11111" > maps_tester/error12.ber
echo "
111111
1E1CP1
111111" > maps_tester/error13.ber
echo "
111111
1EC1P1
111111" > maps_tester/error14.ber
echo "


111111
1EC1P1
111111" > maps_tester/error15.ber

echo '
test-leaks: re
	@clear
	@echo Senza parametri
	-valgrind ./so_long
	@echo
	@echo Piu parametri
	-valgrind ./so_long maps_tester/1.ber maps_tester/2.ber
	@echo
	@echo File inesistente
	-valgrind ./so_long maps_tester/no_exist.ber
	@echo
	@echo File con estenzione non .ber
	-valgrind ./so_long maps_tester/1.aanghi
	@echo
	@echo File vuoto
	-valgrind ./so_long maps_tester/error1.ber
	@echo
	@echo Nessuna uscita nella mappa
	-valgrind ./so_long maps_tester/error2.ber
	@echo
	@echo Nessun collezionabile nella mappa
	-valgrind ./so_long maps_tester/error3.ber
	@echo
	@echo Nessun player nella mappa
	-valgrind ./so_long maps_tester/error4.ber
	@echo
	@echo Carattere estraneo nella mappa
	-valgrind ./so_long maps_tester/error5.ber
	@echo
	@echo Mappa aperta con lo ' '
	-valgrind ./so_long maps_tester/error6.ber
	@echo
	@echo Mappa aperta con lo 0
	-valgrind ./so_long maps_tester/error7.ber
	@echo
	@echo Mappa incompletabile [Nota se non da errore va bene lo stesso]
	-valgrind ./so_long maps_tester/error8.ber
	@echo
	@echo Mappa quadrata
	-valgrind ./so_long maps_tester/error9.ber
	@echo
	@echo Piu uscite nella mappa
	-valgrind ./so_long maps_tester/error10.ber
	@echo
	@echo Piu player nella mappa
	-valgrind ./so_long maps_tester/error11.ber
	@echo
	@echo Linea vuota nella mappa
	-valgrind ./so_long maps_tester/error12.ber
	@echo
	@echo Mappa incompletabile, uscita irraggiungibile
	-valgrind ./so_long maps_tester/error13.ber
	@echo
	@echo Mappa incompletabile, moneta irraggiungibile
	-valgrind ./so_long maps_tester/error14.ber
	@echo
	@echo Righe vuote sopra la mappa
	-valgrind ./so_long maps_tester/error15.ber
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks: re
	@clear
	@echo Senza parametri
	-./so_long
	@echo
	@echo Piu parametri
	-./so_long maps_tester/1.ber maps_tester/2.ber
	@echo
	@echo File inesistente
	-./so_long maps_tester/no_exist.ber
	@echo
	@echo File con estenzione non .ber
	-./so_long maps_tester/1.aanghi
	@echo
	@echo File vuoto
	-./so_long maps_tester/error1.ber
	@echo
	@echo Nessuna uscita nella mappa
	-./so_long maps_tester/error2.ber
	@echo
	@echo Nessun collezionabile nella mappa
	-./so_long maps_tester/error3.ber
	@echo
	@echo Nessun player nella mappa
	-./so_long maps_tester/error4.ber
	@echo
	@echo Carattere estraneo nella mappa
	-./so_long maps_tester/error5.ber
	@echo
	@echo Mappa aperta con lo ' '
	-./so_long maps_tester/error6.ber
	@echo
	@echo Mappa aperta con lo 0
	-./so_long maps_tester/error7.ber
	@echo
	@echo Mappa incompletabile [Nota se non da errore va bene lo stesso]
	-./so_long maps_tester/error8.ber
	@echo
	@echo Mappa quadrata
	-./so_long maps_tester/error9.ber
	@echo
	@echo Piu uscite nella mappa
	-./so_long maps_tester/error10.ber
	@echo
	@echo Piu player nella mappa
	-./so_long maps_tester/error11.ber
	@echo
	@echo Linea vuota nella mappa
	-./so_long maps_tester/error12.ber
	@echo
	@echo Mappa incompletabile, uscita irraggiungibile
	-./so_long maps_tester/error13.ber
	@echo
	@echo Mappa incompletabile, moneta irraggiungibile
	-./so_long maps_tester/error14.ber
	@echo
	@echo Righe vuote sopra la mappa
	-./so_long maps_tester/error15.ber
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