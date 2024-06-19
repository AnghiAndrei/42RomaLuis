echo '
test-leaks: re
	@clear
	-valgrind ./philo
	@echo
	-valgrind ./philo 0 800 200
	@echo
	-valgrind ./philo 0 800 200 200
	@echo
	-valgrind ./philo 2 0 200 200
	@echo
	-valgrind ./philo 2 800 0 200
	@echo
	-valgrind ./philo 2 800 200 0
	@echo
	-valgrind ./philo 0 0 0 0
	@echo
	-valgrind ./philo 2 800 200 200 0
	@echo
	-valgrind ./philo 0 0 0 0 0
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks: re
	@clear
	-./philo
	@echo
	-./philo 0 800 200
	@echo
	-./philo 0 800 200 200
	@echo
	-./philo 2 0 200 200
	@echo
	-./philo 2 800 0 200
	@echo
	-./philo 2 800 200 0
	@echo
	-./philo 0 0 0 0
	@echo
	-./philo 2 800 200 200 0
	@echo
	-./philo 0 0 0 0 0
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-norm:
	@echo Errori di norma:
	@norminette *.c *.h | grep Error! | wc -l
	@echo
	@echo
	@echo TESTER AANGHI [Angly colui che regna]
' >> philo/Makefile

clear
echo "! Tester installato !"
echo
echo "Istruzioni:"
echo "make test-leaks: per testare l'input con controllo leaks"
echo "make test-nleaks: per testare l'input senza controllo leaks"
echo "make test-norm: per testare la norma"