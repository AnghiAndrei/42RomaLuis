FROM debian:latest

RUN apt-get update \
    apt-get install mariadb-server

COPY configure.sh /tmp/configure.sh
CMD ["sh", "/tmp/configure.sh"]