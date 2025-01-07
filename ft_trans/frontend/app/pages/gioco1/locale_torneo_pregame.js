import { navigateTo2,torneoclass,setPartitaincorso } from '../../js/router.js';

function cambiapagina() {
  navigateTo2("/locale_torneo_gioco");
}

class Torneo {
  constructor() {
    sessionStorage.setItem('tp1', sessionStorage.getItem('p1'));
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
        if (j==0)
          this.gruppo1.push({ name: playerName });
        else
          this.gruppo2.push({ name: playerName });
      }
    }
  }

  update(){
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
      const text = module.text;

      if(this.gruppo1.length==1 && this.turno==1){
        this.gruppo3.push({ name: this.gruppo1.name });
        this.turno=this.turno+1;
      }
      if(this.turno==1){
        sessionStorage.setItem('p1', this.gruppo1[0].name);
        sessionStorage.setItem('p2', this.gruppo1[1].name);
      }

      if(this.gruppo2.length==1 && this.turno==2){
        this.gruppo3.push({ name: this.gruppo2.name });
        this.turno=this.turno+1;
      }
      if(this.turno==2){
        sessionStorage.setItem('p1', this.gruppo2[0].name);
        sessionStorage.setItem('p2', this.gruppo2[1].name);
      }

      if(this.turno==3){
        sessionStorage.setItem('p1', this.gruppo3[0].name);
        sessionStorage.setItem('p2', this.gruppo3[1].name);
      }

      const player1 = this.gruppo1[0].name || '-';
      const player2 = this.gruppo1[1].name || '-';
      const player3 = this.gruppo2[0].name || '-';
      const player4 = this.gruppo2[1].name || '-';
      
      const player5 = this.gruppo3[0].name || '-';
      const player6 = this.gruppo3[1].name || '-';
      
      const win = this.winner[0].name || '-';
      
      if(this.turno!=4){
        const content = document.getElementById('main-content');
        content.innerHTML = `
          <div class="d-flex justify-content-center align-items-center">
            <main class="form-signin m-auto mioform">
              <h1 class="text-white">`+text.p53+`</h1>
              <div id="tabellapunti" style="display: flex; flex-direction: row;"></div>
              <table>
                <td><th><h4>${text.p55} 1</h4></th></td>
                <td>
                  <th><h4>${player1}<br>${player2}</h4></th>
                  <th><h4>${player3}<br>${player4}</h4></th>
                </td>
                <td><th><h4>${text.p55} 2</h4></th></td>
                <td><th><h4>${player5}<br>${player6}</h4></th></td>
                <td><th><h4>${text.p56}</h4></th></td>
                <td><th><h4>${win}</h4></th></td>
              </table>
              <br><br>
              <h2 class="text-white">`+text.p54+`</h2>
              <h2 class="text-white">`+sessionStorage.getItem('p1')+" vs "+sessionStorage.getItem('p2')+`</h2>
              <a data-link onclick="cambiapagina" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p37+`</a>
            </main>
          </div>
        `;
      }else{
        const content = document.getElementById('main-content');
        content.innerHTML = `
          <div class="d-flex justify-content-center align-items-center">
            <main class="form-signin m-auto mioform">
              <h1 class="text-white">`+text.p53+`</h1>
              <div id="tabellapunti" style="display: flex; flex-direction: row;"></div>
              <table>
                <td><th><h4>${text.p55} 1</h4></th></td>
                <td>
                  <th><h4>${player1}<br>${player2}</h4></th>
                  <th><h4>${player3}<br>${player4}</h4></th>
                </td>
                <td><th><h4>${text.p55} 2</h4></th></td>
                <td><th><h4>${player5}<br>${player6}</h4></th></td>
                <td><th><h4>${text.p56}</h4></th></td>
                <td><th><h4>${win}</h4></th></td>
              </table>
              <p class="mt-5 mb-3"><a data-link href="/giochi" class="h4 px-2 link-secondary text-white">`+text.p19+`</a></p>
            </main>
          </div>
        `;
      }
    })
  }

  finepartita(nomevincitore){
    if(this.turno=1){
      this.gruppo3.push({ name: nomevincitore });
      this.turno=this.turno+1;
    }
    if(this.turno=2){
      this.gruppo3.push({ name: nomevincitore });
      this.turno=this.turno+1;
    }
    if(this.turno=3){
      this.winner.push({ name: nomevincitore });
      this.turno=this.turno+1;
    }
  }
}

export function loadLocalePreGameTorneoGame1Page() {
  setPartitaincorso(true);
  if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
  import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
  .then((module) => {
    const text = module.text;
    if (!torneoclass)
      torneoclass = new Torneo();
    torneoclass.update();
  })
}