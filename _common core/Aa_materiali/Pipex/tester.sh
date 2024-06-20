echo '
test-leaks-m: re
	@rm -f infile
	@clear
	@echo ================= Mandatori: controllo dell input =================
	-valgrind ./pipex
	@echo
	-valgrind ./pipex infile
	@echo
	-valgrind ./pipex infile ls
	@echo
	-valgrind ./pipex infile ls wc
	@echo
	@echo "! Nota: Deve dare errore perche il file: infile; non esiste !"
	-valgrind ./pipex infile ls cat outfile
	@echo
	@echo "                 ==== Creazione file: infile ===="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	@echo "             ==== Controllo esistenza dei comandi ===="
	-valgrind ./pipex infile aanghi cat outfile
	@echo
	-valgrind ./pipex infile ls aanghi outfile
	@echo ==================== Mandatori: function check ====================
	-valgrind ./pipex infile "ls -la" "grep .c" outfile
	@echo ! E errore se il file: outfile, non ha i permessi di lettura/scrittura !
	@cat outfile
	@-< infile ls -la | grep .c > outfile2
	@echo ! Se i 2 output non sono uguali e considerato errore !
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-valgrind ./pipex infile "grep hola" "cat -e" outfile
	@-< infile grep hola | cat -e > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo "             ==== Controllo delle \' ===="
	-valgrind ./pipex infile "grep \'hola\'" "cat -e" outfile
	@-< infile grep \'hola\' | cat -e > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo "             ==== Controllo delle \" ===="
	-valgrind ./pipex infile "grep \"hola\"" "cat -e" outfile
	@-< infile grep \"hola\" | cat -e > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-leaks-b: bonus
	@clear
	@echo ===== Bonus: input check =====
	-valgrind ./pipex
	@echo
	-valgrind ./pipex infile
	@echo
	-valgrind ./pipex infile cmd1
	@echo
	-valgrind ./pipex infile cmd1 cmd2
	@echo
	-valgrind ./pipex infile ls cat outfile
	@echo
	@echo "===== File: infile; create from tester ====="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	-valgrind ./pipex infile aanghi cat outfile
	@echo
	-valgrind ./pipex infile ls aanghi outfile
	@echo
	@cat outfile
	@echo "! Se il file: outfile; non e apribile, e considerato errore"
	@echo ==================== Bonus: function check ====================
	@echo ! Se i 2 output non sono uguali e considerato errore !
	-valgrind ./pipex infile "echo voglio mangiare il tuo pancreas" "grep pancreas" "tr a-z A-Z" "head -n 1" "cat -e" "wc -l" outfile
	@cat outfile
	@rm outfile
	< infile echo 'voglio mangiare il tuo pancreas' | grep pancreas | tr a-z A-Z | head -n 1 | cat -e | wc -l > outfile
	@cat outfile
	@echo "===== CONTROLLO HERE_DOC ====="
	@echo "! Il file: outfile; deve contenere l'output del pipex precedente con l'attuale !"
	-valgrind ./pipex here_doc fine "grep 42" "cat -e" "wc" outfile
	@cat outfile
	-grep 42 << fine | cat -e | wc >> outfile
	@cat outfile
	@rm outfile
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks-m: re
	@clear
	@echo ===== Mandatori: input check =====
	-./pipex
	@echo
	-./pipex infile
	@echo
	-./pipex infile cmd1
	@echo
	-./pipex infile cmd1 cmd2
	@echo
	-./pipex infile ls cat outfile
	@echo
	@echo "===== File: infile; create from tester ====="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	-./pipex infile aanghi cat outfile
	@echo
	-./pipex infile ls aanghi outfile
	@echo
	@cat outfile
	@echo ! Se il file: outfile, non e apribile, e considerato errore
	@echo ==================== Mandatori: function check ====================
	@echo ! Se i 2 output non sono uguali e considerato errore !
	-./pipex infile "ls -la" "grep .c" outfile
	@cat outfile
	@rm outfile
	-< infile ls -la | grep .c > outfile
	@cat outfile
	@rm outfile
	@echo ---------------------------------
	-./pipex infile "grep hola" "cat -e" outfile
	@cat outfile
	@rm outfile
	-< infile grep hola | cat -e > outfile
	@cat outfile
	@rm outfile
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks-b: bonus
	@clear
	@echo ===== Bonus: input check =====
	-./pipex
	@echo
	-./pipex infile
	@echo
	-./pipex infile cmd1
	@echo
	-./pipex infile cmd1 cmd2
	@echo
	-./pipex infile ls cat outfile
	@echo
	@echo "===== File: infile; create from tester ====="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	-./pipex infile aanghi cat outfile
	@echo
	-./pipex infile ls aanghi outfile
	@echo
	@cat outfile
	@echo ==================== Bonus: function check ====================
	@echo "! Se il file: outfile; non e apribile, e considerato errore"
	@echo ! Se i 2 output non sono uguali e considerato errore !
	-./pipex infile "echo voglio mangiare il tuo pancreas" "grep pancreas" "tr a-z A-Z" "head -n 1" "cat -e" "wc -l" outfile
	@cat outfile
	@rm outfile
	< infile echo 'voglio mangiare il tuo pancreas' | grep pancreas | tr a-z A-Z | head -n 1 | cat -e | wc -l > outfile
	@cat outfile
	@echo "===== CONTROLLO HERE_DOC ====="
	@echo "! Il file: outfile; deve contenere l'output del pipex precedente con l'attuale !"
	-./pipex here_doc fine "grep 42" "cat -e" "wc" outfile
	@cat outfile
	-grep 42 << fine | cat -e | wc >> outfile
	@cat outfile
	@rm outfile
	@rm infile
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
echo "make test-leaks-m: per testare l'input della parte mandatori con controllo leaks"
echo "make test-nleaks-m: per testare l'input della parte mandatori senza controllo leaks"
echo "make test-leaks-b: per testare l'input della parte bonus con controllo leaks"
echo "make test-nleaks-b: per testare l'input della parte bonus senza controllo leaks"
echo "make test-norm: per testare la norma"