FROM debian:bullseye

RUN apt-get update && apt-get install -y  postfix dovecot-core dovecot-imapd dovecot-pop3d \
    && apt-get clean

COPY main.cf /etc/postfix/main.cf
COPY sasl_passwd /etc/postfix/sasl_passwd
COPY dovecot.conf /etc/dovecot/dovecot.conf
COPY 10-master.conf /etc/dovecot/conf.d/10-master.conf
COPY 10-auth.conf /etc/dovecot/conf.d/10-auth.conf

RUN echo "${SEND_EMAIL} ${SEND_PASSWORD}" > /etc/postfix/sasl_passwd && \
    chmod 600 /etc/postfix/sasl_passwd && \
    postmap /etc/postfix/sasl_passwd && \
    sed -i "s/placeholder_hostname/${HOSTNAME}/g" /etc/postfix/main.cf

EXPOSE 25
CMD service postfix start && service dovecot start && tail -f /dev/null