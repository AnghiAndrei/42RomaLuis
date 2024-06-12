export default class {
	constructor() {
		this._x = 0;
		this._y = 0;
		this._speed = 0;
		this._direction = { x: 0, y: 0 };
		this._color = "#fff";
	}

	init(canvas) {
		this._color = canvas.innerObjsColor;
	}

	resize(canvas, speed) {
		this._speed = canvas.width * speed / 100;
	}

	move(delta) {
		this._x += this._direction.x * this._speed * delta;
		this._y += this._direction.y * this._speed * delta;
	}


	get x() {
		return this._x;
	}
	get y() {
		return this._y;
	}
	get sizeRatio() {
		return this._sizeRatio;
	}
	get speed() {
		return this._speed;
	}
	get speedRatio() {
		return this._speedRatio;
	}
	get direction() {
		return this._direction;
	}
	get color() {
		return this._color;
	}

	set x(value) {
		this._x = value;
	}
	set y(value) {
		this._y = value;
	}
	set sizeRatio(value) {
		this._sizeRatio = value;
	}
	set speed(value) {
		this._speed = value;
	}
	set speedRatio(value) {
		this._speedRatio = value;
	}
	set direction(value) {
		this._direction = value;
	}
	set color(value) {
		this._color = value;
	}
}