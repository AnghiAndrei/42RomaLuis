import { navigateTo } from './../../js/router.js';

export function loadModifyPage() {
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
          						<h1 class="h3 mb-3 fw-normal text-white">`+text.p74+`</h1>
								<div class="form-floating mb-3">
									<input type="text" class="form-control text-black" value="`+data.nome+`" id="nome" placeholder="`+text.p6+`">
									<label class="text-black" for="nome">`+text.p6+`</label>
								</div>
								<div class="form-floating mb-3">
									<input type="file" class="form-control text-black" id="imgform" placeholder="`+text.p75+`">
									<label class="text-black" for="imgform">`+text.p75+`</label>
								</div>
          						<h2 id="testoerrore" class="text-white"></h2>
          						<button class="btn btn-primary w-100 py-2" id="loggin">`+text.p76+`</button>
        					</main>
      					</div>`;
						  document.getElementById('loggin').addEventListener('click', () => {
							let nome=document.getElementById('nome').value;
							let imgform=document.getElementById('imgform').value;
					  
							if(nome==""){
							  document.getElementById('testoerrore').innerHTML=text.p72;
							  return;
							}
					  
							fetch('https://localhost:8000/users/modify', {
							  method: 'POST',
							  headers: {
								'Content-Type': 'application/json',
							  },
							  body: JSON.stringify({
								nome: nome,
								img: imgform
							}),
							})
							.then(response => {
								const status = response.status;
								if (status == 200) {
								  return response.json().then(data => {
									sessionStorage.setItem('tempjwt', data.tempjwt);
									sessionStorage.setItem('p1', nome);
									sessionStorage.setItem('tp1', nome);
									navigateTo('/profile');
								  });
								} else if (status == 204)
								  document.getElementById('testoerrore').innerHTML=text.p46;
								else
								  document.getElementById('testoerrore').innerHTML=text.p47;
							})
							.catch(error => {
							  document.getElementById('testoerrore').innerHTML=text.p47;
							});
						  });
				});
			} else navigateTo('/');
		})
		.catch(error => { navigateTo('/'); })
    })
}
