import View from "/static/js/views/View.js";

class ChatView extends View {

	constructor() {
		super();
	}

	_generateMessageListMarkup() {
		const chat = this._data.chats.find(chat => chat.user === this._data.contact.username)
		if (!chat)
			return `<p class="text-center h3 text-muted py-5">No messages</p>`;
		let html = "";
		chat.messages.forEach(message => {
			html += `
				<div class="d-flex flex-column">
					<div class=" rounded mb-2 me-1 ${message.user === this._data.user.username ? 'bg-primary-subtle align-self-end me-sm-3' : 'bg-secondary-subtle align-self-start'}" style="max-width: 75%; min-width: 25%;">
						<div class="p-2 text-break">
							${message.content}
						</div>
						<div class="p-2 d-flex align-items-center justify-content-between">
							<a ${message.user === this._data.user.username ? "" : "role='button'  data-bs-toggle='modal' data-bs-target='#profileModal'"} class="text-decoration-none me-2 fw-bold ${message.user === this._data.user.username ? "text-dark" : ""}">
								${message.user}
							</a>
							<span>
								${this._generateFormattedDateMarkup(message.date)}
							</span>
						</div>
					</div>
				</div>
			`
		});
		return html;
	}

	_generateMarkup() {
		const html = `
			<div class="container flex-grow-1 d-flex flex-column mb-3">
				<nav aria-label="breadcrumb">
					<ol class="breadcrumb pt-3 mb-2" typeof="BreadcrumbList">
						<li class="breadcrumb-item">
							<a href="/" data-link>
								<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-house-door-fill mb-1" viewBox="0 0 16 16">
									<path d="M6.5 14.5v-3.505c0-.245.25-.495.5-.495h2c.25 0 .5.25.5.5v3.5a.5.5 0 0 0 .5.5h4a.5.5 0 0 0 .5-.5v-7a.5.5 0 0 0-.146-.354L13 5.793V2.5a.5.5 0 0 0-.5-.5h-1a.5.5 0 0 0-.5.5v1.293L8.354 1.146a.5.5 0 0 0-.708 0l-6 6A.5.5 0 0 0 1.5 7.5v7a.5.5 0 0 0 .5.5h4a.5.5 0 0 0 .5-.5"/>
								</svg>
							</a>
						</li>
						<li class="breadcrumb-item">
							<a href="/messages" class="text-decoration-none" data-link>
								Messages
							</a>
						</li>
						<li class="breadcrumb-item active" aria-current="page">
							${this._data.contact.username}
						</li>
					</ol>
				</nav>
				<div class="d-block d-sm-flex align-items-sm-center mb-3 border-bottom">
					<div class="flex-grow-1">
						<h1 class="mb-0">Messages with ${this._data.contact.username}</h1>
					</div>
					<div class="align-self-end d-flex justify-content-end mb-md-1">
						<div class="nav dropdown">
							<a href="" data-bs-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false" class="nav-link dropdown-toggle text-nowrap text-uppercase fw-bold">
								More Options
							</a>
							<ul class="dropdown-menu dropdown-menu-right">
								<li>
									<a role="button" class="dropdown-item text-decoration-none text-center fw-bold px-4 py-2" data-bs-toggle="modal" data-bs-target="#profileModal">
										${this._data.contact.username}
									</a>
								</li>
								<li>
									<div class="dropdown-divider"></div>
								</li>
								<li>
									<div class="dropdown-item px-4 py-2">
										<button id="play-together" class="btn btn-sm btn-outline-primary d-flex align-items-center">
											<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-controller me-2" viewBox="0 0 16 16">
												<path d="M11.5 6.027a.5.5 0 1 1-1 0 .5.5 0 0 1 1 0m-1.5 1.5a.5.5 0 1 0 0-1 .5.5 0 0 0 0 1m2.5-.5a.5.5 0 1 1-1 0 .5.5 0 0 1 1 0m-1.5 1.5a.5.5 0 1 0 0-1 .5.5 0 0 0 0 1m-6.5-3h1v1h1v1h-1v1h-1v-1h-1v-1h1z"/>
												<path d="M3.051 3.26a.5.5 0 0 1 .354-.613l1.932-.518a.5.5 0 0 1 .62.39c.655-.079 1.35-.117 2.043-.117.72 0 1.443.041 2.12.126a.5.5 0 0 1 .622-.399l1.932.518a.5.5 0 0 1 .306.729q.211.136.373.297c.408.408.78 1.05 1.095 1.772.32.733.599 1.591.805 2.466s.34 1.78.364 2.606c.024.816-.059 1.602-.328 2.21a1.42 1.42 0 0 1-1.445.83c-.636-.067-1.115-.394-1.513-.773-.245-.232-.496-.526-.739-.808-.126-.148-.25-.292-.368-.423-.728-.804-1.597-1.527-3.224-1.527s-2.496.723-3.224 1.527c-.119.131-.242.275-.368.423-.243.282-.494.575-.739.808-.398.38-.877.706-1.513.773a1.42 1.42 0 0 1-1.445-.83c-.27-.608-.352-1.395-.329-2.21.024-.826.16-1.73.365-2.606.206-.875.486-1.733.805-2.466.315-.722.687-1.364 1.094-1.772a2.3 2.3 0 0 1 .433-.335l-.028-.079zm2.036.412c-.877.185-1.469.443-1.733.708-.276.276-.587.783-.885 1.465a14 14 0 0 0-.748 2.295 12.4 12.4 0 0 0-.339 2.406c-.022.755.062 1.368.243 1.776a.42.42 0 0 0 .426.24c.327-.034.61-.199.929-.502.212-.202.4-.423.615-.674.133-.156.276-.323.44-.504C4.861 9.969 5.978 9.027 8 9.027s3.139.942 3.965 1.855c.164.181.307.348.44.504.214.251.403.472.615.674.318.303.601.468.929.503a.42.42 0 0 0 .426-.241c.18-.408.265-1.02.243-1.776a12.4 12.4 0 0 0-.339-2.406 14 14 0 0 0-.748-2.295c-.298-.682-.61-1.19-.885-1.465-.264-.265-.856-.523-1.733-.708-.85-.179-1.877-.27-2.913-.27s-2.063.091-2.913.27"/>
												</svg>
											<span class="text-uppercase">
												Play Pong together
											</span>
										</button>
									<div>
								</li>
							</ul>
						</div>
					</div>
				</div>
				<div id="chat-container" class="flex-grow-1 position-relative overflow-y-auto">
					<div class="d-flex flex-column position-absolute top-0 start-0 w-100 h-100">
						${this._generateMessageListMarkup()}
					</div>
				</div>
			</div>
			<div class="container border rounded mb-sm-3 px-sm-0 p-0 bg-body-tertiary">
				<form id="message-form" class="px-4 py-3">
					<div class="input-group">
						<input name="message" placeholder="Message to ${this._data.contact.username}..." maxlength="500" autocomplete="off" autofocus required class="form-control">
						<button type="submit" class="btn btn-dark">
							<span>
								<svg xmlns="http://www.w3.org/2000/svg" width="1rem" height="1rem" fill="currentColor" class="bi bi-send-fill mb-1" viewBox="0 0 16 16">
									<path d="M15.964.686a.5.5 0 0 0-.65-.65L.767 5.855H.766l-.452.18a.5.5 0 0 0-.082.887l.41.26.001.002 4.995 3.178 3.178 4.995.002.002.26.41a.5.5 0 0 0 .886-.083zm-1.833 1.89L6.637 10.07l-.215-.338a.5.5 0 0 0-.154-.154l-.338-.215 7.494-7.494 1.178-.471z"/>
								</svg>
							</span>
							<span class="fw-medium text-uppercase d-none d-md-inline ms-2">
								Send
							</span>
						</button>
					</div>
				</form>
			</div>
			<div class="modal fade" id="profileModal" tabindex="-1" aria-labelledby="profileModalLabel" aria-hidden="true">
				<div class="modal-dialog modal-dialog-centered">
					<div class="modal-content">
						<div class="modal-header">
							<h1 class="modal-title fs-5 fw-bold">${this._data.contact.username}'s Profile</h1>
							<button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
						</div>
						<div class="modal-body">
							<div class="row">
								<div class="col-6 d-flex align-items-center">
									<div class="flex-fill ratio ratio-1x1">
										<img id="profile-picture" src="/static/media/profile_images/${this._data.contact.username}_profile_image.jpg?=${new Date().getTime()}" class="rounded-circle h-100 w-100" alt="Avatar">
									</div>
								</div>
								<div class="col-6 d-flex flex-column text-uppercase text-center">
									<div class="flex-fill">
										<div>
											games played
										</div>
										<div>
											${this._data.contact.gamesPlayed}
										</div>
									</div>
									<div class="flex-fill">
										<div>
											games won
										</div>
										<div>
											${this._data.contact.gamesWon}
										</div>
									</div>
									<div class="flex-fill">
										<div>
											games lost
										</div>
										<div>
											${this._data.contact.gamesLost}
										</div>
									</div>
								</div>
							</div>
						</div>
						<div class="modal-footer">
							<button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
						</div>
					</div>
				</div>
			</div>
		`;
		return html;
	}

	async render(data) {
		await super.render(data);
		const chatContainer = document.getElementById("chat-container");
		chatContainer.scrollTop = chatContainer.scrollHeight;
	}

	addEventHandler(handler) {
		document.addEventListener("submit", (event) => {
			const form = event.target;
			if (event.target.id !== "message-form") return ;
			event.preventDefault();
			event.stopPropagation();
			const message = new FormData(form).get("message");
			form.querySelector("input").value = "";
			handler({other: this._data.contact.username, sender: this._data.user.username, message: message});
		});
		document.addEventListener("click", (event) => {
			const button = event.target.closest("#play-together");
			if (!button) return ;
			event.stopPropagation();
			const message = "ZONG TIME!\nCome to me to play pong together.";
			handler({other: this._data.contact.username, sender: this._data.user.username, message: message});
		});
	}
}

export default new ChatView();
