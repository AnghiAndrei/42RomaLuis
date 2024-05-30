echo '
test-leaks-m: re
    @-title TESTER AANGHI [Angly colui che regna]
    @clear
	@echo ===== Mandatori =====
	-valgridn ./push_swap
	@echo
	-valgridn ./push_swap ""
	@echo
	-valgridn ./push_swap ''
	@echo
	-valgridn ./push_swap "   "
	@echo
	-valgridn ./push_swap 42 42
	@echo
	-valgridn ./push_swap Voglio mangiare il tuo pancreas
	@echo
	-valgridn ./push_swap "Voglio mangiare il tuo pancreas"
	@echo
	-valgridn ./push_swap "Voglio mangiare il tuo pancreas" 42
	@echo
	-valgridn ./push_swap "42" Voglio mangiare il tuo pancreas
	@echo
	-valgridn ./push_swap "++42"
	@echo
	-valgridn ./push_swap "--42"
	@echo
	-valgridn ./push_swap 1 "2" 3
	@echo
	-valgridn ./push_swap 1 "2 3" 4
	@echo
	-valgridn ./push_swap 1 "2 3" 2
	@echo
	-valgridn ./push_swap "''"
	@echo
	-valgridn ./push_swap '""'
    @echo
    @echo
    @echo TESTER AANGHI [Angly colui che regna]

test-leaks-b: bonus
    @-title TESTER AANGHI [Angly colui che regna]
    @clear
	@echo ===== Bonus =====
	-valgridn ./checker
	@echo
	-valgridn ./checker ""
	@echo
	-valgridn ./checker ''
	@echo
	-valgridn ./checker "   "
	@echo
	-valgridn ./checker 42 42
	@echo
	-valgridn ./checker Voglio mangiare il tuo pancreas
	@echo
	-valgridn ./checker "Voglio mangiare il tuo pancreas"
	@echo
	-valgridn ./checker "Voglio mangiare il tuo pancreas" 42
	@echo
	-valgridn ./checker "42" Voglio mangiare il tuo pancreas
	@echo
	-valgridn ./checker "++42"
	@echo
	-valgridn ./checker "--42"
	@echo
	-valgridn ./checker 1 "2" 3
	@echo
	-valgridn ./checker 1 "2 3" 4
	@echo
	-valgridn ./checker 1 "2 3" 2
    @echo
    @echo
    @echo TESTER AANGHI [Angly colui che regna]

test-nleaks-m: re
    @-title TESTER AANGHI [Angly colui che regna]
    @clear
	@echo ===== Mandatori =====
	-./push_swap
	@echo
	-./push_swap ""
	@echo
	-./push_swap ''
	@echo
	-./push_swap "   "
	@echo
	-./push_swap 42 42
	@echo
	-./push_swap Voglio mangiare il tuo pancreas
	@echo
	-./push_swap "Voglio mangiare il tuo pancreas"
	@echo
	-./push_swap "Voglio mangiare il tuo pancreas" 42
	@echo
	-./push_swap "42" Voglio mangiare il tuo pancreas
	@echo
	-./push_swap "++42"
	@echo
	-./push_swap "--42"
	@echo
	-./push_swap 1 "2" 3
	@echo
	-./push_swap 1 "2 3" 4
	@echo
	-./push_swap 1 "2 3" 2
	@echo
	-./push_swap "''"
	@echo
	-./push_swap '""'
    @echo
    @echo
    @echo TESTER AANGHI [Angly colui che regna]

test-nleaks-b: bonus
    @-title TESTER AANGHI [Angly colui che regna]
    @clear
	@echo ===== Bonus =====
	-./checker
	@echo
	-./checker ""
	@echo
	-./checker ''
	@echo
	-./checker "   "
	@echo
	-./checker 42 42
	@echo
	-./checker Voglio mangiare il tuo pancreas
	@echo
	-./checker "Voglio mangiare il tuo pancreas"
	@echo
	-./checker "Voglio mangiare il tuo pancreas" 42
	@echo
	-./checker "42" Voglio mangiare il tuo pancreas
	@echo
	-./checker "++42"
	@echo
	-./checker "--42"
	@echo
	-./checker 1 "2" 3
	@echo
	-./checker 1 "2 3" 4
	@echo
	-./checker 1 "2 3" 2
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
echo "make test-leaks-m: per testare l'input della parte mandatori con controllo leaks"
echo "make test-nleaks-m: per testare l'input della parte mandatori senza controllo leaks"
echo "make test-leaks-b: per testare l'input della parte bonus con controllo leaks"
echo "make test-nleaks-b: per testare l'input della parte bonus senza controllo leaks"
echo "make test-norm: per testare la norma"