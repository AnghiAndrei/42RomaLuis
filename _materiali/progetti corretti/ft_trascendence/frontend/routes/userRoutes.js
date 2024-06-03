const express = require("express");
const router = express.Router();
const userController = require("../controllers/userController");
const { checkToken, getUserInfo } = require("../utils/utils");
const multer = require("multer");
const upload = multer({ limits: { fileSize: 50 * 1024 * 1024 } }); //
router.get("/friends", checkToken, userController.getUserFriends);
router.get("/availables", checkToken, userController.getAvailableUsers);
router.get("/authenticated", checkToken, userController.checkAuthenticated);
router.post("/language", checkToken, userController.setUserLanguage);
router.get("/language", checkToken, userController.getUserLanguage);
router.get("/info", checkToken, userController.getUserInfo);
router.post(
  "/update-username",
  checkToken,
  userController.updateUsername,
  getUserInfo,
);
router.post(
  "/update-email",
  checkToken,
  userController.updateEmail,
  getUserInfo,
);
router.post(
  "/update-password",
  checkToken,
  userController.updatePassword,
  getUserInfo,
);
router.post(
  "/update-avatar",
  upload.single("avatar"),
  checkToken,
  userController.updateAvatar,
  getUserInfo,
);
router.get("/getLenguageJson", checkToken, userController.getLenguageJson);
router.post("/add-friend/:friendId", checkToken, userController.addFriend);
router.post(
  "/remove-friend/:friendId",
  checkToken,
  userController.removeFriend,
);
router.get("/friend-requests", checkToken, userController.getFriendRequests);
router.post(
  "/friend-request/:friendId/accept",
  checkToken,
  userController.acceptFriendRequest,
);
router.post(
  "/friend-request/:friendId/decline",
  checkToken,
  userController.declineFriendRequest,
);

router.post(
  "/block-user/:friendId/block",
  checkToken,
  userController.blockUser,
);

router.post(
  "/block-user/:friendId/unblock",
  checkToken,
  userController.unblockUser,
);

router.get("/user-info/:id", checkToken, userController.getplayerInfo);
module.exports = router;
