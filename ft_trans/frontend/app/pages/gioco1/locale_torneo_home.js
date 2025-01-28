import { isEmptyOrWhitespace, sanitizeInput } from './../../js/assets.js';
import { navigateTo } from './../../js/router.js';

function update() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        document.getElementById('giocatoritext').innerHTML=text.p17+document.getElementById('giocatori').value;

        const content = document.getElementById('gest');
        switch (parseInt(document.getElementById('giocatori').value, 10)) {
            case 2:
                content.innerHTML = `
                    <div class="form-floating mb-3">
                        <input type="text" class="form-control text-black" id="gest1" placeholder="`+text.p6+` Gest1">
                        <label class="text-black" for="gest1">`+text.p6+` Gest1</label>
                    </div>
                `;
                if(sessionStorage.getItem('p2')!=null)
                    document.getElementById('gest1').value=sessionStorage.getItem('p2');
                break;
            case 3:
                content.innerHTML = `
                    <div class="form-floating mb-3">
                        <input type="text" class="form-control text-black" id="gest1" placeholder="`+text.p6+` Gest1">
                        <label class="text-black" for="gest1">`+text.p6+` Gest1</label>
                    </div>
                    <div class="form-floating mb-3">
                        <input type="text" class="form-control text-black" id="gest2" placeholder="`+text.p6+` Gest2">
                        <label class="text-black" for="gest2">`+text.p6+` Gest2</label>
                    </div>
                `;
                if(sessionStorage.getItem('p2')!=null)
                    document.getElementById('gest1').value=sessionStorage.getItem('p2');
                if(sessionStorage.getItem('p3')!=null)
                    document.getElementById('gest2').value=sessionStorage.getItem('p3');
                break;
            case 4:
                content.innerHTML = `
                    <div class="form-floating mb-3">
                        <input type="text" class="form-control text-black" id="gest1" placeholder="`+text.p6+` Gest1">
                        <label class="text-black" for="gest1">`+text.p6+` Gest1</label>
                    </div>
                    <div class="form-floating mb-3">
                        <input type="text" class="form-control text-black" id="gest2" placeholder="`+text.p6+` Gest2">
                        <label class="text-black" for="gest2">`+text.p6+` Gest2</label>
                    </div>
                    <div class="form-floating mb-3">
                        <input type="text" class="form-control text-black" id="gest3" placeholder="`+text.p6+` Gest3">
                        <label class="text-black" for="gest3">`+text.p6+` Gest3</label>
                    </div>
                `;
                if(sessionStorage.getItem('p2')!=null)
                    document.getElementById('gest1').value=sessionStorage.getItem('p2');
                if(sessionStorage.getItem('p3')!=null)
                    document.getElementById('gest2').value=sessionStorage.getItem('p3');
                if(sessionStorage.getItem('p4')!=null)
                    document.getElementById('gest3').value=sessionStorage.getItem('p4');
                break;
            default:
                break;
        }
    })
}

export function loadLocaleHomeTorneoGame1Page() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const content = document.getElementById('main-content');
        content.innerHTML = `
            <div class="d-flex justify-content-center align-items-center">
                <main class="form-signin m-auto mioform">
                    <h1 class="text-white">`+text.p51+`</h1>
                    <label for="giocatori" id="giocatoritext" class="form-label text-white"></label>
                    <input type="range" class="form-range" value="2" min="2" max="4" step="1" id="giocatori">
                    <div id="gest"></div>
                    <h3 class="h3 mb-3 fw-normal text-white" id="texterror"></h3>
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
            if(document.getElementById('giocatori').value==2){
                let p2=document.getElementById('gest1').value;
                if(p2=='' || isEmptyOrWhitespace(p2)){
                    document.getElementById('texterror').innerHTML=text.p20;
                    return;
                }
                if(p2==sessionStorage.getItem('p1')){
                    document.getElementById('texterror').innerHTML=text.p21;
                    return;
                }
                sessionStorage.setItem('p2', sanitizeInput(p2));
            }else if(document.getElementById('giocatori').value==3){
                let p2=document.getElementById('gest1').value;
                let p3=document.getElementById('gest2').value;
                if(p2=='' || p3=='' || isEmptyOrWhitespace(p2) || isEmptyOrWhitespace(p3)){
                    document.getElementById('texterror').innerHTML=text.p20;
                    return;
                }
                if( p2==sessionStorage.getItem('p1')
                    || p2==p3 || sessionStorage.getItem('p1')==p3){
                    document.getElementById('texterror').innerHTML=text.p21;
                    return;
                }
                sessionStorage.setItem('p2', sanitizeInput(p2));
                sessionStorage.setItem('p3', sanitizeInput(p3));
            }else if(document.getElementById('giocatori').value==4){
                let p2=document.getElementById('gest1').value;
                let p3=document.getElementById('gest2').value;
                let p4=document.getElementById('gest3').value;
                if(p2=='' || p4=='' || p3=='' || isEmptyOrWhitespace(p2) || isEmptyOrWhitespace(p3) || isEmptyOrWhitespace(p4)){
                    document.getElementById('texterror').innerHTML=text.p20;
                    return;
                }
                if( p2==sessionStorage.getItem('p1')
                    || p2==p3 || sessionStorage.getItem('p1')==p3
                    || p4==p3 || p4==p2 || p4==sessionStorage.getItem('p1')){
                    document.getElementById('texterror').innerHTML=text.p21;
                    return;
                }
                sessionStorage.setItem('p2', sanitizeInput(p2));
                sessionStorage.setItem('p3', sanitizeInput(p3));
                sessionStorage.setItem('p4', sanitizeInput(p4));
            }
            sessionStorage.setItem('nplayerg1', '2');
            sessionStorage.setItem('tornplayerg1', sanitizeInput(document.getElementById('giocatori').value));
            sessionStorage.setItem('ia', "torneo");
            navigateTo('/costumeser');
        });
    })
}