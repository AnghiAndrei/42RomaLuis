const axios = require("axios");
const { gameUrl } = require("../config/serverConfig");
const { agent } = require("../config/sslConfig");

exports.getLeaderboard = async (req, res) => {
  try {
    const response = await axios.get(`${gameUrl}/leaderboard`, {
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${req.session.token["access"]}`,
      },
      httpsAgent: agent,
    });
    if (response.status === 200) {
      console.log("~get('/game/leaderboard'):", response.data);
      res.status(200).send(response.data);
    }
  } catch (error) {
    console.error("~get('/user/availables'):", error);
    res.status(400).send("Something went wrong");
  }
};
