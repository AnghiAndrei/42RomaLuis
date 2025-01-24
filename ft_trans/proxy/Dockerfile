FROM nginx:alpine

COPY ./nginx/nginx.conf /etc/nginx/nginx.conf

RUN mkdir -p /etc/nginx/certs && \
    apk add --no-cache openssl && \
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/certs/server.key -out /etc/nginx/certs/server.crt -subj "/C=IT/ST=Rome/L=Rome/O=fttrans/OU=fttrans/CN=$IPADDR" && \
    apk del openssl
