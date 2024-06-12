import View from "/static/js/views/View.js";

class GameView extends View {

	constructor() {
		super();
	}

	addHandlerGameControls(handler) {
		["keydown", "keyup", "resize"].forEach(event => window.addEventListener(event, handler));
	}

	_generateMarkup() {
		return `
			<div class="mt-2">
				<canvas class="w-100 h-100"></canvas>
			</div>
		`;
	}

	_drawScene(board) {
		const context = board.domElement.getContext("2d");
		context.fillStyle = board.color;
		context.fillRect(0, 0, board.width, board.height);
		context.strokeStyle = board.stroke.color;
		context.lineWidth = board.stroke.size;
		context.beginPath();
		context.setLineDash([20, 20]);
		context.moveTo(board.width / 2, 0);
		context.lineTo(board.width / 2, board.height);
		context.stroke();
	}

	draw(data) {
		const board = data.board;
		const context = board.domElement.getContext("2d");
		const ball = data.ball;
		const p1Paddle = data.player1;
		const p2Paddle = data.player2;
		const p1Score = data.player1.score;
		const p2Score = data.player2.score;
	
		context.clearRect(0, 0, board.width, board.height);
		this._drawScene(board);
		context.beginPath();
		context.arc(ball.x, ball.y, ball.radius, 0, Math.PI * 2);
		context.fillStyle = ball.color;
		context.fill();
		context.fillStyle = p1Paddle.color;
		context.fillRect(p1Paddle.x, p1Paddle.y, p1Paddle.width, p1Paddle.height);
		context.fillStyle = p2Paddle.color;
		context.fillRect(p2Paddle.x, p2Paddle.y, p2Paddle.width, p2Paddle.height);
		context.fillStyle = "white";
		context.textAlign = "center";
		context.font = `${p1Score.size}px ${p1Score.font}`;
		context.fillText(`${p1Score.value}`, p1Score.x, p1Score.y);
		context.fillText(`${p2Score.value}`, p2Score.x, p1Score.y);
	}
};

export default new GameView();