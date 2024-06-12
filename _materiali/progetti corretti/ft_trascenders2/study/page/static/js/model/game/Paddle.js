import GameObj from "./GameObj.js";

export default class extends GameObj {
	constructor(side) {
		super();
		this._sizeRatio = 8;
		this._width = 0;
		this._height = 0;
		this._ai = false;
		this._side = side;
		this._score = {
			color: "#fff",
			x: 0,
			y: 0,
			size: 0,
			value: 0,
		}
		this._powerUp = {
			color: "#fff",
			x: 0,
			y: 0,
			maxRadius: 0,
			step: 0,
			isVisible: false,
			sizeRatio: 2,
			interval: 0,
		}
	}

	init(canvas, speed) {
		super.init(canvas);
		this.resize(canvas, speed);
		this.scoreInit(canvas);
		this.powerUpInit(canvas);
		this.reset(canvas);
	}

	scoreInit(canvas) {
		this._score.color = canvas.innerObjsColor;
		this._score.size = canvas.height * 15 / 100;
		this._score.y = canvas.height * 2 / 100 + this.score.size;
		const x = canvas.width / 3;
		this._score.x = this._side === "left" ? x : x * 2;
	}

	powerUpInit(canvas) {
		this.powerUp.maxRadius = canvas.width * this.powerUp.sizeRatio / 100;
		this.powerUp.step = this.powerUp.maxRadius * 2 / 100;
		this._powerUp.color = canvas.innerObjsColor;
		const x = canvas.width * 4 / 100;
		this._powerUp.x = this._side === "left" ? x : canvas.width - this.powerUp.sizeRatio - x;
	}

	resize(canvas, speed) {
		super.resize(canvas, speed)
		this._height = canvas.width * this._sizeRatio / 100;
		this._width = canvas.width / 100;
		const x = canvas.width * 3 / 100;
		this._x = this._side === "left" ? x : canvas.width - this._width - x;
		if (this._y + this._height > canvas.height)
			this._y = canvas.height - this._height;
	}

	reset(canvas) {
		this._y = canvas.height / 2 - this._height / 2;
		this._direction = { x: 0, y: 0 };
		this._ai = false;
	}

	resetScore() {
		this._score.value = 0;
	}
	

	get width() {
		return this._width;
	}
	get height() {
		return this._height;
	}
	get side() {
		return this._side;
	}
	get ai() {
		return this._ai;
	}
	get score() {
		return this._score;
	}
	get powerUp() {
		return this._powerUp;
	}

	set width(value) {
		this._width = value;
	}
	set height(value) {
		this._height = value;
	}
	set side(value) {
		this._side = value;
	}
	set ai(value) {
		this._ai = value;
	}
	set score(value) {
		this._score = value;
	}
	set powerUp(value) {
		this._powerUp = value;
	}
}