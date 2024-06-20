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
	@rm infile
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-leaks-b: bonus
	@rm -f infile
	@clear
	@echo ================= Bonus: controllo dell input =================
	-valgrind ./pipex_bonus
	@echo
	-valgrind ./pipex_bonus infile
	@echo
	-valgrind ./pipex_bonus infile ls
	@echo
	-valgrind ./pipex_bonus infile ls wc
	@echo
	@echo "! Nota: Deve dare errore perche il file: infile; non esiste !"
	-valgrind ./pipex_bonus infile ls cat outfile
	@echo
	@echo "                 ==== Creazione file: infile ===="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	@echo "             ==== Controllo esistenza dei comandi ===="
	-valgrind ./pipex_bonus infile aanghi cat outfile
	@echo
	-valgrind ./pipex_bonus infile ls aanghi outfile
	@echo ==================== Bonus: function check ====================
	-valgrind ./pipex_bonus infile "ls -la" "grep .c" outfile
	@echo ! E errore se il file: outfile, non ha i permessi di lettura/scrittura !
	@cat outfile
	@-< infile ls -la | grep .c > outfile2
	@echo ! Se i 2 output non sono uguali e considerato errore !
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-valgrind ./pipex_bonus infile "grep hola" "cat -e" outfile
	@-< infile grep hola | cat -e > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-valgrind ./pipex infile "echo voglio mangiare il tuo pancreas" "grep pancreas" "tr a-z A-Z" "head -n 1" "cat -e" "wc -l" outfile
	< infile echo 'voglio mangiare il tuo pancreas' | grep pancreas | tr a-z A-Z | head -n 1 | cat -e | wc -l > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo "                ===== CONTROLLO HERE_DOC ====="
	@echo "! Il file: outfile; deve contenere una righa vuota all inizio !"
	-valgrind ./pipex here_doc fine "grep 42" "cat -e" "wc" outfile
	-grep 42 << fine | cat -e | wc >> outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@rm infile
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks-m: re
	@rm -f infile
	@clear
	@echo ================= Mandatori: controllo dell input =================
	-./pipex
	@echo
	-./pipex infile
	@echo
	-./pipex infile ls
	@echo
	-./pipex infile ls wc
	@echo
	@echo "! Nota: Deve dare errore perche il file: infile; non esiste !"
	-./pipex infile ls cat outfile
	@echo
	@echo "                 ==== Creazione file: infile ===="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	@echo "             ==== Controllo esistenza dei comandi ===="
	-./pipex infile aanghi cat outfile
	@echo
	-./pipex infile ls aanghi outfile
	@echo ==================== Mandatori: function check ====================
	-./pipex infile "ls -la" "grep .c" outfile
	@echo ! E errore se il file: outfile, non ha i permessi di lettura/scrittura !
	@cat outfile
	@-< infile ls -la | grep .c > outfile2
	@echo ! Se i 2 output non sono uguali e considerato errore !
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-./pipex infile "grep hola" "cat -e" outfile
	@-< infile grep hola | cat -e > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@rm infile
	@echo
	@echo TESTER AANGHI [Angly colui che regna]

test-nleaks-b: bonus
	@rm -f infile
	@clear
	@echo ================= Bonus: controllo dell input =================
	-./pipex_bonus
	@echo
	-./pipex_bonus infile
	@echo
	-./pipex_bonus infile ls
	@echo
	-./pipex_bonus infile ls wc
	@echo
	@echo "! Nota: Deve dare errore perche il file: infile; non esiste !"
	-./pipex_bonus infile ls cat outfile
	@echo
	@echo "                 ==== Creazione file: infile ===="
	@echo hola > infile
	@echo hola42 >> infile
	@echo ciao42 >> infile
	@echo ciao >> infile
	@echo "             ==== Controllo esistenza dei comandi ===="
	-./pipex_bonus infile aanghi cat outfile
	@echo
	-./pipex_bonus infile ls aanghi outfile
	@echo ==================== Bonus: function check ====================
	-./pipex_bonus infile "ls -la" "grep .c" outfile
	@echo ! E errore se il file: outfile, non ha i permessi di lettura/scrittura !
	@cat outfile
	@-< infile ls -la | grep .c > outfile2
	@echo ! Se i 2 output non sono uguali e considerato errore !
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-./pipex_bonus infile "grep hola" "cat -e" outfile
	@-< infile grep hola | cat -e > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo ---------------------------------
	-./pipex infile "echo voglio mangiare il tuo pancreas" "grep pancreas" "tr a-z A-Z" "head -n 1" "cat -e" "wc -l" outfile
	< infile echo 'voglio mangiare il tuo pancreas' | grep pancreas | tr a-z A-Z | head -n 1 | cat -e | wc -l > outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
	@echo "                ===== CONTROLLO HERE_DOC ====="
	@echo "! Il file: outfile; deve contenere una righa vuota all inizio !"
	-./pipex here_doc fine "grep 42" "cat -e" "wc" outfile
	-grep 42 << fine | cat -e | wc >> outfile2
	diff outfile outfile2
	@rm outfile
	@rm outfile2
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