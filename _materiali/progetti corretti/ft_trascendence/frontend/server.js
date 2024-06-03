const path = require("path");
const { app, httpsServer, port, ip } = require("./config/serverConfig");
const WebSocket = require("ws");
const wss = new WebSocket.Server({ server: httpsServer });

const authRoutes = require("./routes/authRoutes");
const userRoutes = require("./routes/userRoutes");
const gameRoutes = require("./routes/gameRoutes");
//
// let waitingPlayer = null;
//
// wss.on("connection", function connection(ws) {
//   console.log("A new player connected.");
//
//   if (waitingPlayer === null) {
//     // Nessun giocatore è in attesa, quindi questo giocatore deve attendere
//     waitingPlayer = ws;
//     waitingPlayer.send(JSON.stringify({ type: "WAITING_FOR_PLAYER" }));
//     console.log("Player is waiting for an opponent.");
//   } else {
//     // Abbina questo giocatore con il giocatore in attesa
//     const opponent = waitingPlayer;
//     waitingPlayer = null;
//
//     ws.send(JSON.stringify({ type: "GAME_START", role: "Player 1" }));
//     opponent.send(JSON.stringify({ type: "GAME_START", role: "Player 2" }));
//
//     console.log("Match found, game starts.");
//
//     // Gestisci la disconnessione
//     ws.on("close", () => {
//       opponent.send(JSON.stringify({ type: "OPPONENT_DISCONNECTED" }));
//     });
//     opponent.on("close", () => {
//       ws.send(JSON.stringify({ type: "OPPONENT_DISCONNECTED" }));
//     });
//   }
// });

app.use("/auth", authRoutes);
app.use("/user", userRoutes);
app.use("/game", gameRoutes);

app.get("*", (req, res) => {
  console.log("NOT ABLE TO SERVE url: ", req.url);
  res.sendFile(path.join(__dirname, "views", "index.html"));
});

// Avvia il server
httpsServer.listen(port, ip, () => {
  console.log(`Server running at https://${ip}:${port}/`);
});
