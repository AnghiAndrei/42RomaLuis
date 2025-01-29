export class PaddleIA {
  constructor(x, y, width, height, pos, ball) {
	if (pos === 'ds')
		width=width*2;

    this.x = x;
    this.y = y;
    this.oheight = height;
    this.owidth = width;
    this.width = width;
    this.height = height;
    this.speed = (parseFloat(sessionStorage.getItem('velmovg1'))*5);
    this.dy = 0;
    this.dx = 0;
    this.timercaos = 0;
    this.pos=pos;
    this.aumenta = true;
    this.ball=ball;
    this.lastUpdateTime = Date.now();
  }

  draw(ctx) {
    ctx.fillStyle = sessionStorage.getItem('color');
    ctx.fillRect(this.x, this.y, this.width, this.height);
  }

  update(canvas) {
    const currentTime = Date.now();
    if (currentTime - this.lastUpdateTime >= 1000)
      this.lastUpdateTime = currentTime;
    if (this.pos === 'sg') {
      let projectedY = this.ball.y + this.ball.dy * ((this.x - this.ball.x) / this.ball.dx);
      if (projectedY < 0 || projectedY > canvas.height) {
        projectedY = Math.abs(projectedY) % canvas.height;
        if (projectedY > canvas.height)
          projectedY = canvas.height - (projectedY - canvas.height);
      }
      if (Math.random() > 0.5) {
        if (projectedY < this.y + this.height / 2 - 10)
          this.dy = -this.speed;
        else if (projectedY > this.y + this.height / 2 + 10)
          this.dy = this.speed;
        else
          this.dy = 0;
      } else
        this.dy = 0;
    } else {
      let projectedX = this.ball.x + this.ball.dx * ((this.y - this.ball.y) / this.ball.dy);
      if (projectedX < 0 || projectedX > canvas.width) {
        projectedX = Math.abs(projectedX) % canvas.width;
        if (projectedX > canvas.width)
          projectedX = canvas.width - (projectedX - canvas.width);
      }
      if (Math.random() > 0.5) {
        if (projectedX < this.x + this.width / 2 - 10)
          this.dx = -this.speed;
        else if (projectedX > this.x + this.width / 2 + 10)
          this.dx = this.speed;
        else
          this.dx = 0;
      } else
        this.dx = 0;
    }
    
    if(sessionStorage.getItem('caosg1')=='true'){
      if(this.timercaos==0) this.aumenta=true;
      if(this.timercaos==100) this.aumenta=false;

      if(this.pos === 'sg'){
        if(this.aumenta==true){
          if(this.oheight==this.height) this.height=this.height+Math.floor(Math.random() * 101);
          this.timercaos++;
        }else{
          if(this.oheight!=this.height) this.height=this.oheight;
          this.timercaos--;
        }
      }else{
        if(this.aumenta==true){
          if(this.owidth==this.width) this.width=this.width+Math.floor(Math.random() * 101);
          this.timercaos++;
        }else{
          if(this.owidth!=this.width) this.width=this.owidth;
          this.timercaos--;
        }
      }
    }
    this.y += this.dy;
    this.x += this.dx;
    if (this.pos === 'sg') {
      if (this.y < 0) this.y = 0; 
      if (this.y + this.height > canvas.height) this.y = canvas.height - this.height;
    } else {
      if (this.x < 0) this.x = 0; 
      if (this.x + this.width > canvas.width) this.x = canvas.width - this.width;
    }
  }
}
