const express = require("express");
const router = express.Router();
const gameController = require("../controllers/gameController");
router.get("/leaderboard", gameController.getLeaderboard);
module.exports = router;
