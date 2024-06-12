import NavView from "/static/js/views/NavView.js"
import View from "/static/js/views/View.js";

class SecurityView extends View {

	constructor() {
		super();
		this._navView = new NavView("Security");
	}

	_generateMarkup() {
		const html = `
			<div class="container mt-3 pb-3">
				${this._navView._generateMarkup()}
					<div class="col-12 col-md-8 col-lg-9">
						<h2>Two-Factor Authentication</h2>
						<p>
							Two-Factor Authentication (2FA) provides an additional layer of security to help protect user accounts. With 2FA, the user passes through two layers of security when performing certain actions on the website. First the user logs in using their username and password, and then, they input a code provided through Email. This additional level of security is nearly impossible to break through and, as a result, we highly recommend that all Zong users enable 2FA.
						</p>
						<hr class="border">
						<div class="${this._data.user.twoFactorAuth ? '' : 'd-none'}">
							<div class="alert alert-success d-flex align-items-center" role="alert">
								<svg xmlns="http://www.w3.org/2000/svg" width="1.5rem" height="1.5rem" fill="currentColor" class="bi bi-check-circle-fill flex-shrink-0 me-2" viewBox="0 0 16 16">
									<path d="M16 8A8 8 0 1 1 0 8a8 8 0 0 1 16 0m-3.97-3.03a.75.75 0 0 0-1.08.022L7.477 9.417 5.384 7.323a.75.75 0 0 0-1.06 1.06L6.97 11.03a.75.75 0 0 0 1.079-.02l3.992-4.99a.75.75 0 0 0-.01-1.05z"/>
								</svg>
  								<div>
									Two-Factor authentication is enabled
  								</div>
							</div>
							<h3>Deactivate Two-Factor Authentication</h3>
							<p>Deactivating Two-Factor Authentication will completely remove it from your account. You will need to complete the entire Two-Factor Authentication setup again if you decide to activate Two-Factor Authentication again.</p>
							<button class="btn btn-outline-dark text-uppercase" data-tfa="disable-tfa">Deactivate Two-Factor Authentication</button>
						</div>
						<div class="${this._data.user.twoFactorAuth ? 'd-none' : ''}">
							<div class="mb-4">
								<h3>How to set up Two-Factor Authentication</h3>
								<ol>
									<li>
										Make sure you have a valid email associated with your <a href="/account" data-link>account</a>
									</li>
									<li>
										Click on the button below to receive an authentication code
									</li>
									<li>
										Confirm the 6-digit code provided in your email
									</li>
									<li>
										Click the submit button to finalize the two-factor authentication setup
									</li>
								</ol>
							</div>
							<div role="alert" class="alert alert-danger d-flex align-items-center">
								<svg xmlns="http://www.w3.org/2000/svg" width="1.5rem" height="1.5rem" fill="currentColor" class="bi flex-shrink-0" viewBox="0 0 16 16">
									<path d="M16 8A8 8 0 1 1 0 8a8 8 0 0 1 16 0M5.354 4.646a.5.5 0 1 0-.708.708L7.293 8l-2.647 2.646a.5.5 0 0 0 .708.708L8 8.707l2.646 2.647a.5.5 0 0 0 .708-.708L8.707 8l2.647-2.646a.5.5 0 0 0-.708-.708L8 7.293z"/>
								</svg>
								<span class="ms-2">
									Two-Factor authentication is disabled
								</span>
							</div>
							<span class="d-inline-block mb-3" tabindex="0" ${this._data.user.email ? "" : "data-bs-toggle='popover'"} data-bs-trigger="hover focus" data-bs-content="missing email">
								<button class="btn btn-dark" type="button" ${this._data.user.email ? "" : "disabled"} data-tfa="get-tfa-code">
									<span class="fw-medium text-uppercase">
										Send authentication code
									</span>
								</button>
							</span>
							<form id="tfa-form" class="${this._data.user.email ? "" : "d-none"}">
								<h4>Confirm the code from your email</h4>
								<div class="input-group mb-4">
									<input type="text" name="code" pattern="^[0-9]{6}$" maxlength="6" size="6" required autocomplete="off" class="form-control" placeholder="Code">
									<button type="submit" class="btn btn-dark">
										<span class="fw-medium text-uppercase">Submit</span>
									</button>
								</div>
							</form>
						</div>
					</div>
				</div>
			</div>
		`;
		return html;
	}

	render(data) {
		super.render(data);
		const popoverTriggerList = document.querySelectorAll('[data-bs-toggle="popover"]');
		popoverTriggerList.forEach(popoverTriggerEl => new bootstrap.Popover(popoverTriggerEl));
	}

	addHandlerTwoFactorAuth(handler) {
		document.addEventListener("click", e => {
			const button = e.target.closest("[data-tfa]");
			if (!button) return ;
			e.stopPropagation();
			const action = button.dataset.tfa;
			handler(action);
		});
		document.addEventListener("submit", e => {
			const form = e.target;
			if (form.id !== "tfa-form") return ;
			e.stopPropagation();
			e.preventDefault();
			const formData = new FormData(form);
			handler("submit-tfa-code", formData.get("code"));
		});
	}
};

export default new SecurityView();