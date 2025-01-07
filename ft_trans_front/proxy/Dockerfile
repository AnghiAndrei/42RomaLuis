# proxy/Dockerfile

FROM nginx:alpine

# Copy the custom Nginx configuration file
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf

RUN mkdir -p /etc/nginx/certs && \
    apk add --no-cache openssl && \
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/certs/server.key -out /etc/nginx/certs/server.crt -subj "/C=IT/ST=Rome/L=Rome/O=Sergio/OU=Sergio/CN=localhost" && \
    apk del openssl