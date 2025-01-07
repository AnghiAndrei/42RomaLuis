import { updateNavbar } from './../../js/assets.js';
import { navigateTo } from './../../js/router.js';

export function loadRegistraPage() {
	if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
  import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
  .then((module) => {
    const text = module.text;
    const content = document.getElementById('main-content');
    if (!content) {return;}
    content.innerHTML = `
      <div class="d-flex justify-content-center align-items-center">
        <main class="form-signin m-auto mioform">
          <h1 class="h3 mb-3 fw-normal text-white">`+text.p5+`</h1>
          <div class="form-floating">
            <input type="email" class="form-control text-black" id="email" placeholder="`+text.p39+`">
            <label class="text-black" for="email">`+text.p39+`</label>
          </div>
          <div class="form-floating">
            <input type="text" class="form-control text-black" id="nome" placeholder="`+text.p6+`">
            <label class="text-black" for="nome">`+text.p6+`</label>
          </div>
          <br>
          <div class="form-floating">
            <input type="password" class="form-control text-black" id="password" placeholder="`+text.p40+`">
            <label class="text-black" for="password">`+text.p40+`</label>
          </div>
          <div class="form-floating">
            <input type="password" class="form-control text-black" id="conferpassword" placeholder="`+text.p6+`">
            <label class="text-black" for="conferpassword">`+text.p6+`</label>
          </div>
          <h2 id="testoerrore" class="text-white"></h2>
          <button class="btn btn-primary w-100 py-2" id="registra">`+text.p8+`</button>
          <p class="mt-5 mb-3">
            <a data-link href="/login" class="h4 px-2 link-secondary text-white">`+text.p9+`</a>
          </p>
        </main>
      </main>
    `;
    document.getElementById('registra').addEventListener('click', () => {
      sessionStorage.setItem('imguser', './../img/_default.png');
      sessionStorage.setItem('jwtToken', 'log');
      sessionStorage.setItem('p1', 'angly');
      navigateTo('/');
      updateNavbar();

      let email=document.getElementById('email').value;
      let nome=document.getElementById('nome').value;
      let password=document.getElementById('password').value;
      let conferpassword=document.getElementById('conferpassword').value;

      if(conferpassword != password){
        document.getElementById('testoerrore').innerHTML=text.p50;
        return;
      }

      fetch('https://localhost:8000/users/registra', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          nome: nome,
          email: email,
          password: password,
      }),
      })
      .then(response => {
        const status = response.status;
        if (status == 200) {
          return response.json().then(data => {
            sessionStorage.setItem('imguser', data.fotoprofilo);
            sessionStorage.setItem('jwtToken', data.jwttoken);
            sessionStorage.setItem('p1', nome);
            navigateTo('/');
            updateNavbar();
          });
        } else if (status == 204 || status == 205)
          document.getElementById('testoerrore').innerHTML=text.p49;
        else
          document.getElementById('testoerrore').innerHTML=text.p47;
      })
      .catch(error => {
        document.getElementById('testoerrore').innerHTML=text.p47;
      });
    });
  })
}
