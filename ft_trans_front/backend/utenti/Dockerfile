FROM python:3.10

WORKDIR /app

# Installa le dipendenze di sistema e Python
RUN apt-get update && \
    apt-get install -y --no-install-recommends dos2unix

COPY requirements.txt /app/
RUN pip install --no-cache-dir -r requirements.txt

COPY . /app/

#RUN chmod +x entrypoint.sh

COPY entrypoint.sh /app/

# Converti gli script con dos2unix e rendi eseguibile lo script entrypoint
RUN dos2unix entrypoint.sh && \
    chmod +x entrypoint.sh

ENTRYPOINT ["/app/entrypoint.sh"]

CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]
