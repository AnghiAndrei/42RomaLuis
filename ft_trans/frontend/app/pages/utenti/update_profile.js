import { navigateTo } from '../../js/router.js';
import { isEmptyOrWhitespace, updateNavbar } from '../../js/assets.js';

export function loadModifyPage() {
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
        					<main class="form-signin m-auto mioform">
          						<h1 class="h3 mb-3 fw-normal text-white">`+text.p74+`</h1>
								<div class="form-floating mb-3">
									<input type="text" class="form-control text-black" value="`+data.nome+`" id="nome" placeholder="`+text.p6+`">
									<label class="text-black" for="nome">`+text.p6+`</label>
								</div>
								<div class="form-floating mb-3">
									<input type="file" accept="image/png" class="form-control text-black" id="imgform" placeholder="`+text.p75+`">
									<label class="text-black" for="imgform">`+text.p75+`</label>
								</div>
          						<h2 id="testoerrore" class="text-white"></h2>
          						<button class="btn btn-primary w-100 py-2" id="loggin">`+text.p76+`</button>
								<p class="mt-5 mb-3">
									<a data-link href="/profile" class="h4 px-2 link-secondary text-white">`+text.p77+`</a>
								</p>
        					</main>
      					</div>`;
						  document.getElementById('loggin').addEventListener('click', () => {
							let nome=document.getElementById('nome').value;
							const file = document.getElementById('imgform').files[0];

							if(nome=="" || isEmptyOrWhitespace(nome)){
							  document.getElementById('testoerrore').innerHTML=text.p72;
							  return;
							}

							const formData = new FormData();
							formData.append('nome', nome);
							if (file){
								var maxFileSize = 5 * 1024 * 1024;
								if (file.size > maxFileSize){
									document.getElementById('testoerrore').innerHTML=text.p78;
									return;
								}
								formData.append('img', file);
							}

							fetch(sessionStorage.getItem("hostapp")+'/users/modify', {
							  method: 'POST',
							  headers: { 'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'), },
							  body: formData
							})
							.then(response => {
								const status = response.status;
								if (status == 200) {
									return response.json().then(data => {
										sessionStorage.setItem('imguser', "./../img/"+data.imguser);
										sessionStorage.setItem('p1', nome);
										sessionStorage.setItem('tp1', nome);
										updateNavbar();
										navigateTo('/profile');
									});
								} else if (status == 204)
								  document.getElementById('testoerrore').innerHTML=text.p46;
								else if (status == 413)
									document.getElementById('testoerrore').innerHTML=text.p78;
								else if (status == 420)
									document.getElementById('testoerrore').innerHTML=text.p111;
								else if (status == 414)
									document.getElementById('testoerrore').innerHTML=text.p79;
								else
								  document.getElementById('testoerrore').innerHTML=text.p47;
							})
							.catch(error => {
							  document.getElementById('testoerrore').innerHTML=text.p47;
							});
						  });
				});
			} else logout();
		})
		.catch(error => { logout(); })
    })
}
