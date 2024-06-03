const translationDictEN = {
  add: "Add",
  block: "Block",
  remove: "Remove",
  unblock: "Unblock",
  joined: "Joined",
};

const translationDictIT = {
  add: "Aggiungi",
  block: "Blocca",
  remove: "Rimuovi",
  unblock: "Sblocca",
  joined: "Entrato",
};

const translationDictES = {
  add: "Añadir",
  block: "Bloquear",
  remove: "Eliminar",
  unblock: "Desbloquear",
  joined: "Unido",
};

const translationDictFR = {
  add: "Ajouter",
  block: "Bloquer",
  remove: "Supprimer",
  unblock: "Débloquer",
  joined: "Rejoint",
};

const translationDictDE = {
  add: "Hinzufügen",
  block: "Blockieren",
  remove: "Entfernen",
  unblock: "Freischalten",
  joined: "Beigetreten",
};

export function translatorWord(key, language) {
  switch (language) {
    case "en":
      return translationDictEN[key];
    case "it":
      return translationDictIT[key];
    case "es":
      return translationDictES[key];
    case "fr":
      return translationDictFR[key];
    case "de":
      return translationDictDE[key];
    default:
      return key;
  }
}

export function translatorError(key, language) {
  switch (language) {
    case "en":
      return translationDictErrEN[key];
    case "it":
      return translationDictErrIT[key];
    case "es":
      return translationDictErrES[key];
    case "fr":
      return translationDictErrFR[key];
    case "de":
      return translationDictErrDE[key];
    default:
      return key;
  }
}

export function applyTranslations(translationData) {
  for (let key in translationData) {
    if (translationData.hasOwnProperty(key)) {
      const element = document.getElementById(key);
      if (element) {
        element.innerText = translationData[key];
      }
    }
  }
}

const pathToIndexMapping = {
  "friends.html": 0,
  "settings.html": 1,
};

export function loadHTML(url, containerId) {
  const container = document.getElementById(containerId);
  fetch(url)
    .then((response) => response.text())
    .then(async (data) => {
      container.innerHTML = data;

      Array.from(container.getElementsByTagName("script")).forEach(
        (oldScript) => {
          const newScript = document.createElement("script");
          Array.from(oldScript.attributes).forEach((attr) =>
            newScript.setAttribute(attr.name, attr.value),
          );
          newScript.appendChild(document.createTextNode(oldScript.innerHTML));
          oldScript.parentNode.replaceChild(newScript, oldScript);
        },
      );
      initialize(url);
      const path = url.split("/").pop();
      if (path in pathToIndexMapping) {
        // Get the corresponding index
        const index = pathToIndexMapping[path];

        // Get the hr element
        const hrElement = document.querySelector(".menu hr");

        // Update the position of the hr element
        hrElement.className = "";
        hrElement.classList.add(`hr-position-${index}`);
      }
    })
    .catch((err) => console.warn(err));
}

export function routeWholeHtml(path) {
  const oldHead = document.head.innerHTML;
  fetch(path)
    .then((response) => response.text())
    .then((data) => {
      Array.from(document.getElementsByTagName("script")).forEach(
        (oldScript) => {
          oldScript.parentNode.removeChild(oldScript);
        },
      );

      document.documentElement.innerHTML = data;
      document.head.innerHTML = oldHead + document.head.innerHTML;

      Array.from(document.getElementsByTagName("script")).forEach(
        (oldScript) => {
          const newScript = document.createElement("script");
          Array.from(oldScript.attributes).forEach((attr) =>
            newScript.setAttribute(attr.name, attr.value),
          );
          newScript.appendChild(document.createTextNode(oldScript.innerHTML));
          oldScript.parentNode.replaceChild(newScript, oldScript);
        },
      );

      initialize(path);
    })
    .catch((error) => {
      console.warn("Something went wrong.", error);
    });
}

function initialize(path) {
  switch (path) {
    case "login.html":
      import("./login.js").then((module) => {
        module.initialize();
      });
      console.log("Login page initialized");
      break;
    case "home.html":
      import("./home.js").then(async (module) => {
        await module.attachEventListeners();
      });
      console.log("Home page initialized");
      break;
    case "gameLobby.html":
      import("./home.js").then(async (module) => {
        await module.setupGameLobbyPage();
      });
      console.log("Game Lobby page initialized");
      break;
    case "index.html":
      import("./main.js").then((module) => {
        module.navigate("/", false);
      });
      console.log("Main page initialized");
      break;
    case "friends.html":
      import("./friends.js").then(async (module) => {
        await module.setupFriendsPage();
      });
      console.log("Friends page initialized");
      break;
    case "settings.html":
      import("./settings.js").then(async (module) => {
        await module.initializeSettings();
      });
      console.log("Settings page initialized");
      break;
    case "profile.html":
      import("./profile.js").then(async (module) => {
        await module.initializeProfile();
      });
      console.log("Profile page initialized");
      break;
    case "loginForm.html":
      import("./login.js").then(async (module) => {
        await module.attachEventListeners();
      });
      console.log("Login form initialized");
      break;
    case "registerForm.html":
      import("./login.js").then(async (module) => {
        await module.attachEventListeners();
      });
      console.log("Register form initialized");
      break;
    case "pongcpugame.html":
      import("./playervsai.js").then(async (module) => {
        await module.showPongCPUGamePage();
      });
      console.log("Pong CPU game initialized");
      break;
    case "ponggame.html":
      import("./ponglocal.js").then(async (module) => {
        await module.showPongGamePage();
      });
      console.log("Pong player game initialized");
      break;
    case "tictactoe.html":
      import("./tictactoe.js").then(async (module) => {
        await module.showTicTacToeGamePage();
      });
      console.log("Tic Tac Toe game initialized");
      break;
    case "tournament.html":
      import("./tournament.js").then(async (module) => {
        await module.showTournamentGame();
      });
      console.log("Tournament game initialized");
      break;
    default:
      console.log("No initialization possible for this page:", path);
  }
}

const translationDictErrEN = {
  "invalid-email": "Invalid email",
  "passwords-not-match": "Passwords do not match",
  "password-empty": "Password cannot be empty",
  "password-short": "Password must be at least 8 characters long.",
  "error-adding-friend": "Error adding friend!",
  "error-occurred": "An error occurred:",
  "error-try-again": "An error occurred, please try again",
};

const translationDictErrIT = {
  "invalid-email": "Email non valida",
  "passwords-not-match": "Le password non corrispondono",
  "password-empty": "La password non può essere vuota",
  "password-short": "La password deve essere lunga almeno 8 caratteri.",
  "error-adding-friend": "Errore aggiunta amico!",
  "error-occurred": "Si è verificato un errore:",
  "error-try-again": "Si è verificato un errore, riprova",
};

const translationDictErrES = {
  "invalid-email": "Correo electrónico inválido",
  "passwords-not-match": "Las contraseñas no coinciden",
  "password-empty": "La contraseña no puede estar vacía",
  "password-short": "La contraseña debe tener al menos 8 caracteres.",
  "error-adding-friend": "Error al agregar amigo!",
  "error-occurred": "Se ha producido un error:",
  "error-try-again": "Se ha producido un error, por favor intente de nuevo",
};

const translationDictErrFR = {
  "invalid-email": "Email invalide",
  "passwords-not-match": "Les mots de passe ne correspondent pas",
  "password-empty": "Le mot de passe ne peut pas être vide",
  "password-short": "Le mot de passe doit comporter au moins 8 caractères.",
  "error-adding-friend": "Erreur lors de l'ajout de l'ami!",
  "error-occurred": "Une erreur s'est produite:",
  "error-try-again": "Une erreur s'est produite, veuillez réessayer",
};

const translationDictErrDE = {
  "invalid-email": "Ungültige E-Mail",
  "passwords-not-match": "Passwörter stimmen nicht überein",
  "password-empty": "Passwort darf nicht leer sein",
  "password-short": "Passwort muss mindestens 8 Zeichen lang sein.",
  "error-adding-friend": "Fehler beim Hinzufügen eines Freundes!",
  "error-occurred": "Ein Fehler ist aufgetreten:",
  "error-try-again": "Ein Fehler ist aufgetreten, bitte versuche es erneut",
};

export function showError(key, language) {
  const message = translatorError(key, language);

  Swal.fire({
    icon: "error",
    title: "Oops...",
    text: message,
    customClass: {
      container: "centered-swal",
    },
  });
}

export function validateEmail(email) {
  const regex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  return regex.test(email);
}
