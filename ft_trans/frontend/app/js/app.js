import { navigateTo,router } from './router.js';
import { updateNavbar,setSocketInput } from './assets.js';

if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
if(localStorage.getItem('tp1')==null)sessionStorage.setItem('p1', sessionStorage.getItem('tp1'));

if (sessionStorage.getItem('jwtToken') != null){
  const online_sock = new WebSocket(sessionStorage.getItem('hostsock')+'/online/'+sessionStorage.getItem('jwtToken')+"/");
  setSocketInput(online_sock);
  online_sock.onopen = () => {};
  online_sock.onmessage = (event) => {};
  online_sock.onerror = (error) => {};
  online_sock.onclose = () => {};
}

document.addEventListener('DOMContentLoaded', () => {
  document.body.addEventListener('click', (e) => {
    const target = e.target;
    if (target.matches('[data-link]') || target.closest('[data-link]')) {
      e.preventDefault();
      const link = target.closest('[data-link]').getAttribute('href');
      navigateTo(link);
      updateNavbar();
    }
  });
  updateNavbar();
  router();
});