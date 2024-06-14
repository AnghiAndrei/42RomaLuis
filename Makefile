all:
	git add .
	git commit -m "voglio mangiare il tuo pancreas"
	git push

MSG=$$(read var)
-m:
	git add .
	git commit -m "$(MSG)"
	git push