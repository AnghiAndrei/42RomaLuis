all:
	git add .
	git commit -m "voglio mangiare il tuo pancreas"
	git push

pull:
	git pull
	sh finish_close.sh

MSG=$$(read var; echo $$var;)
m:
	git add .
	git commit -m "$(MSG)"
	git push