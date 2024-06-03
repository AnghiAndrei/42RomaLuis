import { applyTranslations, showError } from "./utils.js";

async function get2FAStatus() {
  try {
    const response = await fetch("/auth/2fa-status", {
      headers: {
        "Content-Type": "application/json",
      },
    });
    if (response.status === 200) {
      return true;
    } else if (response.status === 204) {
      return false;
    }
  } catch (error) {
    console.error("Error fetching 2FA status:", error);
    return false;
  }
}

export async function getLanguage() {
  try {
    const response = await fetch("/user/language", {
      headers: {
        "Content-Type": "application/json",
      },
    });
    if (response.status === 200) {
      return await response.text();
    }
  } catch (error) {
    console.error("Error fetching language:", error);
    return "en";
  }
}

async function updateUserLanguage(language) {
  try {
    const response = await fetch("/user/language", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ language }),
    });
    if (response.status === 200) {
      return true;
    } else {
      showError("error-occurred", language);
      return false;
    }
  } catch (error) {
    console.error(error);
    return false;
  }
}

async function send2FACode() {
  try {
    const res = await fetch("/auth/MFA", {
      headers: {
        "Content-Type": "application/json",
      },
    });
    if (res.status === 200) {
      return true;
    } else {
      showError("error-occurred", "en");
      return false;
    }
  } catch (error) {
    console.error("Error fetching 2FA status:", error);
    return false;
  }
}

async function confirm2FAActivation(confirmationCode) {
  try {
    const res = await fetch("/auth/MFA/confirm", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ confirmationCode }),
    });
    if (res.status === 200) {
      return true;
    } else {
      showError("error-occurred", "en");
      return false;
    }
  } catch (error) {
    console.error("Error confirming the 2FA activation:", error);
    return false;
  }
}

async function deactivate2FA() {
  try {
    const res = await fetch("/auth/MFA/deactivate", {
      headers: {
        "Content-Type": "application/json",
      },
    });
    if (res.status === 200) {
      return true;
    } else {
      showError("error-occurred", "en");
      return false;
    }
  } catch (error) {
    console.error("Error confirming the 2FA activation:", error);
    return false;
  }
}

async function deactivate2FAConfirm(confirmationCode) {
  try {
    const res = await fetch("/auth/MFA/confirmDeactivation", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ confirmationCode }),
    });
    if (res.status === 200) {
      return true;
    } else {
      showError("error-occurred", "en");
      return false;
    }
  } catch (error) {
    console.error("Error confirming the 2FA activation:", error);
    return false;
  }
}

export async function getTranslationData() {
  try {
    const response = await fetch("/user/getLenguageJson");
    if (response.status === 200) {
      return await response.json();
    }
  } catch (error) {
    console.error("Error fetching translation data:", error);
  }
}

export async function initializeSettings() {
  const languageSelect = document.getElementById("language-select");
  languageSelect.value = await getLanguage();

  const data = await getTranslationData();
  if (data) {
    applyTranslations(data);
  }
  if (await get2FAStatus()) {
    document.getElementById("toggle2FA").checked = true;
  }

  const saveButton = document.getElementById("saveSettings");

  let toggle2FAChanged = false;
  let languageSelectChanged = false;

  async function enableSaveButton(event) {
    const target = event.target.id;
    if (target === "toggle2FA") {
      const value = await get2FAStatus();
      toggle2FAChanged = event.target.checked !== value;
    } else if (target === "language-select") {
      const value = await getLanguage();
      languageSelectChanged = event.target.value !== value;
    }

    if (toggle2FAChanged || languageSelectChanged) {
      saveButton.disabled = false;
      saveButton.classList.remove("btn-secondary");
      saveButton.classList.add("btn-success");
    } else {
      saveButton.disabled = true;
      saveButton.classList.remove("btn-success");
      saveButton.classList.add("btn-secondary");
    }
  }

  saveButton.addEventListener("click", async function () {
    if (languageSelectChanged !== false) {
      const language = document.getElementById("language-select").value;
      await updateUserLanguage(language);
      const data = await getTranslationData();
      applyTranslations(data);
      languageSelectChanged = false;
    }
    if (toggle2FAChanged !== false) {
      if (!(await get2FAStatus())) {
        const toggle2FASuccess = await send2FACode();
        if (toggle2FASuccess) {
          $("#confirmationModal").modal("show");

          document
            .getElementById("confirmButton")
            .addEventListener("click", async function () {
              const confirmationCode =
                document.getElementById("confirmationCode").value;
              await confirm2FAActivation(confirmationCode);
              $("#confirmationModal").modal("hide");
            });

          // When the user clicks on the cancel button, hide the modal
          document
            .getElementById("cancelButton")
            .addEventListener("click", function () {
              $("#confirmationModal").modal("hide");
            });
        }
      } else {
        const deactivate2FASuccess = await deactivate2FA();
        if (deactivate2FASuccess) {
          $("#confirmationModal").modal("show");

          document
            .getElementById("confirmButton")
            .addEventListener("click", async function () {
              const confirmationCode =
                document.getElementById("confirmationCode").value;
              await deactivate2FAConfirm(confirmationCode);
              $("#confirmationModal").modal("hide");
            });

          // When the user clicks on the cancel button, hide the modal
          document
            .getElementById("cancelButton")
            .addEventListener("click", function () {
              $("#confirmationModal").modal("hide");
            });
        }
      }
    }
    saveButton.disabled = true;
    saveButton.classList.remove("btn-success");
    saveButton.classList.add("btn-secondary");
  });

  document
    .getElementById("toggle2FA")
    .addEventListener("change", enableSaveButton);
  document
    .getElementById("language-select")
    .addEventListener("change", enableSaveButton);
}
