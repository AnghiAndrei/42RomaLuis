import { navigateTo } from './../../js/router.js';

export function loadProfilePage() {
	if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
	import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
	.then((module) => {
		const text = module.text;
		fetch('https://localhost:8000/users/profile', {
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
							<main class="form-signin m-auto mioform">
								<h1 class="text-white text-center">`+text.p73+`</h1>
								<br>
								<img src="`+sessionStorage.getItem('imguser')+`" width="50" height="50" class="rounded-circle" />
								<h2 class="text-white">`+text.p39+`: `+data.email+`</h2>
								<h2 class="text-white">`+text.p6+`: `+data.nome+`</h2>
								<br>
								<a data-link href="/update_profile"><h2 class="text-white">`+text.p74+`</h2></a>
								<a data-link href="/stats"><h2 class="text-white">`+text.p42+`</h2></a>
								<h2 onclick="logout()" class="text-white">`+text.p43+`</h2>
							</main>
						</div>`;
				});
			} else navigateTo('/');
		})
		.catch(error => { navigateTo('/'); })
    })
}
