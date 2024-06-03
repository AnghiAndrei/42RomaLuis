// authRoutes.js

const express = require("express");
const router = express.Router();
const authController = require("../controllers/authController");
const {
  getUserAuthMethods,
  checkToken,
  getUserInfo,
} = require("../utils/utils");

router.post("/login", authController.login, getUserAuthMethods, getUserInfo);
router.post(
  "/login/confirm2FA",
  authController.confirm2FALogin,
  getUserAuthMethods,
  getUserInfo,
);
router.get("/logout", authController.logout);
router.post(
  "/register",
  authController.register,
  getUserAuthMethods,
  getUserInfo,
);
router.get(
  "/oauth_42",
  authController.oauth_42,
  getUserAuthMethods,
  getUserInfo,
);
router.get("/auth_42", authController.auth_42);
router.get("/2fa-status", authController.get2FAStatus);
router.get("/MFA", checkToken, authController.activate2FA);
router.get("/MFA/deactivate", checkToken, authController.deactivate2FA);
router.post(
  "/MFA/confirm",
  checkToken,
  authController.confirm2FAactivation,
  getUserAuthMethods,
);
router.post(
  "/MFA/confirmDeactivation",
  checkToken,
  authController.confirm2FADeactivation,
  getUserAuthMethods,
);

module.exports = router;
