FROM alpine:3.13
COPY configure.sh configure.sh
EXPOSE 3306
RUN	apk update && \
	apk upgrade && \
	apk add --no-cache mariadb mariadb-client openrc