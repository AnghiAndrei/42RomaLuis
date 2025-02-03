import { updateNavbar,sanitizeInput,setSocketInput } from './../../js/assets.js';
import { navigateTo } from './../../js/router.js';

export function load2faPage() {
	if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
  import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
  .then((module) => {
    const text = module.text;
    const content = document.getElementById('main-content');
    if (!content) {return;}
    content.innerHTML = `
      <div class="d-flex justify-content-center align-items-center">
        <main class="form-signin m-auto mioform">
          <h1 class="h3 mb-3 fw-normal text-white">`+text.p13+`</h1>
          <div class="form-floating mb-3">
            <input type="text" class="form-control text-black" id="codeotp" placeholder="`+text.p14+`">
            <label class="text-black" for="codeotp">`+text.p14+`</label>
          </div>
          <h2 id="testoerrore" class="text-white text-center"></h2>
          <button class="btn btn-primary w-100 py-2" id="valid">`+text.p15+`</button>
        </main>
      </div>`;
    document.getElementById('valid').addEventListener('click', () => {

      let codeotp=document.getElementById('codeotp').value;

	  codeotp=sanitizeInput(codeotp);

      if(codeotp==""){
        document.getElementById('testoerrore').innerHTML=text.p72;
        return;
      }

      fetch(sessionStorage.getItem("hostapp")+'/users/check_2fa', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          codeotp: codeotp, 
          key: sessionStorage.getItem("tempjwt")
        }),
      })
      .then(response => {
        const status = response.status;
        if (status == 200) {
            return response.json().then(data => {
			        sessionStorage.setItem('imguser', "./../img/"+data.imguser);
              sessionStorage.setItem('jwtToken', data.jwttoken);
              sessionStorage.setItem('p1', data.nome);
              sessionStorage.setItem('tp1', data.nome);
              sessionStorage.removeItem('tempjwt');
              if (sessionStorage.getItem('jwtToken') != null){
                const online_sock = new WebSocket(sessionStorage.getItem('hostsock')+'/online/'+sessionStorage.getItem('jwtToken')+"/");
                setSocketInput(online_sock);
				online_sock.onopen = () => {};
                online_sock.onmessage = (event) => {};
                online_sock.onerror = (error) => {};
                online_sock.onclose = () => {};
              }
              navigateTo('/');
              updateNavbar();
            });
          } else if (status == 204 || status == 205)
            document.getElementById('testoerrore').innerHTML=text.p48;
          else
            document.getElementById('testoerrore').innerHTML=text.p47;
        })
        .catch(error => {
          document.getElementById('testoerrore').innerHTML=text.p47;
        });
      });
    })
}
