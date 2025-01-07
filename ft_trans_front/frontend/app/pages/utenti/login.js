import { navigateTo } from './../../js/router.js';

export function loadLoginPage() {
  if(localStorage.getItem('lingua')==null)
    localStorage.setItem('lingua', 'it');
  import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
  .then((module) => {
    const text = module.text;
    const content = document.getElementById('main-content');
    if (!content) {return;}
    content.innerHTML = `
      <div class="d-flex justify-content-center align-items-center">
        <main class="form-signin m-auto mioform">
          <h1 class="h3 mb-3 fw-normal text-white">`+text.p10+`</h1>
          <div class="form-floating mb-3">
            <input type="email" class="form-control text-black" id="email" placeholder="`+text.p39+`">
            <label class="text-black" for="email">`+text.p39+`</label>
          </div>
          <div class="form-floating mb-3">
            <input type="password" class="form-control text-black" id="password" placeholder="`+text.p40+`">
            <label class="text-black" for="password">`+text.p40+`</label>
          </div>
          <h2 id="testoerrore" class="text-white"></h2>
          <button class="btn btn-primary w-100 py-2" id="loggin">`+text.p11+`</button>
          <p class="mt-5 mb-3">
            <a data-link href="/registrati" class="h4 px-2 link-secondary text-white">`+text.p12+`</a>
          </p>
        </main>
      </div>
    `;
    document.getElementById('loggin').addEventListener('click', () => {
      // sessionStorage.setItem('tempjwt', 'tempjwt');
      // navigateTo('/2fa');

      let email=document.getElementById('email').value;
      let password=document.getElementById('password').value;

      fetch('https://localhost:8000/users/login', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          email: email,
          password: password
      }),
      })
      .then(response => {
          const status = response.status;
          if (status == 200) {
            return response.json().then(data => {
              sessionStorage.setItem('tempjwt', data.tempjwt);
              navigateTo('/2fa');
            });
          } else if (status == 204)
            document.getElementById('testoerrore').innerHTML=text.p46;
          else
            document.getElementById('testoerrore').innerHTML=text.p47;
      })
      .catch(error => {
        document.getElementById('testoerrore').innerHTML=text.p47;
      });
    });
  })
}
