import { navigateTo } from './../../js/router.js';
import { logout } from './../../js/assets.js';

window.searchFriend=searchFriend;
function searchFriend() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const query = document.getElementById("searchBar").value;
        fetch(`https://localhost:8000/users/search_friend?query=${query}`, {
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
                    let lista_amici=data.lista_amici;
                    document.getElementById("friendList").innerHTML = "";
                    if (lista_amici && lista_amici.length > 0) {
                        lista_amici.forEach(amico => {
                            const li = document.createElement("li");
                            li.classList.add("list-group-item", "d-flex", "align-items-center");
                            li.innerHTML = `
                                <img src="./../img/${amico.imgfriend}" alt="${amico.nome}" class="rounded-circle me-3" width="40" height="40"/>
                                <span>${amico.nome}</span>`;
                            friendList.appendChild(li);
                        });
                    } else {
                        const li = document.createElement("li");
                        li.classList.add("list-group-item");
                        li.textContent = text.p90;
                        friendList.appendChild(li);
                    }
                });
            } else if (status == 401){
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p67;
                logout();
            } else {
                document.getElementById("friendList").innerHTML = "";
                const li = document.createElement("li");
                li.classList.add("list-group-item");
                li.textContent = text.p90;
                friendList.appendChild(li);
            }
        })
        .catch(error => {
            document.getElementById("friendList").innerHTML = "";
            const li = document.createElement("li");
            li.classList.add("list-group-item");
            li.textContent = text.p90;
            friendList.appendChild(li);
        });
    });
}

window.updatepagefriendo=updatepagefriendo;
function updatepagefriendo(data) {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
		if(data=="listaamici"){
			fetch('https://localhost:8000/users/get_friend', {
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
						let listaamici=data.richiesta_list;
						const content = document.getElementById('amicirichieste');
						content.innerHTML = `<table id="amici" class="w-70"></table>`;

						const tableBody = document.getElementById('amici');
						listaamici.forEach(listaamici => {
							const row = document.createElement('tr');
							row.innerHTML = `
								<td><img src="./../img/`+listaamici.img+`" alt="mdo" width="32" height="32" class="rounded-circle"></td>
								<td><h2 class="text-white p-3">`+listaamici.img+`</h2></td>
								<td><br></td>
								<td><h2 class="text-white p-3">`+text.p84+`</h2></td>
							`;
							tableBody.appendChild(row);
                            const row2 = document.createElement('tr');
							row2.innerHTML = `<td colspa="3"><br></td>`;
							tableBody.appendChild(row2);
						});
					});
				} else if (status == 400){
					const content = document.getElementById('amicirichieste');
					content.innerHTML = `<h2 class="text-white text-center">`+text.p87+`</h2>`;
				} else if (status == 401){
					const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
					modal2.show();
					document.getElementById('ERROREMessage').innerHTML=text.p67;
					logout();
				} else{
					alert("error2");
					const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
					modal2.show();
					document.getElementById('ERROREMessage').innerHTML=text.p66;
				}
			})
			.catch(error => {
				alert("error1: "+error);
				const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
				modal2.show();
				document.getElementById('ERROREMessage').innerHTML=text.p66;
			});
		} else if(data=="richiesteamicizia"){
			fetch('https://localhost:8000/users/get_request', {
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
						let listaamici=data.lista_richiesta;
						const content = document.getElementById('amicirichieste');
						content.innerHTML = `<table id="amici" class="w-70"></table>`;

						const tableBody = document.getElementById('amici');
						listaamici.forEach(listaamici => {
							const row = document.createElement('tr');
							row.innerHTML = `
								<td><img src="./../img/`+listaamici.img+`" alt="mdo" width="32" height="32" class="rounded-circle"></td>
								<td><h2 class="text-white p-3">`+listaamici.img+`</h2></td>
								<td><br></td>
								<td>
                                    <h2 class="text-white p-3">`+text.p86+`</h2>
                                    <h2 class="text-white p-3">`+text.p85+`</h2>
                                </td>
							`;
							tableBody.appendChild(row);
                            const row2 = document.createElement('tr');
							row2.innerHTML = `<td colspa="3"><br></td>`;
							tableBody.appendChild(row2);
						});
					});
				} else if (status == 400){
					const content = document.getElementById('amicirichieste');
					content.innerHTML = `<h2 class="text-white text-center">`+text.p88+`</h2>`;
				} else if (status == 401){
					const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
					modal2.show();
					document.getElementById('ERROREMessage').innerHTML=text.p67;
					logout();
				} else{
					alert("error2");
					const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
					modal2.show();
					document.getElementById('ERROREMessage').innerHTML=text.p66;
				}
			})
			.catch(error => {
				alert("error1: "+error);
				const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
				modal2.show();
				document.getElementById('ERROREMessage').innerHTML=text.p66;
			});
		} else if(data=="cercaamico"){
            const content = document.getElementById('amicirichieste');
            content.innerHTML = `<div class="container mt-4">
                                    <input type="text" id="searchBar" class="form-control" placeholder="`+text.p91+`" onkeyup="searchFriend()" />
                                    <ul id="friendList" class="list-group mt-3"></ul>
                                </div>`;
        }
    })
}

export function loadFriendPage() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const content = document.getElementById('main-content');
		content.innerHTML = `
			<div class="d-flex flex-column justify-content-center align-items-center">
				<h1 class="text-white text-center">`+text.p82+`</h1>
				<h2 class="text-white text-center">`+text.p83+`</h2>
                <div class="d-flex justify-content-start mt-3">
                    <a onclick="updatepagefriendo('listaamici')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p80+`</a>
                    <a onclick="updatepagefriendo('richiesteamicizia')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p81+`</a>
                    <a onclick="updatepagefriendo('cercaamico')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p89+`</a>
                </div>
                <br><br>
				<div id="amicirichieste" class="d-flex flex-column align-items-center w-100"></div>
			</div>`;
    })
}