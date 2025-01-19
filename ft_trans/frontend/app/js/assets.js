import { navigateTo,router } from '../js/router.js';

/* ========== LOGOUT ========== */
window.logout = logout;
export function logout() {
  	sessionStorage.removeItem('jwtToken');
  	sessionStorage.removeItem('imguser');
  	sessionStorage.removeItem('tp1');
  	sessionStorage.removeItem('p1');
  	navigateTo("/");
  	updateNavbar();
}

/* ========== LINGUE ========== */
window.cambialingua = cambialingua;
function cambialingua(lingua){
	localStorage.setItem('lingua', lingua);
	router();
}

/* ========== NAVBAR ========== */
export function updateNavbar() {
	if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
	import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
  	.then((module) => {
      	const text = module.text;
      	if (sessionStorage.getItem('jwtToken')==null) {
        	document.getElementById('navbar-content').innerHTML = `
				<div class="container">
					<div class="d-flex flex-wrap align-items-center justify-content-center justify-content-lg-start">
						<a data-link href="/" class="d-flex align-items-center mb-2 mb-lg-0 link-body-emphasis text-decoration-none">
						<img class="bi me-2" width="40" height="32" src="./img/favicon.png" />
					</a>
					<ul class="nav col-12 col-lg-auto me-lg-auto mb-2 justify-content-center mb-md-0">
						<li><a data-link href="/" class="nav-link px-2 link-secondary text-white">`+text.p36+`</a></li>
						<li><a data-link href="/giochi" class="nav-link px-2 link-secondary text-white">`+text.p37+`</a></li>
						<li><a download href="./../module.txt" class="nav-link px-2 link-secondary text-white">`+text.p38+`</a></li>
						<li><a data-link href="/login" class="nav-link px-2 link-secondary text-white">`+text.p11+`</a></li>
					</ul>
					<div class="dropdown text-end">
						<a href="#" class="d-block link-body-emphasis text-decoration-none dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false">
							<img src="" id="imguser" alt="mdo" width="32" height="32">
						</a>
						<ul class="dropdown-menu text-small" style="">
							<li><a class="dropdown-item" data-link href="/" onclick="cambialingua('it')"><img src="./../img/lingue/it.png" alt="mdo" width="32" height="32"> Italiano</a></li>
							<li><a class="dropdown-item" data-link href="/" onclick="cambialingua('gb')"><img src="./../img/lingue/gb.png" alt="mdo" width="32" height="32"> English</a></li>
							<li><a class="dropdown-item" data-link href="/" onclick="cambialingua('jp')"><img src="./../img/lingue/jp.png" alt="mdo" width="32" height="32"> 日本語</a></li>
							<li><a class="dropdown-item" data-link href="/" onclick="cambialingua('itnapol')"><img src="./../img/lingue/itnapol.png" alt="mdo" width="32" height="32"> Napoletano</a></li>
						</ul>
					</div>
				</div>
          	</div>`;
      	} else {
			document.getElementById('navbar-content').innerHTML = `
				<div class="container">
					<div class="d-flex flex-wrap align-items-center justify-content-center justify-content-lg-start">
						<a data-link href="/" class="d-flex align-items-center mb-2 mb-lg-0 link-body-emphasis text-decoration-none">
							<img class="bi me-2" width="40" height="32" src="./img/favicon.png" />
						</a>
						<ul class="nav col-12 col-lg-auto me-lg-auto mb-2 justify-content-center mb-md-0">
							<li><a data-link href="/" class="nav-link px-2 link-secondary text-white">`+text.p36+`</a></li>
							<li><a data-link href="/giochi" class="nav-link px-2 link-secondary text-white">`+text.p37+`</a></li>
							<li><a download href="./../module.txt" class="nav-link px-2 link-secondary text-white">`+text.p38+`</a></li>
						</ul>
						<div class="dropdown text-end">
							<a href="#" class="d-block link-body-emphasis text-decoration-none dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false">
								<img src="`+sessionStorage.getItem('imguser')+`" alt="mdo" width="32" height="32" class="rounded-circle">
							</a>
							<ul class="dropdown-menu text-small" style="">
								<li><a class="dropdown-item" data-link href="/profile">`+text.p41+`</a></li>
								<li><a class="dropdown-item" data-link href="/stats">`+text.p42+`</a></li>
								<li><a class="dropdown-item" data-link href="/friend">`+text.p82+`</a></li>
								<li><hr class="dropdown-divider"></li>
								<li><a class="dropdown-item" data-link href="/" onclick="logout()">`+text.p43+`</a></li>
							</ul>
						</div>
						<div class="dropdown text-end">
							<a href="#" class="d-block link-body-emphasis text-decoration-none dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false">
								<img src="" id="imguser" alt="mdo" width="32" height="32">
							</a>
							<ul class="dropdown-menu text-small" style="">
								<li><a class="dropdown-item" data-link href="/" onclick="cambialingua('it')"><img src="./../img/lingue/it.png" alt="mdo" width="32" height="32"> Italiano</a></li>
								<li><a class="dropdown-item" data-link href="/" onclick="cambialingua('gb')"><img src="./../img/lingue/gb.png" alt="mdo" width="32" height="32"> English</a></li>
								<li><a class="dropdown-item" data-link href="/" onclick="cambialingua('jp')"><img src="./../img/lingue/jp.png" alt="mdo" width="32" height="32"> 日本語</a></li>
								<li><a class="dropdown-item" data-link href="/" onclick="cambialingua('itnapol')"><img src="./../img/lingue/itnapol.png" alt="mdo" width="32" height="32"> Napoletano</a></li>
							</ul>
						</div>
					</div>
				</div>`;
    	}
		document.getElementById('imguser').src='./../img/lingue/'+localStorage.getItem('lingua')+'.png';
  	})
}

export function isEmptyOrWhitespace(str) {return !str || str.trim().length === 0;}