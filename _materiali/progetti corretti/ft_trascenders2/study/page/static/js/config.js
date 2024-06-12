const ip = "10.11.13.1";
const ZongPort = 8443;

export const CHAT_URL = `wss://${ip}:${ZongPort}/wss/chat/1/`;

export const API_42 = `https://api.intra.42.fr/oauth/authorize?client_id=u-s4t2ud-ab59fc71f7b7652d5f41a4fcd4a00faa23d9e7cb45aa7999f919b0d7eae26bc9&redirect_uri=https%3A%2F%2F10.11.13.1%3A8443%2Fuser%2FgetData&response_type=code`;

export const ENDPOINTS = {
	apiBaseUrl: `https://${ip}:${ZongPort}`,
	user: {
		baseUrl: `/user`,
		endpoints: {
			signUp: `/register`,
			logIn: `/authenticate`,
			logOut: `/logout`,
			saveAlias: `/updateAlias`,
			saveImg: `/updateImage`,
			getUserInfo: `/getUserData/:username`,
			addFriend: `/addFriend`,
			removeFriend: `/removeFriend`,
			blockUser: `/blockUser`,
			unblockUser: `/removeBlocked`,
			getBlockedUsers: `/getUserBlocked/:username`,
			getFriends: `/getUserFriend/:username`,
		}
	},
	tfa: {
		baseUrl: `/2f`,
		endpoints: {
			saveEmail: `/saveMail`,
			getTfaCode: `/sendMail`,
			submitTfaCode: `/checkCode`,
			disableTfa: `/disablewTwof`,
		}
	},
	game: {
		baseUrl: `/game`,
		endpoints: {
			getMatchData: `/getMatchData`,
			saveMatch: `/showWinner`,
		}
	}
}

export const GUEST = { alias: "Guest", image: "/static/images/guest_profile_image.png" };
export const AI = { alias: "Ai", image: "/static/images/ai_profile_image.png" };
export const UNDEFINED_PLAYER = { alias: undefined, image: "/static/images/undefined_profile_image.svg" };

export const STARTING_SPEED = 0.04;
export const SPEED_LEVELS = [ 0.04, 0.06, 0.08, 0.1 ];
export const TIME_LIMITS = [ 30, 60, 90, 120 ];
export const MAPS = [
	{ boardColor: "#000", innerColor: "#fff" },
	{ boardColor: "#0b310f", innerColor: "#a1c0d6" },
	{ boardColor: "#5a1a1a", innerColor: "#ddb9d9" },
];
