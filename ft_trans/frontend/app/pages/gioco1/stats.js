function update(data) {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        if(data=="gioco1"){
            const content = document.getElementById('main-content');
		    content.innerHTML = `
                `;
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
                <a onclick="update('gioco1')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p4+`</a>
                <a onclick="update('torneog1')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p44+`</a>
                <div id="statsid">
                </div>
			</div>`;
    })
}