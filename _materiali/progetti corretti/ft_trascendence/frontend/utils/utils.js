const jwt = require("jsonwebtoken");
const axios = require("axios");
const { authUrl, userUrl, jwtSecret } = require("../config/serverConfig");
const { agent } = require("../config/sslConfig");

const getUserInfo = async (req, res) => {
  try {
    const response = await axios.get(`${userUrl}/info`, {
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${req.session.token["access"]}`,
      },
      httpsAgent: agent,
    });

    if (response.status === 200) {
      req.session.userInfo = response.data;
      req.session.save();
      res.status(200).send();
    }
  } catch (error) {
    console.error("~get('/user/info'):", error);
    res.status(500).send();
  }
};

const getUserAuthMethods = async (req, res, next) => {
  try {
    const response = await axios.get(`${authUrl}/mfa/user-active-methods/`, {
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${req.session.token["access"]}`,
      },
      httpsAgent: agent,
    });

    if (response.status === 200) {
      req.session.MFAstatus = response.data;
    } else {
      console.error(
        "Error fetching 2FA status:",
        response.status,
        response.data,
      );
      // res.status(response.status).send("Something went wrong");
    }
  } catch (error) {
    console.error("~get('/user/2fa-status'):", error);
  }
  req.session.language = "en";
  req.session.save();
  next();
};

const checkToken = async (req, res, next) => {
  if (req.session.token) {
    const accessToken = req.session.token["access"];
    const refreshToken = req.session.token["refresh"];

    const decoded = jwt.decode(accessToken);
    if (decoded.exp <= Date.now() / 1000) {
      try {
        const response = await axios.post(
          `${authUrl}/token/refresh`,
          { refresh: refreshToken },
          {
            headers: {
              "Content-Type": "application/json",
            },
            httpsAgent: agent,
          },
        );
        if (response.status === 200) {
          req.session.token = response.data;
          req.session.save();
        } else {
          req.session.token = null;
          res.status(401).send({ message: "Please log in again" });
          return;
        }
      } catch (error) {
        console.error("~refresh token:", error);
        res
          .status(500)
          .send({ message: "An error occurred while refreshing the token" });
        return;
      }
    }
  }
  next();
};

const handleResponse = async (axiosResponse, res, req) => {
  const data = axiosResponse.data; // Directly access data sent by the server
  const AccessToken = data["access"];
  const tokenValidation = jwt.verify(AccessToken, jwtSecret, function (err) {
    return !err;
  });
  if (tokenValidation) {
    req.session.token = data;
    res.status(200).send();
  } else {
    throw new Error("Invalid token");
  }
};

function sanitizeErrorMessage(errorObject) {
  let cleanedErrors = [];

  for (let property in errorObject) {
    if (typeof errorObject[property] === "string") {
      cleanedErrors.push(`${property}: ${errorObject[property]}`);
    }
  }
  return cleanedErrors.join("\n");
}

function handleCatchesApiCall(res, error, functionName) {
  if (error.response) {
    console.log(`Error data in ${functionName} :`, error.response.data);
    res.status(error.response.status).send(error.response.data);
  } else if (error.request) {
    console.log("No response received:", error.request);
    res.status(500).send("No response received from the server.");
  } else {
    console.log("Error", error.message);
    res.status(500).send(`Request setup error: ${error.message}`);
  }
}

module.exports = {
  checkToken,
  handleResponse,
  sanitizeErrorMessage,
  getUserAuthMethods,
  getUserInfo,
  handleCatchesApiCall,
};
