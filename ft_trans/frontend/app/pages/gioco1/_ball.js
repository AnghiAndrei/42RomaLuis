import { torneoclass } from '../../js/router.js';

export class Ball {
	constructor(x, y, radius) {
		this.x = x;
		this.y = y;
		this.radius = radius;
		this.dx = (parseFloat(sessionStorage.getItem('velmovballg1'))*5);
		this.dy = (parseFloat(sessionStorage.getItem('velmovballg1'))*5);
		this.pp1 = 0;
		this.pp2 = 0;
		this.pp3 = 0;
		this.pp4 = 0;
		this.last = '';
		this.stop = false;
	}

	draw(ctx) {
		ctx.beginPath();
		ctx.arc(this.x, this.y, this.radius, 0, Math.PI * 2);
		ctx.fillStyle = 'white';
		ctx.fill();
		ctx.closePath();
	}
	
	update(canvas, leftPaddle, rightPaddle) {
		if(sessionStorage.getItem('caosg1')=='true'){
			if(Math.floor(Math.random() * 6)==1){
				if(Math.floor(Math.random() * 3)==1){
					this.y -= Math.floor(Math.random() * 40);
					this.x -= Math.floor(Math.random() * 40);
				}else{
				this.y += Math.floor(Math.random() * 40);
				this.x += Math.floor(Math.random() * 40);
				}
			}
    	}
		this.x += this.dx;
		this.y += this.dy;
    	if(sessionStorage.getItem("nplayerg1")==2){
			if (this.y - this.radius < 0 || this.y + this.radius > canvas.height)
        		this.dy *= -1;
		}else if(sessionStorage.getItem("nplayerg1")==3){
			if (this.y + this.radius > canvas.height)
				this.dy *= -1;
			if (this.y - this.radius < 4) {
				this.incrementScore(canvas);
				this.x = canvas.width / 2;
				this.y = canvas.height / 2;
				if(Math.floor(Math.random() * 2)==1)
					this.dx *= -1;
				else
					this.dy *= -1;
			}
		}else if(sessionStorage.getItem("nplayerg1")==4){
			if (this.y + this.radius > canvas.height-4) {
				this.incrementScore(canvas);
				this.x = canvas.width / 2;
				this.y = canvas.height / 2;
				if(Math.floor(Math.random() * 2)==1)
					this.dx *= -1;
				else
					this.dy *= -1;
			}
			if (this.y - this.radius < 4){
				this.incrementScore(canvas);
				this.x = canvas.width / 2;
				this.y = canvas.height / 2;
				if(Math.floor(Math.random() * 2)==1)
					this.dx *= -1;
				else
					this.dy *= -1;
			}
		}
		if (this.x - this.radius < 4) {
			this.incrementScore(canvas);
			this.x = canvas.width / 2;
			this.y = canvas.height / 2;
			if(Math.floor(Math.random() * 2)==1)
					this.dx *= -1;
			else
				this.dy *= -1;
		}
		if (this.x + this.radius > canvas.width-4) {
			this.incrementScore(canvas);
			this.x = canvas.width / 2;
			this.y = canvas.height / 2;
			if(Math.floor(Math.random() * 2)==1)
					this.dx *= -1;
			else
				this.dy *= -1;
		}
		if (document.getElementById('testo') == null)
			return;
		if(sessionStorage.getItem('ia')=='true'){
			if(sessionStorage.getItem("nplayerg1")==2)
				document.getElementById('testo').innerHTML=sessionStorage.getItem('p1')+" "+this.pp1+" - "+this.pp2+" BOT1";
			else if(sessionStorage.getItem("nplayerg1")==3)
				document.getElementById('testo').innerHTML=sessionStorage.getItem('p1')+" "+this.pp1+" - BOT1 "+this.pp2+" - BOT2 "+this.pp3;
			else if(sessionStorage.getItem("nplayerg1")==4)
				document.getElementById('testo').innerHTML=sessionStorage.getItem('p1')+" "+this.pp1+" - BOT1 "+this.pp2+" - BOT2 "+this.pp3+" - BOT3 "+this.pp4;
		}else{
			if(sessionStorage.getItem("nplayerg1")==2)
				document.getElementById('testo').innerHTML=sessionStorage.getItem('p1')+" "+this.pp1+" - "+this.pp2+" "+sessionStorage.getItem('p2');
			else if(sessionStorage.getItem("nplayerg1")==3)
				document.getElementById('testo').innerHTML=sessionStorage.getItem('p1')+" "+this.pp1+" - "+sessionStorage.getItem('p2')+" "+this.pp2+" - "+sessionStorage.getItem('p3')+" "+this.pp3;
			else if(sessionStorage.getItem("nplayerg1")==4)
				document.getElementById('testo').innerHTML=sessionStorage.getItem('p1')+" "+this.pp1+" - "+sessionStorage.getItem('p2')+" "+this.pp2+" - "+sessionStorage.getItem('p3')+" "+this.pp3+" - "+sessionStorage.getItem('p4')+" "+this.pp4;
		}
	}

	incrementScore(canvas) {
		if(sessionStorage.getItem("nplayerg1")!=2){
			if (this.last === 'left') this.pp1++;
			else if (this.last === 'right') this.pp2++;
			else if (this.last === 'up') this.pp3++;
			else if (this.last === 'down') this.pp4++;
		}else{
			if (this.x + this.radius > canvas.width-4)
				this.pp1++;
			if (this.x - this.radius < 4)
				this.pp2++;
		}
	}

  checkCollision(leftPaddle, rightPaddle, upPaddle, downPaddle) {
    if (this.x - this.radius < leftPaddle.x + leftPaddle.width &&
        this.y > leftPaddle.y &&
        this.y < leftPaddle.y + leftPaddle.height){
          this.x = leftPaddle.x + leftPaddle.width + this.radius;
          this.last='left';
          this.dx *= -1;
        }

    if (this.x + this.radius > rightPaddle.x &&
        this.y > rightPaddle.y &&
        this.y < rightPaddle.y + rightPaddle.height){
          this.x = rightPaddle.x - this.radius;
          this.last='right';
          this.dx *= -1;
        }

    if (upPaddle != null &&
        this.y - this.radius < upPaddle.y + upPaddle.height &&
        this.x > upPaddle.x &&
        this.x < upPaddle.x + upPaddle.width){
          this.y = upPaddle.y + upPaddle.height + this.radius;
          this.last='up';
          this.dy *= -1;
        }

    if (downPaddle != null &&
        this.y + this.radius > downPaddle.y &&
        this.x > downPaddle.x &&
        this.x < downPaddle.x + downPaddle.width){
          this.y = downPaddle.y - this.radius;
          this.last='down';
          this.dy *= -1;
        }
  }

  	gameover(){
    	if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    	import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
	    .then((module) => {
      		const text = module.text;
      		const modal = new bootstrap.Modal(document.getElementById('gameOverModal'));
      		modal.show();

			let p2=sessionStorage.getItem('p2');
			let p3=sessionStorage.getItem('p3');
			let p4=sessionStorage.getItem('p4');
			if(sessionStorage.getItem('ia')=='true'){
				if (sessionStorage.getItem('nplayerg1')==2){
					p2="BOT2";
					p3=null;
					p4=null;
				} else if (sessionStorage.getItem('nplayerg1')==3){
					p2="BOT2";
					p3="BOT3";
					p4=null;
				} else if (sessionStorage.getItem('nplayerg1')==4){
					p2="BOT2";
					p3="BOT3";
					p4="BOT4";
				}
			}

      		const players = [
        		{ name: sessionStorage.getItem('p1'), score: this.pp1 },
        		{ name: p2, score: this.pp2 },
      		];
      		if (sessionStorage.getItem('nplayerg1') == 3) players.push({ name: p3, score: this.pp3 });
      		if (sessionStorage.getItem('nplayerg1') == 4) players.push({ name: p4, score: this.pp4 });

      		const maxScore = Math.max(...players.map(player => player.score));
      		const winners = players.filter(player => player.score === maxScore);
			let esito="S";
			if (winners.length === 1) {
				players.sort((a, b) => b.score - a.score);
        		const winner = players[0];
        		document.getElementById('gameOverMessage').innerHTML=text.p32+winner.name;
				if(winner.name==sessionStorage.getItem('p1'))
					esito="V";
				if(sessionStorage.getItem('ia')=='torneo')
					torneoclass.finepartita(winner.name);
      		}else{
        		document.getElementById('gameOverMessage').innerHTML=text.p33;
				esito="P";
      		}

			let gioco="lpia"; //ia
			if(sessionStorage.getItem('ia')=='false')
				gioco="lp24"; //normale

			if(sessionStorage.getItem('ia')!='torneo'){
				fetch('https://localhost:8000/g1/set_game', {
					method: 'POST',
					headers: {
					  'Content-Type': 'application/json',
					  'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
					},
					body: JSON.stringify({
						nomep1: sessionStorage.getItem('p1'),
						nomep2: p2,
						nomep3: p3,
						nomep4: p4,
						esito: esito,
						pp1: this.pp1,
						pp2: this.pp2,
						pp3: this.pp3,
						pp4: this.pp4,
						game: gioco
					}),
				})
				.then(response => {
					const status = response.status;
					if(status==200){
						;
					} else if (status == 401){
						const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
						modal2.show();
						document.getElementById('ERROREMessage').innerHTML=text.p67;
					}else{
						const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
						modal2.show();
						document.getElementById('ERROREMessage').innerHTML=text.p59;
					}
				})
				.catch(error => {
					const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
					modal2.show();
					document.getElementById('ERROREMessage').innerHTML=text.p59;
				});
			}
    	})
  	}
}
