MAKEFLAGS += -s

all: start

start: stop prune
	clear
	-docker compose up -d --remove-orphans --build

show:
	docker ps -as

stop:
	docker compose down -v --rmi all

prune:
	docker image prune --all --force
	docker system prune --all --force --volumes

test: start show stop