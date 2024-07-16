<!DOCTYPE html>
<html>
<head>
        <link rel="shortcut icon" href="./Assets/img/icona.jpg" type="image/x-icon">
        <link rel="stylesheet" type="text/css" href="./Assets/main.css">
        <meta charset="UTF-8">
        <meta http-equiv="x-ua-compatible" content="ie=8">
        <meta name="keywords" content="">
        <meta name="author" content="Andrei Anghi[Angly colui che regna]">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta name="copyright" content="Andrei Anghi[Angly colui che regna]">
        <title>Funzionalita | Wengly</title>
    </head>
    <body>
        <center>
            <div class="centro2">
                <h1 class="titolo">Funzionalita del Web Server</h1>
                <table>
                    <tr>
                        <td>
                            <h2 class="sottotitolo">Variabili POST</h2>
                            <form method="post">
                                <input name="post" type="text" value="<?php if(isset($_POST["post"])){echo$_POST["post"];}?>">
                                <button class="pulsanti">Invia</button>
                                <p class="sottotitolo">Valore: <?php if(isset($_POST["post"])){echo$_POST["post"];}?></p>
                            </form>
                        </td>
                        <td width="50px"><br></td>
                        <td>
                            <h2 class="sottotitolo">Variabili GET</h2>
                            <form method="get">
                                <input name="get" type="text" value="<?php if(isset($_GET["get"])){echo$_GET["get"];};?>">
                                <button class="pulsanti">Invia</button>
                                <p class="sottotitolo">Valore: <?php if(isset($_GET["get"])){echo$_GET["get"];};?></p>
                            </form>
                        </td>
                    </tr>
                </table>
                <hr class="linea">
                <table>
                    <tr><td colspan='3'><center><h2 class="sottotitolo">Carico File</h2></center></td></tr>
                    <tr>
                        <td>
                            <form method="post" enctype="multipart/form-data">
                                <input name="imginput" type="file" accept=".png, .jpg" display="none">
                                <?php
                                	if(isset($_FILES["imginput"])){
										$nome_file=$_FILES['imginput'];
										$ext=pathinfo($nome_file, PATHINFO_EXTENSION);
                                        $ext_acc=["png", "jpg"];
                                        if(in_array($ext,$ext_acc)){
                                            $percorso_temporaneo=$_FILES['tmp_name'];
                                            $percorso_salvataggio="Assets/img/$nome_file";
                                            move_uploaded_file($percorso_temporaneo, $percorso_salvataggio);
                                            rename($percorso_salvataggio,'./Assets/img/foto'.$ext);
                                        }else echo "<br><p id='sottotitolo'>La foto deve essere .png / .jpg</p>";
                                    }
                                ?>
                                <br><br>
                                <button class="pulsanti">Carica</button>
                            </form>
                        </td>
                        <td>
                            <input id="server" type="text" value="localhost:9069">
                            <input id="delfile" type="text" list="listafile">
                            <datalist id="listafile">
                                <option>Rascal dosent dream of bunny girl sempai</option>
                                <option>Voglio mangiare il tuo pancreas</option>
                                <option>Darling in the FranXX</option>
                                <option>Your lae in April</option>
                            </datalist>
                            <br><br>
                            <script>
								function can(){
									if(document.getElementById('server').value=="" || document.getElementById('delfile').value==""){
										alert("Parametri mancanti");
									}
									else{
										let url='http://'+document.getElementById('server').value+'/Assets/img/'+document.getElementById('delfile').value+'.png';
										fetch(url,{method: 'DELETE',}).then(response=>{
											if(response.ok)alert('File eliminato con successo');
											else{
												let url='http://'+document.getElementById('server').value+'/Assets/img/'+document.getElementById('delfile').value+'.jpg';
												fetch(url,{method: 'DELETE',}).then(response=>{
													if(response.ok)alert('File eliminato con successo');
													else{
														alert('Errore durante l\'eliminazione del file:', response.statusText);
													}
												})
											}
										})
									}
									window.location="funzionalita.php";
								}
							</script>
                            <button class="pulsanti" onclick="can()">Cancella</button>
                        </td>
                    </tr>
					<tr>
                        <td colspan='3'>
                            <?php
                                if(file_exists("./Assets/img/Rascal dosent dream of bunny girl sempai.png"))echo'<img class="img" src="Assets/img/Rascal dosent dream of bunny girl sempai.png"/>';
                                if(file_exists("./Assets/img/Voglio mangiare il tuo pancreas.png"))echo'<img class="img" src="./Assets/img/Voglio mangiare il tuo pancreas.png"/>';
                                echo"<br>";
								if(file_exists("./Assets/img/Darling in the FranXX.jpg"))echo'<img class="img" src="./Assets/img/Darling in the FranXX.jpg"/>';
                                if(file_exists("./Assets/img/Your lae in April.jpg"))echo'<img class="img" src="./Assets/img/Your lae in April.jpg"/>';
                            ?>
                        </td>
                    </tr>
                </table>
                <br>
                <hr class="linea">
                <p class="sottotitolod"><a target="_blank" class="link" href="cartella_no_index/">Vedi cartella senza index</a></p>
                <p class="sottotitolod"><a target="_blank" class="link" href="cartella_inesistente/">Vedi error 404 con cartella</a></p>
                <p class="sottotitolod"><a target="_blank" class="link" href="inesistente.html">Vedi error 404 con file</a></p>
                <br>
                <p class="sottotitolod"><a target="_blank" class="link" href="cgi.py">Vedi CGI con python</a></p>
                <p class="sottotitolod"><a target="_blank" class="link" href="cgi.sh">Vedi CGI con shell</a></p>
				<br>
                <p class="sottotitolod"><a target="_blank" class="link" href="cgi2.py">Vedi: Errore di compilazione</a></p>
                <p class="sottotitolod"><a target="_blank" class="link" href="cgi3.py">Vedi: Tempo di esecuzione massimo</a></p>
                <br>
                <p class="sottotitolod"><a target="_blank" class="link" href="/ripasso">Redirection</a></p>
                <br>
                <p class="sottotitolod"><a class="link" href="home.html">Torna alla Home</a></p>
            </div>
        </center>
    </body>
</html>