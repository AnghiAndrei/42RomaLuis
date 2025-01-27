FROM node:16
WORKDIR /app
RUN npm install -g serve
COPY ./app ./
EXPOSE 8080
CMD ["serve", "-s", ".", "-l", "8080"]