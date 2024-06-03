# Usa un'immagine leggera di Node.js come base
FROM node:14-alpine

# Imposta la directory di lavoro nel container
WORKDIR /app

# Copia il package.json e il package-lock.json nella directory di lavoro
# COPY ./package*.json ./

# Installa le dipendenze del progetto

# Copia il resto del frontend nella directory di lavoro
COPY . .

RUN npm install

# Compila il frontend (puoi adattare questo comando in base al tuo ambiente e framework)
# RUN npm run start

# Esponi la porta 3000 per consentire l'accesso all'applicazione
 EXPOSE 3000

# Comando di avvio dell'applicazione
CMD ["npm", "start"]
#CMD ["tail", "-f", "/dev/null"]
