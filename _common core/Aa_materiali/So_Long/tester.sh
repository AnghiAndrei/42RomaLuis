mkdir maps

echo "" > maps/error1.ber
echo "
11111
10CP1
11111" > maps/error2.ber
echo "
11111
1E0P1
11111" > maps/error3.ber
echo "
11111
1EC01
11111" > maps/error4.ber
echo "
111111
1ECPX1
111111" > maps/error5.ber
echo "
111111
1ECP0
111111" > maps/error6.ber
echo "
111111
1ECP00
111111" > maps/error7.ber
echo "
111111
1CEP01
111111" > maps/error8.ber
echo "
11111
1ECP1
10001
10001
11111" > maps/error9.ber
echo "
11111
1ECP1
1E001
11111" > maps/error10.ber
echo "
11111
1ECP1
10P01
11111" > maps/error11.ber

echo '
test-leaks: re
	@clear
	-valgrind ./so_long
	@echo
	-valgrind ./so_long maps/1.ber maps/2.ber
	@echo
	-valgrind ./so_long maps/no_exist.ber
	@echo
	-valgrind ./so_long maps/1.aanghi
	@echo
	-valgrind ./so_long maps/error1.ber
	@echo
	-valgrind ./so_long maps/error2.ber
	@echo
	-valgrind ./so_long maps/error3.ber
	@echo
	-valgrind ./so_long maps/error4.ber
	@echo
	-valgrind ./so_long maps/error5.ber
	@echo
	-valgrind ./so_long maps/error6.ber
	@echo
	-valgrind ./so_long maps/error7.ber
	@echo
	-valgrind ./so_long maps/error8.ber
	@echo
	-valgrind ./so_long maps/error9.ber
	@echo
	-valgrind ./so_long maps/error10.ber
	@echo
	-valgrind ./so_long maps/error11.ber
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks: re
	@clear
	- ./so_long
	@echo
	- ./so_long maps/1.ber maps/2.ber
	@echo
	- ./so_long maps/no_exist.ber
	@echo
	- ./so_long maps/1.aanghi
	@echo
	- ./so_long maps/error1.ber
	@echo
	- ./so_long maps/error2.ber
	@echo
	- ./so_long maps/error3.ber
	@echo
	- ./so_long maps/error4.ber
	@echo
	- ./so_long maps/error5.ber
	@echo
	- ./so_long maps/error6.ber
	@echo
	- ./so_long maps/error7.ber
	@echo
	- ./so_long maps/error8.ber
	@echo
	- ./so_long maps/error9.ber
	@echo
	- ./so_long maps/error10.ber
	@echo
	- ./so_long maps/error11.ber
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