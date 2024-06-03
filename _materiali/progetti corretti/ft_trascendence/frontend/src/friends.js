import { getLanguage, getTranslationData } from "./settings.js";
import { applyTranslations, showError, translatorWord } from "./utils.js";

export async function setupFriendsPage() {
  const translationData = await getTranslationData();
  if (translationData) {
    applyTranslations(translationData);
  }
  const language = await getLanguage();
  try {
    const availablesResponse = await fetch("/user/availables");
    if (availablesResponse.status === 401) {
      logOut();
      return;
    }
    const availables = await availablesResponse.json();
    for (const available of availables) {
      createAvailableElement(available, language);
    }
  } catch (error) {
    console.error("Error fetching available friends:", error);
    return;
  }
  try {
    const friendsResponse = await fetch("/user/friends");
    if (friendsResponse.status === 401) {
      logOut();
      return;
    }
    const friends = await friendsResponse.json();
    for (const friend of friends) {
      createFriendElement(friend, language);
    }
  } catch (error) {
    console.error("Error fetching friends:", error);
    return;
  }
  setupFriendsPageButtons();
}

export function setupFriendsPageButtons() {
  const moreButtons = document.querySelectorAll(".more-button");
  moreButtons.forEach((button) => {
    button.addEventListener("click", function (event) {
      showDropdown(event); // Pass the event object to the showDropdown export function
    });
  });
}

function createCustomModal(friend, language) {
  // Create the modal elements
  const modal = document.createElement("div");
  modal.id = "userProfileModal";
  modal.className = "custom-modal";

  const modalContent = document.createElement("div");
  modalContent.className = "custom-modal-content";

  const closeSpan = document.createElement("span");
  closeSpan.className = "custom-close";
  closeSpan.textContent = "×";

  const infoContainer = document.createElement("div");
  infoContainer.className = "custom-info-container";

  // Column 1
  const column1 = document.createElement("div");
  column1.className = "custom-column";

  const usernameP = document.createElement("p");
  usernameP.id = "username";

  const emailP = document.createElement("p");
  emailP.id = "email";

  column1.appendChild(usernameP);
  column1.appendChild(emailP);

  // Profile image
  const profileImageContainer = document.createElement("div");
  profileImageContainer.className = "custom-profile-image-container";

  const profileImage = document.createElement("img");
  profileImage.id = "profileImage";
  profileImageContainer.appendChild(profileImage);

  // Column 2
  const column2 = document.createElement("div");
  column2.className = "custom-column";

  const scoreP = document.createElement("p");
  scoreP.id = "score";

  const joinedP = document.createElement("p");
  joinedP.id = "joined";

  column2.appendChild(scoreP);
  column2.appendChild(joinedP);

  // Append columns and profile image container to the info container
  infoContainer.appendChild(column1);
  infoContainer.appendChild(profileImageContainer);
  infoContainer.appendChild(column2);

  // Append elements to the modal content
  modalContent.appendChild(closeSpan);
  modalContent.appendChild(infoContainer);

  // Append the modal content to the modal
  modal.appendChild(modalContent);

  // Append the modal to the body of the HTML document
  document.body.appendChild(modal);

  // Fetch and display the user's data
  fetchUserData(friend.id).then((userData) => {
    document.getElementById("username").textContent =
      `Username: ${userData.username}`;
    document.getElementById("email").textContent = `Email: ${userData.email}`;
    const dateJoined = new Date(userData.date_joined);
    const formattedDate = `${dateJoined.getFullYear()}-${dateJoined.getMonth() + 1}-${dateJoined.getDate()}`;
    document.getElementById("joined").textContent =
      `${translatorWord("joined", language)}: ${formattedDate}`;
    document.getElementById("profileImage").src = userData.profile_image; // Ensure your userData contains the profile_image_url

    // Show the modal
    modal.style.display = "block";
  });

  // When the user clicks on <span> (x), close the modal
  closeSpan.onclick = function () {
    modal.style.display = "none";
    // Remove the modal from the body after closing
    document.body.removeChild(modal);
  };

  // When the user clicks anywhere outside the modal, close it
  window.onclick = function (event) {
    if (event.target === modal) {
      modal.style.display = "none";
      // Remove the modal from the body after closing
      document.body.removeChild(modal);
    }
  };
}

function createButton(friend, language) {
  const button = document.createElement("button");
  button.className = "button-style";
  button.textContent = friend.username;

  button.addEventListener("click", function () {
    createCustomModal(friend, language);
  });

  return button;
}

function createDropdownContent(friend, isAvailable, language) {
  const dropdownContent = document.createElement("div");
  dropdownContent.className = isAvailable
    ? "dropdown-content-right"
    : "dropdown-content-left";

  if (isAvailable) {
    const addButton = document.createElement("button");
    addButton.className = "add-friend";
    addButton.textContent = translatorWord("add", language);
    addButton.addEventListener("click", async function () {
      await addFriend(friend.id, language);
    });
    dropdownContent.appendChild(addButton);
  } else {
    const removeButton = document.createElement("button");
    removeButton.className = "remove-friend";
    removeButton.textContent = translatorWord("remove", language);
    removeButton.addEventListener("click", async function () {
      await removeFriend(friend.id, language);
    });
    dropdownContent.appendChild(removeButton);
  }

  const blockButton = document.createElement("button");
  blockButton.className = "block-unblock-friend";
  blockButton.textContent = friend.is_blocked
    ? translatorWord("unblock", language)
    : translatorWord("block", language);
  blockButton.addEventListener("click", async function () {
    if (friend.is_blocked) {
      await unblockUser(friend.id, language);
      blockButton.textContent = translatorWord("block", language);
    } else {
      await blockUser(friend.id, language);
      blockButton.textContent = translatorWord("unblock", language);
    }
  });

  dropdownContent.appendChild(blockButton);

  return dropdownContent;
}

export function createFriendElement(friend, language) {
  const container = document.getElementById("friend-container");
  const row = document.createElement("div");
  row.className = "row";

  const nameButton = createButton(friend, language);

  const dropdownWrapper = document.createElement("div");
  dropdownWrapper.className = "dropdown-wrapper";

  const moreButton = document.createElement("button");
  moreButton.className = "more-button";

  const dropdownContent = createDropdownContent(friend, false, language);

  // Append the more button and dropdown content to the dropdown wrapper
  dropdownWrapper.appendChild(moreButton);
  dropdownWrapper.appendChild(dropdownContent);

  // Append the name button, status, and dropdown wrapper to the row
  row.appendChild(nameButton);
  row.appendChild(dropdownWrapper);

  // Append the row to the container
  container.appendChild(row);
}

export function createAvailableElement(friend, language) {
  const container = document.getElementById("available-container");
  const row = document.createElement("div");
  row.className = "row";

  const nameButton = createButton(friend, language);

  const dropdownWrapper = document.createElement("div");
  dropdownWrapper.className = "dropdown-wrapper";

  const moreButton = document.createElement("button");
  moreButton.className = "more-button";

  const dropdownContent = createDropdownContent(friend, true, language);

  // Append the more button and dropdown content to the dropdown wrapper
  dropdownWrapper.appendChild(moreButton);
  dropdownWrapper.appendChild(dropdownContent);

  // Append the name button, status, and dropdown wrapper to the row
  row.appendChild(nameButton);
  row.appendChild(dropdownWrapper);

  // Append the row to the container
  container.appendChild(row);
}

function showDropdown(event) {
  const button = event.target;
  // Get the next sibling element of the button, which is the dropdown content
  const dropdown = button.nextElementSibling;

  // Close any other open dropdowns
  const openDropdowns = document.querySelectorAll(".dropdown-content.show");
  openDropdowns.forEach((openDropdown) => {
    if (openDropdown !== dropdown) {
      openDropdown.classList.remove("show");
    }
  });

  dropdown.classList.toggle("show");
  dropdown.style.zIndex = "1";
}

async function addFriend(friendId, language) {
  try {
    const response = await fetch(`/user/add-friend/${friendId}`, {
      method: "POST",
    });
    if (response.status === 200) {
      const modal = new bootstrap.Modal(
        document.getElementById("confirmationModal"),
      );
      const messageElement = document.getElementById("modalMessage");
      const res = await response.json();
      messageElement.innerHTML = getTranslation(
        "friend-request-sent",
        language,
      );
      modal.show();
    }
  } catch (error) {
    showError("error-adding-friend", language);
  }
}

async function removeFriend(friendId, language) {
  try {
    const response = await fetch(`/user/remove-friend/${friendId}`, {
      method: "POST",
    });
    if (response.status === 200) {
      const modal = new bootstrap.Modal(
        document.getElementById("confirmationModal"),
      );
      const messageElement = document.getElementById("modalMessage");
      const res = await response.json();
      messageElement.innerHTML = getTranslation("friend-removed", language);
      modal.show();
    }
  } catch (error) {
    console.error("Error removing friend:", error);
  }
}

async function blockUser(friendId, language) {
  try {
    const response = await fetch(`/user/block-user/${friendId}/block`, {
      method: "POST",
    });
    if (response.status === 200) {
      const modal = new bootstrap.Modal(
        document.getElementById("confirmationModal"),
      );
      const messageElement = document.getElementById("modalMessage");
      messageElement.innerHTML = getTranslation("user-blocked", language);
      modal.show();
    }
  } catch (error) {
    console.error("Error blocking user:", error);
  }
}

async function unblockUser(friendId, language) {
  try {
    const response = await fetch(`/user/block-user/${friendId}/unblock`, {
      method: "POST",
    });
    if (response.status === 200) {
      const modal = new bootstrap.Modal(
        document.getElementById("confirmationModal"),
      );
      const messageElement = document.getElementById("modalMessage");
      messageElement.innerHTML = getTranslation("user-unblocked", language);
      modal.show();
    }
  } catch (error) {
    console.error("Error unblocking user:", error);
  }
}

async function fetchUserData(id) {
  try {
    const response = await fetch(`/user/user-info/${id}`);
    if (response.status === 200) {
      return await response.json();
    }
  } catch (error) {
    console.error("Error fetching user data:", error);
  }
}

const translations = {
  en: {
    "user-blocked": "User blocked!",
    "user-unblocked": "User unblocked!",
    "friend-removed": "Friend removed",
    "friend-request-sent": "Friend request already sent",
  },
  es: {
    "user-blocked": "¡Usuario bloqueado!",
    "user-unblocked": "Usuario desbloqueado!",
    "friend-removed": "Amigo eliminado",
    "friend-request-sent": "Solicitud de amistad ya enviada",
  },
  fr: {
    "user-blocked": "Utilisateur bloqué!",
    "user-unblocked": "Utilisateur débloqué!",
    "friend-removed": "Ami supprimé",
    "friend-request-sent": "Demande d'ami déjà envoyée",
  },
  it: {
    "user-blocked": "Utente bloccato!",
    "user-unblocked": "Utente sbloccato!",
    "friend-removed": "Amico rimosso",
    "friend-request-sent": "Richiesta di amicizia già inviata",
  },
  de: {
    "user-blocked": "Benutzer blockiert!",
    "user-unblocked": "Benutzer entblockt!",
    "friend-removed": "Freund entfernt",
    "friend-request-sent": "Freundschaftsanfrage bereits gesendet",
  },
};

function getTranslation(key, language) {
  const languageTranslations = translations[language];
  if (languageTranslations) {
    return languageTranslations[key];
  } else {
    return null; // Or a default value
  }
}
