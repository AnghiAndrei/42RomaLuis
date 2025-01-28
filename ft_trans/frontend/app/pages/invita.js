import { navigateTo } from './../js/router.js';
import { logout, sanitizeInput } from './../js/assets.js';

function get_friend() {
	fetch(sessionStorage.getItem("hostapp")+'/users/get_friend', {
		method: 'GET',
		headers: {
			'Content-Type': 'application/json',
			'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
		},
	})
	.then(response => {
		const status = response.status;
		if (status == 200) {
			return response.json().then(data => {
				let listaamici = data.lista_amici;
				const select = document.getElementById('amico');
				listaamici.forEach(amico => {
					const option = document.createElement('option');
					option.value = amico.idfriend;
					option.text = amico.nome;
					select.appendChild(option);
				});
			});
		} else if (status == 400){
			;
		} else if (status == 401){
			const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
			modal2.show();
			document.getElementById('ERROREMessage').innerHTML=text.p67;
			logout();
		} else{
			const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
			modal2.show();
			document.getElementById('ERROREMessage').innerHTML=text.p66;
		}
	})
	.catch(error => {
		const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
		modal2.show();
		document.getElementById('ERROREMessage').innerHTML=text.p66;
	});
}

export function loadInvitaHomePage() {
	if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
	import(`./../traduzioni/${localStorage.getItem('lingua')}.js`)
	.then((module) => {
		const text = module.text;
		const content = document.getElementById('main-content');
		content.innerHTML = `
		<div class="d-flex justify-content-center align-items-center">
			<main class="form-signin m-auto mioform">
				<h1 class="h3 mb-3 fw-normal text-white">`+text.p100+`</h1>
				<div class="form-floating mb-3">
					<input type="text" class="form-control text-black" id="posto" placeholder="`+text.p101+`">
					<label class="text-black" for="posto">`+text.p101+`</label>
				</div>
				<br>
				<label for="amico" class="form-label text-white">`+text.p102+`</label>
				<select class="form-select" id="amico"></select>
				<label for="gioco" class="form-label text-white">`+text.p103+`</label>
				<select class="form-select" id="gioco">
					<option value="`+text.p4+`">`+text.p4+`</option>
					<option value="`+text.p52+`">`+text.p52+`</option>
					<option value="`+text.p44+`">`+text.p44+`</option>
				</select>
				<h2 id="testoerrore" class="text-white text-center"></h2>
				<button class="btn btn-primary w-100 py-2" id="invia">`+text.p104+`</button>
				<p class="mt-5 mb-3">
					<a data-link href="/giochi" class="h4 px-2 link-secondary text-white">`+text.p31+`</a>
				</p>
			</main>
		</div>`;
		get_friend();
		document.getElementById('invia').addEventListener('click', () => {
			let amico=document.getElementById('amico').value;
			let posto=document.getElementById('posto').value;
			let gioco=document.getElementById('gioco').value;

			amico=sanitizeInput(amico);
			posto=sanitizeInput(posto);
			gioco=sanitizeInput(gioco);

			if(amico=="" || amico=="undefined" || posto=="" || gioco==""){
				document.getElementById('testoerrore').innerHTML=text.p72;
				return;
			}

			const friendSocket = new WebSocket(sessionStorage.getItem('hostsock')+'/chat/'+amico+'/');
			friendSocket.onmessage = function (event) { ; };
			friendSocket.onclose = function () { ; };
			friendSocket.onerror = function (error) { ; };
			friendSocket.onopen = function () {
				if (friendSocket.readyState === WebSocket.OPEN) {
					try {	
						friendSocket.send(JSON.stringify({
							message: text.p105+gioco+text.p106+posto,
							token: sessionStorage.getItem('jwtToken'),
						}));
					} catch (error) {
						const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
						modal2.show();
						document.getElementById('ERROREMessage').innerHTML=text.p96;
					}
				} else {
					const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
					modal2.show();
					document.getElementById('ERROREMessage').innerHTML=text.p96;
				}
				navigateTo("/giochi");
			};
		});
	})
}