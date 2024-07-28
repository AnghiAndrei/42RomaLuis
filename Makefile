all:
	git add .
	git commit -m "voglio mangiare il tuo pancreas"
	git push
	git submodule foreach --recursive 'branch=$$(git symbolic-ref --short HEAD); git push origin $$branch'

pull:
	git pull
	sh finish_clone.sh

MSG=$$(read var; echo $$var;)
m:
	git add .
	git commit -m "$(MSG)"
	git push
	git submodule foreach --recursive 'branch=$$(git symbolic-ref --short HEAD); git push origin $$branch'
