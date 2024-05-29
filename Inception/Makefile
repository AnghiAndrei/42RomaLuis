MAKEFLAGS += -s

all: stop prune canc start show

start:
	clear
	-docker compose -f ./srcs/docker-compose.yml up -d --remove-orphans --build

show:
	-echo ============= Conteiner =============
	docker ps -as
	-echo 
	-echo ============= Network =============
	docker network ls
	-echo 
	-echo ============= Volume =============
	docker volume ls
	-echo 

stop:
	docker compose -f ./srcs/docker-compose.yml down -v --rmi all

prune:
	-docker stop $$(docker ps -qa)
	-docker rm $$(docker ps -a -qa)
	-docker rmi -f $$(docker images -qa)
	-docker volume rm $$(docker volume ls -qa)
	-docker network rm $$(docker network ls -q)
	-docker image prune --all --force
	-docker system prune --all --force --volumes

canc:
	sudo rm -fr /home/aanghi/data/mdb_vol
	sudo rm -fr /home/aanghi/data/wp_vol
	mkdir /home/aanghi/data/mdb_vol
	mkdir /home/aanghi/data/wp_vol