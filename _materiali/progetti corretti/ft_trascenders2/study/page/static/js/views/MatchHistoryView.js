import NavView from "/static/js/views/NavView.js"
import View from "/static/js/views/View.js";

class MatchHistoryView extends View {

	constructor() {
		super();
		this._navView = new NavView("Match history");
	}

	_generateMatchListMarkup() {
		if (!this._data.matches.length)
			return `<p class="text-center h3 text-muted py-5">No matches</p>`;
		let html = `
			<table class="table">
				<thead class="table-dark">
					<tr>
						<th>Date</th>
						<th>Opponent</th>
						<th>Score</th>
						<th>Result</th>
					</tr>
				</thead>
				<tbody>
		`
		this._data.matches.forEach(match => {
			html += `
					<tr class="table-${match.result === "victory" ? "success" : "danger"}">
						<td>${this._generateFormattedDateMarkup(match.date)}</td>
						<td>${match.opponent}</td>
						<td>${match.score[0]}-${match.score[1]}</td>
						<td>${match.result}</td>
					</tr>
			`;
		});
		html += `
				</tbody>
			</table>
		`
		return html;
	}

	_generateMarkup() {
		return `
		<div class="container mt-3 pb-3">
			${this._navView._generateMarkup()}
				<div class="col-12 col-md-8 col-lg-9">
					${this._generateMatchListMarkup()}
				</div>
			</div>
		</div>
		`;
	}
};

export default new MatchHistoryView();