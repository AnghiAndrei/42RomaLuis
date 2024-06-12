export default class {
	constructor() {
		this._boardColor = "#000";
		this._innerObjsColor = "#fff";
		this._domElement = undefined;
		this._width = undefined;
		this._height = undefined;
		this._stroke = {
			size: 0,
			dash: 0,
		};
	}

	init(info) {
		this._domElement = info.domElement;
		this._boardColor = info.boardColor;
		this._innerObjsColor = info.innerColor;
		this.resize();
	}

	resize() {
		const rect = this._domElement.getBoundingClientRect();
		this._domElement.width = rect.width;
		this._domElement.height = rect.height;
		this._width = this._domElement.width;
		this._height = this._domElement.height;
		this._stroke.size = rect.width / (100 * 2);
		this._stroke.dash = rect.height / 50;
	}


	get boardColor() {
		return this._boardColor;
	}
	get innerObjsColor() {
		return this._innerObjsColor;
	}
	get domElement() {
		return this._domElement;
	}
	get width() {
		return this._width;
	}
	get height() {
		return this._height;
	}
	get stroke() {
		return this._stroke;
	}
	
	set boardColor(value) {
		this._boardColor = value;
	}
	set innerObjsColor(value) {
		this._innerObjsColor = value;
	}
	set domElement(value) {
		this._domElement = value;
	}
	set width(value) {
		this._width = value;
	}
	set height(value) {
		this._height = value;
	}
	set stroke(value) {
		this._stroke = value;
	}
}