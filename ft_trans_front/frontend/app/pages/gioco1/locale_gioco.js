import { startCountdown } from './_timer.js';
import { Paddle } from './_paddle_uman.js';
import { Ball } from './_ball.js';

function gameLoop(canvas, leftPaddle, rightPaddle, upPaddle, downPaddle, ball, gameState) {
    const ctx = canvas.getContext('2d');
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    leftPaddle.draw(ctx);
    leftPaddle.update(canvas);
  
    rightPaddle.draw(ctx);
    rightPaddle.update(canvas);

    if(sessionStorage.getItem('nplayerg1')==3 || sessionStorage.getItem('nplayerg1')==4){
        upPaddle.draw(ctx);
        upPaddle.update(canvas);
    }

    if(sessionStorage.getItem('nplayerg1')==4){
        downPaddle.draw(ctx);
        downPaddle.update(canvas);
    }

    ball.draw(ctx);
    ball.update(canvas);
    ctx.fillStyle='white';
    ctx.font='bold 100px Arial';
    ctx.textAlign='center';
    ctx.textBaseline = 'middle';
    ctx.fillText('PONG', canvas.width / 2, canvas.height / 2);
    ball.checkCollision(leftPaddle, rightPaddle, upPaddle, downPaddle);
    if (gameState.gameRunning)
        requestAnimationFrame(() => gameLoop(canvas, leftPaddle, rightPaddle, upPaddle, downPaddle, ball, gameState));
}

export function loadLocaleGame1Page() {
    if(localStorage.getItem('lingua')==null)
        localStorage.setItem('lingua', 'it');
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const content = document.getElementById('main-content');
        content.innerHTML = `
            <div class="d-flex flex-column justify-content-center align-items-center">
                <h1 class="h3 mb-3 fw-normal text-white" id="testo">`+text.p22+`</h1>
                <h2 class="h3 mb-3 fw-normal text-white" id="tempo">0 : 0</h2>
                <canvas class="h-100 w-100" id="gameCanvas"></canvas>
            </div>
            <div class="modal fade" id="gameOverModal" tabindex="-1" aria-labelledby="gameOverModalLabel" aria-hidden="true" data-bs-backdrop="static" data-bs-keyboard="false">
                <div class="modal-dialog modal-dialog-centered">
                    <div class="modal-content mybg">
                        <div class="modal-header d-flex flex-column justify-content-center align-items-center">
                            <h5 class="modal-title text-white" id="gameOverModalLabel">Game Over</h5>
                        </div>
                        <div class="modal-body">
                            <h1 class="text-white" id="gameOverMessage"></h1>
                            <p class="mt-5 mb-3">
                                <a data-link href="/giochi" class="h4 px-2 link-secondary text-white">`+text.p31+`</a>
                            </p>
                        </div>
                    </div>
                </div>
            </div>
        `;
        const canvas = document.getElementById('gameCanvas');
        const devicePixelRatio = window.devicePixelRatio || 1;
        const width = canvas.offsetWidth * devicePixelRatio;
        const height = canvas.offsetHeight * devicePixelRatio;

        canvas.width = width;
        canvas.height = height;

        const paddleWidth = 15;
        const paddleHeight = 220;
        const radioball = 20;
    
        const leftPaddle = new Paddle(10, canvas.height / 2 - paddleHeight / 2, paddleWidth, paddleHeight, 'w', 's', 'sg');
        const rightPaddle = new Paddle(canvas.width - paddleWidth - 10, canvas.height / 2 - paddleHeight / 2, paddleWidth, paddleHeight, 'ArrowUp', 'ArrowDown', 'sg');
        let upPaddle = null;
        let downPaddle = null;
        if(sessionStorage.getItem('nplayerg1')==3 || sessionStorage.getItem('nplayerg1')==4)
            upPaddle = new Paddle(canvas.width / 2 - paddleHeight / 2, 10, paddleHeight, paddleWidth, 'v', 'b', 'ds');
        if(sessionStorage.getItem('nplayerg1')==4)
            downPaddle = new Paddle(canvas.width / 2 - paddleHeight / 2, canvas.height - 10 - paddleWidth, paddleHeight, paddleWidth, '2', '3', 'ds');
        const ball = new Ball(canvas.width / 2, canvas.height / 2, radioball);
    
        const ctx = canvas.getContext('2d');
        ctx.scale(devicePixelRatio, devicePixelRatio);
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.fillStyle='white';
        ctx.font='bold 25px Arial';
        ctx.textAlign='center';
        ctx.textBaseline = 'middle';
        if(sessionStorage.getItem("nplayerg1")==2 || sessionStorage.getItem("nplayerg1")==3 || sessionStorage.getItem("nplayerg1")==4){
            ctx.fillText(sessionStorage.getItem("p1"), 40, (canvas.height / 2)- 60);
            ctx.fillText('↑ w', 30, (canvas.height / 2)- 30);
            ctx.fillText('↓ s', 30, canvas.height / 2);
            ctx.fillText(sessionStorage.getItem("p2"), canvas.width - 100, (canvas.height / 2)- 60);
            ctx.fillText(text.p16+' ↑', canvas.width - 100, (canvas.height / 2)- 30);
            ctx.fillText(text.p34+' ↓', canvas.width - 100, canvas.height / 2);
        }
        if(sessionStorage.getItem("nplayerg1")==3 || sessionStorage.getItem("nplayerg1")==4){
            ctx.fillText('← v | b →', canvas.width / 2, 30);
            ctx.fillText(sessionStorage.getItem("p3"), canvas.width / 2, 60);
        }
        if(sessionStorage.getItem("nplayerg1")==4){
            ctx.fillText('← 2 | 3 →', canvas.width / 2, canvas.height - 30);
            ctx.fillText(sessionStorage.getItem("p4"), canvas.width / 2, canvas.height - 60);
        }
        ctx.font='bold 100px Arial';
        ctx.fillText('PONG', canvas.width / 2, canvas.height / 2);

        document.getElementById('testo').innerHTML=text.p22;
        let gameState = {
            gameRunning: false,
            gameStart: false,
        };
        document.addEventListener('keydown', (e) => {
            if (e.key === ' '){
                if (gameState.gameStart==false){
                    gameState.gameRunning = true;
                    gameState.gameStart = true;
                    if(sessionStorage.getItem("nplayerg1")==2)
                        document.getElementById('testo').innerHTML=sessionStorage.getItem('p1')+" 0 - 0 "+sessionStorage.getItem('p2');
                    else if(sessionStorage.getItem("nplayerg1")==3)
                        document.getElementById('testo').innerHTML=sessionStorage.getItem('p1')+" 0 - 0 "+sessionStorage.getItem('p2')+" - "+sessionStorage.getItem('p3')+" 0";
                    else if(sessionStorage.getItem("nplayerg1")==4)
                        document.getElementById('testo').innerHTML=sessionStorage.getItem('p1')+" 0 - 0 "+sessionStorage.getItem('p2')+" - "+sessionStorage.getItem('p3')+" 0 - "+sessionStorage.getItem('p4')+" 0";
                    gameLoop(canvas, leftPaddle, rightPaddle, upPaddle, downPaddle, ball, gameState);
                    startCountdown(gameState, ball);
                }
            }
        });
    })
}
