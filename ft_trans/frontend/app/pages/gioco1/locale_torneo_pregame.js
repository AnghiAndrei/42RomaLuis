import { navigateTo2,torneoclass,setTorneoClass,setTorneoincorso } from '../../js/router.js';

class Torneo {
  constructor() {
	setTorneoincorso(true);
	this.player1=sessionStorage.getItem('p1');
	this.player2=sessionStorage.getItem('p2');
	this.player3=sessionStorage.getItem('p3');
	this.player4=sessionStorage.getItem('p4');
    this.numPlayers = parseInt(sessionStorage.getItem("tornplayerg1"));
    this.gruppo1 = [];
    this.gruppo2 = [];
    this.gruppo3 = [];
    this.winner = [];
    this.turno=1;

    if (this.numPlayers) {
      for (let i = 1; i <= this.numPlayers; i++) {
        const playerName = sessionStorage.getItem(`p${i}`);
        const j = Math.floor(Math.random() * 2);
		if(j==0 && this.gruppo1.length!=2)
			this.gruppo1.push(playerName);
		else
			this.gruppo2.push(playerName);
      }
    }
  }

  update(){
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
      const text = module.text;

      if(this.gruppo1.length==1 && this.turno==1){
        this.gruppo3.push(this.gruppo1[0]);
        this.turno=this.turno+1;
      }
	  if(this.gruppo1.length==0 && this.turno==1)
        this.turno=this.turno+1;
      if(this.turno==1){
        sessionStorage.setItem('p1', this.gruppo1[0]);
        sessionStorage.setItem('p2', this.gruppo1[1]);
      }

      if(this.gruppo2.length==1 && this.turno==2){
        this.gruppo3.push(this.gruppo2[0]);
        this.turno=this.turno+1;
      }
	  if(this.gruppo2.length==0 && this.turno==2)
        this.turno=this.turno+1;
      if(this.turno==2){
        sessionStorage.setItem('p1', this.gruppo2[0]);
        sessionStorage.setItem('p2', this.gruppo2[1]);
      }

	  if(this.gruppo3.length==1 && this.turno==3){
        this.winner.push(this.gruppo3[0]);
        this.turno=this.turno+1;
      }
      if(this.turno==3){
        sessionStorage.setItem('p1', this.gruppo3[0]);
        sessionStorage.setItem('p2', this.gruppo3[1]);
      }

      const player1 = this.gruppo1[0] || '-';
      const player2 = this.gruppo1[1] || '-';
      const player3 = this.gruppo2[0] || '-';
      const player4 = this.gruppo2[1] || '-';
      
      const player5 = this.gruppo3[0] || '-';
      const player6 = this.gruppo3[1] || '-';
      
      const win = this.winner[0] || '-';

	  if(this.turno!=4){
        const content = document.getElementById('main-content');
        content.innerHTML = `
          <div class="d-flex justify-content-center align-items-center">
            <main class="form-signin m-auto mioform">
              <h1 class="text-white">`+text.p53+`</h1>
              <div id="tabellapunti" style="display: flex; flex-direction: row;"></div>
              	<table class="table text-white table-bordered rounded" style="border-color: black;">
				 	<tr>
						<th>${text.p55} 1</th>
						<th>${text.p55} 2</th>
						<th>${text.p56}</th>
					</tr>
					<tr>
						<th>
							${player1} vs ${player2}
							<br>
							${player3} vs ${player4}
						</th>
						<th>${player5} vs ${player6}</th>
						<th>${win}</th>
					</tr>
                </table>
              	<br><br>
              <h2 class="text-white">`+text.p54+sessionStorage.getItem('p1')+" vs "+sessionStorage.getItem('p2')+`</h2>
              <a data-link id="navigate-button" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p37+`</a>
            </main>
          </div>
        `;
		document.getElementById('navigate-button').addEventListener('click', () => {navigateTo2('/locale_torneo_gioco');});
      }else{
        const content = document.getElementById('main-content');
        content.innerHTML = `
          <div class="d-flex justify-content-center align-items-center">
            <main class="form-signin m-auto mioform">
              <h1 class="text-white">`+text.p58+`</h1>
              <div id="tabellapunti" style="display: flex; flex-direction: row;"></div>
              	<table class="table text-white table-bordered rounded" style="border-color: black;">
				 	<tr>
						<th>${text.p55} 1</th>
						<th>${text.p55} 2</th>
						<th>${text.p56}</th>
					</tr>
					<tr>
						<th>
							${player1} vs ${player2}
							<br>
							${player3} vs ${player4}
						</th>
						<th>${player5} vs ${player6}</th>
						<th>${win}</th>
					</tr>
                </table>
              <p class="mt-5 mb-3"><a data-link href="/giochi" class="h4 px-2 link-secondary text-white">`+text.p31+`</a></p>
            </main>
          </div>
        `;
		setTorneoincorso(false);
		setTorneoClass(null);

		let esito="S";
		if(win==sessionStorage.getItem('tp1'))
			esito="V";

		fetch('https://localhost:8000/g1/set_tornament', {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
				'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
			},
			body: JSON.stringify({
				nomep1: this.player1,
				nomep2: this.player2,
				nomep3: this.player3,
				nomep4: this.player4,
				vincitore: win,
				esito: esito
			}),
		})
		.then(response => {
			const status = response.status;
			if(status==200){
				;
			} else if (status == 401){
				const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
				modal2.show();
				document.getElementById('ERROREMessage').innerHTML=text.p67;
			}else{
				const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
				modal2.show();
				document.getElementById('ERROREMessage').innerHTML=text.p59;
			}
		})
		.catch(error => {
			const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
			modal2.show();
			document.getElementById('ERROREMessage').innerHTML=text.p59;
		});
		sessionStorage.removeItem('p2');
		sessionStorage.removeItem('p3');
		sessionStorage.removeItem('p4');
      }
    })
  }

  finepartita(nomevincitore){
	if(this.turno==1){
      	this.gruppo3.push(nomevincitore);
      	this.turno=this.turno+1;
    }
    else if(this.turno==2){
		this.gruppo3.push(nomevincitore);
      	this.turno=this.turno+1;
    }
    else if(this.turno==3){
		this.winner.push(nomevincitore);
      	this.turno=this.turno+1;
    }
  }
}

export function loadLocalePreGameTorneoGame1Page() {
  if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
  import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
  .then((module) => {
    const text = module.text;
    if (!torneoclass){
		setTorneoClass(new Torneo());
		torneoclass.update();
	}else
		torneoclass.update();
  })
}