MAKEFLAGS += -s

all: stop prune canc start show

start:
	clear
	-docker compose up -d --remove-orphans --build

show:
	docker ps -as

stop:
	docker compose down -v --rmi all

prune:
	-docker stop $$(docker ps -q)
	-docker rm $$(docker ps -a -q)
	-docker rmi $$(docker images -q)
	-docker image prune --all --force
	-docker system prune --all --force --volumes

canc:
	sudo rm -fr /home/aanghi/data/db
	sudo rm -fr /home/aanghi/data/wp