import { navigateTo } from '../../js/router.js';

function update() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        document.getElementById('giocatoritext').innerHTML=text.p45+document.getElementById('giocatori').value;
    })
}

export function loadLocaleHomeIaGame1Page() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const content = document.getElementById('main-content');
        content.innerHTML = `
            <div class="d-flex justify-content-center align-items-center">
                <main class="form-signin m-auto mioform">
                    <h1 class="text-white">`+text.p17+`</h1>
                    <label for="giocatori" id="giocatoritext" class="form-label text-white"></label>
                    <input type="range" class="form-range" value="2" min="2" max="4" step="1" id="giocatori">
                    <button class="btn btn-primary w-100 py-2" id="iniza">`+text.p18+`</button>
                    <p class="mt-5 mb-3">
                        <a data-link href="/giochi" class="h4 px-2 link-secondary text-white">`+text.p19+`</a>
                    </p>
                </main>
            </div>
        `;

        document.getElementById('giocatori').addEventListener('input', update);
        update();

        if(sessionStorage.getItem('nplayerg1')!=null)
            document.getElementById('giocatori').value=sessionStorage.getItem('nplayerg1');

        document.getElementById('iniza').addEventListener('click', () => {
            sessionStorage.setItem('nplayerg1', document.getElementById('giocatori').value);
            sessionStorage.setItem('ia', "true");
            navigateTo('/costumeser');
        });
    })
}