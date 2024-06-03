import { getTranslationData } from "./settings.js";
import { applyTranslations, routeWholeHtml } from "./utils.js";

document.addEventListener("DOMContentLoaded", () => {
  showPongCPUGamePage();
});

export async function showPongCPUGamePage() {
  const translationData = await getTranslationData();
  if (translationData) {
    applyTranslations(translationData);
  }
  console.log("pong game page");
  const canvas = document.getElementById("pongCPUGameCanvas");
  if (!canvas) {
    console.error("Canvas element not found!");
    return; // Uscire dalla funzione se il canvas non esiste
  }
  const context = canvas.getContext("2d");

  canvas.width = window.innerWidth * 0.7; // Ad esempio, 70% della larghezza della finestra
  canvas.height = window.innerHeight * 0.7; // Ad esempio, 70% dell'altezza della finestra
  // Funzione per ridimensionare il canvas
  let lastCanvasWidth = canvas.width; // Memorizza l'ultima larghezza del canvas per calcoli proporzionali
  let keys = {}; // Memorizza i tasti premuti

  let paddleImage = new Image();
  let ballImage = new Image();
  let fieldType = "default";
  let ballType = "default";
  let paddleType = "default";
  let ballColor = "#FFF";
  let paddleColor = "#FFF";
  let borderColor = "#FFF";
  let textColor = "#FFF"; // Default text color

  // Simulate key press events for up and down keys
  const KEY_UP = "ArrowUp";
  const KEY_DOWN = "ArrowDown";
  let keysPressed = {};
  let targetPosition;
  let errorMargin;

  function resizeCanvas() {
    // Calcola il rapporto di ridimensionamento basato sulla nuova larghezza del canvas rispetto all'ultima larghezza memorizzata
    const scaleRatio = canvas.width / lastCanvasWidth;

    // Aggiorna la larghezza e l'altezza del canvas
    canvas.width = window.innerWidth * 0.6;
    canvas.height = window.innerHeight * 0.6;

    // Aggiorna le posizioni orizzontali di palla e giocatori proporzionalmente al nuovo cambio di scala
    ball.x *= scaleRatio;
    giocatore1.x = 10; // giocatore1 rimane sempre a 10px dal bordo sinistro
    cpupaddle.x = canvas.width - cpupaddle.width - 10; // cpu paddle rimane a 10px dal bordo destro

    // Memorizza la nuova larghezza del canvas per i futuri ridimensionamenti
    lastCanvasWidth = canvas.width;
  }

  window.addEventListener("resize", resizeCanvas); // Aggiorna il canvas quando la finestra viene ridimensionata

  window.addEventListener("keydown", function (e) {
    keys[e.key] = true;
  });

  window.addEventListener("keyup", function (e) {
    keys[e.key] = false;
  });

  let gameOver = false;
  let gameStarted = false;

  let ball = {
    x: canvas.width / 2,
    y: canvas.height / 2,
    radius: 10,
    velocityX: 8,
    velocityY: 8,
    speed: 8,
    color: ballColor,
  };

  // Player 1
  let giocatore1 = {
    x: 10,
    y: (canvas.height - 100) / 2,
    width: 50,
    height: 100,
    score: 0,
    color: paddleColor,
  };

  // Player 2
  let cpupaddle = {
    x: canvas.width - 10 - 50,
    y: (canvas.height - 100) / 2,
    width: 50,
    height: 100,
    score: 0,
    color: paddleColor,
    speed: 10, // AI speed
    lastUpdate: Date.now() - 1001,
  };

  // Funzione che disegna un rettangolo sul canvas (giocatori)
  function rectangleDraw(x, y, width, height, color, context) {
    if (!context) return;
    context.fillStyle = color;
    context.fillRect(x, y, width, height);
  }

  function drawText(text, x, y) {
    context.fillStyle = textColor;
    context.font = "50px sans-serif";
    context.fillText(text, x, y);
  }

  function drawGameField() {
    const borderWidth = 3; // Spessore del bordo del campo
    const midLineThickness = 3; // Spessore della linea di metà campo

    // Disegna il bordo esterno del campo
    // Assicura di disegnare solo il bordo, non riempie tutto il rettangolo
    rectangleDraw(0, 0, canvas.width, borderWidth, borderColor, context); // Top border
    rectangleDraw(0, 0, borderWidth, canvas.height, borderColor, context); // Left border
    rectangleDraw(
      canvas.width - borderWidth,
      0,
      borderWidth,
      canvas.height,
      borderColor,
      context,
    ); // Right border
    rectangleDraw(
      0,
      canvas.height - borderWidth,
      canvas.width,
      borderWidth,
      borderColor,
      context,
    ); // Bottom border

    // Disegna la linea di metà campo
    rectangleDraw(
      canvas.width / 2 - midLineThickness / 2,
      0,
      midLineThickness,
      canvas.height,
      borderColor,
      context,
    );
  }

  function ballAtCenter(whoScored) {
    setTimeout(() => {}, 2000);
    ball.x = canvas.width / 2;
    ball.y = canvas.height / 2;

    if (whoScored === 1) {
      ball.velocityX = -8;
      ball.velocityY = -8;
    } else if (whoScored === 2) {
      ball.velocityX = 8;
      ball.velocityY = 8;
    }
    ball.speed = 8;
  }

  function render() {
    // Pulisci il canvas
    context.clearRect(0, 0, canvas.width, canvas.height);

    // Imposta lo sfondo del campo di gioco
    if (fieldType === "default") {
      context.fillStyle = "#000"; // Sfondo nero
    } else if (fieldType === "ping_pong") {
      context.fillStyle = "#48ACDA"; // Sfondo azzurro
    } else if (fieldType === "tennis") {
      context.fillStyle = "green"; // Sfondo verde
    } else if (fieldType === "hockey") {
      context.fillStyle = "white"; // Sfondo bianco
    }
    context.fillRect(0, 0, canvas.width, canvas.height);
    drawGameField();

    if (ballType === "default") {
      drawCircle(ball.x, ball.y, ball.radius, ball.color, context);
    } else {
      context.drawImage(
        ballImage,
        ball.x - ball.radius,
        ball.y - ball.radius,
        ball.radius * 2,
        ball.radius * 2,
      );
    }

    // Disegna i giocatori
    if (paddleType === "default") {
      rectangleDraw(
        giocatore1.x,
        giocatore1.y,
        giocatore1.width,
        giocatore1.height,
        giocatore1.color,
        context,
      );
      rectangleDraw(
        cpupaddle.x,
        cpupaddle.y,
        cpupaddle.width,
        cpupaddle.height,
        cpupaddle.color,
        context,
      );
    } else {
      context.drawImage(
        paddleImage,
        giocatore1.x,
        giocatore1.y,
        giocatore1.width,
        giocatore1.height,
      );
      context.drawImage(
        paddleImage,
        cpupaddle.x,
        cpupaddle.y,
        cpupaddle.width,
        cpupaddle.height,
      );
    }

    // Disegna lo score
    drawText(giocatore1.score, canvas.width / 4, 60);
    drawText(cpupaddle.score, (3 * canvas.width) / 4, 60);
  }

  function drawCircle(x, y, radius, color, context) {
    if (!context) return;
    context.fillStyle = color;
    context.beginPath();
    context.arc(x, y, radius, 0, Math.PI * 2, false);
    context.closePath();
    context.fill();
  }

  function ballPlayerCollision(ball, player) {
    // Controlla se i bordi della palla e del giocatore si sovrappongono
    return (
      ball.x + ball.radius > player.x && // Il lato destro della palla è a destra del lato sinistro del giocatore
      ball.x - ball.radius < player.x + player.width && // Il lato sinistro della palla è a sinistra del lato destro del giocatore
      ball.y + ball.radius > player.y && // Il lato inferiore della palla è sotto il lato superiore del giocatore
      ball.y - ball.radius < player.y + player.height // Il lato superiore della palla è sopra il lato inferiore del giocatore
    );
  }

  function drawFieldPreview(type, context) {
    if (!context) return;
    context.clearRect(0, 0, 100, 100); // Clear the canvas before drawing

    if (type === "default") {
      context.fillStyle = "#000"; // Black background
    } else if (type === "ping_pong") {
      context.fillStyle = "#48ACDA"; // Blue background
    } else if (type === "tennis") {
      context.fillStyle = "green"; // Green background
    } else if (type === "hockey") {
      context.fillStyle = "white"; // White background
    }
    context.fillRect(0, 0, 100, 100);

    // Draw borders
    context.strokeStyle = "#00FFFF"; // Celeste border
    context.lineWidth = 2;
    context.strokeRect(0, 0, 100, 100);

    // Draw center line
    context.beginPath();
    context.moveTo(50, 0);
    context.lineTo(50, 100);
    context.stroke();
  }

  function calculateCollisionPoint(ball, player) {
    // Calcola la posizione relativa del punto di contatto sulla racchetta
    return (ball.y - (player.y + player.height / 2)) / (player.height / 2);
  }

  function calculateBounceAngle(collidePoint) {
    // Calcola l'angolo di rimbalzo basato sul punto di collisione
    return (Math.PI / 4) * collidePoint;
  }

  function updateBallDirection(ball, canvas) {
    // Determina la direzione del rimbalzo basata sulla posizione della palla sul campo
    return ball.x + ball.radius < canvas.width / 2 ? 1 : -1;
  }

  function updateBallVelocity(ball, angleRad, direction) {
    // Aggiorna la velocità della palla dopo la collisione
    ball.velocityX = direction * ball.speed * Math.cos(angleRad);
    ball.velocityY = ball.speed * Math.sin(angleRad);
  }

  function increaseBallSpeed(ball) {
    // Incrementa la velocità della palla per aumentare la difficoltà
    ball.speed += 0.35;
    ball.velocityX += 0.35;
    ball.velocityY += 0.35;
  }

  function movePaddle() {
    const step = 10; // Definisce quanto spostarsi per ogni pressione del tasto
    if (keys["w"] && giocatore1.y > 0) {
      // Check that the player does not exit above the canvas
      giocatore1.y -= step;
    } else if (keys["s"] && giocatore1.y + giocatore1.height < canvas.height) {
      // Check that the player does not exit below the canvas
      giocatore1.y += step;
    }
  }

  function getRandomBetween(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
  }

  function updateAI() {
    // Calculate the time it will take for the ball to reach the AI paddle
    const timeToReachPaddle = (cpupaddle.x - ball.x) / ball.velocityX;

    // Predict the future position of the ball
    let futureBallPosition = ball.y + ball.velocityY * timeToReachPaddle;

    // Handle bounces off the top and bottom walls
    while (futureBallPosition < 0 || futureBallPosition > canvas.height) {
      if (futureBallPosition < 0) {
        futureBallPosition = -futureBallPosition;
      } else if (futureBallPosition > canvas.height) {
        futureBallPosition = 2 * canvas.height - futureBallPosition;
      }
    }

    const idealPosition = futureBallPosition - cpupaddle.height / 2;
    if (giocatore1.score - cpupaddle.score >= 2) {
      errorMargin = 20 + getRandomBetween(5, 10) + ball.speed;
    } else {
      errorMargin = getRandomBetween(30, 35) + ball.speed;
    }

    targetPosition = idealPosition + errorMargin;
  }

  // Function to simulate key press
  function simulateKeyPress(key) {
    keysPressed[key] = true;
  }

  // Function to simulate key release
  function simulateKeyRelease(key) {
    keysPressed[key] = false;
  }

  // Move AI paddle based on simulated key press
  function moveAIPaddle() {
    if (keysPressed[KEY_UP]) {
      cpupaddle.y -= cpupaddle.speed;
    }
    if (keysPressed[KEY_DOWN]) {
      cpupaddle.y += cpupaddle.speed;
    }

    // Ensure the paddle doesn't move out of the canvas boundaries
    cpupaddle.y = Math.max(
      0,
      Math.min(cpupaddle.y, canvas.height - cpupaddle.height),
    );
  }

  function update() {
    // Aggiorna la posizione della palla
    ball.x += ball.velocityX;
    ball.y += ball.velocityY;

    // Verifica del rimbalzo verticale della palla (contro il soffitto o il pavimento)
    if (ball.y + ball.radius > canvas.height) {
      ball.y = canvas.height - ball.radius; // Ensure the ball stays within the canvas
      ball.velocityY = -ball.velocityY; // Inverti la direzione verticale della palla
    } else if (ball.y - ball.radius < 0) {
      ball.y = ball.radius; // Ensure the ball stays within the canvas
      ball.velocityY = -ball.velocityY; // Inverti la direzione verticale della palla
    }

    if (ball.velocityX > 0) {
      const currentTime = Date.now();
      const predictionTime = 1000; // Prediction interval in milliseconds
      if (currentTime - cpupaddle.lastUpdate >= predictionTime) {
        updateAI();
        console.log("Target position: ", targetPosition);
        console.log("Current position: ", cpupaddle.y);
        cpupaddle.lastUpdate = currentTime;
      }

      let randomError = getRandomBetween(5, 20);

      if (
        targetPosition < cpupaddle.y &&
        cpupaddle.y - targetPosition > randomError
      ) {
        simulateKeyRelease(KEY_DOWN);
        simulateKeyPress(KEY_UP);
      } else if (
        targetPosition > cpupaddle.y - cpupaddle.height &&
        targetPosition - cpupaddle.y > randomError
      ) {
        simulateKeyRelease(KEY_UP);
        simulateKeyPress(KEY_DOWN);
      } else {
        simulateKeyRelease(KEY_UP);
        simulateKeyRelease(KEY_DOWN);
      }
      moveAIPaddle();
    }

    // Determina quale giocatore (player) è attualmente in gioco in base alla posizione della palla
    let player = ball.x < canvas.width / 2 ? giocatore1 : cpupaddle;

    // Gestisce la collisione della palla con il giocatore
    if (ballPlayerCollision(ball, player)) {
      let collidePoint = calculateCollisionPoint(ball, player);
      let angleRad = calculateBounceAngle(collidePoint);
      let direction = updateBallDirection(ball, canvas);
      updateBallVelocity(ball, angleRad, direction);
      increaseBallSpeed(ball); // Aumenta la velocità della palla dopo la collisione
    }

    // Controlla se la palla è andata fuori dal campo a sinistra o a destra per aggiornare il punteggio
    if (ball.x - ball.radius < 0) {
      cpupaddle.score++;
      ballAtCenter(2); // Riporta la palla al centro del campo, assegnandola alla CPU
    } else if (ball.x + ball.radius > canvas.width) {
      giocatore1.score++;
      ballAtCenter(1); // Riporta la palla al centro del campo, assegnandola al player
    }

    // Controlla se il gioco è finito (un giocatore ha raggiunto il punteggio massimo)
    if (giocatore1.score === 5 || cpupaddle.score === 5) {
      gameOver = true;
      const winner = giocatore1.score === 5 ? "Player 1" : "CPU";
      showGameOver(winner); // Mostra lo schermo di fine partita e annuncia il vincitore
      return; // Termina l'aggiornamento del gioco
    }
  }

  function showGameOver(winner) {
    const gameOverScreen = document.getElementById("gameOverScreen");
    const winnerMessage = document.getElementById("winnerMessage");
    winnerMessage.textContent = `Letsgoski, ${winner}!!!`;
    gameOverScreen.style.display = "block";
    canvas.style.display = "none"; // Nasconde il canvas del gioco
  }

  document.getElementById("goBackButton").addEventListener("click", goBack);
  document
    .getElementById("playAgainButton")
    .addEventListener("click", playAgain);

  function goBack() {
    routeWholeHtml("index.html");
  }

  function playAgain() {
    // Resetta tutte le variabili del gioco
    initializeGameState();

    // Nascondi il gameOverScreen e mostra di nuovo il canvas
    const gameOverScreen = document.getElementById("gameOverScreen");
    gameOverScreen.style.display = "none";
    canvas.style.display = "none";

    // Riavvia il game loop
    showPongCPUGamePage();
  }

  function resetPlayer() {
    giocatore1.y = (canvas.height - 100) / 2;
    cpupaddle.y = (canvas.height - 100) / 2;
    giocatore1.x = 10;
    cpupaddle.x = canvas.width - cpupaddle.width - 10;
    giocatore1.score = 0;
    cpupaddle.score = 0;
  }

  function initializeGameState() {
    ballAtCenter(getRandomBetween(1, 2));
    resetPlayer();
    gameOver = false;
    gameStarted = false;
    document.getElementById("customizationContainer").style.display = "block";
    document.getElementById("pongCPUGameCanvas").style.display = "none";
  }

  function updateImagePreview(selectElementId, previewElementId) {
    const selectElement = document.getElementById(selectElementId);
    const previewElement = document.getElementById(previewElementId);
    const context = previewElement?.getContext("2d");
    if (!context) {
      console.error(
        `Canvas context not found for previewElementId: ${previewElementId}`,
      );
      return;
    }
    selectElement.addEventListener("change", function () {
      const selectedValue = selectElement.value;
      context.clearRect(0, 0, previewElement.width, previewElement.height);

      if (selectElementId === "fieldType") {
        drawFieldPreview(selectedValue, context);
      } else {
        const color = fieldType === "hockey" ? "#00FFFF" : "#FFF";
        if (selectedValue === "default") {
          if (selectElementId === "ballType") {
            drawCircle(
              previewElement.width / 2,
              previewElement.height / 2,
              20,
              color,
              context,
            );
          } else if (selectElementId === "paddleType") {
            rectangleDraw(
              20,
              (previewElement.height - 50) / 2,
              10,
              50,
              color,
              context,
            );
          }
        } else {
          const image = new Image();
          image.src = `public/${selectedValue}`;
          image.onload = () => {
            context.drawImage(
              image,
              0,
              0,
              previewElement.width,
              previewElement.height,
            );
          };
        }
      }
    });
  }

  function initializePreviews() {
    const ballPreviewCanvas = document.getElementById("ballImagePreview");
    const paddlePreviewCanvas = document.getElementById("paddleImagePreview");
    const fieldPreviewCanvas = document.getElementById("fieldImagePreview");

    const ballPreviewContext = ballPreviewCanvas?.getContext("2d");
    const paddlePreviewContext = paddlePreviewCanvas?.getContext("2d");
    const fieldPreviewContext = fieldPreviewCanvas?.getContext("2d");

    if (!ballPreviewContext) {
      console.error("Ball preview context not found!");
      return;
    }
    if (!paddlePreviewContext) {
      console.error("Paddle preview context not found!");
      return;
    }
    if (!fieldPreviewContext) {
      console.error("Field preview context not found!");
      return;
    }

    drawCircle(50, 50, 20, "#FFF", ballPreviewContext);
    rectangleDraw(20, 25, 10, 50, "#FFF", paddlePreviewContext);
    drawFieldPreview("default", fieldPreviewContext);
  }

  function startGame() {
    ballType = document.getElementById("ballType").value;
    fieldType = document.getElementById("fieldType").value;
    paddleType = document.getElementById("paddleType").value;

    if (fieldType === "hockey") {
      ballColor = "#6495ed"; // Change to celeste for visibility
      paddleColor = "#6495ed"; // Change to celeste for visibility
      borderColor = "#6495ed"; // Change border color to celeste
      textColor = "#6495ed"; // Change text color to celeste
    } else {
      ballColor = "#FFF";
      paddleColor = "#FFF";
      borderColor = "#FFF";
      textColor = "#FFF"; // Default text color
    }

    ball.color = ballColor;
    giocatore1.color = paddleColor;
    cpupaddle.color = paddleColor;

    if (ballType !== "default") {
      ballImage.src = `public/${ballType}`;
    }

    if (paddleType !== "default") {
      paddleImage.src = `public/${paddleType}`;
    }

    if (ballType === "default" || ballImage.complete) {
      if (paddleType === "default" || paddleImage.complete) {
        gameStarted = true;
        document.getElementById("customizationContainer").style.display =
          "none";
        document.getElementById("pongCPUGameCanvas").style.display = "block";
        gameLoop();
      } else {
        paddleImage.onload = function () {
          gameStarted = true;
          document.getElementById("customizationContainer").style.display =
            "none";
          document.getElementById("pongCPUGameCanvas").style.display = "block";
          gameLoop();
        };
      }
    } else {
      ballImage.onload = function () {
        if (paddleType === "default" || paddleImage.complete) {
          gameStarted = true;
          document.getElementById("customizationContainer").style.display =
            "none";
          document.getElementById("pongCPUGameCanvas").style.display = "block";
          gameLoop();
        } else {
          paddleImage.onload = function () {
            gameStarted = true;
            document.getElementById("customizationContainer").style.display =
              "none";
            document.getElementById("pongCPUGameCanvas").style.display =
              "block";
            gameLoop();
          };
        }
      };
    }
  }

  updateImagePreview("ballType", "ballImagePreview");
  updateImagePreview("fieldType", "fieldImagePreview");
  updateImagePreview("paddleType", "paddleImagePreview");

  initializePreviews(); // Inizializza le anteprime dei canvas di default

  document
    .getElementById("startGameButton")
    .addEventListener("click", startGame);

  function gameLoop() {
    if (!gameOver) {
      movePaddle();
      update();
      render();
      requestAnimationFrame(gameLoop);
    }
  }

  initializeGameState();
}
