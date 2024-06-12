import Game from "/static/js/model/game/Game.js";

import * as helper from "/static/js/helpers.js";

import WebSocketService from "/static/js/model/WebSocketService.js";
import { CHAT_URL } from "/static/js/config.js";

export const state = {
	chatSocket: new WebSocketService(CHAT_URL),
	chats: undefined,
	user: undefined,
	game: new Game(),
};

export const sendRequest = async (url, method, body) => {
	const headers = method === "POST" ?  { "X-CSRFToken": helper.getCookie("csrftoken") } : {};
	const options = {
		method,
		headers,
		body,
	};
	return await fetch(url, options);
}

export const getUserInfo = async () => {
	const url = helper.getFullUrl("user", "getUserInfo", {username: "me"});
	const response = await sendRequest(url, "GET");
	if (!response.ok)
	{
		delete state.user
		state.chatSocket.disconnect();
		throw new Error(await response.text());
	}
	const json = await response.json();
	const { User: username, Alias: alias, game_total: gamesPlayed, game_won: gamesWon, email: email, isTwoFactorEnabled: twoFactorAuth } = json;
	const gamesLost = gamesPlayed - gamesWon;
	state.user = { username, alias, gamesPlayed, gamesWon, gamesLost, email, twoFactorAuth };
	state.chats = Object.entries(json.chat).map(([user, messages]) => {
		messages.forEach(message => {
			message.date = new Date(message.date);
		});
		return {user, messages};
	});
	state.chatSocket.connect();
}

export const getOtherUserInfo = async (contactUsername) => {
	const url = helper.getFullUrl("user", "getUserInfo", {username: contactUsername});
	const response = await sendRequest(url, "GET");
	if (!response.ok) return undefined;
	const json = await response.json();
	const { User: username, Alias: alias, game_total: gamesPlayed, game_won: gamesWon, email: email, isTwoFactorEnabled: twoFactorAuth, friends: friends, online: online } = json;
	const gamesLost = gamesPlayed - gamesWon;
	const contact = { username, alias, gamesPlayed, gamesWon, gamesLost, email, twoFactorAuth, friends, online };
	return contact;
}

export const logOut = async () => {
	state.game.resetObject();
	const url = helper.getFullUrl("user", "logOut");
	const response = await sendRequest(url, "POST");
	if (response.ok)
		state.chatSocket.disconnect();
	return response;
}

export const logIn = async (data) => {
	const url = helper.getFullUrl("user", "logIn");
	const requestBody = { username: data.username, password: data.password };
	return await sendRequest(url, "POST", JSON.stringify(requestBody));
}

export const signUp = async (data) => {
	const url = helper.getFullUrl("user", "signUp");
	const requestBody = { username: data.username, password: data.password };
	return await sendRequest(url, "POST", JSON.stringify(requestBody));
}

export const saveImg = async (image) => {
	const url = helper.getFullUrl("user", "saveImg");
	const formData = new FormData();
	formData.append('Image', image);
	return await sendRequest(url, "POST", formData);
}

export const saveAlias = async (alias) => {
	const url = helper.getFullUrl("user", "saveAlias");
	const requestBody = { Alias: alias };
	return await sendRequest(url, "POST", JSON.stringify(requestBody));
}

export const saveEmail = async (email) => {
	const url = helper.getFullUrl("tfa", "saveEmail");
	const requestBody = { "email": email };
	return await sendRequest(url, "POST", JSON.stringify(requestBody));
}

export const getTfaCode = async () => {
	const url = helper.getFullUrl("tfa", "getTfaCode");
	return await sendRequest(url, "GET");
}

export const submitTfaCode = async (code) => {
	const url = helper.getFullUrl("tfa", "submitTfaCode");
	const requestBody = { "code": code };
	return await sendRequest(url, "POST", JSON.stringify(requestBody));
}

export const disableTfa = async () => {
	const url = helper.getFullUrl("tfa", "disableTfa");
	return await sendRequest(url, "POST");
}

export const addFriend = async (username) => {
	const url = helper.getFullUrl("user", "addFriend");
	const requestBody = { "username": username };
	return await sendRequest(url, "POST", JSON.stringify(requestBody));
}

export const removeFriend = async (username) => {
	const url = helper.getFullUrl("user", "removeFriend");
	const requestBody = { "username": username };
	return await sendRequest(url, "POST", JSON.stringify(requestBody));
}

export const saveMatch = async (winner, loser) => {
	const url = helper.getFullUrl("game", "saveMatch");
	const requestBody = { winner: winner.username, swinner: winner.score, loser: loser.username, sloser: loser.score };
	return await sendRequest(url, "POST", JSON.stringify(requestBody));
}

export const blockUser = async (username) => {
	const url = helper.getFullUrl("user", "blockUser");
	const requestBody = { "username": username };
	const response = await sendRequest(url, "POST", JSON.stringify(requestBody));
	return response;
}

export const unblockUser = async (username) => {
	const url = helper.getFullUrl("user", "unblockUser");
	const requestBody = { "username": username };
	return await sendRequest(url, "POST", JSON.stringify(requestBody));
}

export const getMatchData = async () => {
	const url = helper.getFullUrl("game", "getMatchData");
	const response = await sendRequest(url, "GET");
	if (!response.ok) return ;
	const json = await response.json();
	const jsonMatches = json.matches;
	const matches = [];
	jsonMatches.forEach((match) => {
		const winner = match.winner;
		const score = match.score.split(" : ").map(Number);
		if(winner !== state.user.username)
			[score[0], score[1]] = [score[1], score[0]];
		matches.push({
			date: new Date(match.date),
			opponent: winner === state.user.username ? match.loser : winner,
			result: winner === state.user.username ? "victory" : "defeat",
			score: score,
		});
	});
	matches.sort((a, b) => b.date - a.date);
	return matches;
}

export const getBlockedUsers = async () => {
	const url = helper.getFullUrl("user", "getBlockedUsers", {username: "me"});
	const response = await sendRequest(url, "GET");
	if (!response.ok)
		return [];
	const json = await response.json();
	return json.blocked;
}

export const getFriends = async () => {
	const url = helper.getFullUrl("user", "getFriends", {username: "me"});
	const response = await sendRequest(url, "GET");
	if (!response.ok)
		return [];
	const json = await response.json();
	state.friends = json.friends.map( friend => {
		const { username, alias, game_total: gamesPlayed, game_won: gamesWon, online } = friend;
    	return { username, alias, gamesPlayed, gamesWon, online };
	});
	return json.friends;
}

export const sendMessage = (message) => {
	state.chatSocket.sendMessage(message);
}

export const assignInGameQueue = (player) => {
	state.game.assignInQueue(player, state.friends);
}

export const addHandlerUploadChat = function(handler) {
	state.chatSocket.addEventListener("message", (event) => {
		const chats = JSON.parse(event.data);
		handler();
	});
}

export const sendGameNotification = function() {
	if (!state.user)
		return ;
	const userUsername = state.user.username;
	state.game.queue.forEach((player) => {
		if (player.username !== userUsername || player.alias === "Ai")
		{
			const message = {other: player.username, sender: userUsername, message: `Im starting a game with you. Come play with me!`}
			state.chatSocket.sendMessage(message);
		}
	});
}

export const addMessageHandler = (handler) => {
	console.log(state.chatSocket);
	state.chatSocket.onMessage = (data) => {
		handler();
	}
}