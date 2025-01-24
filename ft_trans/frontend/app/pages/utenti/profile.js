import { navigateTo } from './../../js/router.js';
import { logout } from './../../js/assets.js';

export function loadProfilePage() {
	if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
	import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
	.then((module) => {
		const text = module.text;
		fetch(sessionStorage.getItem("hostapp")+'/users/profile', {
			method: 'GET',
			headers: {
				'Content-Type': 'application/json',
				'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
			}
		})
		.then(response => {
			const status = response.status;
			if (status == 200) {
				return response.json().then(data => {
					const content = document.getElementById('main-content');
					content.innerHTML = `
						<div class="d-flex justify-content-center align-items-center">
							<div class="container my-5">
								<div class="row align-items-center">
									<div class="col-md-6 text-center"><img src="`+sessionStorage.getItem('imguser')+`" width="200" height="200" class="rounded-circle" /></div>
									<div class="col-md-6">
										<h1 class="text-white text-center">`+text.p73+`</h1>
										<br>
										<h2 class="text-white">`+text.p39+`: `+data.email+`</h2>
										<h2 class="text-white">`+text.p6+`: `+data.nome+`</h2>
										<br>
										<a data-link href="/update_profile"><h3 class="text-white">`+text.p74+`</h3></a>
										<a data-link href="/stats"><h3 class="text-white">`+text.p42+`</h3></a>
										<a data-link href="/friend"><h3 class="text-white">`+text.p82+`</h3></a>
										<h3 onclick="logout()" class="text-white">`+text.p43+`</h3>
									</div>
								</div>
							</div>
						</div>`;
				});
			} else logout();
		})
		.catch(error => { logout(); })
    })
}
