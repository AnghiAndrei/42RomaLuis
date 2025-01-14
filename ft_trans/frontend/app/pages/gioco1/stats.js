window.updatestats=updatestats;
function updatestats(data) {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
		if(data=="lp24" || data=="lpia"){
			fetch('https://localhost:8000/g1/get_game', {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
					'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
				},
				body: JSON.stringify({
					game: data,
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
						const content = document.getElementById('statsid');
						content.innerHTML = `
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
				} else if (status == 404){
					const content = document.getElementById('statsid');
					content.innerHTML = `<h2 class="text-white text-center">`+text.p68+`</h2>`;
				} else if (status == 401){
					const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
					modal2.show();
					document.getElementById('ERROREMessage').innerHTML=text.p67;
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
		} else if(data=="lt24"){
			fetch('https://localhost:8000/g1/get_tornament', {
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
						let tornei=data.totegame;
						let vittoria=data.totwin;
						let sconfitta=data.totsco;
						let torneolist=data.tornei;
						const content = document.getElementById('statsid');
						content.innerHTML = `
							<div class="container my-5">
								<div class="row align-items-center">
									<div class="col-md-6 text-center">
										<canvas id="pieChart"></canvas>
									</div>
									<div class="col-md-6">
										<h2 class="text-white">`+text.p71+tornei+`</h2>
										<h2 class="text-white">`+text.p63+vittoria+`</h2>
										<h2 class="text-white">`+text.p64+sconfitta+`</h2>
									</div>
								</div>
							</div>
							<table id="tornei" class="table-bordered w-70"></table>`;

						const ctx = document.getElementById("pieChart").getContext('2d');
						new Chart(ctx, {
							type: 'pie',
							data: {
								labels: [text.p69, text.p70],
								datasets: [{
									data: [vittoria, sconfitta],
									backgroundColor: ["#2A9D8F", "#E63946"],
								}]
							},
							options: {
								responsive: true,
								plugins: { 
									legend: { position: 'top' } 
								}
							}
						});

						const tableBody = document.getElementById('tornei');
						torneolist.forEach(torneolist => {
							let esito=torneolist.esito;
							if(esito=="V")esito=text.p69;
							if(esito=="S")esito=text.p70;

							let p3nome=torneolist.nomep3;
							let scorep3=torneolist.pp3;
							if(p3nome==null){
								p3nome=" ";
								scorep3=" ";
							}

							let p4nome=torneolist.nomep4;
							let scorep4=torneolist.pp4;
							if(p4nome==null){
								p4nome=" ";
								scorep4=" ";
							}

							const row = document.createElement('tr');
							row.innerHTML = `
								<td><h2 class="text-white p-3">${torneolist.nomep1}</h2></td>
								<td><h2 class="text-white p-3">${torneolist.nomep2}</h2></td>
								<td><h2 class="text-white p-3">${p3nome}</h2></td>
								<td><h2 class="text-white p-3">${p4nome}</h2></td>
								<td><h2 class="text-white p-3">${torneolist.data}<br>${esito}</h2></td>
							`;
							tableBody.appendChild(row);
						});
					});
				} else if (status == 404){
					const content = document.getElementById('statsid');
					content.innerHTML = `<h2 class="text-white text-center">`+text.p68+`</h2>`;
				} else if (status == 401){
					const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
					modal2.show();
					document.getElementById('ERROREMessage').innerHTML=text.p67;
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
    })
}

export function loadStatsPage() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const content = document.getElementById('main-content');
		content.innerHTML = `
			<div class="d-flex flex-column justify-content-center align-items-center">
				<h1 class="text-white text-center">`+text.p60+`</h1>
				<h2 class="text-white text-center">`+text.p61+`</h2>
                <a onclick="updatestats('lp24')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p4+`</a>
                <a onclick="updatestats('lpia')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p44+`</a>
                <a onclick="updatestats('lt24')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p52+`</a>
                <br><br>
				<div id="statsid" class="d-flex flex-column align-items-center w-100" style="overflow-y: auto;"></div>
			</div>`;
    })
}