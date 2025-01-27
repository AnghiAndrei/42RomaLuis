import { updateNavbar } from './../../js/assets.js';
import { navigateTo } from './../../js/router.js';
import { isEmptyOrWhitespace } from './../../js/assets.js';
import { hashPassword } from './zz_assets.js';

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
          <label for="sessoinput" class="form-label text-white">`+text.p93+`</label>
          <select class="form-select" id="sessoinput">
            <option value="`+text.p84+`">`+text.p84+`</option>
            <option value="`+text.p86+`">`+text.p86+`</option>
            <option value="`+text.p85+`">`+text.p85+`</option>
            <option value="`+text.p94+`">`+text.p94+`</option>
          </select>
          <br><br>
          <div class="form-floating">
            <input type="password" class="form-control text-black" id="password" placeholder="`+text.p40+`">
            <label class="text-black" for="password">`+text.p40+`</label>
          </div>
          <div class="form-floating">
            <input type="password" class="form-control text-black" id="conferpassword" placeholder="`+text.p6+`">
            <label class="text-black" for="conferpassword">`+text.p6+`</label>
          </div>
          <h2 id="testoerrore" class="text-white text-center"></h2>
          <button class="btn btn-primary w-100 py-2" id="registra">`+text.p8+`</button>
          <p class="mt-5 mb-3">
            <a data-link href="/login" class="h4 px-2 link-secondary text-white">`+text.p9+`</a>
          </p>
        </main>
      </main>`;
    document.getElementById('registra').addEventListener('click', () => {
      let email=document.getElementById('email').value;
      let nome=document.getElementById('nome').value;
      let password=document.getElementById('password').value;
      let conferpassword=document.getElementById('conferpassword').value;
      let sesso=document.getElementById('sessoinput').value;

      if(email=="" || nome=="" || password=="" || conferpassword=="" || sesso=="" || isEmptyOrWhitespace(email) || isEmptyOrWhitespace(nome)){
        document.getElementById('testoerrore').innerHTML=text.p72;
        return;
      }

      if(sesso==text.p84) sesso='p84';
      else if(sesso==text.p94){
        document.getElementById('testoerrore').innerHTML=text.p95;
        return;
      }
      else if(sesso==text.p86) sesso='p86';
      else if(sesso==text.p85) sesso='p85';
      else{
        document.getElementById('testoerrore').innerHTML=text.p72;
        return;
      }

      if(conferpassword != password){
        document.getElementById('testoerrore').innerHTML=text.p50;
        return;
      }

      hashPassword(password).then(hash => {password=hash;});

      fetch(sessionStorage.getItem("hostapp")+'/users/registrati', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
			nome: nome,
			email: email,
			password: password,
			sesso: sesso,
		}),
      })
      .then(response => {
        const status = response.status;
        if (status == 200) {
          return response.json().then(data => {
            sessionStorage.setItem('imguser', "./../img/"+data.imguser);
            sessionStorage.setItem('jwtToken', data.jwttoken);
            sessionStorage.setItem('tp1', data.nome);
            sessionStorage.setItem('p1', data.nome);
            if (sessionStorage.getItem('jwtToken') != null){
              const online_sock = new WebSocket(sessionStorage.getItem('hostsock')+'/online/'+sessionStorage.getItem('jwtToken')+"/");
              online_sock.onopen = () => {};
              online_sock.onmessage = (event) => {};
              online_sock.onerror = (error) => {};
              online_sock.onclose = () => {};
            }
            navigateTo('/');
            updateNavbar();
          });
        } else if (status == 204 || status == 205)
          document.getElementById('testoerrore').innerHTML=text.p49;
		else if (status == 501)
            document.getElementById('testoerrore').innerHTML=text.p110;
        else
          document.getElementById('testoerrore').innerHTML=text.p47;
      })
      .catch(error => {
        document.getElementById('testoerrore').innerHTML=text.p47;
      });
    });
  })
}
