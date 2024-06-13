all:
	git add .
	git commit -m "hola"
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