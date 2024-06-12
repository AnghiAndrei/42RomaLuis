import GameObj from "./GameObj.js";

export default class extends GameObj {
	constructor() {
		super();
		this._sizeRatio = 1;
		this._radius = 0;
	}

	init(canvas, speed) {
		super.init(canvas, speed);
		this.resize(canvas, speed);
		this.reset(canvas);
	}

	resize(canvas, speed) {
		super.resize(canvas, speed);
		this._radius = canvas.width * this._sizeRatio / 100;
		if (this._x + this._radius > canvas.width)
			this._x = canvas.width - this._radius;
		if (this._y + this._radius > canvas.height)
			this._y = canvas.height - this._radius;
	}

	reset(canvas) {
		this._x = canvas.width / 2;
		this._y = canvas.height / 2;
		this._direction.y = 0;
		this._direction.x = Math.random() < 0.5 ? 1 : -1;
	}
	

	get radius() {
		return this._radius;
	}

	set radius(value) {
		this._radius = value;
	}
}