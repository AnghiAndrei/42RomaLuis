import View from "/static/js/views/View.js"

class PongView extends View {
	constructor() {
		super();
	}

	addHandlerView(handler) {
		["keydown", "keyup"].forEach(event => window.addEventListener(event, handler));
		["mousedown", "mouseup", "mouseleave", "touchstart", "touchend"].forEach( event => window.addEventListener(event, e => {
			const input = e.target.closest("[data-move]");
			if (!input) return;
			e.data = input.dataset.move;
			handler(e);
		}));
	}

	removeListeners(handler) {
		["keydown", "keyup"].forEach(event => window.removeEventListener(event, handler));
		["mousedown", "mouseup", "mouseleave", "touchstart", "touchend"].forEach( event => window.addEventListener(event, handler));
	}

	_generateMarkup() {
		const game = this._data.game;
		const modeSelected = game.modes.find( mode => mode.isSelected );
		const minutes = Math.floor(game.timeLimit / 60);
		const seconds = game.timeLimit - minutes * 60;
		const html = `
			<div class="container d-flex flex-column text-center justify-content-md-center justify-content-start row-gap-4 mt-5 pt-md-5">
				<h1 id="timer" class="changa-font display-3">
					<span id="minutes">${String(minutes).padStart(2, '0')}</span>:<span id="seconds">${String(seconds).padStart(2, '0')}</span>
				</h1>
				<canvas class="border rounded-2"></canvas>
				<section class="d-lg-none d-flex justify-content-around mt-5 pt-3">
					<div class="col-2 d-flex flex-column row-gap-2">
						<button type="button" class="btn border rounded-3 border-dark py-md-3 py-2 px-3" data-move="up-paddle1">
							<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" fill="currentColor" class="mb-1 bi bi-caret-up-fill" viewBox="0 0 16 16">
								<path d="m7.247 4.86-4.796 5.481c-.566.647-.106 1.659.753 1.659h9.592a1 1 0 0 0 .753-1.659l-4.796-5.48a1 1 0 0 0-1.506 0z"/>
							</svg>
						</button>
						<button type="button" class="btn border rounded-3 border-dark py-md-3 py-2 px-3" data-move="down-paddle1">
							<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" fill="currentColor" class="bi bi-caret-down-fill" viewBox="0 0 16 16">
								<path d="M7.247 11.14 2.451 5.658C1.885 5.013 2.345 4 3.204 4h9.592a1 1 0 0 1 .753 1.659l-4.796 5.48a1 1 0 0 1-1.506 0z"/>
							</svg>
						</button>
					</div>
					<div class="col-2 d-flex flex-column row-gap-2">
						<button type="button" class="btn border rounded-3 border-dark py-md-3 py-2 px-3" data-move="up-paddle2">
							<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" fill="currentColor" class="mb-1 bi bi-caret-up-fill" viewBox="0 0 16 16">
								<path d="m7.247 4.86-4.796 5.481c-.566.647-.106 1.659.753 1.659h9.592a1 1 0 0 0 .753-1.659l-4.796-5.48a1 1 0 0 0-1.506 0z"/>
							</svg>
						</button>
						<button type="button" class="btn border rounded-3 border-dark py-md-3 py-2 px-3" data-move="down-paddle2">
							<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" fill="currentColor" class="bi bi-caret-down-fill" viewBox="0 0 16 16">
								<path d="M7.247 11.14 2.451 5.658C1.885 5.013 2.345 4 3.204 4h9.592a1 1 0 0 1 .753 1.659l-4.796 5.48a1 1 0 0 1-1.506 0z"/>
							</svg>
						</button>
					</div>
				</section>
			</div>
			<div id="modalPreGame" class="modal px-4" tabindex="-1">
				<div class="modal-dialog">
					<div class="modal-content">
						<div class="modal-header">
							<div class="w-100 text-center">
								<h2 class="modal-title" id="modalLabel">Match Players</h2>
								<span class="${modeSelected.name !== "tournament" ? "d-none" : "d-block"}">
									The queue created was rearranged with a win rate based matchmaking system
								</span>
							</div>
						</div>
						<div id="queuePlaceholder" class="modal-body d-flex justify-content-evenly"></div>
						<div class="modal-footer d-flex justify-content-center">
							<button class="btn btn-outline-dark px-5" data-bs-dismiss="modal" data-action="start-game">
								<span class="fw-medium text-uppercase">
									Start game
								</span>
							</button>
						</div>
					</div>
				</div>
			</div>
			<div id="modalPostGame" class="modal px-4" tabindex="-1">
				<div class="modal-dialog">
					<div class="modal-content">
						<div class="modal-header">
							<div class="w-100 text-center">
								<h2 class="modal-title" id="modalLabel">${modeSelected.name !== "tournament" ? "Match" : "Tournament"} finished</h2>
							</div>
						</div>
						<div class="modal-body d-flex justify-content-evenly pt-0">
							<div class="d-flex flex-column w-25 align-items-center row-gap-2">
								<h4 class="modal-title" id="modalLabel">Winner</h4>
								<section id="winnerPlaceholder" class="w-75"></section>
							</div>
						</div>
						<div class="modal-footer d-flex justify-content-center">
							<a href="/" role="button" class="btn btn-outline-dark px-5" data-bs-dismiss="modal" data-link>
								<span class="fw-medium text-uppercase">
									Done playing
								</span>
							</a>
						</div>
					</div>
				</div>
			</div>
		`;
		return html;
	}

	_generateQueueMarkup(queue) {
		let html = "";
		for (let index = 0; index < 2; index++) {
			html += `
				<div class="col-lg-4 col-md-3 col-2 px-md-4">
					<div class="d-flex flex-column align-items-center row-gap-2">
						<div class="changa-font" style="white-space: nowrap;">
							<h4 class="d-md-block d-none">
								Player ${index + 1}
							</h4>
							<small class="d-md-none d-block">
								Player ${index + 1}
							</small>
						</div>
						<div class="col-md-4 col-12 w-100 border-0 p-0 m-0 rounded-circle">
							<div class="ratio ratio-1x1 p-0 border-0 position-relative rounded-circle z-1">
								<img src=${queue[index].username
									? `/static/media/profile_images/${queue[index].username}_profile_image.jpg?=${new Date().getTime()}`
									: queue[index].image
								} class="bg-white img-fluid rounded-circle" alt="Avatar"/>
							</div>
						</div>
						<div class="d-flex flex-column align-items-center mt-md-2 mt-1 fs-5">
							<span class="col mb-0 text-uppercase text-muted" style="white-space: nowrap;">
								Alias: 
							</span>
							<span class="col">
								${queue[index].alias}
							</span>
						</div>
					</div>
				</div>
			`;
		};
		return html;
	}

	renderPreGame(data) {
		const queueContent = this._generateQueueMarkup(data.game.queue);
		document.querySelector("#queuePlaceholder").innerHTML = queueContent;
		const modal = new bootstrap.Modal(document.getElementById("modalPreGame"), {backdrop: 'static'});
		modal.toggle();
	}

	renderPostGame(winner) {
		const winnerContent = `
			<div class="border-0 p-0 m-0 rounded-circle">
				<div class="ratio ratio-1x1 p-0 border-0 position-relative rounded-circle z-1">
					<img src=${winner.image} class="bg-white img-fluid rounded-circle" alt="Avatar"/>
				</div>
			</div>
			<div class="d-flex flex-column align-items-center mt-md-2 mt-1 fs-5">
				<span class="col mb-0 text-uppercase text-muted" style="white-space: nowrap;">
					Alias: 
				</span>
				<span class="col">
					${winner.alias}
				</span>
			</div>
		`;
		document.querySelector("#winnerPlaceholder").innerHTML = winnerContent;
		const modal = new bootstrap.Modal(document.getElementById("modalPostGame"), {backdrop: 'static'});
		modal.toggle();
	}

	_drawBoard(canvas) {
		const context = canvas.domElement.getContext("2d");
		context.fillStyle = canvas.boardColor;
		context.fillRect(0, 0, canvas.width, canvas.height);
		context.strokeStyle = canvas.innerObjsColor;
		context.lineWidth = canvas.stroke.size;
		context.beginPath();
		context.setLineDash([canvas.stroke.dash, canvas.stroke.dash]);
		context.moveTo(canvas.width / 2, 0);
		context.lineTo(canvas.width / 2, canvas.height);
		context.stroke();
	}

	_drawPowerUp(context, paddle) {
		const { powerUp } = paddle;
		context.strokeStyle = powerUp.color;
		context.beginPath();
		let angle = 0;
		let radius = 0;
		while (radius < powerUp.maxRadius) {
			const x = powerUp.x + radius * Math.cos(angle);
			const y = powerUp.y + radius * Math.sin(angle);
			context.lineTo(x, y);
			angle += 0.3;
			radius += powerUp.step;
		}
		context.stroke();
		context.beginPath();
		angle = 0;
		while (angle < 360) {
			const x = powerUp.x + radius * Math.cos(angle);
			const y = powerUp.y + radius * Math.sin(angle);
			context.lineTo(x, y);
			angle += 0.3;
		}
		context.stroke();
	}

	draw(data) {
		const { canvas, ball, paddle1, paddle2 } = data;
		const { score: score1, powerUp: powerUp1 } = paddle1;
		const { score: score2, powerUp: powerUp2 } = paddle2;

		const context = canvas.domElement.getContext("2d");
		context.clearRect(0, 0, canvas.width, canvas.height);
		this._drawBoard(canvas);
		context.setLineDash([]);
		context.beginPath();
		context.arc(ball.x, ball.y, ball.radius, 0, Math.PI * 2);
		context.fillStyle = ball.color;
		context.fill();

		context.fillStyle = paddle1.color;
		context.fillRect(paddle1.x, paddle1.y, paddle1.width, paddle1.height);
		context.fillStyle = paddle2.color;
		context.fillRect(paddle2.x, paddle2.y, paddle2.width, paddle2.height);
		context.fillStyle = canvas.innerObjsColor;
	
		context.textAlign = "center";
		context.font = `${score1.size}px Changa`;
		context.fillText(`${score1.value}`, score1.x, score1.y);
		context.fillText(`${score2.value}`, score2.x, score2.y);
	
		context.lineWidth = canvas.width * 0.003;
		powerUp1.isVisible && this._drawPowerUp(context, paddle1);
		powerUp2.isVisible && this._drawPowerUp(context, paddle2);
	}
}

export default new PongView();