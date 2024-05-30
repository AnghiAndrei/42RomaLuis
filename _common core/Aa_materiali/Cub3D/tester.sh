mkdir maps

echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0

        1111111111
        1000000001
111111111000000001
100000000000000001
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
        1000000001
111111111000000001
100000000000000001
100000000000000001
111111111111111111" > maps/error3.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1111111111
        1000000001
111111111000000001
100000000000S00001
100000N00000000001
111111111111111111" > maps/error4.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 220,100,0
C 225,30,0

        1011111111
        1000000001
111111111000000001
100000000000000001
100000N00000000001
111111111111111111" > maps/error5.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm
F 220,100,0
C 225,30,0

11111111111111111111
 0000000000000000001
10010000000000000001
10010N00000000000001
11111111111111110111
               101
               111" > maps/error6.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 156,156,156
C 37,  40,  80

11111111111111111111
100000000000000000011111111111111111111111111
100000000000000000000000010000000100000100N01
100000000000000000011111010011100100101000001
11000000000111111111   1000000010000100000001
 11100000111           1111111111111111111111
   1000001
   1000001111111111111111111111111111111111111111
   1000000000000000000000000000000000000000000001
   1011101001011101001010001110111011101001011101
   1010101101010001001010001010100010001101010101
   1010101101010001001010001010111010001101010101
   1011101011010101000100001100100010101011011101
   1010101001011101110100001010111011101001010101
   1000000000000000000000000000000000000000000001
   1111111111111111111111111111111111111111111111" > maps/error7.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 156,156,156
C 

11111111111111111111
100000000000000000011111111111111111111111111
100000000000000000000000010000000100000100N01
100000000000000000011111010011100100101000001
11000000000111111111   1000000010000100000001
 11100000111           1111111111111111111111
   1000001
   1000001111111111111111111111111111111111111111
   1000000000000000000000000000000000000000000001
   1011101001011101001010001110111011101001011101
   1010101101010001001010001010100010001101010101
   1010101101010001001010001010111010001101010101
   1011101011010101000100001100100010101011011101
   1010101001011101110100001010111011101001010101
   1000000000000000000000000000000000000000000001
   1111111111111111111111111111111111111111111111" > maps/error8.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 156,156,156
C -156,156,156

11111111111111111111
100000000000000000011111111111111111111111111
100000000000000000000000010000000100000100N01
100000000000000000011111010011100100101000001
11000000000111111111   1000000010000100000001
 11100000111           1111111111111111111111
   1000001
   1000001111111111111111111111111111111111111111
   1000000000000000000000000000000000000000000001
   1011101001011101001010001110111011101001011101
   1010101101010001001010001010100010001101010101
   1010101101010001001010001010111010001101010101
   1011101011010101000100001100100010101011011101
   1010101001011101110100001010111011101001010101
   1000000000000000000000000000000000000000000001
   1111111111111111111111111111111111111111111111" > maps/error9.cub
echo "NO ./textures/NO.xpm
SO ./textures/SO.xpm
WE ./textures/WE.xpm
EA ./textures/EA.xpm

F 156,156,156
C 43156,156,156

11111111111111111111
100000000000000000011111111111111111111111111
100000000000000000000000010000000100000100N01
100000000000000000011111010011100100101000001
11000000000111111111   1000000010000100000001
 11100000111           1111111111111111111111
   1000001
   1000001111111111111111111111111111111111111111
   1000000000000000000000000000000000000000000001
   1011101001011101001010001110111011101001011101
   1010101101010001001010001010100010001101010101
   1010101101010001001010001010111010001101010101
   1011101011010101000100001100100010101011011101
   1010101001011101110100001010111011101001010101
   1000000000000000000000000000000000000000000001
   1111111111111111111111111111111111111111111111" > maps/error10.cub
echo "" > maps/error11.cub

echo '
test-leaks: re
    @-title TESTER AANGHI [Angly colui che regna]
    @clear
	-valgrind ./cub3D
	@echo
	-valgrind ./cub3D maps/1.cub maps/2.cub
	@echo
	-valgrind ./cub3D maps/no_exist.cub
	@echo
	-valgrind ./cub3D maps/1.aanghi
	@echo
	-valgrind ./cub3D maps/error1.cub
	@echo
	-valgrind ./cub3D maps/error2.cub
	@echo
	-valgrind ./cub3D maps/error3.cub
	@echo
	-valgrind ./cub3D maps/error4.cub
	@echo
	-valgrind ./cub3D maps/error5.cub
	@echo
	-valgrind ./cub3D maps/error6.cub
	@echo
	-valgrind ./cub3D maps/error7.cub
	@echo
	-valgrind ./cub3D maps/error8.cub
	@echo
	-valgrind ./cub3D maps/error9.cub
	@echo
	-valgrind ./cub3D maps/error10.cub
    @echo
    -valgrind ./cub3D maps/error11.cub
    @echo
    @echo
    @echo TESTER AANGHI [Angly colui che regna]

test-nleaks: re
    @-title TESTER AANGHI [Angly colui che regna]
    @clear
	-./cub3D
	@echo
	-./cub3D maps/1.cub maps/2.cub
	@echo
	-./cub3D maps/no_exist.cub
	@echo
	-./cub3D maps/1.aanghi
	@echo
	-./cub3D maps/error1.cub
	@echo
	-./cub3D maps/error2.cub
	@echo
	-./cub3D maps/error3.cub
	@echo
	-./cub3D maps/error4.cub
	@echo
	-./cub3D maps/error5.cub
	@echo
	-./cub3D maps/error6.cub
	@echo
	-./cub3D maps/error7.cub
	@echo
	-./cub3D maps/error8.cub
	@echo
	-./cub3D maps/error9.cub
	@echo
	-./cub3D maps/error10.cub
    @echo
    -./cub3D maps/error11.cub
    @echo
    @echo
    @echo TESTER AANGHI [Angly colui che regna]

test-norm:
    @echo Errori di norma:
    norminette *.c *.h | grep Error! | wc -l
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