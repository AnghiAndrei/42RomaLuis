import View from "/static/js/views/View.js";

export default class extends View {

	constructor(outerView) {
		super();
		this._outerView = outerView;
	}
	
	_generateMarkup() {
		return `
			<nav class="d-none d-md-block" aria-label="breadcrumb">
				<ol class="breadcrumb">
					<li class="breadcrumb-item">
						<a href="/" data-link>
							<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-house-door-fill mb-1" viewBox="0 0 16 16">
								<path d="M6.5 14.5v-3.505c0-.245.25-.495.5-.495h2c.25 0 .5.25.5.5v3.5a.5.5 0 0 0 .5.5h4a.5.5 0 0 0 .5-.5v-7a.5.5 0 0 0-.146-.354L13 5.793V2.5a.5.5 0 0 0-.5-.5h-1a.5.5 0 0 0-.5.5v1.293L8.354 1.146a.5.5 0 0 0-.708 0l-6 6A.5.5 0 0 0 1.5 7.5v7a.5.5 0 0 0 .5.5h4a.5.5 0 0 0 .5-.5"/>
					  		</svg>
						</a>
					</li>
					<li class="breadcrumb-item active" aria-current="page">
						${this._outerView}
					</li>
				</ol>
			</nav>
			<div class="d-flex border-bottom mb-4">
				<h1 class="mb-0">${this._outerView}</h1>
			</div>
			<div class="row">
				<div class="d-none col-md-4 col-lg-3 d-md-flex">
					<div class="list-group list-group-flush border-end w-100">
						<a href="/account" class="list-group-item list-group-item-action border-0 border-start border-3 ${this._outerView === "Account" ? "border-primary bg-body-secondary": "border-white"}" data-link>
							<div class="d-flex align-items-center">
								<svg xmlns="http://www.w3.org/2000/svg" width="1.5rem" height="1.5rem" fill="currentColor" class="bi bi-person-fill" viewBox="0 0 16 16">
									<path d="M3 14s-1 0-1-1 1-4 6-4 6 3 6 4-1 1-1 1zm5-6a3 3 0 1 0 0-6 3 3 0 0 0 0 6"./>
								</svg>
								<span class="ms-2 fs-5 fw-medium">Account</span>
							</div>
						</a>
						<a href="/match-history" class="list-group-item list-group-item-action border-0 border-start border-3 ${this._outerView === "Match history" ? "border-primary bg-body-secondary": "border-white"}" data-link>
							<div class="d-flex align-items-center">
								<svg xmlns="http://www.w3.org/2000/svg" width="1.5rem" height="1.5rem" fill="currentColor" class="bi bi-table" viewBox="0 0 16 16">
									<path d="M0 2a2 2 0 0 1 2-2h12a2 2 0 0 1 2 2v12a2 2 0 0 1-2 2H2a2 2 0 0 1-2-2zm15 2h-4v3h4zm0 4h-4v3h4zm0 4h-4v3h3a1 1 0 0 0 1-1zm-5 3v-3H6v3zm-5 0v-3H1v2a1 1 0 0 0 1 1zm-4-4h4V8H1zm0-4h4V4H1zm5-3v3h4V4zm4 4H6v3h4z"/>
								</svg>
								<span class="ms-2 fs-5 fw-medium">Match History</span>
							</div>
						</a>
						<hr class="border">
						<a href="/other-users" class="list-group-item list-group-item-action border-0 border-start border-3 ${this._outerView === "Other users" ? "border-primary bg-body-secondary": "border-white"}" data-link>
							<div class="d-flex align-items-center">
								<svg xmlns="http://www.w3.org/2000/svg" width="1.5rem" height="1.5rem" fill="currentColor" class="bi bi-people-fill" viewBox="0 0 16 16">
									<path d="M7 14s-1 0-1-1 1-4 5-4 5 3 5 4-1 1-1 1zm4-6a3 3 0 1 0 0-6 3 3 0 0 0 0 6m-5.784 6A2.24 2.24 0 0 1 5 13c0-1.355.68-2.75 1.936-3.72A6.3 6.3 0 0 0 5 9c-4 0-5 3-5 4s1 1 1 1zM4.5 8a2.5 2.5 0 1 0 0-5 2.5 2.5 0 0 0 0 5"./>
								</svg>
								<span class="ms-2 fs-5 fw-medium">Other Users</span>
							</div>
						</a>
						<a href="/messages" class="list-group-item list-group-item-action border-0 border-start border-3 ${this._outerView === "Messages" ? "border-primary bg-body-secondary": "border-white"}" data-link>
							<div class="d-flex align-items-center">
								<svg xmlns="http://www.w3.org/2000/svg" width="1.5rem" height="1.5rem" fill="currentColor" class="bi bi-envelope-fill" viewBox="0 0 16 16">
									<path d="M.05 3.555A2 2 0 0 1 2 2h12a2 2 0 0 1 1.95 1.555L8 8.414zM0 4.697v7.104l5.803-3.558zM6.761 8.83l-6.57 4.027A2 2 0 0 0 2 14h12a2 2 0 0 0 1.808-1.144l-6.57-4.027L8 9.586zm3.436-.586L16 11.801V4.697z"./>
								</svg>
								<span class="ms-2 fs-5 fw-medium">Messages</span>
							</div>
						</a>
						<hr class="border">
						<a href="/security" class="list-group-item list-group-item-action border-0 border-start border-3 ${this._outerView === "Security" ? "border-primary bg-body-secondary": "border-white"}" data-link>
							<div class="d-flex justify-content-between align-items-center">
								<div class="d-flex align-items-center">
									<svg xmlns="http://www.w3.org/2000/svg" width="1.5rem" height="1.5rem" fill="currentColor" class="bi bi-shield-lock-fill" viewBox="0 0 16 16">
										<path fill-rule="evenodd" d="M8 0c-.69 0-1.843.265-2.928.56-1.11.3-2.229.655-2.887.87a1.54 1.54 0 0 0-1.044 1.262c-.596 4.477.787 7.795 2.465 9.99a11.8 11.8 0 0 0 2.517 2.453c.386.273.744.482 1.048.625.28.132.581.24.829.24s.548-.108.829-.24a7 7 0 0 0 1.048-.625 11.8 11.8 0 0 0 2.517-2.453c1.678-2.195 3.061-5.513 2.465-9.99a1.54 1.54 0 0 0-1.044-1.263 63 63 0 0 0-2.887-.87C9.843.266 8.69 0 8 0m0 5a1.5 1.5 0 0 1 .5 2.915l.385 1.99a.5.5 0 0 1-.491.595h-.788a.5.5 0 0 1-.49-.595l.384-1.99A1.5 1.5 0 0 1 8 5"/>
									</svg>
									<span class="ms-2 fs-5 fw-medium">Security</span>
								</div>
							</div>
						</a>
					</div>
				</div>
			`;
	}
};
