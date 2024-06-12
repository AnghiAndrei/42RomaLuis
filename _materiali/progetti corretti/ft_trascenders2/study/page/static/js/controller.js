import * as model from "/static/js/model/model.js";
const { game } = model.state;

import { API_42 } from "/static/js/config.js"

import headerView from "/static/js/views/HeaderView.js";
import footerView from "/static/js/views/FooterView.js";
import mainPageView from "/static/js/views/MainPageView.js";
import pongView from "/static/js/views/PongView.js";
import accountView from "/static/js/views/AccountView.js";
import matchHistoryView from "./views/MatchHistoryView.js";
import otherUsersView from "/static/js/views/OtherUsersView.js"
import messagesView from "/static/js/views/MessagesView.js"
import chatView from "/static/js/views/ChatView.js";
import securityView from "/static/js/views/SecurityView.js";
import twoFactorAuthView from "/static/js/views/TwoFactorAuthView.js";
import notAuthorizedView from "/static/js/views/NotAuthorizedView.js"
import notFoundView from "/static/js/views/NotFoundView.js"
import alertView from "/static/js/views/AlertView.js";

const routes = {
	401: { view: notAuthorizedView, requiresAuth: false },
	404: { view: notFoundView, requiresAuth: false },
	"/": { view: mainPageView, requiresAuth: false },
	"/account": { view: accountView, requiresAuth: true },
	"/match-history": { view: matchHistoryView, requiresAuth: true },
	"/messages": { view: messagesView, requiresAuth: true },
	"/messages/:contact": { view: chatView, requiresAuth: true },
	"/other-users": { view: otherUsersView, requiresAuth: true },
	"/security": { view: securityView, requiresAuth: true },
};

const controlTwoFactorAuth = () => {
	model.getTfaCode();
	history.pushState(null, null, "two-factor-authentication");
	headerView.clearMarkup();
	footerView.clearMarkup();
	twoFactorAuthView.render();
	alertView.render();
};

const authorizeGameplay = async () => {
	alertView.clearMarkup();
	try { await model.getUserInfo(); }
	catch (error) { }
	const modeSelected = game.modes.find( mode => mode.isSelected );
	if (!model.state.user && modeSelected.requiresAuth) {
		const route = routes[401];
		headerView.render(model.state);
		footerView.render();
		return route.view.render();
	}
	headerView.clearMarkup();
	footerView.clearMarkup();
}

const controlPreGame = async () => {
	authorizeGameplay();
	model.sendGameNotification();
	history.pushState(null, null, "pong");
	game.matchMaking();
	await pongView.render(model.state);
	pongView.renderPreGame(model.state);
	game.init(document.querySelector("canvas"));
	pongView.draw(game);
};

const controlGameInteractions = (event) => {
	event.type === "keydown" && game.redirectPaddle(event);
	(event.type === "mousedown" || event.type === "touchstart") && game.redirectPaddle(event);
	event.type === "keyup" && game.stopPaddle(event);
	(event.type === "mouseup" || event.type === "mouseleave" || event.type === "touchend") && game.stopPaddle(event);
}

const controlPostGame = async () => {
	authorizeGameplay();
	const timerDomElement = document.querySelector("#timer");
	const domMinutes = timerDomElement.querySelector("#minutes");
	const domSeconds = timerDomElement.querySelector("#seconds");

	await game.timer(domMinutes, domSeconds);
	const { winner, loser } = await game.decretWinner();
	game.resetGame();
	if (game.modes.find( mode => mode.isSelected).name !== "practice")
		model.saveMatch(winner, loser);
	game.prunePlayers();
	game.pushWinner(winner);
	if (game.queue.length !== 1) return pongView.renderPreGame(model.state);
	pongView.renderPostGame(winner);
	pongView.removeListeners(controlGameInteractions);
}

const controlInGame = async () => {
	authorizeGameplay();
	let lastTime = 0;
	let delta = 0;

	const animation = function(time) {
		if (location.pathname !== "/pong") return;
		if (lastTime) {
			if (delta < 700) {
				pongView.draw(game);
				game.update(delta);
				if (!game.isRunning) return;
			}
			delta = time - lastTime;
		}
		lastTime = time;
		requestAnimationFrame(animation);
	};

	pongView.addHandlerView(controlGameInteractions);
	game.isRunning = true;
	await pongView.render(model.state);
	game.init(document.querySelector("canvas"));
	controlPostGame();
	game.powerUps && game.displayPowerUps();
	game.paddle2.ai && game.predictBallY();
	requestAnimationFrame(animation);
};

const gameActions = {
	"change-mode": { function: game.changeMode.bind(game), higherLevel: false },
	"game-customization": { function: game.changeCustomization.bind(game), higherLevel: false },
	"reset-queue": { function: game.resetQueue.bind(game), higherLevel: false },
	"choose-player": { function: model.assignInGameQueue, higherLevel: false },
	"play-pong": { function: controlPreGame, higherLevel: true },
	"start-game": { function: controlInGame, higherLevel: true },
};

const controlUserGameInputs = async (input, data) => {
	const functionToCall = gameActions[input];
	functionToCall.function(data);
	if (functionToCall.higherLevel) return;
	mainPageView.render(model.state);
};

const control42Auth = () => {
	window.location.replace(API_42);
}

const controlContactSearch = (username) => {
	history.pushState(null, null, `/messages/${username}`);
};

const actions = {
	"add-friend": model.addFriend,
	"remove-friend": model.removeFriend,
	"block-user": model.blockUser,
	"unblock-user": model.unblockUser,
	"get-tfa-code": model.getTfaCode,
	"submit-tfa-code": model.submitTfaCode,
	"disable-tfa": model.disableTfa,
	"login": model.logIn,
	"signup": model.signUp,
	"auth42": control42Auth,
	"logout": model.logOut,
	"save-image": model.saveImg,
	"save-alias": model.saveAlias,
	"save-email": model.saveEmail,
	"search-contact": controlContactSearch,
};


const matchRoute = (pathname) => {
	for (const [route, config] of Object.entries(routes)) {
		const paramNames = [];
		const regexPath = route.replace(/:([^\/]+)/g, (_, key) => {
			paramNames.push(key);
			return '([^\/]+)';
		});
		const regex = new RegExp(`^${regexPath}$`);
		const match = pathname.match(regex);
		if (match)
		{
			const params = paramNames.reduce((acc, paramName, index) => {
				acc[paramName] = match[index + 1];
				return acc;
			}, {});
			return { ...config, params };
		}
	}
	return routes[404];
}

const renderView = async () => {
	try {
		await model.getUserInfo();
	} catch (error) {
		if (error.message === "Two-factor authentication code required.")
		{
			controlTwoFactorAuth();
			return ;
		}
	}
	game.isRunning && game.resetGame();
	game.queueCompose(model.state.user);
	let route = matchRoute(location.pathname);
	if (route.requiresAuth && !model.state.user)
		route = routes[401];
	if (route.view === chatView)
	{
		const contactInfo = await model.getOtherUserInfo(route.params.contact);
		if (!contactInfo) route = routes[404];
		else route.params.contact = contactInfo;
	}
	if (route.view === matchHistoryView)
		route.params.matches = await model.getMatchData();
	if (route.view === otherUsersView)
	{
		route.params.blockedUsers = await model.getBlockedUsers();
		route.params.friends = await model.getFriends();
	}
	if (route.view === mainPageView)
		route.params.friends = await model.getFriends();
	alertView.render();
	headerView.render(model.state);
	route.view.render( {...model.state, ...route.params} );
	footerView.render();
};

const controlUserInputs = async (input, data) => {
	const functionToCall = actions[input];
	const response = await functionToCall(data);
	if (response)
	{
		const status = response.ok ? "success" : "danger";
		alertView.data = { message: await response.text(), type: status };
	}
	if (input === "login" || input === "signup" || input === "logout")
		history.pushState(null, null, "/");
	renderView();
};

const handleLinkClick = (e) => {
	const link = e.target.closest("[data-link]");
	if (!link) return;
	e.preventDefault();
	history.pushState(null, null, link.href);
	alertView.clearMarkup();
	renderView();
}

const handleChatSocket = () => {
	const path = location.pathname.split("/");
	if (path[1] === "messages")
		renderView();
}

const controlUserMessages = (message) => {
	model.sendMessage(message);
}

const init = async () => {
	document.addEventListener("DOMContentLoaded", renderView);
	window.addEventListener("popstate", renderView);
	document.addEventListener("click", handleLinkClick);

	headerView.addHandlerAuth(controlUserInputs);
	mainPageView.addHandlerCustomization(controlUserGameInputs);
	accountView.addHandlerCustomization(controlUserInputs);
	securityView.addHandlerTwoFactorAuth(controlUserInputs);
	otherUsersView.addHandlerUsers(controlUserInputs);
	messagesView.addHandlerListener(controlUserInputs);
	chatView.addEventHandler(controlUserMessages);

	model.addMessageHandler(handleChatSocket);
};

init();
