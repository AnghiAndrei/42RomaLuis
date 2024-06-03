const session = require("express-session");
const crypto = require("crypto");

const sessionConfig = session({
  secret: crypto.randomBytes(64).toString("hex"),
  resave: false,
  saveUninitialized: false,
  cookie: {
    secure: true,
    httpOnly: true,
    maxAge: 1000 * 60 * 60 * 24, // 24 hours
  },
});

module.exports = { sessionConfig };
