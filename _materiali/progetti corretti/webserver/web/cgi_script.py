#!/usr/bin/env python3

import sys
import os
import urllib.parse

# Stampa l'intestazione HTTP per indicare che verrà restituito testo HTML
print("Content-type: text/html\n")

# Leggi i dati inviati dalla richiesta POST
content_length = int(os.environ.get("CONTENT_LENGTH", 0))
post_data = sys.stdin.read(content_length)
post_data_decoded = urllib.parse.parse_qs(post_data)

# Recupera i valori dei campi 'name' ed 'email' dalla richiesta POST
name = post_data_decoded.get('name', [''])[0]
email = post_data_decoded.get('email', [''])[0]

# scrivi una risposta HTML con i dati ricevuti in un file HTML chiamato cgi_response.html
with open('web/cgi_response.html', 'w') as f:
	f.write(f"""
		<!DOCTYPE html>
		<html>
		<head>
			<title>CGI Response</title>
		</head>
		<body>
			<h1>CGI Response</h1>
			<p>Nome: {name}</p>
			<p>Email: {email}</p>
			<br/><br/>

		<a href="index.html">Torna alla home</a>
		</body>
		</html>
	""")