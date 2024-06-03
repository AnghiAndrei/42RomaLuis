const express = require("express");
const cors = require("cors");
const dotenv = require("dotenv");
const app = express();
const {
  helmetConfig,
  corsOptions,
  limiter,
  credentials,
} = require("./sslConfig");
const {
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
} = require("../middleware/serverMiddleware");
const https = require("https");
const { sessionConfig } = require("./sessionConfig");
const bodyParser = require("body-parser");

app.use(sessionConfig);
app.use(secureHeaders);
// app.use(loggingService);
app.use(nonce);
app.use(helmetConfig);
app.use(cors(corsOptions));
app.use(limiter);
app.use("/src", serveSrc);
app.use("/node_modules", serveNodeModules);
app.use("/public", servePublic);
app.use("/styles", serveStyles);
app.use("/user_images", serveUserImages);
app.use(serveViews);
app.use(serveFavicon);
app.use(express.json());
// app.use(bodyParser.json({ limit: "50mb" }));
// app.use(bodyParser.urlencoded({ limit: "50mb", extended: true }));

dotenv.config({ path: ".env" }); //NODE_TLS_REJECT_UNAUTHORIZED
const httpsServer = https.createServer(credentials, app);

const ip = process.env.BASE_IP;
const authIp = process.env.BACKEND_AUTH_IP;
const userIp = process.env.BACKEND_USER_IP;
const gameIp = process.env.BACKEND_GAME_IP;
const friendsIp = process.env.BACKEND_FRIENDS_IP;
const port = process.env.BASE_PORT;
const backPort = process.env.BACKEND_PORT;
const authUrl = `https://${authIp}:${backPort}`;
const userUrl = `https://${userIp}:${backPort}`;
const gameUrl = `https://${gameIp}:${backPort}`;
const friendsUrl = `https://${friendsIp}:${backPort}`;
const jwtSecret = process.env.JWT_SECRET;

module.exports = {
  app,
  httpsServer,
  ip,
  port,
  authUrl,
  userUrl,
  gameUrl,
  friendsUrl,
  jwtSecret,
  backPort,
};
