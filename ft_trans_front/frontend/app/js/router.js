import { loadHomePage } from '../pages/home.js';

import { loadLoginPage } from '../pages/utenti/login.js';
import { loadRegistraPage } from '../pages/utenti/registrati.js';
import { load2faPage } from '../pages/utenti/2fa.js';

import { loadGiochiHomePage } from '../pages/giochi.js';
import { loadLocaleHomeGame1Page } from '../pages/gioco1/locale_home.js';
import { loadLocaleGame1Page } from '../pages/gioco1/locale_gioco.js';
import { loadCustumeserPage } from '../pages/gioco1/costumeser.js';

import { loadLocaleHomeIaGame1Page } from '../pages/gioco1/locale_home_ia.js';
import { loadLocaleIaGame1Page } from '../pages/gioco1/locale_gioco_ia.js';

import { loadLocaleHomeTorneoGame1Page } from '../pages/gioco1/locale_torneo_home.js';
import { loadLocaleTorneoGame1Page } from '../pages/gioco1/locale_torneo_gioco.js';
import { loadLocalePreGameTorneoGame1Page } from '../pages/gioco1/locale_torneo_pregame.js';

export let actualpossion='/';

export let torneoclass = null;

export let partitaincorso=false;
export function setPartitaincorso(value){partitaincorso=value;}

export let torneoincorso=false;
export function setTorneoincorso(value){torneoincorso=value;}

export function navigateTo(url) {
  if(partitaincorso==true || torneoincorso==true)
    return;
  history.pushState(null, null, url);
  actualpossion=url;
  router();
}

export let activeTimers = [];

export function router() {
  const routes = [
    { path: '/', view: loadHomePage },
    
    { path: '/login', view: loadLoginPage },
    { path: '/registrati', view: loadRegistraPage },
    { path: '/2fa', view: load2faPage },

    { path: '/giochi', view: loadGiochiHomePage },
    { path: '/costumeser', view: loadCustumeserPage },
    { path: '/locale_home', view: loadLocaleHomeGame1Page },
    { path: '/locale_gioco', view: loadLocaleGame1Page },
    { path: '/locale_home_ia', view: loadLocaleHomeIaGame1Page },
    { path: '/locale_gioco_ia', view: loadLocaleIaGame1Page },
    { path: '/locale_torneo_home', view: loadLocaleHomeTorneoGame1Page },
    { path: '/locale_torneo_gioco', view: loadLocaleTorneoGame1Page },
    { path: '/locale_torneo_pregame', view: loadLocalePreGameTorneoGame1Page },
  ];
  const potentialMatch = routes.find((route) => location.pathname === route.path);
  if (potentialMatch) {
    activeTimers.forEach(id => clearInterval(id));

    if (document.getElementById('gameOverModal') != null) {
      const modal = bootstrap.Modal.getInstance(document.getElementById('gameOverModal'));
      if(modal) modal.hide();
    }    

    if(potentialMatch.path!='/2fa')
      sessionStorage.removeItem('tempjwt');

    if((sessionStorage.getItem('jwtToken')==null && (potentialMatch.path=='/locale_torneo_pregame' || potentialMatch.path=='/locale_torneo_home' || potentialMatch.path=='/locale_home_ia' || potentialMatch.path=='/locale_gioco_ia' || potentialMatch.path=='/locale_gioco' || potentialMatch.path=='/locale_home')) || (sessionStorage.getItem('tempjwt')==null && potentialMatch.path=='/2fa')){
      navigateTo("/");
      return;
    }

    const navbar = document.getElementById('navbar-content');
    if ((partitaincorso==true || torneoincorso==true) && (potentialMatch.path === '/locale_torneo_pregame' || potentialMatch.path === '/locale_gioco' || potentialMatch.path === '/locale_gioco_ia' || potentialMatch.path === '/locale_torneo_gioco'))
      navbar.style.display = 'none';
    else
      navbar.style.display = 'block';

    if(partitaincorso==true || torneoincorso==true)
      potentialMatch.view();
  } else {
    if(localStorage.getItem('lingua')==null)
      localStorage.setItem('lingua', 'it');
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
      const text = module.text;
      document.getElementById('main-content').innerHTML = '<div class="d-flex justify-content-center"><h2 class="text-white">'+text.p30+'</h2></div>';
    })
  }
}
window.addEventListener('popstate', router);




/* NO BLOC TOUR */
export function navigateTo2(url) {
  if(partitaincorso==true)
    return;
  history.pushState(null, null, url);
  actualpossion=url;
  router2();
}
export function router2() {
  const routes = [
    { path: '/', view: loadHomePage },
    
    { path: '/login', view: loadLoginPage },
    { path: '/registrati', view: loadRegistraPage },
    { path: '/2fa', view: load2faPage },

    { path: '/giochi', view: loadGiochiHomePage },
    { path: '/costumeser', view: loadCustumeserPage },
    { path: '/locale_home', view: loadLocaleHomeGame1Page },
    { path: '/locale_gioco', view: loadLocaleGame1Page },
    { path: '/locale_home_ia', view: loadLocaleHomeIaGame1Page },
    { path: '/locale_gioco_ia', view: loadLocaleIaGame1Page },
    { path: '/locale_torneo_home', view: loadLocaleHomeTorneoGame1Page },
    { path: '/locale_torneo_gioco', view: loadLocaleTorneoGame1Page },
    { path: '/locale_torneo_pregame', view: loadLocalePreGameTorneoGame1Page },
  ];
  const potentialMatch = routes.find((route) => location.pathname === route.path);
  if (potentialMatch) {
    activeTimers.forEach(id => clearInterval(id));

    if (document.getElementById('gameOverModal') != null) {
      const modal = bootstrap.Modal.getInstance(document.getElementById('gameOverModal'));
      if(modal) modal.hide();
    }    

    if(potentialMatch.path!='/2fa')
      sessionStorage.removeItem('tempjwt');

    if((sessionStorage.getItem('jwtToken')==null && (potentialMatch.path=='/locale_torneo_pregame' || potentialMatch.path=='/locale_torneo_home' || potentialMatch.path=='/locale_home_ia' || potentialMatch.path=='/locale_gioco_ia' || potentialMatch.path=='/locale_gioco' || potentialMatch.path=='/locale_home')) || (sessionStorage.getItem('tempjwt')==null && potentialMatch.path=='/2fa')){
      navigateTo("/");
      return;
    }

    const navbar = document.getElementById('navbar-content');
    if ((partitaincorso==true) && (potentialMatch.path === '/locale_torneo_pregame' || potentialMatch.path === '/locale_gioco' || potentialMatch.path === '/locale_gioco_ia' || potentialMatch.path === '/locale_torneo_gioco'))
      navbar.style.display = 'none';
    else
      navbar.style.display = 'block';

    if(partitaincorso==true)
      potentialMatch.view();
  } else {
    if(localStorage.getItem('lingua')==null)
      localStorage.setItem('lingua', 'it');
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
      const text = module.text;
      document.getElementById('main-content').innerHTML = '<div class="d-flex justify-content-center"><h2 class="text-white">'+text.p30+'</h2></div>';
    })
  }
}