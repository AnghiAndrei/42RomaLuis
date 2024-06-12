import View from "/static/js/views/View.js"

class TwoFactorAuthView extends View {
	constructor() {
		super();
	}

	_generateMarkup() {
		const html = `
			<div class="modal position-static d-block z-0" tabindex="-1">
				<div class="modal-dialog">
					<div class="modal-content">
						<div class="modal-header">
							<div class="w-100 text-center">
								<h2 class="modal-title" id="modalLabel">Two-Factor Authentication</h2>
							</div>
						</div>
						<div class="modal-body">
							<div class="w-100 text-center mb-2">
								Enter your authentication 6-digits code
							</div>
							<form id="tfa-form">
								<input type="text" name="code" pattern="^[0-9]{6}$" maxlength="6" size="6" required autocomplete="off" class="form-control mb-3" placeholder="Code">
								<button type="submit" class="btn btn-dark w-100">
									<span class="fw-medium text-uppercase">Submit</span>
								</button>
							</form>
						</div>
						<div class="modal-footer">
							<a href="/" tabindex="" title="Click to log out" class="btn btn-outline-dark" data-bs-dismiss="modal" data-auth="logout">
								<span class="fw-medium text-uppercase">Log out</span>
							</a>
						</div>
					</div>
				</div>
			</div>
		`
		return html;
	}
}

export default new TwoFactorAuthView();