const helmet = require("helmet");
const rateLimit = require("express-rate-limit");
const fs = require("fs");
const https = require("https");

const helmetConfig = (req, res, next) => {
  helmet({
    contentSecurityPolicy: {
      directives: {
        defaultSrc: ["'self'"],
        scriptSrc: ["'self'", `'nonce-${res.locals.nonce}'`],
        imgSrc: ["'self'", "data:", "https://cdn.intra.42.fr"], // Add the domain here
        objectSrc: ["'none'"],
        upgradeInsecureRequests: [],
        connectSrc: ["'self'", "wss://0.0.0.0:8000"], // Add your WebSocket URL here
      },
    },
    crossOriginOpenerPolicy: {
      policy: "unsafe-none",
    },
  })(req, res, next);
};

const corsOptions = {
  origin: function (origin, callback) {
    if (origin !== undefined) {
      console.log("Origin:", origin);
    }
    const allowedOrigins = [
      `https://${process.env.BASE_IP}:${process.env.BASE_PORT}`,
      `wss://0.0.0.0:8000/ws/chat/ss/`,
    ];
    if (origin === undefined || origin === null) {
      callback(null, true);
    } else if (allowedOrigins.includes(origin)) {
      callback(null, true);
    } else {
      callback(new Error("Not allowed by CORS"));
    }
  },
  optionsSuccessStatus: 200,
};

const limiter = rateLimit({
  windowMs: 3 * 60 * 1000, // 3 minutes
  max: 1000, // Limit each IP to X requests per windowMs
});

const sslPass = process.env.SSL_PASS;
const privateKey = fs.readFileSync("./ssl/cert-key.pem", "utf8");
const certificate = fs.readFileSync("./ssl/fullchain.pem", "utf8");
const DjangoCertificate = fs.readFileSync("./back_ssl/fullchain.pem", "utf8");

const agent = new https.Agent({
  ca: DjangoCertificate,
  rejectUnauthorized: true,
});

const credentials = { key: privateKey, cert: certificate, passphrase: sslPass };

module.exports = { helmetConfig, corsOptions, limiter, agent, credentials };
