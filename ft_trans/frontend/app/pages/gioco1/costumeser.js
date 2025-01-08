import { navigateTo } from './../../js/router.js';

function update() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        document.getElementById('tempotext').innerHTML=text.p27+document.getElementById('Tempo').value+text.p28;
        document.getElementById('velmovtext').innerHTML=text.p29+document.getElementById('velmov').value;
        document.getElementById('velmovballtext').innerHTML=text.p35+document.getElementById('velmovball').value;
    })
}

export function loadCustumeserPage() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const content = document.getElementById('main-content');
        content.innerHTML = `
            <div class="d-flex justify-content-center align-items-center">
                <main class="form-signin m-auto mioform">
                    <h1 class="h3 mb-3 fw-normal text-white">`+text.p23+`</h1>
                    <label for="Tempo" id="tempotext" class="form-label text-white"></label>
                    <input type="range" class="form-range" value="1" min="1" max="5" step="1" id="Tempo">
                    <label for="velmovball" id="velmovballtext" class="form-label text-white"></label>
                    <input type="range" class="form-range" value="1" min="1" max="10" step="0.5" id="velmovball">
                    <label for="velmov" id="velmovtext" class="form-label text-white"></label>
                    <input type="range" class="form-range" value="1" min="1" max="10" step="0.5" id="velmov">
                    <h3 class="h3 mb-3 fw-normal text-white">`+text.p24+`</h3>
                    <div class="form-check">
                        <input class="form-check-input" type="radio" name="flexRadioDefault" id="classc" checked>
                        <label class="form-check-label text-white" for="classc">`+text.p25+`</label>
                    </div>
                    <div class="form-check">
                        <input class="form-check-input" type="radio" name="flexRadioDefault" id="caos">
                        <label class="form-check-label text-white" for="caos">Caos</label>
                    </div>
                    <button class="btn btn-primary w-100 py-2" id="iniza">`+text.p26+`</button>
                    <p class="mt-5 mb-3">
                        <a data-link href="/locale_home" class="h4 px-2 link-secondary text-white">`+text.p19+`</a>
                    </p>
                </main>
            </div>
        `;
        if(sessionStorage.getItem('tempog1')!=null)
            document.getElementById('Tempo').value=sessionStorage.getItem('tempog1');
        if(sessionStorage.getItem('velmovg1')!=null)
            document.getElementById('velmov').value=sessionStorage.getItem('velmovg1');
        if(sessionStorage.getItem('velmovballg1')!=null)
            document.getElementById('velmovball').value=sessionStorage.getItem('velmovballg1');
        if (sessionStorage.getItem('caosg1') != null) {
            const caosg1 = JSON.parse(sessionStorage.getItem('caosg1'));
            document.getElementById('classc').checked = !caosg1;
            document.getElementById('caos').checked = caosg1;
        }

        document.getElementById('Tempo').addEventListener('input', update);
        document.getElementById('velmov').addEventListener('input', update);
        document.getElementById('velmovball').addEventListener('input', update);
        update();

        document.getElementById('iniza').addEventListener('click', () => {
            sessionStorage.setItem('tempog1', document.getElementById('Tempo').value);
            sessionStorage.setItem('velmovg1', document.getElementById('velmov').value);
            sessionStorage.setItem('velmovballg1', document.getElementById('velmovball').value);
            if(document.getElementById('classc').checked)
                sessionStorage.setItem('caosg1', 'false');
            else
                sessionStorage.setItem('caosg1', 'true');
            if(sessionStorage.getItem('ia')=='false')
                navigateTo('/locale_gioco');
            else if(sessionStorage.getItem('ia')=='torneo')
                navigateTo('/locale_torneo_pregame');
            else
                navigateTo('/locale_gioco_ia');
        });
    })
}
