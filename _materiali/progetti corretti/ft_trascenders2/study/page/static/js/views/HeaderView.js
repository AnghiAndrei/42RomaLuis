import View from "/static/js/views/View.js";

class HeaderView extends View {

	constructor() {
		super();
		this._parentElement = document.querySelector("header");
	}

	_generateMarkup() {
		return `
			<div class="navbar justify-content-center sticky-top bg-white border-bottom shadow-sm" style="height: 4rem">
				<div class="container-fluid d-flex align-items-center justify-content-center">
					<div class="row w-100 align-items-center">
						<div class="col-4 col-lg-3">
							<a id="home" href="/" tabindex="1" role="button" class="fs-3 text-decoration-none link-body-emphasis" data-link>ZONG</a>
						</div>
						<div class="col-4 col-lg-8 col-xl-7 col-xxl-6">
							<div class="d-none ${this._data.user ? "" : "d-lg-flex"} justify-content-center align-items-center">
								<form class="d-flex align-items-center auth-form">
									<div class="input-group input-group-sm pe-2">
										<span class="input-group-text">
											<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-person-fill mb-1" viewBox="0 0 16 16">
												<path d="M3 14s-1 0-1-1 1-4 6-4 6 3 6 4-1 1-1 1zm5-6a3 3 0 1 0 0-6 3 3 0 0 0 0 6"/>
											</svg>
										</span>
										<input type="text" name="username" placeholder="Username" tabindex="2" class="form-control" required autocomplete="username" minlength="4" maxlength="10" pattern="^[a-zA-Z0-9_]+$" title="Username should only contain letters, numbers, and underscores.">
									</div>
									<div class="input-group input-group-sm pe-2">
										<span class="input-group-text">
											<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-key-fill mb-1" viewBox="0 0 16 16">
												<path d="M3.5 11.5a3.5 3.5 0 1 1 3.163-5H14L15.5 8 14 9.5l-1-1-1 1-1-1-1 1-1-1-1 1H6.663a3.5 3.5 0 0 1-3.163 2M2.5 9a1 1 0 1 0 0-2 1 1 0 0 0 0 2"/>
											</svg>
										</span>
										<input type="password" name="password" placeholder="Password" tabindex="3" title="Password must be 8-20 characters long, include at least one uppercase letter, one lowercase letter, one number, and one special character." class="form-control" minlength="8" maxlength="20" pattern="(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&*\\-\\/]).{8,}" required autocomplete="off">
									</div>
									<div class="pe-2">
										<input type="submit" value="login" title="Click to log in" tabindex="4" class="btn btn-outline-primary btn-sm text-uppercase">
									</div>
									<div class="pe-2">
										<input type="submit" value="signup" title="Click to sign up" tabindex="5" class="btn btn-primary btn-sm text-uppercase">
									</div>
								</form>
								<button tabindex="6" title="Click to use 42API" class="btn btn-dark btn-sm" data-auth="auth42">
									<span class="text-uppercase text-nowrap">OAuth 2.0</span>
								</button>
							</div>
						</div>
						<div class="col-4 col-lg-1 col-xl-2 col-xxl-3 text-end">
							<button tabindex="7" class="navbar-toggler" type="button" data-bs-toggle="offcanvas" data-bs-target="#offcanvasNavbar" aria-controls="offcanvasNavbar" aria-label="Toggle Navbar">
								<span class="navbar-toggler-icon"></span>
							</button>
						</div>
					</div>
					<div id="offcanvasNavbar" class="offcanvas offcanvas-end border-0 z-1" style="top: 4rem">
						<div class="container-fluid">
							<div class="${this._data.user ? "d-none" : "d-lg-none"}">
								<form class="auth-form mt-3">
									<div class="input-group mb-3">
										<span class="input-group-text">
											<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-person-fill" viewBox="0 0 16 16">
												<path d="M3 14s-1 0-1-1 1-4 6-4 6 3 6 4-1 1-1 1zm5-6a3 3 0 1 0 0-6 3 3 0 0 0 0 6"/>
											</svg>
										</span>
										<input type="text" name="username" placeholder="Username" tabindex="1" class="form-control" required autocomplete="username" minlength="4" maxlength="10" pattern="^[a-zA-Z0-9_]+$" title="Username should only contain letters, numbers, and underscores.">
									</div>
									<div class="input-group mb-3">
										<span class="input-group-text">
											<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-key-fill" viewBox="0 0 16 16">
												<path d="M3.5 11.5a3.5 3.5 0 1 1 3.163-5H14L15.5 8 14 9.5l-1-1-1 1-1-1-1 1-1-1-1 1H6.663a3.5 3.5 0 0 1-3.163 2M2.5 9a1 1 0 1 0 0-2 1 1 0 0 0 0 2"/>
											</svg>
										</span>
										<input type="password" name="password" placeholder="Password" tabindex="2" title="Password must be 8-20 characters long, include at least one uppercase letter, one lowercase letter, one number, and one special character." class="form-control" minlength="8" maxlength="20" pattern="(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&*\\-\\/]).{8,}" required autocomplete="off">
									</div>
									<div class="row mb-2">
										<div class="col-6 pe-1">
											<input type="submit" value="login" title="Click to log in" tabindex="3" class="btn btn-outline-primary w-100 text-uppercase">
										</div>
										<div class="col-6 ps-1">
											<input type="submit" value="signup" title="Click to sign up" tabindex="4" class="btn btn-primary w-100 text-uppercase">
										</div>
									</div>
								</form>
								<button tabindex="4" title="Click to use 42API" class="btn btn-dark w-100" data-auth="auth42">
									<span class="text-uppercase text-nowrap">OAuth 2.0</span>
								</button>
								<hr class="border">
							</div>
							<div class="list-group list-group-flush fw-medium text-uppercase w-100">
								<a href="/account" class="${this._data.user ? "" : "d-none"} list-group-item list-group-item-action" data-link data-bs-toggle="offcanvas" data-bs-target="#offcanvasNavbar">
									<span>Account</span>
								</a>
								<a href="/match-history" class="${this._data.user ? "" : "d-none"} list-group-item list-group-item-action" data-link data-bs-toggle="offcanvas" data-bs-target="#offcanvasNavbar">
									<span>Match History</span>
								</a>
								<a href="/other-users" class="${this._data.user ? "" : "d-none"} list-group-item list-group-item-action" data-link data-bs-toggle="offcanvas" data-bs-target="#offcanvasNavbar">
									<span>Other Users</span>
								</a>
								<a href="/messages" class="${this._data.user ? "" : "d-none"} list-group-item list-group-item-action" data-link data-bs-toggle="offcanvas" data-bs-target="#offcanvasNavbar">
									<span>Messages</span>
								</a>
								<a href="/security" class="${this._data.user ? "" : "d-none"} list-group-item list-group-item-action" data-link data-bs-toggle="offcanvas" data-bs-target="#offcanvasNavbar">
									<span>Security</span>
								</a>
								<div class="dropdown list-group-item list-group-item-action">
									<a class="nav-link dropdown-toggle" type="button" data-bs-toggle="dropdown" aria-expanded="false">
										<span class="me-1">
											<img src="/static/images/united-kingdom.svg" alt="mdo" width="16" height="16" class="mb-1">
										</span>
										<span>English</span>
									</a>
									<ul class="dropdown-menu fw-medium text-uppercase w-100">
									</ul>
								</div>
							</div>
							<div class="${this._data.user ? "" : "d-none"}">
								<hr class="border">
								<a href="/" tabindex="" title="Click to log out" class="btn btn-outline-dark w-100" data-auth="logout" data-bs-toggle="offcanvas" data-bs-target="#offcanvasNavbar">
									<span class="fw-medium text-uppercase">Log out</span>
								</a>
							</div>
						</div>
					</div>
				</div>
			</div>
		`;
	}

	addHandlerAuth(handler) {
		document.addEventListener('click', e => {
			const button = e.target.closest("[data-auth]");
			if (!button) return ;
			const action = button.dataset.auth;
			handler(action);
		});

		document.addEventListener('submit', e => {
			const form = e.target;
			if (!form.classList.contains("auth-form")) return ;
			e.preventDefault();
			e.stopPropagation();
			const action = e.submitter.value;
			const data = Object.fromEntries(new FormData(form));
			handler(action, data);
		});
	}
};

export default new HeaderView();