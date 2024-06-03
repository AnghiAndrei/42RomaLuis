import { getTranslationData } from "./settings.js";
import { applyTranslations } from "./utils.js";

export async function showPongRemoteGame() {
    const translationData = await getTranslationData();
    if (translationData){
      applyTranslations(translationData);
    }
    const canvas = document.getElementById('pongRemoteGameCanvas');
    const ctx = canvas.getContext('2d');

    // Connessione al server tramite WebSocket
    const socket = new WebSocket('wss://0.0.0.0:3000');

    // Stato iniziale del gioco
    let ball, player1, player2;
    let gameOver = false;
    let gameStarted = false;
    initializeGameState();

    // Gestione della connessione WebSocket
    socket.onopen = function () {
        console.log("Connected to server");
    };

    socket.onerror = function (error) {
        console.log("WebSocket error:", error);
    };

    socket.onclose = function () {
        console.log("Disconnected from server");
    };

    // Ricezione degli aggiornamenti di stato dal server
    document.addEventListener('DOMContentLoaded', function() {
        // Il tuo codice che dipende dal DOM va qui
        socket.onmessage = function (event) {
            const data = JSON.parse(event.data);
            const modal = document.getElementById('myModal');
            const modalText = document.getElementById('modalText');
    
            if (!modalText) {
                console.error("Element with ID 'modalText' not found.");
                return;
            }
    
            switch (data.type) {
                case 'WAITING_FOR_PLAYER':
                    modalText.textContent = "Waiting for an opponent...";
                    modal.style.display = "flex";  // Mostra il modal
                    break;
                case 'GAME_START':
                    gameStarted = true;
                    console.log("Match found, game starts.");
                    modal.style.display = "none";  // Nascondi il modal
                    break;
                // aggiungi altri casi qui
            }
        };
    });    

    // Funzione per aggiornare lo stato del gioco
    function updateGameState(data) {
        ball.x = data.ball.x;
        ball.y = data.ball.y;
        ball.velocityX = data.ball.velocityX;
        ball.velocityY = data.ball.velocityY;

        player1.y = data.player1.y;
        player2.y = data.player2.y;
    }

    // Gestione degli input del giocatore
    document.addEventListener('keydown', function(event) {
        handlePlayerInput(event.key, true);
    });

    document.addEventListener('keyup', function(event) {
        handlePlayerInput(event.key, false);
    });

    function handlePlayerInput(key, isPressed) {
        if (['w', 's', 'ArrowUp', 'ArrowDown'].includes(key)) {
            socket.send(JSON.stringify({ type: 'input', key: key, isPressed: isPressed }));
        }
    }

    // Inizializzazione dello stato del gioco
    function initializeGameState() {
        ball = {
            x: canvas.width / 2,
            y: canvas.height / 2,
            radius: 10,
            velocityX: 5,
            velocityY: 5,
            speed: 7,
            color: '#FFF'
        };

        player1 = {
            y: canvas.height / 2 - 50,
            height: 100,
            move: false
        };

        player2 = {
            y: canvas.height / 2 - 50,
            height: 100,
            move: false
        };
    }

    // Renderizzazione del gioco
    function render() {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        drawBall();
        drawPlayers();
        requestAnimationFrame(render);
    }

    function drawBall() {
        ctx.fillStyle = ball.color;
        ctx.beginPath();
        ctx.arc(ball.x, ball.y, ball.radius, 0, Math.PI * 2, true);
        ctx.closePath();
        ctx.fill();
    }

    function drawPlayers() {
        ctx.fillStyle = '#FFF';
        ctx.fillRect(20, player1.y, 10, player1.height);
        ctx.fillRect(canvas.width - 30, player2.y, 10, player2.height);
    }

    // Avvio del rendering del gioco
    function gameLoop() {
        if (!gameStarted) {
            requestAnimationFrame(gameLoop);
            return;
        }

        if (gameOver) {
            return; // Stop the game loop if the game is over
        }

        render();
        requestAnimationFrame(gameLoop);
    }

    requestAnimationFrame(gameLoop);
}
