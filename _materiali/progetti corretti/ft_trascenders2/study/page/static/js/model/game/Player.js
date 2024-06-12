import Paddle from "/static/js/model/game/Paddle.js";

export default class {
	constructor() {
		this._username = undefined;
		this._alias = undefined;
		this._image = undefined;
		this._paddle = new Paddle();
		this._score = undefined;
		this._gamesPlayed = undefined;
		this._gamesWon = undefined;
	}
};