window.updatestats=updatestats;
function updatestats(data) {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
		fetch('https://localhost:8000/g1/get_games', {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
				'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
			},
			body: JSON.stringify({
				gioco: data,
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
					let partitelist=partite;
					const dataJson = [
						{ label: text.p63, value: vittoria, color: "#2A9D8F" },
						{ label: text.p62, value: pareggio, color: "#F1FAEE" },
						{ label: text.p64, value: sconfitta, color: "#E63946" }
					];
					const labels = dataJson.map(item => item.label);
					const values = dataJson.map(item => item.value);
					const colors = dataJson.map(item => item.color);
					const ctx = document.getElementById('pieChart').getContext('2d');
					new Chart(ctx, {
						type: 'pie',
						data: {
							labels: labels,
							datasets: [{
								data: values,
								backgroundColor: colors,
							}]
						},
						options: {
							responsive: true,
							plugins: { legend: { position: 'top', } }
						}
					});
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
						<table id="partite"></table>`;
					const tableBody = document.querySelector('#partite tbody');
					jsonData.forEach(partitelist => {
						const row = document.createElement('tr');
						row.innerHTML = `
							<td><h2 class="text-white">${partitelist.nomep1}</h2></td>
							<td><h2 class="text-white">${partitelist.nomep2}</h2></td>
							<td><h2 class="text-white">${partitelist.nomep3}</h2></td>
							<td><h2 class="text-white">${partitelist.nomep4}</h2></td>
							<td><h2 class="text-white">${partitelist.esito}</h2></td>
							<td><h2 class="text-white">${partitelist.data}</h2></td>
						`;
						tableBody.appendChild(row);
						const row2 = document.createElement('tr');
						row2.innerHTML = `
							<td><h2 class="text-white">${partitelist.pp1}</h2></td>
							<td><h2 class="text-white">${partitelist.pp2}</h2></td>
							<td><h2 class="text-white">${partitelist.pp3}</h2></td>
							<td><h2 class="text-white">${partitelist.pp4}</h2></td>
							<td colspan="2"><br></td>
						`;
						tableBody.appendChild(row2);
						const row3 = document.createElement('tr');
						row3.innerHTML = `<td colspan="5"><br></td>`;
						tableBody.appendChild(row3);
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
                <a onclick="updatestats('${text.p4}')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p4+`</a>
                <a onclick="updatestats('${text.p44}')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p44+`</a>
                <br><br>
				<div id="statsid"></div>
			</div>`;
    })
}