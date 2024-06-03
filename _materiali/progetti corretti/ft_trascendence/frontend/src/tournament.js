import { getTranslationData } from "./settings.js";
import { applyTranslations, routeWholeHtml } from "./utils.js";


export async function showTournamentGame() {
    const translationData = await getTranslationData();

    if (translationData) {
        applyTranslations(translationData);
    }

    updateImagePreview("ballType", "ballImagePreview");
    updateImagePreview("fieldType", "fieldImagePreview");
    updateImagePreview("paddleType", "paddleImagePreview");

    const canvas = document.getElementById("pongTournamentCanvas");
    if (!canvas) {
      console.error("Canvas element not found!");
      return;
    }

    const context = canvas.getContext("2d");
    if (!context) {
      console.error("Canvas context not found!");
      return;
    }

    canvas.width = window.innerWidth * 0.7;
    canvas.height = window.innerHeight * 0.7;

    let lastCanvasWidth = canvas.width;
    let keys = {};
    let numberOfPlayers = 4;
    let players, matches;
    let matchCounter = 1;
    let nextBracket = numberOfPlayers / 2;
    let paddleImage = new Image();
    let ballImage = new Image();
    let fieldType = "default";
    let ballType = "default";
    let paddleType = "default";
    let ballColor = "#FFF";
    let paddleColor = "#FFF";
    let borderColor = "#FFF";
    let textColor = "#FFF";
    let gameOver = false;
    let gameStarted = false;
    let ball;
    let giocatore1;
    let giocatore2;

    document.getElementById("startTournament").addEventListener("click", function() {
        players = [
            { alias: document.getElementById("alias1").value, score: 0 },
            { alias: document.getElementById("alias2").value, score: 0 },
            { alias: document.getElementById("alias3").value, score: 0 },
            { alias: document.getElementById("alias4").value, score: 0 }
        ];

        // Shuffling players to create random matches
        players.sort(() => Math.random() - 0.5);

        // Organizing matches
        matches = [
            { player1: players[0].alias, player2: players[1].alias },
            { player1: players[2].alias, player2: players[3].alias },
            { player1: "-", player2: "-"},
            { winner: "-"}
        ];

        // Updating the HTML for the brackets
        document.getElementById('semifinal1').textContent = `${matches[0].player1} vs ${matches[0].player2}`;
        document.getElementById('semifinal2').textContent = `${matches[1].player1} vs ${matches[1].player2}`;

        // Display the tournament bracket
        document.getElementById('tournamentBracket').style.display = 'flex'; // Note the display style matches the flex layout of the container

        document.getElementById("tournamentRegistration").style.display = "none";
		document.getElementById("playMatch").style.display = "block";

		document.getElementById("playMatch").addEventListener("click", function() {
            initializePreviews();
		});
	});

    document.getElementById("startGameButton").addEventListener("click", startGame);

    document.getElementById("exitButton").addEventListener("click", exit);
    document.getElementById("nextGameButton").addEventListener("click", nextGame);

    window.addEventListener("resize", resizeCanvas);
    window.addEventListener("keydown", function (e) {
      keys[e.key] = true;
    });
    window.addEventListener("keyup", function (e) {
      keys[e.key] = false;
    });

    function resizeCanvas() {
        const scaleRatio = canvas.width / lastCanvasWidth;
        canvas.width = window.innerWidth * 0.6;
        canvas.height = window.innerHeight * 0.6;
        ball.x *= scaleRatio;
        giocatore1.x = 10;
        giocatore2.x = canvas.width - giocatore2.width - 10;
        lastCanvasWidth = canvas.width;
      }

    function movePaddle() {
      const step = 10;
      if (keys["w"] && giocatore1.y > 0) {
        giocatore1.y -= step;
      }
      if (keys["s"] && giocatore1.y + giocatore1.height < canvas.height) {
        giocatore1.y += step;
      }
      if (keys["ArrowUp"] && giocatore2.y > 0) {
        giocatore2.y -= step;
      }
      if (keys["ArrowDown"] && giocatore2.y + giocatore2.height < canvas.height) {
        giocatore2.y += step;
      }
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
      setTimeout(() => {}, 1000);
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
          giocatore2.x,
          giocatore2.y,
          giocatore2.width,
          giocatore2.height,
          giocatore2.color,
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
          giocatore2.x,
          giocatore2.y,
          giocatore2.width,
          giocatore2.height,
        );
      }

      drawText(giocatore1.score, canvas.width / 4, 60);
      drawText(giocatore2.score, (3 * canvas.width) / 4, 60);
    }

    function ballPlayerCollision(ball, player) {
      return (
        ball.x + ball.radius > player.x &&
        ball.x - ball.radius < player.x + player.width &&
        ball.y + ball.radius > player.y &&
        ball.y - ball.radius < player.y + player.height
      );
    }

    function drawCircle(x, y, radius, color, context) {
      if (!context) return;
      context.fillStyle = color;
      context.beginPath();
      context.arc(x, y, radius, 0, Math.PI * 2, false);
      context.closePath();
      context.fill();
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
      return (ball.y - (player.y + player.height / 2)) / (player.height / 2);
    }

    function calculateBounceAngle(collidePoint) {
      return (Math.PI / 4) * collidePoint;
    }

    function updateBallDirection(ball, canvas) {
      return ball.x + ball.radius < canvas.width / 2 ? 1 : -1;
    }

    function updateBallVelocity(ball, angleRad, direction) {
      ball.velocityX = direction * ball.speed * Math.cos(angleRad);
      ball.velocityY = ball.speed * Math.sin(angleRad);
    }

    function increaseBallSpeed(ball) {
      ball.speed += 0.25;
      ball.velocityX += 0.25;
      ball.velocityY += 0.25;
    }

    function update() {
      if (!gameStarted) return;

      ball.x += ball.velocityX;
      ball.y += ball.velocityY;

      if (ball.y + ball.radius > canvas.height || ball.y - ball.radius < 0) {
        ball.velocityY = -ball.velocityY;
      }

      let player =
        ball.x + ball.radius < canvas.width / 2 ? giocatore1 : giocatore2;

      if (ballPlayerCollision(ball, player)) {
        let pointOfCollision = calculateCollisionPoint(ball, player);
        let collisionAngle = calculateBounceAngle(pointOfCollision);
        let newBallDirection = updateBallDirection(ball, canvas);
        updateBallVelocity(ball, collisionAngle, newBallDirection);
        increaseBallSpeed(ball);
      }

      if (ball.x - ball.radius < 0) {
        giocatore2.score++;
        ballAtCenter(2);
      } else if (ball.x + ball.radius > canvas.width) {
        giocatore1.score++;
        ballAtCenter(1);
      }

      if ((giocatore1.score === 5 || giocatore2.score === 5) && nextBracket === 3) {
        gameOver = true;
        const winner = giocatore1.score === 5 ? giocatore1.name : giocatore2.name;
        gameFinish(winner);
        return;
    }
      if (giocatore1.score === 5 || giocatore2.score === 5) {
        gameOver = true;
        const winner = giocatore1.score === 5 ? giocatore1.name : giocatore2.name;
        showGameOver(winner);
        return;
      }
    }

    function gameFinish(winner) {
        const nextMatch = document.getElementById("nextMatch");
        const nextGameButton = document.getElementById("nextGameButton");
        const exitButton = document.getElementById("exitButton");
        const winnerMessage = document.getElementById("winnerMessage");
        winnerMessage.textContent = `Letsgoski, ${winner}!!!`;
        nextMatch.style.display = "block";
        canvas.style.display = "none";
        nextGameButton.style.display = "none";
        exitButton.style.display = "block";
    }

    function showGameOver(winner) {
      const nextMatch = document.getElementById("nextMatch");
      const winnerMessage = document.getElementById("winnerMessage");
      winnerMessage.textContent = `Letsgoski, ${winner}!!!`;
      nextMatch.style.display = "block";
      canvas.style.display = "none";
      let toInsert = players.find(player => player.alias === winner);
      console.log(toInsert);
      if (matchCounter % 2 === 1) {
        matchCounter++;
        matches[nextBracket].player1 = toInsert.alias;
      }
      else {
        matchCounter++;
        matches[nextBracket].player2 = toInsert.alias;
      }
    }


    function nextGame() {
      const nextMatch = document.getElementById("nextMatch");
      nextMatch.style.display = "none";
      canvas.style.display = "none";

      updateBrackets();
      showBrackets();
    }

    let semifinal1 = '-';
    let semifinal2 = '-';
    function updateBrackets() {
        if (matchCounter === 2) {
            semifinal1 = matches[nextBracket].player1;
            document.getElementById('final').textContent = `${semifinal1} vs ${semifinal2}`;
        }
        else if (matchCounter === 3) {
            semifinal2 = matches[nextBracket].player2;
            nextBracket++;
            document.getElementById('final').textContent = `${semifinal1} vs ${semifinal2}`;
        }
        else if (matchCounter === 4) {
            document.getElementById('champion').textContent = `${matches[nextBracket].winner}`;

        }
    }

    function showBrackets() {
        // Display the tournament bracket
        document.getElementById('tournamentBracket').style.display = 'flex'; // Note the display style matches the flex layout of the container
        document.getElementById("playMatch").style.display = "block";
    }

    function exit() {
      routeWholeHtml("index.html");
    }

    function initPlayer() {
        giocatore1 = {
            name: matches[matchCounter - 1].player1,
            x: 10,
            y: (canvas.height - 125) / 2,
            width: 50,
            height: 125,
            score: 0,
            color: paddleColor,
          };
        giocatore2 = {
            name: matches[matchCounter - 1].player2,
            x: canvas.width - 10 - 50,
            y: (canvas.height - 125) / 2,
            width: 50,
            height: 125,
            score: 0,
            color: paddleColor,
        };
        ball = {
            x: canvas.width / 2,
            y: canvas.height / 2,
            radius: 10,
            velocityX: 8,
            velocityY: 8,
            speed: 8,
            color: ballColor,
        };
    }

    function initializeGameState() {
      initPlayer();
      gameOver = false;
      gameStarted = false;
      document.getElementById("customizationContainer").style.display = "none";
      document.getElementById("pongTournamentCanvas").style.display = "none";
      document.getElementById("nextMatch").style.display = "none";
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

    function rectangleDraw(x, y, width, height, color, context) {
      if (!context) return;
      context.fillStyle = color;
      context.fillRect(x, y, width, height);
    }

    function initializePreviews() {
      document.getElementById("tournamentRegistration").style.display = "none";
      document.getElementById("tournamentBracket").style.display = "none";
      document.getElementById("customizationContainer").style.display = "block";

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
      initializeGameState();
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
      giocatore2.color = paddleColor;

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
          document.getElementById("pongTournamentCanvas").style.display = "block";
          gameLoop();
        } else {
          paddleImage.onload = function () {
            gameStarted = true;
            document.getElementById("customizationContainer").style.display =
              "none";
            document.getElementById("pongTournamentCanvas").style.display = "block";
            gameLoop();
          };
        }
      } else {
        ballImage.onload = function () {
          if (paddleType === "default" || paddleImage.complete) {
            gameStarted = true;
            document.getElementById("customizationContainer").style.display =
              "none";
            document.getElementById("pongTournamentCanvas").style.display = "block";
            gameLoop();
          } else {
            paddleImage.onload = function () {
              gameStarted = true;
              document.getElementById("customizationContainer").style.display =
                "none";
              document.getElementById("pongTournamentCanvas").style.display = "block";
              gameLoop();
            };
          }
        };
      }
    }

    function gameLoop() {
      if (!gameOver) {
        movePaddle();
        update();
        render();
        requestAnimationFrame(gameLoop);
      }
    }
}

