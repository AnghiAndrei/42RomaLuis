FROM node:16
WORKDIR /app
RUN npm install -g http-server
COPY ./app ./
EXPOSE 8080
CMD ["http-server", "-p", "8080", "-P", "http://0.0.0.0:8080"]