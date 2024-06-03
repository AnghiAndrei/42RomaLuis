// userController.js

const axios = require("axios");
const jwt = require("jsonwebtoken");
const { friendsUrl, userUrl, jwtSecret } = require("../config/serverConfig");
const { agent } = require("../config/sslConfig");
const { handleCatchesApiCall } = require("../utils/utils");
const fs = require("fs");
const path = require("path");

exports.getAvailableUsers = async (req, res) => {
  try {
    const response = await axios.get(`${userUrl}/availables`, {
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${req.session.token["access"]}`,
      },
      httpsAgent: agent,
    });

    if (response.status === 200) {
      const availables = response.data;
      res.status(200).send(availables);
    } else {
      res.status(response.status).send("Something went wrong");
    }
  } catch (error) {
    console.error("~get('/user/availables'):", error);
    res.status(400).send("Something went wrong");
  }
};

exports.getUserFriends = async (req, res) => {
  try {
    const response = await axios.get(`${userUrl}/user_friends`, {
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${req.session.token["access"]}`,
      },
      httpsAgent: agent,
    });

    if (response.status === 200) {
      const friends = response.data;
      res.status(200).send(friends);
    } else {
      res.status(response.status).send("Something went wrong");
    }
  } catch (error) {
    console.error("~get('/user/user_friends'):", error);
  }
};

exports.checkAuthenticated = async (req, res) => {
  if (!req.session.token) {
    res.status(200).send({ authenticated: false });
    return;
  }
  try {
    const token = req.session.token["refresh"];
    const verify = jwt.verify(token, jwtSecret, function (err) {
      return !err;
    });
    if (verify) {
      res.status(200).send({ authenticated: true });
    } else {
      res.status(200).send({ authenticated: false });
    }
  } catch (error) {
    console.error("~get('/user/authenticated'):", error);
    res.status(200).send({ authenticated: false });
  }
};

exports.getUserLanguage = async (req, res) => {
  res.status(200).send(req.session.language);
};

exports.setUserLanguage = async (req, res) => {
  try {
    req.session.language = req.body.language;
    req.session.save();
    res.status(200).send();
  } catch (error) {
    console.error("Errore nel caricamento del file di traduzione:", error);
    res
      .status(500)
      .send(
        "Si è verificato un errore durante il caricamento del file di traduzione.",
      );
  }
};

exports.getLenguageJson = async (req, res) => {
  const language = req.session.language;
  const translationFilePath = path.join(
    __dirname,
    "..",
    "translations",
    `${language}.json`,
  );
  const translationData = fs.readFileSync(translationFilePath, "utf8");
  res.status(200).json(JSON.parse(translationData));
};

exports.getUserInfo = async (req, res) => {
  console.log("getUserInfo DIOCANE");
  if (req.session.userInfo) {
    if (!req.session.userInfo.profile_image) {
      req.session.userInfo.profile_image = "/public/profile-default.svg";
    }
  }
  res.status(200).send(req.session.userInfo);
};

exports.updateUsername = async (req, res, next) => {
  const data = req.body;
  try {
    const response = await axios.post(
      `${userUrl}/update-username`,
      {
        username: data.username,
      },
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );

    if (response.status === 200) {
      res.status(200).send(response.data);
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "updateUsername");
  }
  next();
};

exports.updateEmail = async (req, res, next) => {
  const data = req.body;
  try {
    const response = await axios.post(
      `${userUrl}/update-email`,
      {
        email: data.email,
      },
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );

    if (response.status === 200) {
      res.status(200).send();
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "updateEmail");
  }
  next();
};

exports.updatePassword = async (req, res, next) => {
  const data = req.body;
  try {
    const response = await axios.post(
      `${userUrl}/update-password`,
      {
        password: data.password,
      },
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );

    if (response.status === 200) {
      res.status(200).send();
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "updatePassword");
  }
  next();
};

exports.updateAvatar = async (req, res, next) => {
  if (!req.file) {
    res.status(400).send("No file uploaded");
    return;
  }

  // Create the directory if it doesn't exist
  const dir = "./user_images";
  if (!fs.existsSync(dir)) {
    fs.mkdirSync(dir);
  }

  const userId = req.session.userInfo.id; // Use user id instead of username
  const extension = path.extname(req.file.originalname);
  const filename = `${userId}${extension}`; // Use user id in the filename

  const filePath = path.join(dir, filename);

  // Delete all files in the user's directory
  fs.readdir(dir, (err, files) => {
    if (err) throw err;

    for (const file of files) {
      if (file.startsWith(userId)) {
        //DA RIVEDERE va messo if file === userID prima del punto estensione
        // Check if the file starts with the user id
        fs.unlink(path.join(dir, file), (err) => {
          if (err) throw err;
        });
      }
    }
  });

  fs.writeFile(filePath, req.file.buffer, async (err) => {
    if (err) {
      console.error("Error saving file:", err);
      res.status(500).send("Error saving file");
      return;
    }

    await axios
      .post(
        `${userUrl}/update-image`,
        { avatar: filePath },
        {
          headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${req.session.token["access"]}`,
          },
          httpsAgent: agent,
        },
      )
      .then((response) => {
        if (response.status === 200) {
          res.status(200).send();
        } else {
          res.status(response.status).send(response.statusText);
        }
      })
      .catch((error) => {
        handleCatchesApiCall(res, error, "updateAvatar");
      });

    next();
  });
};

exports.addFriend = async (req, res) => {
  const friendId = req.params.friendId;
  try {
    const response = await axios.post(
      `${friendsUrl}/addFriend/${friendId}/`,
      {},
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );
    if (response.status < 300) {
      res.status(200).send(response.data);
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "addFriend");
  }
};

exports.removeFriend = async (req, res) => {
  const friendId = req.params.friendId;
  try {
    const response = await axios.post(
      `${friendsUrl}/removeFriend/${friendId}/`,
      {},
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );

    if (response.status === 200) {
      res.status(200).send(response.data);
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "removeFriend");
  }
};

exports.getFriendRequests = async (req, res) => {
  try {
    const response = await axios.get(`${friendsUrl}/requests`, {
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${req.session.token["access"]}`,
      },
      httpsAgent: agent,
    });

    if (response.status === 200) {
      const friendRequests = response.data;
      res.status(200).send(friendRequests);
    }
  } catch (error) {
    console.error("~get('/user/friend-requests'):", error);
  }
};

exports.acceptFriendRequest = async (req, res) => {
  const friendId = req.params.friendId;
  try {
    const response = await axios.post(
      `${friendsUrl}/accept-request/${friendId}/`,
      {},
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );

    if (response.status === 200) {
      res.status(200).send(response.data);
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "acceptFriendRequest");
  }
};

exports.declineFriendRequest = async (req, res) => {
  const friendId = req.params.friendId;
  try {
    const response = await axios.post(
      `${friendsUrl}/decline-request/${friendId}/`,
      {},
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );

    if (response.status === 200) {
      res.status(200).send(response.data);
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "declineFriendRequest");
  }
};

exports.blockUser = async (req, res) => {
  const friendId = req.params.friendId;
  try {
    const response = await axios.post(
      `${friendsUrl}/block-user/${friendId}/`,
      {},
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );

    if (response.status === 200) {
      res.status(200).send(response.data);
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "blockUser");
  }
};

exports.unblockUser = async (req, res) => {
  const friendId = req.params.friendId;
  try {
    const response = await axios.post(
      `${friendsUrl}/unblock-user/${friendId}/`,
      {},
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );

    if (response.status === 200) {
      res.status(200).send(response.data);
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "unblockUser");
  }
};

exports.getplayerInfo = async (req, res) => {
  const player_id = req.params.id;
  try {
    const response = await axios.get(`${userUrl}/player_info/${player_id}/`, {
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${req.session.token["access"]}`,
      },
      httpsAgent: agent,
    });

    if (response.status === 200) {
      if (!response.data.profile_image) {
        response.data.profile_image = "/public/profile-default.svg";
      }
      res.status(200).send(response.data);
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "getplayerInfo");
  }
};
