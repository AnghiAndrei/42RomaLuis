echo '
test-leaks: re
    @-title TESTER AANGHI [Angly colui che regna]
    @clear
	-valgrind ./philosofer
	@echo
	-valgrind ./philosofer 0 800 200 200
	@echo
	-valgrind ./philosofer 2 0 200 200
	@echo
	-valgrind ./philosofer 2 800 0 200
	@echo
	-valgrind ./philosofer 2 800 200 0
	@echo
	-valgrind ./philosofer 0 0 0 0
	@echo
	-valgrind ./philosofer 2 800 200 0
	@echo
	-valgrind ./philosofer 0 0 0 0 0
	@echo
    @echo
    @echo TESTER AANGHI [Angly colui che regna]

test-nleaks: re
    @-title TESTER AANGHI [Angly colui che regna]
    @clear
	-./philosofer
	@echo
	-./philosofer 0 800 200 200
	@echo
	-./philosofer 2 0 200 200
	@echo
	-./philosofer 2 800 0 200
	@echo
	-./philosofer 2 800 200 0
	@echo
	-./philosofer 0 0 0 0
	@echo
	-./philosofer 2 800 200 0
	@echo
	-./philosofer 0 0 0 0 0
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