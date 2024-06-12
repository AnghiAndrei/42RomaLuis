import View from "/static/js/views/View.js"

class NotFoundView extends View {
	
	constructor() {
		super();
	}

	_generateMarkup() {
		return `
			<div class="text-center py-5">
				<h1 class="display-1">404</h1>
				<h2>File not found</h2>
			</div>
		`;
	}
};

export default new NotFoundView();
