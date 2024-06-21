if [ ! -d "Assets_tester" ]; then
	git clone https://github.com/AnghiAndrei/Assets_tester_42RomaLuis.git Assets_tester 
fi

echo '
test-leaks: re
	@clear
	@echo Senza parametri
	-valgrind ./cub3D
	@echo
	@echo Piu di un parametro
	-valgrind ./cub3D Assets_tester/cub3D/maps/1.cub Assets_tester/cub3D/maps/2.cub
	@echo
	@echo Mappa inesistente
	-valgrind ./cub3D Assets_tester/cub3D/maps/no_exist.cub
	@echo
	@echo Mappa non .aanghi
	-valgrind ./cub3D Assets_tester/cub3D/maps/1.aanghi
	@echo
	@echo Manca la configurazione del soffitto
	-valgrind ./cub3D Assets_tester/cub3D/maps/error1.cub
	@echo
	@echo Manca la mappa
	-valgrind ./cub3D Assets_tester/cub3D/maps/error2.cub
	@echo
	@echo 0 player nella mappa
	-valgrind ./cub3D Assets_tester/cub3D/maps/error3.cub
	@echo
	@echo 1+ player nella mappa
	-valgrind ./cub3D Assets_tester/cub3D/maps/error4.cub
	@echo
	@echo Mappa aperta con lo 0
	-valgrind ./cub3D Assets_tester/cub3D/maps/error5.cub
	@echo
	@echo Mappa aperta con lo ' '
	-valgrind ./cub3D Assets_tester/cub3D/maps/error6.cub
	@echo
	@echo Spazi nella configurazione dei colori
	-valgrind ./cub3D Assets_tester/cub3D/maps/error7.cub
	@echo
	@echo Assente configurazione dei colori
	-valgrind ./cub3D Assets_tester/cub3D/maps/error8.cub
	@echo
	@echo Numero negativo nella configurazione dei colori
	-valgrind ./cub3D Assets_tester/cub3D/maps/error9.cub
	@echo
	@echo Numero oltre 255 nella configurazione dei colori
	-valgrind ./cub3D Assets_tester/cub3D/maps/error10.cub
	@echo
	@echo File vuoto
	-valgrind ./cub3D Assets_tester/cub3D/maps/error11.cub
	@echo
	@echo Assente configurazione delle texture
	-valgrind ./cub3D Assets_tester/cub3D/maps/error12.cub
	@echo
	@echo Texture inesistente
	-valgrind ./cub3D Assets_tester/cub3D/maps/error13.cub
	@echo
	@echo Riga vuota nella mappa
	-valgrind ./cub3D Assets_tester/cub3D/maps/error14.cub
	@echo
	@echo Riga vuota nel file
	-valgrind ./cub3D Assets_tester/cub3D/maps/error15.cub
	@echo
	@echo Player fuori dalla mappa
	-valgrind ./cub3D Assets_tester/cub3D/maps/error16.cub
	@echo
	@echo Mappa prima della configurazione
	-valgrind ./cub3D Assets_tester/cub3D/maps/error17.cub
	@echo
	@echo Spazi dentro la mappa
	-valgrind ./cub3D Assets_tester/cub3D/maps/error18.cub
	@echo
	@echo Carattere inaspettato
	-valgrind ./cub3D Assets_tester/cub3D/maps/error19.cub
	@echo
	@echo Configurazione dei colori in piu. Ex 1,1,1,1
	-valgrind ./cub3D Assets_tester/cub3D/maps/error20.cub
	@echo
	@echo Configurazione delle texture in piu. Ex ./NO.xmp ./NO2.xpm
	-valgrind ./cub3D Assets_tester/cub3D/maps/error21.cub
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks: re
	@clear
	@echo Senza parametri
	-./cub3D
	@echo
	@echo Piu di un parametro
	-./cub3D Assets_tester/cub3D/maps/error1.cub Assets_tester/cub3D/maps/error1.cub
	@echo
	@echo Mappa inesistente
	-./cub3D Assets_tester/cub3D/maps/no_exist.cub
	@echo
	@echo Mappa non .aanghi
	-./cub3D Assets_tester/cub3D/maps/1.aanghi
	@echo
	@echo Manca la configurazione del soffitto
	-./cub3D Assets_tester/cub3D/maps/error1.cub
	@echo
	@echo Manca la mappa
	-./cub3D Assets_tester/cub3D/maps/error2.cub
	@echo
	@echo 0 player nella mappa
	-./cub3D Assets_tester/cub3D/maps/error3.cub
	@echo
	@echo 1+ player nella mappa
	-./cub3D Assets_tester/cub3D/maps/error4.cub
	@echo
	@echo Mappa aperta con lo 0
	-./cub3D Assets_tester/cub3D/maps/error5.cub
	@echo
	@echo Mappa aperta con lo ' '
	-./cub3D Assets_tester/cub3D/maps/error6.cub
	@echo
	@echo Spazi nella configurazione dei colori
	-./cub3D Assets_tester/cub3D/maps/error7.cub
	@echo
	@echo Assente configurazione dei colori
	-./cub3D Assets_tester/cub3D/maps/error8.cub
	@echo
	@echo Numero negativo nella configurazione dei colori
	-./cub3D Assets_tester/cub3D/maps/error9.cub
	@echo
	@echo Numero oltre 255 nella configurazione dei colori
	-./cub3D Assets_tester/cub3D/maps/error10.cub
	@echo
	@echo File vuoto
	-./cub3D Assets_tester/cub3D/maps/error11.cub
	@echo
	@echo Assente configurazione delle texture
	-./cub3D Assets_tester/cub3D/maps/error12.cub
	@echo
	@echo Texture inesistente
	-./cub3D Assets_tester/cub3D/maps/error13.cub
	@echo
	@echo Riga vuota nella mappa
	-./cub3D Assets_tester/cub3D/maps/error14.cub
	@echo
	@echo Riga vuota nel file
	-./cub3D Assets_tester/cub3D/maps/error15.cub
	@echo
	@echo Player fuori dalla mappa
	-./cub3D Assets_tester/cub3D/maps/error16.cub
	@echo
	@echo Mappa prima della configurazione
	-./cub3D Assets_tester/cub3D/maps/error17.cub
	@echo
	@echo Spazi dentro la mappa
	-./cub3D Assets_tester/cub3D/maps/error18.cub
	@echo
	@echo Carattere inaspettato
	-./cub3D Assets_tester/cub3D/maps/error19.cub
	@echo
	@echo Configurazione dei colori in piu. Ex 1,1,1,1
	-./cub3D Assets_tester/cub3D/maps/error20.cub
	@echo
	@echo Configurazione delle texture in piu. Ex ./NO.xmp ./NO2.xpm
	-./cub3D Assets_tester/cub3D/maps/error21.cub
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