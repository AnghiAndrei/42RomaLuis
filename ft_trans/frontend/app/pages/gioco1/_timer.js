import { activeTimers,setPartitaincorso } from './../../js/router.js';

export function startCountdown(gameState, ball) {
  let countdown = sessionStorage.getItem('tempog1')*60;
//   countdown=2;
  const timer = setInterval(() => {
    const minutes = Math.floor((countdown % 3600) / 60);
    const seconds = countdown % 60;
    if (countdown > 0) {
      countdown--;
      setPartitaincorso(true);
    } else {
      ball.gameover();
      clearInterval(timer);
      gameState.gameRunning=false;
      setPartitaincorso(false);
    }
    document.getElementById('tempo').innerHTML=minutes+" : "+seconds;
  }, 1000);
  activeTimers.push(timer);
}
