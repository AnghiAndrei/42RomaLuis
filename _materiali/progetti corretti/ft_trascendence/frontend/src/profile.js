import { getTranslationData, getLanguage } from "./settings.js";
import { applyTranslations } from "./utils.js";
import { showError } from "./utils.js";

export async function initializeProfile() {
  const translationData = await getTranslationData();
  if (translationData) {
    applyTranslations(translationData);
  }
  const data = await getUserData();
  const language = await getLanguage();
  let dateJoined = new Date(data.date_joined);
  let formattedDate = `${dateJoined.getFullYear()}-${dateJoined.getMonth() + 1}-${dateJoined.getDate()}`;

  // document.getElementById("rewardPoints").innerHTML =
  //   `<i class="fa fa-award text-md"></i>&nbsp;${data.score} points`;
  document.getElementById("userAvatar").src = data.profile_image;
  document.getElementById("userAvatar").alt = data.username + " Avatar";
  document.getElementById("userName").textContent = data.username;
  document.getElementById("joined").textContent =
    document.getElementById("joined").textContent + " " + formattedDate;
  document.getElementById("account-fn").value = data.username;
  document.getElementById("account-email").value = data.email;

  let originalUsername = document.getElementById("account-fn").value;
  let originalEmail = document.getElementById("account-email").value;
  const newPasswordField = document.getElementById("account-pass");
  const confirmPasswordField = document.getElementById("account-confirm-pass");

  const updateUsernameButton = document.querySelector(
    'button[data-toast-message="Your username has been updated successfully."]',
  );
  const updateEmailButton = document.querySelector(
    'button[data-toast-message="Your email has been updated successfully."]',
  );
  const updatePasswordButton = document.querySelector(
    'button[data-toast-message="Your password updated successfuly."]',
  );

  const imgElement = document.getElementById("userAvatar");
  const fileInput = document.getElementById("fileInput");

  updateUsernameButton.disabled = true;
  updateEmailButton.disabled = true;
  updatePasswordButton.disabled = true;

  document.getElementById("account-fn").addEventListener("input", function () {
    updateUsernameButton.disabled = this.value === originalUsername;
  });
  document
    .getElementById("account-email")
    .addEventListener("input", function () {
      updateEmailButton.disabled = this.value === originalEmail;
    });

  newPasswordField.addEventListener("input", function () {
    updatePasswordButton.disabled = !(
      newPasswordField.value === confirmPasswordField.value &&
      newPasswordField.value !== ""
    );
  });
  confirmPasswordField.addEventListener("input", function () {
    updatePasswordButton.disabled = !(
      newPasswordField.value === confirmPasswordField.value &&
      confirmPasswordField.value !== ""
    );
  });

  updateUsernameButton.addEventListener("click", async function () {
    if (
      (await updateUsername(document.getElementById("account-fn").value)) ===
      true
    ) {
      updateUsernameButton.disabled = true;
      originalUsername = document.getElementById("account-fn").value;
    } else {
      updateUsernameButton.disabled = false;
    }
  });

  updateEmailButton.addEventListener("click", async function () {
    if (
      (await updateEmail(document.getElementById("account-email").value)) ===
      true
    ) {
      updateEmailButton.disabled = true;
      originalEmail = document.getElementById("account-email").value;
    } else {
      updateEmailButton.disabled = false;
    }
  });

  updatePasswordButton.addEventListener("click", async function () {
    await updatePassword(
      newPasswordField.value,
      confirmPasswordField.value,
      language,
    );
    newPasswordField.value = "";
    confirmPasswordField.value = "";
    updatePasswordButton.disabled = true;
  });

  imgElement.addEventListener("click", function () {
    fileInput.click();
  });

  fileInput.addEventListener("change", async function () {
    const file = this.files[0];
    const reader = new FileReader();
    reader.onloadend = async function () {
      imgElement.src = reader.result;
      await updateAvatar(file);
    };
    reader.readAsDataURL(file);
  });
}

async function getUserData() {
  try {
    const response = await fetch("/user/info", {
      headers: {
        "Content-Type": "application/json",
      },
    });
    if (response.status === 200) {
      return await response.json();
    }
  } catch (error) {
    console.error("Error fetching user data:", error);
  }
}

async function updateUsername(username) {
  try {
    const response = await fetch("/user/update-username", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ username }),
    });
    const modal = new bootstrap.Modal(
      document.getElementById("confirmationModal"),
    );
    const messageElement = document.getElementById("modalMessage");
    if (response.status === 200) {
      messageElement.innerHTML = "Your username has been updated successfully.";
      modal.show();
      return true;
    } else {
      const data = await response.json();
      showError("error-occurred", "en");
      return false;
    }
  } catch (error) {
    console.error("Error updating username:", error);
    return false;
  }
}

async function updateEmail(email) {
  try {
    const response = await fetch("/user/update-email", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ email }),
    });
    const modal = new bootstrap.Modal(
      document.getElementById("confirmationModal"),
    );
    const messageElement = document.getElementById("modalMessage");
    if (response.status === 200) {
      messageElement.innerHTML = "Your email has been updated successfully.";
      modal.show();
      return true;
    } else {
      const data = await response.json();
      showError("error-occurred", "en");
      return false;
    }
  } catch (error) {
    console.error("Error updating email:", error);
    return false;
  }
}

async function updatePassword(password, passConfirm, language) {
  if (password === "") {
    showError("password-empty", language);
    return false;
  }
  if (passConfirm !== password) {
    showError("Passwords do not match.", language);
    return false;
  }
  if (password.length < 8) {
    showError("password-short", language);
    return false;
  }
  try {
    const response = await fetch("/user/update-password", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ password }),
    });
    const modal = new bootstrap.Modal(
      document.getElementById("confirmationModal"),
    );
    const messageElement = document.getElementById("modalMessage");
    if (response.status === 200) {
      messageElement.innerHTML = "Your password has been updated successfully.";
      modal.show();
      return true;
    } else {
      const data = await response.json();
      showError("error-occurred", language);
      return false;
    }
  } catch (error) {
    console.error("Error updating password:", error);
    return false;
  }
}

async function updateAvatar(avatar) {
  try {
    let formData = new FormData();
    formData.append("avatar", avatar);

    const response = await fetch("/user/update-avatar", {
      method: "POST",
      body: formData,
    });
    const modal = new bootstrap.Modal(
      document.getElementById("confirmationModal"),
    );
    const messageElement = document.getElementById("modalMessage");
    if (response.status === 200) {
      messageElement.innerHTML = "Your avatar has been updated successfully.";
      modal.show();
      return true;
    } else {
      const data = await response.json();
      showError("error-occurred", "en");
      return false;
    }
  } catch (error) {
    console.error("Error updating avatar:", error);
    return false;
  }
}
