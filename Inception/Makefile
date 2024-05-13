all: nginx_build
	sudo docker run -d -p 443:443 nginx

mostra:
	sudo docker ps

nginx_build:
	make -C NGINX