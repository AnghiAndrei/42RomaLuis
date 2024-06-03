import { applyTranslations, routeWholeHtml } from "./utils.js";
import { getTranslationData } from "./settings.js";

export async function showTicTacToeGamePage() {
  const translationData = await getTranslationData();
  if (translationData) {
    applyTranslations(translationData);
  }
  const board = document.getElementById("ticTacToeBoard");
  const message = document.getElementById("message");
  const playerTurn = document.getElementById("TurnMessage");
  const endPlayer = document.getElementById("EndPlayer");
  const endturnPlayer = document.getElementById("EndTurnPlayer");
  const turnMessage = document.getElementById("turnText");
  const drawMessage = document.getElementById("drawMessage");

  let currentPlayer = "X";
  let gameOver = false;

  const cells = Array.from({ length: 9 }, (_, i) => {
    const cell = document.createElement("div");
    cell.classList.add("cell");
    cell.dataset.index = i;
    board.appendChild(cell);
    return cell;
  });

  function checkWin(player) {
    const winningCombinations = [
      [0, 1, 2],
      [3, 4, 5],
      [6, 7, 8], // rows
      [0, 3, 6],
      [1, 4, 7],
      [2, 5, 8], // columns
      [0, 4, 8],
      [2, 4, 6], // diagonals
    ];

    for (const combination of winningCombinations) {
      if (combination.every((index) => cells[index].textContent === player)) {
        return combination;
      }
    }
    return null;
  }

  function checkDraw() {
    return cells.every((cell) => cell.textContent !== "");
  }

  function highlightWinningCombination(combination) {
    combination.forEach((index) => {
      cells[index].style.backgroundColor = "lightgreen";
    });
  }

  function handleCellClick(event) {
    if (gameOver) return;

    const cell = event.target;
    if (cell.textContent === "") {
      cell.textContent = currentPlayer;
      cell.classList.add("disabled");

      const winningCombination = checkWin(currentPlayer);

      const endMessage = document.getElementById("EndMessage");
      if (winningCombination) {
        message.style.display = "block";
        message.textContent = `${endPlayer.textContent} ${currentPlayer === "X" ? "1" : "2"} ${endMessage.textContent}!`;
        highlightWinningCombination(winningCombination);
        gameOver = true;
      } else if (checkDraw()) {
        playerTurn.textContent = "";
        message.style.display = "none";
        drawMessage.style.display = "block";
        gameOver = true;
      } else {
        currentPlayer = currentPlayer === "X" ? "O" : "X";
        playerTurn.textContent = `${endturnPlayer.textContent} ${currentPlayer === "X" ? "1" : "2"} ${turnMessage.textContent}!`;
      }
    }
  }
  playerTurn.textContent = `${endturnPlayer.textContent} ${currentPlayer === "X" ? "1" : "2"} ${turnMessage.textContent}!`;
  cells.forEach((cell) => cell.addEventListener("click", handleCellClick));

  document.getElementById("goBackButton").addEventListener("click", goBack);

  function goBack() {
    routeWholeHtml("index.html");
  }
}
