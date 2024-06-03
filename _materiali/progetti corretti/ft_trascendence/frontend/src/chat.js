var ws = new WebSocket("wss://0.0.0.0:8000/ws/chat/ss/");

var chatInput = document.querySelector("#chat-input");
var chatSubmitButton = document.querySelector("#chat-message-submit");
var blockInput = document.querySelector("#block-user");
var blockButton = document.querySelector("#block-button");
var inviteInput = document.querySelector("#invite-to-game");
var inviteButton = document.querySelector("#invite-button");
var chatWindow = document.querySelector("#chat-window");

ws.onopen = function (e) {
  console.log("Chat socket successfully connected.");
};

ws.onclose = function (e) {
  console.log("Chat socket closed unexpectedly");
};

ws.onmessage = function (e) {
  var data = JSON.parse(e.data);
  var message = data.message;
  console.log("Message received: ", data.message);
  chatWindow.textContent += message + "\n";
};

function sendMessage(e) {
  var message = chatInput.value;
  console.log("sending message", message);
  ws.send(
    JSON.stringify({
      message: message,
    }),
  );
  chatInput.value = "";
}

function blockUser(e) {
  var userToBlock = blockInput.value;
  console.log("blocking user", userToBlock);
  ws.send(
    JSON.stringify({
      action: "block_user",
      user: userToBlock,
    }),
  );
  blockInput.value = "";
}

function inviteToGame(e) {
  var userToInvite = inviteInput.value;
  console.log("inviting user", userToInvite, "to game");
  ws.send(
    JSON.stringify({
      action: "invite_to_game",
      user: userToInvite,
    }),
  );
  inviteInput.value = "";
}

chatSubmitButton.addEventListener("click", sendMessage);
// blockButton.addEventListener('click', blockUser);
// inviteButton.addEventListener("click", inviteToGame);

chatInput.addEventListener("keyup", function (e) {
  if (e.keyCode === 13) {
    // enter, return
    sendMessage(e);
  }
});
