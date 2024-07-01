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
        <title>Funzionalita | Wegly</title>
    </head>
    <body>
        <center>
            <div class="centro">
                <h1 class="titolo">Funzionalita del Web Server</h1>
                <table>
                    <tr>
                        <td>
                            <p class="sottotitolo">Variabili PSOT</p>
                            <form method="post">
                                <input name="post" type="text">
                                <?php if(isset($_POST["post"])){echo "Valore: ".$_POST["post"];}?>
                                <button class="pulsanti">Invia</button>
                            </form>
                        </td>
                        <td><br></td>
                        <td>
                            <p class="sottotitolo">Variabili GET</p>
                            <form method="get">
                                <input name="get" type="text">
                                <?php if(isset($_GET["get"])){echo "Valore: ".$_GET["get"];}?>
                                <button class="pulsanti">Invia</button>
                            </form>
                        </td>
                    </tr>
                </table>
                <br><br><br>
                <a class="link" href="funzionalita.php">Torna alla Home</a>
            </div>
        </center>
    </body>
</html>