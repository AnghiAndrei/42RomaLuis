export default class {

	constructor() {
		this._parentElement = document.getElementById("mainViewPlaceholder");
		this._data = undefined;
	}

	clearMarkup() {
		this._parentElement.innerHTML = '';
		this._data = undefined;
	}

	_generateMarkup() {
		return ``;
	}

	async render(data) {
		this.clearMarkup();
		this._data = data;
		const markup = this._generateMarkup();
		this._parentElement.insertAdjacentHTML('afterbegin', markup);
	}

	update(data) {
		this._data = data;
		const newMarkup = this._generateMarkup();
		const newDom = document.createRange().createContextualFragment(newMarkup);
		const newElements = Array.from(newDom.querySelectorAll('*'));
		const currElements = Array.from(this._parentElement.querySelectorAll('*'));

		for (let i = 0; i < newElements.length && i < currElements.length; i++) {
			const newEl = newElements[i];
			const currEl = currElements[i];
			if (currEl && !newEl.isEqualNode(currEl))
				currEl.innerHTML = newEl.innerHTML;
		}
	}

	get data() {
		return this._data;
	}

	set data(data) {
		this._data = data;
	}

	_generateFormattedDateMarkup(date) {
		const day = date.getDate().toString().padStart(2, '0');
		const month = (date.getMonth() + 1).toString().padStart(2, '0');
		const year = date.getFullYear().toString().slice(-2);

		const formattedDate = `${day}.${month}.${year}`;

		const html = `
			<span>
				${formattedDate}
			</span>
			<span class="d-none d-sm-inline ms-1">
				${date.toLocaleTimeString(undefined, { hour: "numeric", minute: "numeric" })}
			</span>
		`;
		return html;
	}
};
