start:
	docker compose up --build

prune:
	-docker stop $$(docker ps -qa)
	-docker rm $$(docker ps -a -qa)
	-docker rmi -f $$(docker images -qa)
	-docker volume rm $$(docker volume ls -qa)
	-docker network rm $$(docker network ls -q)
	-docker image prune --all --force
	-docker system prune --all --force --volumes

all: prune start