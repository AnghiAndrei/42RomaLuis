import View from "/static/js/views/View.js";

import { SPEED_LEVELS } from "/static/js/config.js";

class MainPageView extends View {

	constructor() {
		super();
	}

	_generateFriendListMarkup(friends, game) {
		if (!friends || friends.length === 0)
			return `<span class="py-3">No friends ...</span>`;
		const queueAliases = game.queue.map( player => player.alias);
		const friendsAliases = friends.map( friend => friend.alias);
		if (friendsAliases && friendsAliases.every(friend => queueAliases.includes(friend)))
        	return `<span class="py-3">No friends ...</span>`;
	
		let html = "";
		friends.forEach((friend, index) => {
			if (!queueAliases.includes(friend.alias)) {
				html += `
					<li id="${index}" role="button" class="list-group-item list-group-item-action d-flex align-items-center px-0 border-top-0" data-bs-dismiss="modal" data-action="choose-player">
						<div class="col">
							<img src="/static/media/profile_images/${friend.username}_profile_image.jpg?=${new Date().getTime()}" width="60" height="60" class="radio radio1x1 rounded-circle" alt="Avatar"/>
						</div>
						<span class="col">${friend.username}</span>
						<span class="col">${friend.alias}</span>
						<span class="col">
							<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="${friend.online ? "green" : "red"}" class="bi bi-circle-fill" viewBox="0 0 17 17">
								<circle cx="8" cy="8" r="8"/>
							</svg>
						</span>
					</li>
				`;
			}
		});
		return html;
	}

	_generateModesMarkup(modes) {
		let html = "";
		modes.forEach( mode => {
			html += `
				<div class="d-flex flex-column w-100">
					<div class="changa-font text-center ${mode.isSelected ? 'text-danger' : ''}">
						<h4 class="m-0 d-md-block d-none">
							${mode.name}
						</h4>
						<small class="m-0 d-md-none d-block fw-semibold">
							${mode.name}
						</small>
					</div>
					<a id="${mode.name}" role="button" class="btn custom-button col-md-7 col-12 w-100 position-relative d-flex justify-content-center align-content-center p-md-2 p-1 border-0 ${!this._data.user && mode.requiresAuth || mode.isSelected ? 'mode-disabled' : ''}" data-action="change-mode">
						<div class="position-relative rounded-3 z-1 ${mode.isSelected ? 'pressed' : 'released'}">
							<div class="position-absolute w-100 h-100 d-flex justify-content-center align-items-center rounded-3 ${!this._data.user && mode.requiresAuth ? '' : 'd-none'}" style="background-color: rgba(125, 129, 129, 0.69)">
								<img src="/static/images/padlock.svg" alt="mdo" width="40" height="40" class="img-fluid">
							</div>
							<img src="/static/images/${mode.name}.png" class="img-fluid rounded-3" alt="${mode.name}">
						</div>
					</a>
				</div>
			`
		});
		return html;
	}

	_generateQueueMarkup(queue) {
		let html = "";
		for (let index = 0; index < queue.length; index++) {
			html += `
				<div class="col-3 px-md-4">
					<div class="d-flex flex-column align-items-center row-gap-2">
						<div class="changa-font" style="white-space: nowrap;">
							<h5 class="d-md-block d-none">
								Player ${index + 1}
							</h5>
							<small class="d-md-none d-block">
								Player ${index + 1}
							</small>
						</div>
						<button class="ratio ratio-1x1 col-md-4 col-12 w-100 border-0 p-0 m-0 rounded-circle" data-bs-toggle="modal" data-bs-target="#friendListModal" ${index === 0 || queue[index].alias === "Ai" ? 'disabled' : ''}>
							<img src=${queue[index]?.username
								? `/static/media/profile_images/${queue[index].username}_profile_image.jpg?=${new Date().getTime()}`
								: queue[index]?.image
							} class="bg-white img-fluid rounded-circle" alt="Avatar"/>
						</button>
						<div class="d-flex flex-column align-items-center mt-md-2 mt-1">
							<span class="col mb-0 text-uppercase text-muted" style="white-space: nowrap;">
								Alias: 
							</span>
							<span class="col">
								${queue[index]?.alias ?? ''}
							</span>
						</div>
					</div>
				</div>
			`
		};
		return html;
	}

	_generateMarkup() {
		const game = this._data.game;
		const html = `
			<div class="container-xxl pt-xl-5 pt-md-4 pt-3 d-flex flex-md-row flex-column column-gap-md-5 row-gap-4 mb-5">
				<div class="col-md-3 col-12 mx-xl-3 mx-md-1">
					<section id="game-mode" class="d-flex flex-md-column flex-row align-items-center row-gap-4 column-gap-2 mb-2">
						${this._generateModesMarkup(game.modes)}
					</section>
				</div>
				<div class="col mt-md-2">
					<section id="game-customization" class="d-flex flex-column row-gap-md-2 row-gap-1 pt-xl-5 pt-md-4 me-md-3 me-2 pb-md-3">
						<div class="row align-items-lg-start align-items-md-center align-items-sm-start align-items-center column-gap-md-4 column-gap-2">
							<div class="col">
								<div class="d-flex flex-column align-items-center row-gap-xxl-4 row-gap-lg-3 row-gap-md-4 row-gap-sm-3 row-gap-2">
									<section id="game-speed-level" class="row justify-content-between align-items-center w-100">
										<div class="col-lg-3 col-md-4 col-sm-3 col-4 px-0 ps-1">
											<span class="mb-0 text-uppercase text-muted">
												<small>Speed</small>
											</span>
										</div>
										<div class="col-7 d-lg-block d-md-none d-sm-block d-none">
											<div class="d-flex justify-content-between align-items-center">
												<span>
													Choose speed level to customize game experience
												</span>
											</div>
										</div>
										<div class="col-lg-2 col-md-3 col-sm-2 col-4">
											<div class="row justify-content-center">
												<button class="col-3 border-1 border-end-0 p-lg-1 p-0 rounded-start-2" id="decrement-speed" data-action="game-customization">
													<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="mb-1 bi bi-dash" viewBox="0 0 16 16">
														<path d="M4 8a.5.5 0 0 1 .5-.5h7a.5.5 0 0 1 0 1h-7A.5.5 0 0 1 4 8"/>
													</svg>
												</button>
												<input id="speed-input" type="number" value="${SPEED_LEVELS.indexOf(game.speedLevel) + 1}" class="col-5 border-1 rounded-0 text-center p-lg-1 p-0" onkeydown="return false" style="cursor: default;"/>
												<button class="col-3 border-1 border-start-0 p-lg-1 p-0 rounded-end-2" id="increment-speed" data-action="game-customization">
													<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="mb-1 bi bi-plus" viewBox="0 0 16 16">
														<path d="M8 4a.5.5 0 0 1 .5.5v3h3a.5.5 0 0 1 0 1h-3v3a.5.5 0 0 1-1 0v-3h-3a.5.5 0 0 1 0-1h3v-3A.5.5 0 0 1 8 4"/>
													</svg>
												</button>
											</div>
										</div>
									</section>
									<section id="game-time-limit" class="row justify-content-between align-items-center w-100 mt-xxl-3 mt-xl-3 mt-lg-2 mt-sm-1 mt-0">
										<div class="col-lg-3 col-md-4 col-sm-3 col-4 px-0 ps-1">
											<span class="mb-2 mb-md-0 text-uppercase text-muted">
												<small>Time</small>
											</span>
										</div>
										<div class="col-7 d-lg-block d-md-none d-sm-block d-none">
											<div class="d-flex justify-content-between align-items-center">
												<span>
													Choose how many seconds to play to customize game experience
												</span>
											</div>
										</div>
										<div class="col-lg-2 col-md-3 col-sm-2 col-4">
											<div class="row justify-content-center">
												<button class="col-3 border-1 border-end-0 p-lg-1 p-0 rounded-start-2" id="decrement-time" data-action="game-customization">
													<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="mb-1 bi bi-dash" viewBox="0 0 16 16">
														<path d="M4 8a.5.5 0 0 1 .5-.5h7a.5.5 0 0 1 0 1h-7A.5.5 0 0 1 4 8"/>
													</svg>
												</button>
												<input id="time-input" type="number" value="${game.timeLimit}" class="col-5 border-1 rounded-0 text-center p-lg-1 p-0" onkeydown="return false" style="cursor: default;" />
												<button class="col-3 border-1 border-start-0 p-lg-1 p-0 rounded-end-2" id="increment-time" data-action="game-customization">
													<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="mb-1 bi bi-plus" viewBox="0 0 16 16">
														<path d="M8 4a.5.5 0 0 1 .5.5v3h3a.5.5 0 0 1 0 1h-3v3a.5.5 0 0 1-1 0v-3h-3a.5.5 0 0 1 0-1h3v-3A.5.5 0 0 1 8 4"/>
													</svg>
												</button>
											</div>
										</div>
									</section>
								</div>
							</div>
							<section id="game-map-level" class="col-4 carousel slide px-1">
								<div class="carousel-inner">
									<div id="map00" class="carousel-item ${game.mapLevel === 1 ? 'active' : ''}">
										<img src="/static/images/map00.png" class="d-block h-100 w-100 rounded-3" alt="map00">
									</div>
									<div id="map01" class="carousel-item ${game.mapLevel === 2 ? 'active' : ''}">
										<img src="/static/images/map01.png" class="d-block w-100 rounded-3" alt="map01">
									</div>
									<div id="map02" class="carousel-item ${game.mapLevel === 3 ? 'active' : ''}">
										<img src="/static/images/map02.png" class="d-block w-100 rounded-3" alt="map02">
									</div>
								</div>
								<button class="carousel-control-prev w-50 d-flex justify-content-start" data-bs-target="#game-map-level" style="opacity: 1; filter: invert(100%); cursor: default;" id="prev-map-level" data-action="game-customization">
									<span role="button" class="carousel-control-prev-icon bg-secondary rounded-md-2 rounded-1" aria-hidden="true" style="height: 30%; width: 32%; margin-left: -5%;"></span>
									<span class="visually-hidden">Previous</span>
								</button>
								<button class="carousel-control-next w-50 d-flex justify-content-end" data-bs-target="#game-map-level" style="opacity: 1; filter: invert(100%); cursor: default;" id="next-map-level" data-action="game-customization">
									<span role="button" class="carousel-control-next-icon bg-secondary rounded-md-2 rounded-1" aria-hidden="true" style="height: 30%; width: 32%; margin-right: -5%;"></span>
									<span class="visually-hidden">Next</span>
								</button>
							</section>
						</div>
						<div class="row align-items-center column-gap-md-4 column-gap-2">
							<div class="col">
								<div class="d-flex flex-column align-items-center">
									<section id="game-power-ups" class="row justify-content-between align-items-center w-100">
										<div class="col-lg-3 col-md-4 col-sm-3 col-7 px-0 ps-1">
											<span class="mb-0 text-uppercase text-muted">
												<small>Power ups</small>
											</span>
										</div>
										<div class="col-7 d-lg-block d-md-none d-sm-block d-none">
											<div class="d-flex justify-content-between align-items-center">
												<span>
													Choose to enhance game experience by adding power-ups into the map 
												</span>
											</div>
										</div>
										<div class="col-lg-2 col-md-3 col-sm-2 col-4">
											<div class="d-flex justify-content-center form-check form-switch">
												<input id="power-ups-switch" type="checkbox" role="switch" class="form-check-input border-dark" style="width: 3rem; height: 1.5rem; transition: background-position .15s ease-in-out;" ${!game.powerUps ? '' : 'checked'} data-action="game-customization" />
											</div>
										</div>
									</section>
								</div>
							</div>
							<div class="col-4 px-1">
								<button class="btn btn-outline-primary w-100 roundend-2 py-sm-1 py-0 px-0" style="white-space: nowrap;" id="defaults-button" data-action="game-customization">
									<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-arrow-counterclockwise mb-1" viewBox="0 0 16 16">
										<path fill-rule="evenodd" d="M8 3a5 5 0 1 1-4.546 2.914.5.5 0 0 0-.908-.417A6 6 0 1 0 8 2z"/>
										<path d="M8 4.466V.534a.25.25 0 0 0-.41-.192L5.23 2.308a.25.25 0 0 0 0 .384l2.36 1.966A.25.25 0 0 0 8 4.466"/>
									</svg>
									<span>
										Defaults
									</span>
								</button>
							</div>
						</div>
					</section>
					<section id="game-queue" class="row justify-content-center mt-xl-5 mt-lg-0 mt-sm-5 pt-lg-5 pt-sm-4 pt-3">
						${this._generateQueueMarkup(game.queue)}
					</section>
					<div class="d-flex flex-column row-gap-3 align-items-center w-100 text-center mt-xl-5 mt-lg-0 mt-md-3 mt-sm-5 pt-lg-5 pt-sm-4 pt-3">
						<button class="changa-font fs-6 btn btn-outline-primary border-1 px-md-3" style="white-space: nowrap;" ${game.queue.player2?.alias === "Ai" ? "disabled" : ""} data-action="reset-queue">
							Reset game queue
						</button>
						<span class="d-inline-block mt-1" tabindex="0" ${game.queue.map( player => player.alias).includes(undefined) ? "data-bs-toggle='popover'" : ""} data-bs-trigger="hover focus" data-bs-content="The queue is incomplete. Click one queue slot to add more players">
							<button class="changa-font btn btn-lg btn-outline-danger px-5 fs-5" type="button" ${game.queue.map( player => player.alias).includes(undefined) ? "disabled" : ""} data-action="play-pong">
								Play pong
							</button>
						</span>
					</div>
				</div>
			</div>
			<div class="modal fade" id="friendListModal" tabindex="-1" aria-labelledby="friendListModalLabel" aria-hidden="true">
				<div class="modal-dialog modal-dialog-centered">
					<div class="modal-content">
						<div class="modal-header">
							<h1 class="modal-title fs-5" id="friendListModalLabel">Add player</h1>
							<button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
						</div>
						<div class="modal-body">
							<ul class="mb-3 ps-4">
								<li class="mb-2">
									Choose one of your friend to push it into the first available slot in the queue
								</li>
								<li>
									Navigate directly to <a href="/other-users" data-bs-dismiss="modal" data-link>other users</a> page to add new friends
								</li>
							</ul>
							<div class="d-flex bg-dark text-white text-uppercase fw-normal rounded-top-2 py-2 text-center">
								<span class="col mb-0"><small>Picture</small></span>
								<span class="col mb-0"><small>Username</small></span>
								<span class="col mb-0"><small>Alias</small></span>
								<span class="col mb-0"><small>Status</small></span>
							</div>
							<ul class="list-group text-center border border-1 rounded-bottom-2 rounded-top-0">
								${this._generateFriendListMarkup(this._data.friends, game)}
							</ul>
						</div>
					</div>
				</div>
			</div>
		`;
		return html;
	}

	async render(data) {
		await super.render(data);
		const popoverTriggerList = document.querySelectorAll('[data-bs-toggle="popover"]');
		popoverTriggerList.forEach(popoverTriggerEl => new bootstrap.Popover(popoverTriggerEl));
	}

	addHandlerCustomization(handler) {
		document.addEventListener("click", e => {
			const input = e.target.closest("[data-action]");
			if (!input)
				return ;
			e.stopPropagation();
			const action = input.dataset.action;
			const data = input.id;
			handler(action, data);
		});
	}
};

export default new MainPageView();