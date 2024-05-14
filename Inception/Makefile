MAKEFLAGS += -s

all: start

start:
	clear
	-docker compose up -d --remove-orphans

show:
	docker ps -as

stop:
	docker compose down

test: start show stop