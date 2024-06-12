import Canvas from "/static/js/model/game/Canvas.js";
import Ball from "/static/js/model/game/Ball.js";
import Paddle from "/static/js/model/game/Paddle.js";

import { GUEST, AI, UNDEFINED_PLAYER, SPEED_LEVELS, TIME_LIMITS, MAPS } from "/static/js/config.js";

export default class {
	constructor() {
		this._modes = [
			{ name: "tournament", requiresAuth: true, isSelected: false, queueLength: 4 },
			{ name: "versus", requiresAuth: true, isSelected: false, queueLength: 2 },
			{ name: "practice", requiresAuth: false, isSelected: true, queueLength: 2 },
		];
		this._queue = [ GUEST, AI ];
		this._speedLevel = SPEED_LEVELS[0];
		this._timeLimit = TIME_LIMITS[0];
		this._mapLevel = 1;
		this._powerUps = false;
		this._isRunning = false;
		this._canvas = new Canvas();
		this._ball = new Ball();
		this._paddle1 = new Paddle("left");
		this._paddle2 = new Paddle("right");
		this._matchInterval = 0;
		this._powerUpInterval = 0;
		this._aiInterval = 0;
	}

	changeMode(data) {
		this._modes.forEach( mode => {
			mode.isSelected = data === mode.name ? true : false;
		});
		const selectedMode = this._modes.find(mode => mode.isSelected);
		this._queue.length = selectedMode.queueLength;

		if (selectedMode.name === "practice") this._setPlayer(AI, 1);
		else this._setPlayer(UNDEFINED_PLAYER, 1);
		for (let index = 2; index < this._queue.length; index++)
			if (!this._queue[index] || !this._queue[index].alias) this._setPlayer(UNDEFINED_PLAYER, index);
	}

	changeCustomization(element) {
		switch (element) {
			case "decrement-speed":
				this._decrementSpeed();
				break;
			case "increment-speed":
				this._incrementSpeed();
				break;
			case "decrement-time":
				this._decrementTime();
				break;
			case "increment-time":
				this._incrementTime();
				break;
			case "prev-map-level":
				this._decrementMapLevel();
				break;
			case "next-map-level":
				this._incrementMapLevel();
				break;
			case "power-ups-switch":
				this._togglePowerUps();
				break;
			case "defaults-button":
				this._resetCustomization();
				break;
			default:
				break;
		}
	}

	_decrementSpeed() {
		let index = SPEED_LEVELS.indexOf(this._speedLevel);
		if (index > 0) this._speedLevel = SPEED_LEVELS[--index];
	}

	_incrementSpeed() {
		let index = SPEED_LEVELS.indexOf(this._speedLevel);
		if (index < 3) this._speedLevel = SPEED_LEVELS[++index];
	}

	_decrementTime() {
		let index = TIME_LIMITS.indexOf(this._timeLimit);
		if (index > 0) this._timeLimit = TIME_LIMITS[--index];
	}

	_incrementTime() {
		let index = TIME_LIMITS.indexOf(this._timeLimit);
		if (index < 3) this._timeLimit = TIME_LIMITS[++index];
	}

	_decrementMapLevel() {
		this._mapLevel = this._mapLevel === 1 ? 3 : --this._mapLevel;
	}

	_incrementMapLevel() {
		this._mapLevel = this._mapLevel === 3 ? 1 : ++this._mapLevel;
	}

	_togglePowerUps() {
		this._powerUps = this._powerUps ? false : true;
	}
	
	assignInQueue(player, friends) {
		const profileImage = `/static/media/profile_images/${friends[player].username}_profile_image.jpg?=${new Date().getTime()}`;
		const playerInfo = { ...friends[player], image: profileImage };
		const slot = this._queue.find(el => !el.alias);
		slot && this._setPlayer(playerInfo, this._queue.indexOf(slot));
	}

	_resetCustomization() {
		this._speedLevel = SPEED_LEVELS[0];
		this._timeLimit = TIME_LIMITS[0];
		this._mapLevel = 1;
		this._powerUps = false;
	}

	resetQueue() {
		const selectedMode = this._modes.find(mode => mode.isSelected);
		let index = selectedMode.name === "practice" ? 2 : 1;
	
		this._queue.length = selectedMode.name === "tournament" ? 4 : 2;
		for (index; index < this._queue.length; index++)
			this._queue[index] = UNDEFINED_PLAYER;
	}

	_setPlayer(player, index) {
		this._queue[index] = player;
	}

	_setHost(user) {
		this._modes.find(mode => mode.name === "practice").requiresAuth = true;
		const profileImage = `/static/media/profile_images/${user.username}_profile_image.jpg?=${new Date().getTime()}`;
		const playerInfo = { ...user, image: profileImage };
		this._setPlayer(playerInfo, 0);
	}

	_setGuest() {
		this._modes.find(mode => mode.name === "practice").requiresAuth = false;
		this._setPlayer(GUEST, 0);
	}

	queueCompose(user) {
		this.resetQueue();
		if (user) this._setHost(user)
		else this._setGuest();

		const selectedMode = this._modes.find(mode => mode.isSelected);
		this._queue.length = selectedMode.queueLength;
		if (selectedMode.name === "practice") this._setPlayer(AI, 1);
		for (let index = 1; index < this._queue.length; index++)
			if (!this._queue[index] || !this._queue[index].alias) this._setPlayer(UNDEFINED_PLAYER, index);
	}

	init(domElement) {
		this._canvas.init({ domElement, ...MAPS[this._mapLevel - 1] });
		this._ball.init(this._canvas, this._speedLevel);
		this._paddle1.init(this._canvas, this._speedLevel);
		this._paddle2.init(this._canvas, this._speedLevel);
		if (this._modes.find(mode => mode.isSelected).name === "practice")
			this._paddle2.ai = true;
		this._ballYperSecond = this._ball.y
	}
	
	_calculateWinRate(player) {
		return player.gamesWon / player.gamesPlayed;
	}

	matchMaking() {
		const selectedMode = this._modes.find(mode => mode.isSelected);
		if (selectedMode.name !== "tournament") return;

		this._queue.forEach( player => {
			player.winRate = this._calculateWinRate(player);
		});
		const hostPlayer = this._queue.shift();
		const hostWinRate = hostPlayer.winRate;
	
		let secondPlayer = this._queue[0];
		const closestToHost = this._queue.reduce((closest, current) => {
			return Math.abs(current.winRate - hostWinRate) < Math.abs(closest.winRate - hostWinRate) ? current : closest;
		}, secondPlayer);
		this._queue.unshift(hostPlayer);
		if (closestToHost === secondPlayer) return;
		this._queue[this._queue.indexOf(closestToHost)] = secondPlayer;
		this._queue[1] = closestToHost;
	}

	displayPowerUps() {
		this._powerUpInterval = setInterval(() => {
			[this._paddle1, this._paddle2].forEach( paddle => {
				paddle.powerUp.isVisible = true;
				paddle.powerUp.y = paddle.y >= this._canvas.height - paddle.y - paddle.height
					? paddle.powerUp.maxRadius 
					: this._canvas.height - paddle.powerUp.maxRadius;
				setTimeout(() => {
					paddle.powerUp.isVisible = false;
				}, 1500)
			})
		}, 5000);
	}

	async _usePowerUp(paddle) {
		paddle.powerUp.isVisible = false;
		const initialHeight = paddle.height;
		paddle.height *= 1.7;
		paddle.y -= (paddle.height - initialHeight) / 2;
		setTimeout(() => {
			paddle.y += (paddle.height - initialHeight) / 2;
			paddle.height = initialHeight;
		}, 3000);
	}

	_isCollision(ball, paddle) {
		const withinRange = (ball.y - (ball.radius / 2) <= paddle.y + paddle.height && ball.y + (ball.radius / 2) >= paddle.y);
	
		if (paddle.side === "left") {
			if (ball.x - ball.radius <= paddle.x + paddle.width && withinRange)
				return true;
		} else {
			if (ball.x + ball.radius >= paddle.x && withinRange)
				return true;
		}
		return false;
	}

	_handleCollisions(ball, paddle1, paddle2) {
		const threshold = 2e-15;

		if (this._isCollision(ball, paddle1)) {
			let relativeY = Math.max(0, Math.min(ball.y - paddle1.y, paddle1.height));
			let heading = (1.6 + 0.4 * relativeY / (paddle1.height / 2)) * Math.PI;
			if (relativeY > paddle1.height / 2)
				heading = (0.4 * ((relativeY - paddle1.height / 2) / (paddle1.height / 2))) * Math.PI;
			ball.direction = {x: Math.cos(heading), y: Math.sin(heading)};
			if (Math.abs(ball.direction.x) < threshold) ball.direction.x = 0;
			if (Math.abs(ball.direction.y) < threshold) ball.direction.y = 0;
		}
		if (this._isCollision(ball, paddle2)) {
			const relativeY = Math.max(0, Math.min(ball.y - paddle2.y, paddle2.height));
			let heading = (1.4 - 0.4 * relativeY / (paddle2.height / 2)) * Math.PI;
			if (relativeY > paddle2.height / 2)
				heading = (1 - (0.4 * ((relativeY - paddle2.height / 2) / (paddle1.height / 2)))) * Math.PI;
			ball.direction = {x: Math.cos(heading), y: Math.sin(heading)};
			if (Math.abs(ball.direction.x) < threshold) ball.direction.x = 0;
			if (Math.abs(ball.direction.y) < threshold) ball.direction.y = 0;
		}

		[ paddle1, paddle2 ].forEach( paddle => {
			const { powerUp } = paddle;
			if (!powerUp.isVisible) return ;
			const topPowerUp = powerUp.y - powerUp.maxRadius;
			const bottomPowerUp = powerUp.y + powerUp.maxRadius;
			if (topPowerUp < paddle.y && bottomPowerUp > paddle.y)
				this._usePowerUp(paddle);
			if (topPowerUp < paddle.y + paddle.height && bottomPowerUp > paddle.y + paddle.height)
				this._usePowerUp(paddle);
		});
	}

	update(delta) {
		const { _canvas: canvas, _ball: ball, _paddle1: paddle1, _paddle2: paddle2 } = this;

		[ paddle1, paddle2 ].forEach( paddle => {
			if (paddle.y <= 0 && paddle.direction.y === -1) paddle.direction.y = 0;
			if (paddle.y + paddle.height >= canvas.height && paddle.direction.y === 1) paddle.direction.y = 0;
		});
		if (ball.y - ball.radius <= 0 || ball.y + ball.radius >= canvas.height) {
			ball.y = ball.y - ball.radius <= 0 ? ball.radius : canvas.height - ball.radius;
			ball.direction.y *= -1;
		}
		this._handleCollisions(ball, paddle1, paddle2);
		if (ball.x - ball.radius <= 0 || ball.x + ball.radius >= canvas.width) {
			const winner = ball.x - ball.radius <= 0 ? paddle2 : paddle1;
			winner.score.value += 1;
			this._ball.reset(this._canvas);
		}

		ball.move(delta);
		paddle1.move(delta);
		if (!paddle2.ai) paddle2.move(delta);
		else this._moveAi(delta);
	}

	predictBallY() {
		this._aiInterval = setInterval(() => {
			const ball = this._ball;

			if (ball.direction.x < 0)
				this._ballYperSecond = this._canvas.height / 2;
			else if (ball.direction.y === 0)
				this._ballYperSecond = ball.y;
			else {
				let oppositeCathetus = 0;
				let ballY = ball.y;
				let adjacentCathetus = ball.direction.y < 0 ? ballY : this._canvas.height - ballY;
				let ballDirY = ball.direction.y * -1;
				let canvasWidh = this._canvas.width - ball.x;
				let angle = 90 * (Math.PI / 180) - Math.abs(Math.atan2(ballDirY, ball.direction.x));
				while(1) {
					ballDirY *= -1;
					oppositeCathetus = Math.tan(angle) * adjacentCathetus;
					if (canvasWidh < oppositeCathetus)
						break ;
					adjacentCathetus = this._canvas.height;
					canvasWidh -= oppositeCathetus;
				}
				angle = 90 * (Math.PI / 180) - angle;
				adjacentCathetus = oppositeCathetus - canvasWidh;
				oppositeCathetus = Math.tan(angle) * adjacentCathetus;
				this._ballYperSecond = ballDirY < 0 ? oppositeCathetus :  this._canvas.height - oppositeCathetus;
				this._ballYperSecond *= Math.random() * (1.5 - 0.5) + 0.5;
			}
		}, 1000);
	}

	_moveAi(delta) {
		const paddle = this._paddle2;
		const paddleCenter = paddle.y + paddle.height / 2;
		let direction = 0;
		if (paddle.y > this._ballYperSecond || this._ballYperSecond > (paddle.y + paddle.height))
			direction = paddleCenter - this._ballYperSecond < 0 ? 1 : -1;
		const newPosition = paddle.y + direction * paddle.speed * delta;
		if (newPosition < 0 || newPosition + paddle.height > this.canvas.height) return;
		paddle.y = newPosition;
	}

	redirectPaddle(event) {
		const input = event.code || event.data;

		const paddleMap = {
			"KeyW": { paddle: this._paddle1, direction: -1 },
			"KeyS": { paddle: this._paddle1, direction: 1 },
			"ArrowUp": { paddle: this._paddle2, direction: -1, aiControl: this._paddle2.ai },
			"ArrowDown": { paddle: this._paddle2, direction: 1, aiControl: this._paddle2.ai },
			"up-paddle1": { paddle: this._paddle1, direction: -1 },
			"down-paddle1": { paddle: this._paddle1, direction: 1 },
			"up-paddle2": { paddle: this._paddle2, direction: -1, aiControl: this._paddle2.ai },
			"down-paddle2": { paddle: this._paddle2, direction: 1, aiControl: this._paddle2.ai }
		};
		if (!input || !paddleMap[input] || paddleMap[input]?.aiControl) return;
		paddleMap[input].paddle.direction.y = paddleMap[input].direction;
	}
	
	stopPaddle(event) {
		const input = event.code || event.data;
		const directionP1 = this._paddle1.direction.y;
    	const directionP2 = this._paddle2.direction.y;

		const paddleActions = {
			"KeyW": { paddle: this._paddle1, currentDir: directionP1, expectedDir: -1 },
			"KeyS": { paddle: this._paddle1, currentDir: directionP1, expectedDir: 1 },
			"ArrowUp": { paddle: this._paddle2, currentDir: directionP2, expectedDir: -1 },
			"ArrowDown": { paddle: this._paddle2, currentDir: directionP2, expectedDir: 1 },
			"up-paddle1": { paddle: this._paddle1, currentDir: directionP1, expectedDir: -1 },
			"down-paddle1": { paddle: this._paddle1, currentDir: directionP1, expectedDir: 1 },
			"up-paddle2": { paddle: this._paddle2, currentDir: directionP2, expectedDir: -1 },
			"down-paddle2": { paddle: this._paddle2, currentDir: directionP2, expectedDir: 1 }
		};
		if (input && paddleActions[input] && paddleActions[input].currentDir === paddleActions[input].expectedDir)
			paddleActions[input].paddle.direction.y = 0;
	}

	async timer(domMinutes, domSeconds) {
		let time = this._timeLimit;
		await new Promise(resolve => {
			this._matchInterval = setInterval(() => {
				if (time <= 0) {
					clearInterval(this._matchInterval);
					resolve();
				} else {
					time--;
					const minutes = Math.floor(time / 60);
					const seconds = time % 60;
					domMinutes.textContent = String(minutes).padStart(2, '0');
					domSeconds.textContent = String(seconds).padStart(2, '0');
				}
			}, 1000);
		});
	}

	_lastWinningChance(scoreP1, scoreP2) {
		return new Promise((resolve) => {
			const checkScores = () => {
				if (this._paddle1.score.value > scoreP1 ||
					this._paddle2.score.value > scoreP2) {
						resolve();
				} else requestAnimationFrame(checkScores);
			};
			checkScores();
		});
	}

	async decretWinner() {
		const score1 = this._paddle1.score.value;
		const score2 = this._paddle2.score.value;
		if (score1 === score2)
			await this._lastWinningChance(score1, score2);
		const updatedScore1 = this._paddle1.score.value;
		const updatedScore2 = this._paddle2.score.value;
		const winner = updatedScore1 > updatedScore2 ? { ...this._queue[0], score: updatedScore1 } : { ...this._queue[1], score: updatedScore2 };
        const loser = updatedScore1 > updatedScore2 ? { ...this._queue[1], score: updatedScore2 } : { ...this._queue[0], score: updatedScore1 };
		return { winner, loser };
	}

	prunePlayers() {
		this._queue.splice(0, 2);
	}

	pushWinner(winner) {
		this._queue.push(winner);
	}

	resetGame() {
		this._ball.reset(this._canvas);
		this._paddle1.reset(this._canvas);
		this._paddle2.reset(this._canvas);
		this._paddle1.resetScore();
		this._paddle2.resetScore();
		this._isRunning = false;
		clearInterval(this._matchInterval);
		clearInterval(this._powerUpInterval);
		clearInterval(this._aiInterval);
	}
	
	resetObject() {
		this._modes = [
			{ name: "tournament", requiresAuth: true, isSelected: false, queueLength: 4 },
			{ name: "versus", requiresAuth: true, isSelected: false, queueLength: 2 },
			{ name: "practice", requiresAuth: false, isSelected: true, queueLength: 2 },
		];
		this._queue = [ GUEST, AI ];
		this._resetCustomization();
		this.resetGame();
	}


	get modes() {
		return this._modes;
	}
	get speedLevel() {
		return this._speedLevel;
	}
	get timeLimit() {
		return this._timeLimit;
	}
	get mapLevel() {
		return this._mapLevel;
	}
	get powerUps() {
		return this._powerUps;
	}
	get queue() {
		return this._queue;
	}
	get canvas() {
		return this._canvas;
	}
	get ball() {
		return this._ball;
	}
	get paddle1() {
		return this._paddle1;
	}
	get paddle2() {
		return this._paddle2;
	}
	get isRunning() {
		return this._isRunning;
	}
	get matchInterval() {
		return this._matchInterval;
	}
	get powerUpInterval() {
		return this._powerUpInterval;
	}
	get aiInterval() {
		return this._aiInterval;
	}

	set modes(value) {
		this._modes = value;
	}
	set speedLevel(value) {
		this._speedLevel = value;
	}
	set timeLimit(value) {
		this._timeLimit = value;
	}
	set mapLevel(value) {
		this._mapLevel = value;
	}
	set powerUps(value) {
		this._powerUps = value;
	}
	set queue(value) {
		this._queue = value;
	}
	set canvas(value) {
		this._canvas = value;
	}
	set ball(value) {
		this._ball = value;
	}
	set paddle1(value) {
		this._paddle1 = value;
	}
	set paddle2(value) {
		this._paddle2 = value;
	}
	set isRunning(value) {
		this._isRunning = value;
	}
	set matchInterval(value) {
		this._matchInterval = value;
	}
	set powerUpInterval(value) {
		this._powerUpInterval = value;
	}
	set aiInterval(value) {
		this._aiInterval = value;
	}
};