echo '
test-leaks: re
    @-title TESTER AANGHI [Angly colui che regna]
    @clear
	-valgrind ./minishell input
	@echo
	-valgrind ./minishell input input2
	@echo
    @echo
    @echo TESTER AANGHI [Angly colui che regna]

test-nleaks: re
    @-title TESTER AANGHI [Angly colui che regna]
    @clear
	-./minishell input
	@echo
	-./minishell input input2
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