echo '
test-i-leaks-m: re
	@clear
	@echo ===== Mandatori =====
	-valgrind ./push_swap
	@echo
	-valgrind ./push_swap ""
	@echo
	-valgrind ./push_swap ''
	@echo
	-valgrind ./push_swap "   "
	@echo
	-valgrind ./push_swap 42 42
	@echo
	-valgrind ./push_swap Voglio mangiare il tuo pancreas
	@echo
	-valgrind ./push_swap "Voglio mangiare il tuo pancreas"
	@echo
	-valgrind ./push_swap "Voglio mangiare il tuo pancreas" 42
	@echo
	-valgrind ./push_swap "42" Voglio mangiare il tuo pancreas
	@echo
	-valgrind ./push_swap "++42"
	@echo
	-valgrind ./push_swap "--42"
	@echo
	-valgrind ./push_swap 1 "2" 3
	@echo
	-valgrind ./push_swap 1 "2 3" 4
	@echo
	-valgrind ./push_swap 1 "2 3" 2
	@echo
	-valgrind ./push_swap "''"
	@echo
	-valgrind ./push_swap '""'
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-i-leaks-b: bonus
	@clear
	@echo ===== Bonus =====
	-valgrind ./checker
	@echo
	-valgrind ./checker ""
	@echo
	-valgrind ./checker ''
	@echo
	-valgrind ./checker "   "
	@echo
	-valgrind ./checker 42 42
	@echo
	-valgrind ./checker Voglio mangiare il tuo pancreas
	@echo
	-valgrind ./checker "Voglio mangiare il tuo pancreas"
	@echo
	-valgrind ./checker "Voglio mangiare il tuo pancreas" 42
	@echo
	-valgrind ./checker "42" Voglio mangiare il tuo pancreas
	@echo
	-valgrind ./checker "++42"
	@echo
	-valgrind ./checker "--42"
	@echo
	-valgrind ./checker 1 "2" 3
	@echo
	-valgrind ./checker 1 "2 3" 4
	@echo
	-valgrind ./checker 1 "2 3" 2
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-i-nleaks-m: re
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

test-i-nleaks-b: bonus
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

ARG_TESTER_100=$$(shuf -i 1-100 -n 100 | tr "\\n" " ") #genera 100 numeri random da 1 a 100
ARG_TESTER_500=$$(shuf -i 1-500 -n 500 | tr "\\n" " ") #genera 500 numeri random da 1 a 500

test-f100-nleaks-m: re
	@clear
	@wget https://github.com/AnghiAndrei/42RomaLuis/tree/main/_common%20core/Aa_materiali/Push_Swap/checker_aanghi || echo Errore nel scaricare il tester
	@echo "Lista ordinata: "
	@./$(NAME) $(ARG_TESTER_100) | checker_aanghi
	@echo "N. mosse: "
	@./$(NAME) $(ARG_TESTER_100) | wc -l
	@echo
	@rm -f checker_aanghi
	@echo TESTER AANGHI [Angly colui che regna]

test-f500-nleaks-m: re
	@clear
	@wget https://github.com/AnghiAndrei/42RomaLuis/tree/main/_common%20core/Aa_materiali/Push_Swap/checker_aanghi || echo Errore nel scaricare il tester
	@echo "Lista ordinata: "
	@./$(NAME) $(ARG_TESTER_500) | checker_aanghi
	@echo "N. mosse: "
	@./$(NAME) $(ARG_TESTER_500) | wc -l
	@echo
	@rm -f checker_aanghi
	@echo TESTER AANGHI [Angly colui che regna]

test-f100-leaks-m: re
	@clear
	@wget https://github.com/AnghiAndrei/42RomaLuis/tree/main/_common%20core/Aa_materiali/Push_Swap/checker_aanghi || echo Errore nel scaricare il tester
	@echo "Lista ordinata: "
	@valgrind ./$(NAME) $(ARG_TESTER_100) | checker_aanghi
	@echo "N. mosse: "
	@valgrind ./$(NAME) $(ARG_TESTER_100) | wc -l
	@echo
	@rm -f checker_aanghi
	@echo TESTER AANGHI [Angly colui che regna]

test-f500-leaks-m: re
	@clear
	@wget https://github.com/AnghiAndrei/42RomaLuis/tree/main/_common%20core/Aa_materiali/Push_Swap/checker_aanghi || echo Errore nel scaricare il tester
	@echo "Lista ordinata: "
	@valgrind ./$(NAME) $(ARG_TESTER_500) | checker_aanghi
	@echo "N. mosse: "
	@valgrind ./$(NAME) $(ARG_TESTER_500) | wc -l
	@echo
	@rm -f checker_aanghi
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
echo "make test-i-leaks-m: per testare l'input della parte mandatori con controllo leaks"
echo "make test-i-nleaks-m: per testare l'input della parte mandatori senza controllo leaks"
echo "make test-i-leaks-b: per testare l'input della parte bonus con controllo leaks"
echo "make test-i-nleaks-b: per testare l'input della parte bonus senza controllo leaks"
echo
echo "test-f100-nleaks-m: per testare il funzionamento della parte mandatori con 100 numeri senza controllo leaks"
echo "test-f500-nleaks-m: per testare il funzionamento della parte mandatori con 500 numeri senza controllo leaks"
echo "test-f100-leaks-m: per testare il funzionamento della parte mandatori con 100 numeri con il controllo leaks"
echo "test-f500-leaks-m: per testare il funzionamento della parte mandatori con 500 numeri con il controllo leaks"
echo
echo "make test-norm: per testare la norma"