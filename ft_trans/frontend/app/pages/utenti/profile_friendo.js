export function loadProfileFriendoPage() {
	if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
	import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
	.then((module) => {
		const text = module.text;
		fetch(sessionStorage.getItem("hostapp")+'/users/profilefriendo', {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
				'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
			},
			body: JSON.stringify({
				idamico: sessionStorage.getItem('idamico')
			}),
		})
		.then(response => {
			const status = response.status;
			if (status == 200) {
				return response.json().then(data => {
					let partite=data.totegame;
					let vittoria=data.totwin;
					let sconfitta=data.totsco;
					let pareggio=data.totpar;
					let partitelist=data.partite;
					const content = document.getElementById('main-content');
					if (data.online == true)
						content.innerHTML = `
							<div class="d-flex justify-content-center align-items-center">
								<div class="container my-5">
									<div class="row align-items-center">
										<div class="col-md-6 text-center"><img src="./../img/`+data.img+`" width="200" height="200" class="rounded-circle" /></div>
										<div class="col-md-6">
											<h1 class="text-white text-center">`+text.p108+`</h1>
											<br>
											<h2 class="text-white">`+text.p6+`: `+data.nome+`</h2>
											<h2 class="text-white">`+text.p109+`: <span class="bg-success rounded-circle" style="width: 10px; height: 10px; display: inline-block;"></span></h2>
											<br>
											<a data-link href="/friend"><h3 class="text-white">`+text.p107+`</h3></a>
										</div>
									</div>
								</div>
							</div>
							<div class="container my-5">
								<div class="row align-items-center">
									<div class="col-md-6 text-center">
										<canvas id="pieChart"></canvas>
									</div>
									<div class="col-md-6">
										<h2 class="text-white">`+text.p65+partite+`</h2>
										<h2 class="text-white">`+text.p63+vittoria+`</h2>
										<h2 class="text-white">`+text.p62+pareggio+`</h2>
										<h2 class="text-white">`+text.p64+sconfitta+`</h2>
									</div>
								</div>
							</div>
							<table id="partite" class="table-bordered w-70"></table>`;
					else
						content.innerHTML = `
							<div class="d-flex justify-content-center align-items-center">
								<div class="container my-5">
									<div class="row align-items-center">
										<div class="col-md-6 text-center"><img src="./../img/`+data.img+`" width="200" height="200" class="rounded-circle" /></div>
										<div class="col-md-6">
											<h1 class="text-white text-center">`+text.p108+`</h1>
											<br>
											<h2 class="text-white">`+text.p6+`: `+data.nome+`</h2>
											<h2 class="text-white">`+text.p109+`: <span class="bg-danger rounded-circle" style="width: 10px; height: 10px; display: inline-block;"></span></h2>
											<br>
											<a data-link href="/friend"><h3 class="text-white">`+text.p107+`</h3></a>
										</div>
									</div>
								</div>
							</div>
							<div class="container my-5">
									<div class="row align-items-center">
										<div class="col-md-6 text-center">
											<canvas id="pieChart"></canvas>
										</div>
										<div class="col-md-6">
											<h2 class="text-white">`+text.p65+partite+`</h2>
											<h2 class="text-white">`+text.p63+vittoria+`</h2>
											<h2 class="text-white">`+text.p62+pareggio+`</h2>
											<h2 class="text-white">`+text.p64+sconfitta+`</h2>
										</div>
									</div>
								</div>
								<table id="partite" class="table-bordered w-70"></table>`;

					const ctx = document.getElementById("pieChart").getContext('2d');
					new Chart(ctx, {
						type: 'pie',
						data: {
							labels: [text.p63, text.p62, text.p64],
							datasets: [{
								data: [vittoria, pareggio, sconfitta],
								backgroundColor: ["#2A9D8F", "#F1FAEE", "#E63946"],
							}]
						},
						options: {
							responsive: true,
							plugins: { 
								legend: { position: 'top' } 
							}
						}
					});
					const tableBody = document.getElementById('partite');
					partitelist.forEach(partitelist => {
						let esito=partitelist.esito;
						if(esito=="P")esito=text.p33;
						if(esito=="V")esito=text.p69;
						if(esito=="S")esito=text.p70;
						let p3nome=partitelist.nomep3;
						let scorep3=partitelist.pp3;
						if(p3nome==null){
							p3nome=" ";
							scorep3=" ";
						}
						let p4nome=partitelist.nomep4;
						let scorep4=partitelist.pp4;
						if(p4nome==null){
							p4nome=" ";
							scorep4=" ";
						}
						const row = document.createElement('tr');
						row.innerHTML = `
							<td><h2 class="text-white p-3">${partitelist.nomep1}<br>${partitelist.pp1}</h2></td>
							<td><h2 class="text-white p-3">${partitelist.nomep2}<br>${partitelist.pp2}</h2></td>
							<td><h2 class="text-white p-3">${p3nome}<br>${scorep3}</h2></td>
							<td><h2 class="text-white p-3">${p4nome}<br>${scorep4}</h2></td>
							<td><h2 class="text-white p-3">${partitelist.data}<br>${esito}</h2></td>
						`;
						tableBody.appendChild(row);
					});
				});
			} else{
				alert("error");
			}// logout();
		})
		.catch(error => { alert(error); /*logout();*/ })
    })
}