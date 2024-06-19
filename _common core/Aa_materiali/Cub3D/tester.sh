mkdir maps

echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0

        1111111111
111111111000000001
1N0000000000000001
111111111111111111" > maps/error1.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0" > maps/error2.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1111111111
111111111000000001
100000000000000001
111111111111111111" > maps/error3.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1111111111
111111111000000001
1S0N00000000000001
111111111111111111" > maps/error4.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1111011111
111111111000000001
1S0000000000000001
111111111111111111" > maps/error5.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm
F 220,100,0
C 225,30,0

        1111 11111
111111111000000001
1S0000000000000001
111111111111111111" > maps/error6.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 156,156,156
C 37,  40,  80

        1111111111
111111111000000001
1S0000000000000001
111111111111111111" > maps/error7.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 156,156,156
C 

        1111111111
111111111000000001
1S0000000000000001
111111111111111111" > maps/error8.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 156,156,156
C -156,156,156

        1111111111
111111111000000001
1S0000000000000001
111111111111111111" > maps/error9.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 156,156,156
C 43156,156,156

        1111111111
111111111000000001
1S0000000000000001
111111111111111111" > maps/error10.cub
echo "" > maps/error11.cub
echo "NO
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1111111111
111111111000000001
1S0000000000000001
111111111111111111" > maps/error12.cub
echo "NO ./textures/not_exist.xpm
SO ./textures/not_exist.xpm
WE ./textures/not_exist.xpm
EA ./textures/not_exist.xpm

F 220,100,0
C 225,30,0

        1111111111
111111111000000001
1S0000000000000001
111111111111111111" > maps/error13.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1111111111
111111111000000001

1S0000000000000001
111111111111111111" > maps/error14.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm

WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1111111111
111111111000000001
1S0000000000000001
111111111111111111" > maps/error15.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1111111111
111111111000000001
100000000000000001 S
111111111111111111" > maps/error16.cub
echo "        1111111111
111111111000000001
1000000000000000S1
111111111111111111

NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0" > maps/error17.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1111111111
111111111000000001
100   000000S00001
111111111111111111" > maps/error18.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1111111111
111111111000000001
100f00000000S00001
111111111111111111" > maps/error19.cub

echo '
test-leaks: re
	@clear
	@echo Senza parametri
	-valgrind ./cub3D
	@echo
	@echo Piu di un parametro
	-valgrind ./cub3D maps/1.cub maps/2.cub
	@echo
	@echo Mappa inesistente
	-valgrind ./cub3D maps/no_exist.cub
	@echo
	@echo Mappa non .aanghi
	-valgrind ./cub3D maps/1.aanghi
	@echo
	@echo Manca la configurazione del soffitto
	-valgrind ./cub3D maps/error1.cub
	@echo
	@echo Manca la mappa
	-valgrind ./cub3D maps/error2.cub
	@echo
	@echo 0 player nella mappa
	-valgrind ./cub3D maps/error3.cub
	@echo
	@echo 1+ player nella mappa
	-valgrind ./cub3D maps/error4.cub
	@echo
	@echo Mappa aperta con lo 0
	-valgrind ./cub3D maps/error5.cub
	@echo
	@echo Mappa aperta con lo ' '
	-valgrind ./cub3D maps/error6.cub
	@echo
	@echo Spazi nella configurazione dei colori
	-valgrind ./cub3D maps/error7.cub
	@echo
	@echo Assente configurazione dei colori
	-valgrind ./cub3D maps/error8.cub
	@echo
	@echo Numero negativo nella configurazione dei colori
	-valgrind ./cub3D maps/error9.cub
	@echo
	@echo Numero oltre 255 nella configurazione dei colori
	-valgrind ./cub3D maps/error10.cub
	@echo
	@echo File vuoto
	-valgrind ./cub3D maps/error11.cub
	@echo
	@echo Assente configurazione delle texture
	-valgrind ./cub3D maps/error12.cub
	@echo
	@echo Texture inesistente
	-valgrind ./cub3D maps/error13.cub
	@echo
	@echo Riga vuota nella mappa
	-valgrind ./cub3D maps/error14.cub
	@echo
	@echo Riga vuota nel file
	-valgrind ./cub3D maps/error15.cub
	@echo
	@echo Player fuori dalla mappa
	-valgrind ./cub3D maps/error16.cub
	@echo
	@echo Mappa prima della configurazione
	-valgrind ./cub3D maps/error17.cub
	@echo
	@echo Spazi dentro la mappa
	-valgrind ./cub3D maps/error18.cub
	@echo
	@echo Carattere inaspettato
	-valgrind ./cub3D maps/error19.cub
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks: re
	@clear
	@echo Senza parametri
	-./cub3D
	@echo
	@echo Piu di un parametro
	-./cub3D maps/1.cub maps/2.cub
	@echo
	@echo Mappa inesistente
	-./cub3D maps/no_exist.cub
	@echo
	@echo Mappa non .aanghi
	-./cub3D maps/1.aanghi
	@echo
	@echo Manca la configurazione del soffitto
	-./cub3D maps/error1.cub
	@echo
	@echo Manca la mappa
	-./cub3D maps/error2.cub
	@echo
	@echo 0 player nella mappa
	-./cub3D maps/error3.cub
	@echo
	@echo 1+ player nella mappa
	-./cub3D maps/error4.cub
	@echo
	@echo Mappa aperta con lo 0
	-./cub3D maps/error5.cub
	@echo
	@echo Mappa aperta con lo ' '
	-./cub3D maps/error6.cub
	@echo
	@echo Spazi nella configurazione dei colori
	-./cub3D maps/error7.cub
	@echo
	@echo Assente configurazione dei colori
	-./cub3D maps/error8.cub
	@echo
	@echo Numero negativo nella configurazione dei colori
	-./cub3D maps/error9.cub
	@echo
	@echo Numero oltre 255 nella configurazione dei colori
	-./cub3D maps/error10.cub
	@echo
	@echo File vuoto
	-./cub3D maps/error11.cub
	@echo
	@echo Assente configurazione delle texture
	-./cub3D maps/error12.cub
	@echo
	@echo Texture inesistente
	-./cub3D maps/error13.cub
	@echo
	@echo Riga vuota nella mappa
	-./cub3D maps/error14.cub
	@echo
	@echo Riga vuota nel file
	-./cub3D maps/error15.cub
	@echo
	@echo Player fuori dalla mappa
	-./cub3D maps/error16.cub
	@echo
	@echo Mappa prima della configurazione
	-./cub3D maps/error17.cub
	@echo
	@echo Spazi dentro la mappa
	-./cub3D maps/error18.cub
	@echo
	@echo Carattere inaspettato
	-./cub3D maps/error19.cub
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