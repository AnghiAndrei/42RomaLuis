import View from "/static/js/views/View.js";

class FooterView extends View {

	constructor() {
		super();
		this._parentElement = document.querySelector("footer");
	}

	_generateMarkup() {
		const html = `
			<div class="container-fluid border-top bg-body-tertiary">
				<div class="row d-none d-lg-flex">
					<div class="col">
						<ul class="nav align-items-center justify-content-start fw-bold">
							<li class="nav-item text-uppercase">
								<a href="/static/media/developers.txt" download title="About Us" class="nav-link">
									<small>About Us</small>
								</a>
							</li>
							<li class="nav-item text-uppercase">
								<a href="/static/media/modules.txt" download title="Project Modules" class="nav-link">
									<small>Project Modules</small>
								</a>
							</li>
							<li class="nav-item dropup ms-auto">
								<a class="nav-link dropdown-toggle text-uppercase" role="button" data-bs-toggle="dropdown" aria-expanded="false">
									<small class="fw-normal text-secondary">Language:</small>
									<span>
										English
									</span>
								</a>
								<ul class="dropdown-menu dropdown-menu-right">
									<li>
										<h6 class="dropdown-item text-uppercase">Choose a language</h6>
									</li>
									<li>
										<hr class="dropdown-divider">
									</li>
									<li>
										<p class="dropdown-info dropdown-item fw-light py-2">
											<small>This changes the language of the site.<br>It won't change any text entered by users.</small>
										</p>
									</li>
								</ul>
							</li>
						</ul>
					</div>
				</div>
				<div class="row align-items-center px-3">
					<div class="col col-md-6">
						<p class="text-muted text-center text-md-start my-2"><small>© Copyright 2024. All rights reserved.</small></p>
					</div>
					<div class="col d-none d-md-block text-end">
						<a href="https://github.com/dforte21/Trascendence" class="link-body-emphasis text-decoration-none ms-3">
							<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" fill="currentColor" class="bi bi-discord" viewBox="0 0 16 16">
								<path d="M13.545 2.907a13.2 13.2 0 0 0-3.257-1.011.05.05 0 0 0-.052.025c-.141.25-.297.577-.406.833a12.2 12.2 0 0 0-3.658 0 8 8 0 0 0-.412-.833.05.05 0 0 0-.052-.025c-1.125.194-2.22.534-3.257 1.011a.04.04 0 0 0-.021.018C.356 6.024-.213 9.047.066 12.032q.003.022.021.037a13.3 13.3 0 0 0 3.995 2.02.05.05 0 0 0 .056-.019q.463-.63.818-1.329a.05.05 0 0 0-.01-.059l-.018-.011a9 9 0 0 1-1.248-.595.05.05 0 0 1-.02-.066l.015-.019q.127-.095.248-.195a.05.05 0 0 1 .051-.007c2.619 1.196 5.454 1.196 8.041 0a.05.05 0 0 1 .053.007q.121.1.248.195a.05.05 0 0 1-.004.085 8 8 0 0 1-1.249.594.05.05 0 0 0-.03.03.05.05 0 0 0 .003.041c.24.465.515.909.817 1.329a.05.05 0 0 0 .056.019 13.2 13.2 0 0 0 4.001-2.02.05.05 0 0 0 .021-.037c.334-3.451-.559-6.449-2.366-9.106a.03.03 0 0 0-.02-.019m-8.198 7.307c-.789 0-1.438-.724-1.438-1.612s.637-1.613 1.438-1.613c.807 0 1.45.73 1.438 1.613 0 .888-.637 1.612-1.438 1.612m5.316 0c-.788 0-1.438-.724-1.438-1.612s.637-1.613 1.438-1.613c.807 0 1.451.73 1.438 1.613 0 .888-.631 1.612-1.438 1.612"/>
							</svg>
						</a>
						<a href="https://github.com/dforte21/Trascendence" class="link-body-emphasis text-decoration-none ms-3 my-2">
							<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" fill="currentColor" class="bi bi-github" viewBox="0 0 16 16">
								<path d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27s1.36.09 2 .27c1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.01 8.01 0 0 0 16 8c0-4.42-3.58-8-8-8"/>
							</svg>
						</a>
					</div>
				</div>
			</div>
		`;
		return html;
	}

	render(data) {
		super.render(data);
		const backdrop = document.querySelector(".modal-backdrop");
		backdrop?.remove();
	}
}

export default new FooterView();