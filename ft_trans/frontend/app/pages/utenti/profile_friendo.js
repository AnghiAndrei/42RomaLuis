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
							</div>`;
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
						</div>`;
				});
			} else logout();
		})
		.catch(error => { logout();})
    })
}
