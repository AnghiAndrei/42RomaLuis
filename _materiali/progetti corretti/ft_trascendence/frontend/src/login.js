import { loginUser, registerUser, authenticateWith42 } from "./auth.js";
import { navigate } from "./main.js";

export function initialize() {
  document
    .getElementById("intraLogin")
    .addEventListener("click", authenticateWith42);
  document
    .getElementById("switchButton")
    .addEventListener("click", switchForms);
  navigate("/loginForm");
}

export function attachEventListeners() {
  const registerButton = document.getElementById("registerButton");
  const loginButton = document.getElementById("loginButton");
  if (registerButton) registerButton.addEventListener("click", registerUser);
  if (loginButton) loginButton.addEventListener("click", loginUser);
}

function switchForms() {
  const registrationForm = document.getElementById("registrationForm");
  const loginForm = document.getElementById("loginForm");
  const title = document.getElementById("pageTitle");
  const newTitle = title.cloneNode(true);
  title.parentNode.replaceChild(newTitle, title);
  newTitle.classList.add("animate__bounce");
  if (registrationForm) {
    navigate("/loginForm");
  } else if (loginForm) {
    navigate("/registerForm");
  }
}
