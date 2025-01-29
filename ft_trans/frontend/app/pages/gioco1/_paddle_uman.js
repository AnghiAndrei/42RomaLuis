export class Paddle {
  constructor(x, y, width, height, upKey, downKey, pos) {
	if (pos === 'ds')
		width=width*2;

	this.x = x;
    this.y = y;
    this.oheight = height;
    this.owidth = width;
    this.width = width;
    this.height = height;
    this.upKey = upKey;
    this.downKey = downKey;
    this.speed = (parseFloat(sessionStorage.getItem('velmovg1'))*5);
    this.dy = 0;
    this.dx = 0;
    this.timercaos = 0;
    this.pos=pos;
    this.aumenta = true;

    document.addEventListener('keydown', (e) => {
      if (e.key === this.upKey) {
        if (this.pos === 'sg') this.dy = -this.speed;
        else {this.dx = -this.speed;}
      }
      if (e.key === this.downKey) {
        if (this.pos === 'sg') this.dy = this.speed;
        else{this.dx = this.speed;}
      }
    });

    document.addEventListener('keyup', (e) => {
      if (e.key === this.upKey || e.key === this.downKey) {
        this.dy = 0;
        this.dx = 0;
      }
    });
  }

  draw(ctx) {
    ctx.fillStyle = sessionStorage.getItem('color');
    ctx.fillRect(this.x, this.y, this.width, this.height);
  }

  update(canvas) {
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
