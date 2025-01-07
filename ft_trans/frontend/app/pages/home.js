export function loadHomePage() {
	if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
	import(`./../traduzioni/${localStorage.getItem('lingua')}.js`)
	.then((module) => {
		const text = module.text;
		const content = document.getElementById('main-content');
		content.innerHTML = `
			<div class="d-flex flex-column justify-content-center align-items-center">
				<h1 class="text-white">`+text.p1+`</h1>
				<br><br>
				<h3 class="text-white">`+text.p2+`</h3>
			</div>`;
	})
}