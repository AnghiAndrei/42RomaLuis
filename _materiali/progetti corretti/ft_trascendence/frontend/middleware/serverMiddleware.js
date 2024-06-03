const crypto = require("crypto");
const express = require("express");
const path = require("path");
const favicon = require("serve-favicon");

const secureHeaders = (req, res, next) => {
  res.setHeader("X-Frame-Options", "DENY");
  res.setHeader("X-Content-Type-Options", "nosniff");
  res.setHeader("Referrer-Policy", "no-referrer");
  next();
};

const loggingService = (req, res, next) => {
  console.log("Request received:", req.url);
  next();
};

const nonce = (req, res, next) => {
  // Generate a nonce to be used with CSP
  res.locals.nonce = crypto.randomBytes(16).toString("hex");
  next();
};

const serveSrc = express.static(path.join(__dirname, "../src"), {
  setHeaders: function (res, path, stat) {
    if (path.endsWith(".js")) {
      res.setHeader("Content-Type", "application/javascript");
    }
  },
});

const serveNodeModules = express.static(
  path.join(__dirname, "../node_modules"),
);
const servePublic = express.static(path.join(__dirname, "../public"));
const serveStyles = express.static(path.join(__dirname, "../styles"));
const serveViews = express.static(path.join(__dirname, "../views"));
const serveFavicon = favicon(path.join(__dirname, "../public", "favicon.ico"));
const serveUserImages = express.static(path.join(__dirname, "../user_images"));

module.exports = {
  secureHeaders,
  loggingService,
  nonce,
  serveSrc,
  serveNodeModules,
  servePublic,
  serveStyles,
  serveViews,
  serveFavicon,
  serveUserImages,
};
