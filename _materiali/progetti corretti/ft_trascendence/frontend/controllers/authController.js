// authController.js

const axios = require("axios");
const jwt = require("jsonwebtoken");
const { authUrl, jwtSecret } = require("../config/serverConfig");
const { agent } = require("../config/sslConfig");
const {
  handleResponse,
  sanitizeErrorMessage,
  handleCatchesApiCall,
} = require("../utils/utils");
const e = require("express");

exports.login = async (req, res, next) => {
  const formData = req.body;
  try {
    const response = await axios.post(`${authUrl}/login/`, formData, {
      headers: {
        "Content-Type": "application/json",
      },
      httpsAgent: agent,
    });
    if (response.data.ephemeral_token) {
      res.status(202).send(response.data.ephemeral_token);
    } else if (response.data.access) {
      await handleResponse(response, res, req);
      next();
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "login");
  }
};

exports.confirm2FALogin = async (req, res, next) => {
  const formData = req.body;
  try {
    const response = await axios.post(`${authUrl}/login/code/`, formData, {
      headers: {
        "Content-Type": "application/json",
      },
      httpsAgent: agent,
    });
    if (response.data.access) {
      await handleResponse(response, res, req);
      next();
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "confirm2FALogin");
  }
};

exports.logout = async (req, res) => {
  req.session.token = null;
  res.status(200).send({ message: "Logged out successfully" });
};

exports.register = async (req, res, next) => {
  const formData = req.body;
  try {
    const response = await axios.post(`${authUrl}/register_api`, formData, {
      headers: {
        "Content-Type": "application/json",
      },
      httpsAgent: agent,
    });

    if (response.status === 200) {
      await handleResponse(response, res, req);
      next();
    }
  } catch (error) {
    let errorMessage = "An error occurred while processing your request.";
    if (error.response && error.response.data && error.response.data.errors) {
      errorMessage = sanitizeErrorMessage(error.response.data.errors);
    }
    res.status(400).send(errorMessage);
  }
};

exports.oauth_42 = async (req, res, next) => {
  const code = req.query.code;
  const nonce = res.locals.nonce;
  try {
    const response = await axios.post(
      `${authUrl}/oauth_42`,
      { code: code },
      {
        headers: {
          "Content-Type": "application/json",
        },
        httpsAgent: agent,
      },
    );

    if (response.status === 200) {
      const AccessToken = response.data["access"];
      const tokenValidation = jwt.verify(AccessToken, jwtSecret, (err) => !err);

      if (tokenValidation) {
        req.session.token = response.data;
        res.status(200).send(`
          <script nonce="${nonce}">
            window.opener.routeWholeHtml('index.html');
            window.close();
          </script>
        `);
        next();
      } else {
        throw new Error("Invalid token");
      }
    } else if (response.status === 202) {
      res.status(200).send(`
          <script nonce="${nonce}">
            window.close();
            window.opener.promptForCodeAndSend("${response.data.ephemeral_token}");
          </script>
        `);
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "oauth_42");
  }
};

exports.auth_42 = async (req, res) => {
  const auth_url = `${authUrl}/auth_42`;
  try {
    const response = await axios.get(auth_url, {
      httpsAgent: agent,
    });

    res.status(response.status).send(response.data);
  } catch (error) {
    handleCatchesApiCall(res, error, "auth_42");
  }
};

exports.get2FAStatus = async (req, res) => {
  if (req.session.MFAstatus && req.session.MFAstatus.length > 0) {
    res.status(200).send(req.session.MFAstatus);
  } else {
    res.status(204).send();
  }
};

exports.activate2FA = async (req, res) => {
  try {
    const formData = {
      email: process.env.EMAIL,
    };
    const response = await axios.post(`${authUrl}/email/activate/`, formData, {
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${req.session.token["access"]}`,
      },
      httpsAgent: agent,
    });
    if (response.status === 200) {
      res.status(200).send("Settings updated");
    } else {
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "activate2FA");
  }
};

exports.confirm2FAactivation = async (req, res, next) => {
  const code = req.body.confirmationCode;
  const formData = {
    code: code,
  };
  try {
    const response = await axios.post(
      `${authUrl}/email/activate/confirm/`,
      formData,
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );
    if (response.status === 200) {
      res.status(200).send(code);
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "confirm2FAactivation");
  }
  next();
};

exports.deactivate2FA = async (req, res) => {
  try {
    const response = await axios.post(
      `${authUrl}/code/request/`,
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
      res.status(200).send("Settings updated");
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "deactivate2FA");
  }
};

exports.confirm2FADeactivation = async (req, res, next) => {
  const code = req.body.confirmationCode;
  const formData = {
    code: code,
  };
  try {
    const response = await axios.post(
      `${authUrl}/email/deactivate/`,
      formData,
      {
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${req.session.token["access"]}`,
        },
        httpsAgent: agent,
      },
    );
    if (response.status === 204) {
      res.status(200).send("Settings updated");
    }
  } catch (error) {
    handleCatchesApiCall(res, error, "confirm2FADeactivation");
  }
  next();
};
