start:
	@docker compose up --build

prune:
	-docker compose down --volumes --remove-orphans
	-docker stop $(docker ps -qa)
	-docker rm -f $(docker ps -a -qa)
	-docker volume rm -f $(docker volume ls -qa)
	-docker network rm $(docker network ls -q) || true
	-docker image prune --all --force
	-docker system prune --all --force --volumes

all: prune start
