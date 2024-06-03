import { applyTranslations, routeWholeHtml } from "./utils.js";
import { getTranslationData, getLanguage } from "./settings.js";
import { navigate } from "./main.js";

function logOut() {
  fetch("/auth/logout").then((r) => {
    if (r.ok) {
      routeWholeHtml("index.html");
      exitPage();
    } else {
      console.log("Logout failed");
    }
  });
}

const translations = {
  it: {
    accept: "Accetta",
    decline: "Rifiuta",
    "friend-request": "ti ha inviato una richiesta di amicizia",
  },
  es: {
    accept: "Aceptar",
    decline: "Rechazar",
    "friend-request": "te ha enviado una solicitud de amistad",
  },
  fr: {
    accept: "Accepter",
    decline: "Décliner",
    "friend-request": "vous a envoyé une demande d'ami",
  },
  de: {
    accept: "Akzeptieren",
    decline: "Ablehnen",
    "friend-request": "hat dir eine Freundschaftsanfrage gesendet",
  },
  en: {
    accept: "Accept",
    decline: "Decline",
    "friend-request": "has sent you a friend request",
  },
};

function getTranslation(key, language) {
  const languageTranslations = translations[language];
  if (languageTranslations) {
    return languageTranslations[key];
  } else {
    return null;
  }
}

export async function attachEventListeners() {
  navigate("/friends");
  const language = await getLanguage();
  document
    .getElementById("gameLogoButton")
    .addEventListener("click", function () {
      navigate("/gameLobby");
    });

  document
    .getElementById("profileButton")
    .addEventListener("click", function () {
      navigate("/profile");
    });

  document
    .getElementById("logoutButton")
    .addEventListener("click", function () {
      logOut();
    });

  const menuItems = document.querySelectorAll(".menu li");
  const hrElement = document.querySelector(".menu hr");
  menuItems.forEach((item, index) => {
    item.addEventListener("click", function () {
      hrElement.className = "";
      hrElement.classList.add(`hr-position-${index}`);
      switch (index) {
        case 0:
          navigate("/friends");
          break;
        case 1:
          navigate("/settings");
          break;
        default:
          console.log("Invalid option");
      }
    });
  });
  updateNotificationDot();

  document
    .getElementById("notificationButton")
    .addEventListener("click", async function () {
      const friendRequests = await getFriendRequests();
      const friendList = friendRequests.friend_requests;
      const dropdownMenu = document.querySelector(
        '.dropdown-menu[aria-labelledby="notificationButton"]',
      );
      dropdownMenu.style.display =
        dropdownMenu.style.display === "block" ? "none" : "block";

      // Clear the dropdown menu
      dropdownMenu.innerHTML = "";

      friendList.forEach((friend) => {
        const friendRequestElement = document.createElement("div");
        const acceptButton = document.createElement("button");
        acceptButton.textContent = getTranslation("accept", language);
        acceptButton.addEventListener("click", async function () {
          await acceptFriendRequest(friend.id);
          friendRequestElement.remove();
        });

        const declineButton = document.createElement("button");
        declineButton.textContent = getTranslation("decline", language);
        declineButton.addEventListener("click", async function () {
          await declineFriendRequest(friend.id);
          friendRequestElement.remove();
        });
        friendRequestElement.textContent = `${friend.username} ${getTranslation("friend-request", language)}`;
        const hr = document.createElement("hr");
        friendRequestElement.appendChild(acceptButton);
        friendRequestElement.appendChild(declineButton);
        friendRequestElement.appendChild(hr);

        // Append the new div element to the dropdown menu
        dropdownMenu.appendChild(friendRequestElement);
      });
    });
}

function exitPage() {
  if (clockIntervalId !== null) {
    clearInterval(clockIntervalId);
    clockIntervalId = null;
  }
}

let clockIntervalId = null;
function updateClock() {
  const now = new Date();
  const hours = now.getHours().toString().padStart(2, "0");
  const minutes = now.getMinutes().toString().padStart(2, "0");
  const seconds = now.getSeconds().toString().padStart(2, "0");
  document.getElementById("clock").textContent =
    `${hours}:${minutes}:${seconds}`;
}
clockIntervalId = setInterval(updateClock, 1000);

export async function setupGameLobbyPage() {
  const translationData = await getTranslationData();
  if (translationData) {
    applyTranslations(translationData);
  }
  const createGameBtn = document.getElementById("createLocalGame");
  if (createGameBtn) {
    createGameBtn.addEventListener("click", showPongGame);
  } else {
    console.log("Create Game button not found!");
  }
  const createCPUGameBtn = document.getElementById("createCPUGame");
  if (createCPUGameBtn) {
    createCPUGameBtn.addEventListener("click", showCPUGame);
  } else {
    console.log("Create CPU Game button not found!");
  }
  const createTictactoeGameBtn = document.getElementById("createTicTacToe");
  if (createTictactoeGameBtn) {
    createTictactoeGameBtn.addEventListener("click", showTicTacToeGame);
  } else {
    console.log("Create TicTacToe Game button not found!");
  }
  const createTournamentGameBtn = document.getElementById("createTournament");
  if (createTournamentGameBtn) {
    createTournamentGameBtn.addEventListener("click", showTournamentGame);
  } else {
    console.log("Create Tournament Game button not found!");
  }
}

function showTicTacToeGame() {
  navigate("/tictactoe");
  exitPage();
}

function showCPUGame() {
  navigate("/pongcpugame");
  exitPage();
}

function showPongGame() {
  navigate("/ponggame");
  exitPage();
}

function showTournamentGame() {
  navigate("/tournament");
  exitPage();
}

function updateNotificationDot() {
  const notificationDot = document.getElementById("notificationDot");
  const notificationButton = document.getElementById("notificationButton");
  notificationButton.classList.add("shake");
  notificationButton.addEventListener("animationend", () => {
    notificationButton.classList.remove("shake");
  });

  notificationDot.style.display = "none";
}

async function getFriendRequests() {
  try {
    const response = await fetch("/user/friend-requests");
    if (response.status === 200) {
      return await response.json();
    }
  } catch (error) {
    console.error("Error fetching friend requests:", error);
  }
}

async function acceptFriendRequest(friendId) {
  try {
    const response = await fetch(`/user/friend-request/${friendId}/accept`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
    });
    if (response.status === 200) {
      return await response.json();
    }
  } catch (error) {
    console.error("Error accepting friend request:", error);
  }
}

async function declineFriendRequest(friendId) {
  try {
    const response = await fetch(`/user/friend-request/${friendId}/decline`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
    });
    if (response.status === 200) {
      return await response.json();
    }
  } catch (error) {
    console.error("Error declining friend request:", error);
  }
}
