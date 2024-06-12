import View from "/static/js/views/View.js"

class NotAuthorizedView extends View {
	
	constructor() {
		super();
	}

	_generateMarkup() {
		return `
			<div class="text-center py-5">
				<h1 class="display-1">401</h1>
				<h2>Login required</h2>
			</div>
		`;
	}
};

export default new NotAuthorizedView();
