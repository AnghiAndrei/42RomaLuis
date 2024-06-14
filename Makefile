all:
	git add .
	git commit -m "voglio mangiare il tuo pancreas"
	git push

MSG=$$(read var; echo var)
-m:
	git add .
	git commit -m "$(MSG)"
	git push

# m:
# 	@read -p "Inserisci il messaggio di commit: " MSG; \
# 	git add .; \
# 	git commit -m "$$MSG"; \
# 	git push