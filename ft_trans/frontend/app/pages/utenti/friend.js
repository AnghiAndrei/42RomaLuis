import { navigateTo } from './../../js/router.js';
import { logout, sanitizeInput } from './../../js/assets.js';

let connectedSockets = {};
let stanza;

window.blockfriendo=blockfriendo;
function blockfriendo(){
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        fetch(sessionStorage.getItem("hostapp")+`/chat/blockfriendo`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
            },
            body: JSON.stringify({ stanza: stanza }),
        })
        .then(response => {
            const status = response.status;
            if (status == 200) {
                navigateTo("friend");
            } else if (status == 201) {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p99;
            } else {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p47;
            }
        })
        .catch(error => {
            const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
            modal2.show();
            document.getElementById('ERROREMessage').innerHTML=text.p47;
        });
    });
}

window.sblockfriendo=sblockfriendo;
function sblockfriendo(){
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        fetch(sessionStorage.getItem("hostapp")+`/chat/sblockfriendo`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
            },
            body: JSON.stringify({ stanza: stanza }),
        })
        .then(response => {
            const status = response.status;
            if (status == 200) {
                navigateTo("friend");
            } else if (status == 201) {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p99;
            } else {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p47;
            }
        })
        .catch(error => {
            const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
            modal2.show();
            document.getElementById('ERROREMessage').innerHTML=text.p47;
        });
    });
}

window.sendMessage=sendMessage;
function sendMessage() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const socket = connectedSockets[stanza][0];
        if (socket.readyState === WebSocket.OPEN) {
            try {	
                socket.send(JSON.stringify({
                    message: sanitizeInput(document.getElementById('messageInput').value),
                    token: sessionStorage.getItem('jwtToken'),
                }));
                document.getElementById('messageInput').value = "";
            } catch (error) {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p96;
            }
        } else {
            const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
            modal2.show();
            document.getElementById('ERROREMessage').innerHTML=text.p96;
        }
    });
}

window.messaggi=messaggi;
function messaggi(id, nome, img){
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const modal_messaggi = new bootstrap.Modal(document.getElementById('boxmessaggi'));
        modal_messaggi.show();
        document.getElementById('dickpic').src = "./../img/"+img;
        document.getElementById('nomeamicomes').innerHTML=nome;
        stanza=id;
        document.getElementById('chatContainer').innerHTML="";

        document.getElementById('needonclick').onclick = () => {
            sessionStorage.setItem('idamico', id);
            navigateTo("profile_friendo");
        };

        fetch(sessionStorage.getItem("hostapp")+`/chat/get_status`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
            },
            body: JSON.stringify({ stanza: stanza }),
        })
        .then(response => {
            const status = response.status;
            if (status == 200) {
                document.getElementById('statoblocca').innerHTML = `<h2 class="point" onclick="sblockfriendo()"><img src="./../img/amici/sblocca.png" width="25" height="25" /></h2>`;
            } else if (status == 201){
                document.getElementById('statoblocca').innerHTML = `<h2 class="point" onclick="blockfriendo()"><img src="./../img/amici/blocca.png" width="25" height="25" /></h2>`;
            } else {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p98;
            }
        })
        .catch(error => {
            const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
            modal2.show();
            document.getElementById('ERROREMessage').innerHTML=text.p98;
        });

        fetch(sessionStorage.getItem("hostapp")+`/chat/get_message`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ stanza: stanza }),
        })
        .then(response => {
            const status = response.status;
            if (status == 200) {
                return response.json().then(data => {
                    document.getElementById('chatContainer').innerHTML="";
                    let messaggio=data.messaggio;
                    messaggio.forEach(messaggio => {
                        const messageElement = document.createElement("div");
                        messageElement.classList.add("p-2", "mb-2", "rounded", "border", "border-white", "text-white");
                        messageElement.classList.add("list-group-item", "d-flex", "align-items-center");
                        messageElement.innerHTML = `
                            <img src="./../img/${messaggio.imgfriend}" class="rounded-circle me-3" width="40" height="40"/>
                            <span>
                                <h3>${messaggio.nome}</h3>
                                <p class="chatmsg">${messaggio.msg}</p>
                            </span>
                        `;
                        document.getElementById('chatContainer').appendChild(messageElement);
                    });
                    document.getElementById('chatContainer').scrollTop = document.getElementById('chatContainer').scrollHeight;
                });
            } else if (status == 400){
                ;
            } else {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p98;
            }
        })
        .catch(error => {
            const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
            modal2.show();
            document.getElementById('ERROREMessage').innerHTML=text.p98;
        });
    });
}

window.accetta_rifuita_richiesta_rimuovi_amico=accetta_rifuita_richiesta_rimuovi_amico;
function accetta_rifuita_richiesta_rimuovi_amico(id, op) {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        let link;
        if(op=="accetta") link=sessionStorage.getItem('hostapp')+"/users/accept_request_friend";
        else if(op=="rifiuta") link=sessionStorage.getItem('hostapp')+"/users/refuse_request_friend";
        else if(op=="rimuoviamico") link=sessionStorage.getItem('hostapp')+"/users/remove_friend";
        else{
            const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
            modal2.show();
            document.getElementById('ERROREMessage').innerHTML=text.p92;
            return ;
        }
        fetch(link, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
            },
            body: JSON.stringify({ id_req_friendo: id }),
        })
        .then(response => {
            const status = response.status;
            if (status == 200) {
                navigateTo("friend");
            } else if (status == 401){
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p67;
                logout();
            } else {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p92;
            }
        })
        .catch(error => {
            const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
            modal2.show();
            document.getElementById('ERROREMessage').innerHTML=text.p92;
        });
    });
}

function send_request(nome) {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        fetch(sessionStorage.getItem("hostapp")+`/users/send_request_friend`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
            },
            body: JSON.stringify({ nome_frind: nome }),
        })
        .then(response => {
            const status = response.status;
            if (status == 200) {
                navigateTo("friend");
            } else if (status == 207){
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p97;
            } else if (status == 401){
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p67;
                logout();
            } else {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p92;
            }
        })
        .catch(error => {
            const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
            modal2.show();
            document.getElementById('ERROREMessage').innerHTML=text.p92;
        });
    });
}

window.searchFriend=searchFriend;
function searchFriend() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const query = document.getElementById("searchBar").value;
        fetch(sessionStorage.getItem("hostapp")+`/users/search_friend?query=${query}`, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
            },
        })
        .then(response => {
            const status = response.status;
            if (status == 200) {
                return response.json().then(data => {
                    let lista_amici=data.lista_amici;
                    document.getElementById("friendList").innerHTML = "";
                    if (lista_amici && lista_amici.length > 0) {
                        lista_amici.forEach(amico => {
                            const li = document.createElement("li");
                            li.classList.add("point", "list-group-item", "d-flex", "align-items-center");
                            li.onclick = () => send_request(amico.nome);
                            li.innerHTML = `
                                <img src="./../img/${amico.imgfriend}" alt="${amico.nome}" class="rounded-circle me-3" width="40" height="40"/>
                                <span>${amico.nome}</span>`;
                            friendList.appendChild(li);
                        });
                    } else {
                        const li = document.createElement("li");
                        li.classList.add("list-group-item");
                        li.textContent = text.p90;
                        friendList.appendChild(li);
                    }
                });
            } else if (status == 401){
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p67;
                logout();
            } else {
                document.getElementById("friendList").innerHTML = "";
                const li = document.createElement("li");
                li.classList.add("list-group-item");
                li.textContent = text.p90;
                friendList.appendChild(li);
            }
        })
        .catch(error => {
            document.getElementById("friendList").innerHTML = "";
            const li = document.createElement("li");
            li.classList.add("list-group-item");
            li.textContent = text.p90;
            friendList.appendChild(li);
        });
    });
}

window.updatepagefriendo=updatepagefriendo;
function updatepagefriendo(data) {
    const audio = document.getElementById("lonely");
    if (audio && !audio.paused){
        audio.pause();
        audio.currentTime = 0;
    }
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        if(data=="listaamici"){
            fetch(sessionStorage.getItem("hostapp")+'/users/get_friend', {
                method: 'GET',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
                },
            })
            .then(response => {
                const status = response.status;
                if (status == 200) {
                    return response.json().then(data => {
                        let listaamici=data.lista_amici;
                        const content = document.getElementById('amicirichieste');
                        content.innerHTML = `<div class="row align-items-center w-100"><div class="col-md-6"><ul id="friendList2" class="list-group mt-3"></ul></div></div>`;
                        const friendList = document.getElementById('friendList2');
                        listaamici.forEach(listaamici => {
                            const li = document.createElement("li");
                            li.classList.add("list-group-item", "d-flex", "align-items-center");
                            if (listaamici.online == true)
                                li.innerHTML = `
                                    <span class="point" onclick="accetta_rifuita_richiesta_rimuovi_amico(${listaamici.idfriend}, 'rimuoviamico')"><img src="./../img/amici/rimuovi.png" class="me-3" width="40" height="40"/></span>
                                    <span class="point" onclick="messaggi(${listaamici.idfriend}, '${listaamici.nome}', '${listaamici.imgfriend}')"><img src="./../img/amici/message.png" class="me-3" width="40" height="40"/></span>
                                    <span> | </span>
                                    <img src="./../img/${listaamici.imgfriend}" alt="${listaamici.nome}" class="rounded-circle me-3" width="40" height="40"/>
                                    <span>
                                        ${listaamici.nome}
                                        <br>
                                        <span class="bg-success rounded-circle" style="width: 10px; height: 10px; display: inline-block;"></span>
                                    </span>`;
                            else
                                li.innerHTML = `
                                    <span class="point" onclick="accetta_rifuita_richiesta_rimuovi_amico(${listaamici.idfriend}, 'rimuoviamico')"><img src="./../img/amici/rimuovi.png" class="me-3" width="40" height="40"/></span>
                                    <span class="point" onclick="messaggi(${listaamici.idfriend}, '${listaamici.nome}', '${listaamici.imgfriend}')"><img src="./../img/amici/message.png" class="me-3" width="40" height="40"/></span>
                                    <span> | </span>
                                    <img src="./../img/${listaamici.imgfriend}" alt="${listaamici.nome}" class="rounded-circle me-3" width="40" height="40"/>
                                    <span>
                                        ${listaamici.nome}
                                        <br>
                                        <span class="bg-danger rounded-circle" style="width: 10px; height: 10px; display: inline-block;"></span>
                                    </span>`;
                            friendList.appendChild(li);

                            const friendSocket = new WebSocket(sessionStorage.getItem('hostsock') + '/chat/' + listaamici.idfriend + '/');
                            if (!connectedSockets[listaamici.idfriend])
                                connectedSockets[listaamici.idfriend] = [];
                            connectedSockets[listaamici.idfriend].push(friendSocket);
                            friendSocket.onmessage = function (event) {
                                const content = document.getElementById('chatContainer');
                                if (!content) {return;}
                                const data = JSON.parse(event.data);
                                // if (data.type === 'error_message')
                                //     console.error("Error:", data.error);

                                fetch(sessionStorage.getItem("hostapp")+`/chat/get_message`, {
                                    method: 'POST',
                                    headers: {
                                        'Content-Type': 'application/json'
                                    },
                                    body: JSON.stringify({ stanza: stanza }),
                                })
                                .then(response => {
                                    const status = response.status;
                                    if (status == 200) {
                                        return response.json().then(data => {
                                            document.getElementById('chatContainer').innerHTML="";
                                            let messaggio=data.messaggio;
                                            messaggio.forEach(messaggio => {
                                                const messageElement = document.createElement("div");
                                                messageElement.classList.add("p-2", "mb-2", "rounded", "border", "border-white", "text-white");
                                                messageElement.classList.add("list-group-item", "d-flex", "align-items-center");
                                                messageElement.innerHTML = `
                                                    <img src="./../img/${messaggio.imgfriend}" class="rounded-circle me-3" width="40" height="40"/>
                                                    <span>
                                                        <h3>${messaggio.nome}</h3>
                                                        <p class="chatmsg">${messaggio.msg}</p>
                                                    </span>
                                                `;
                                                document.getElementById('chatContainer').appendChild(messageElement);
                                            });
                                            document.getElementById('chatContainer').scrollTop = document.getElementById('chatContainer').scrollHeight;
                                        });
                                    } else if (status == 400){ ; } else {
                                        const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                                        modal2.show();
                                        document.getElementById('ERROREMessage').innerHTML=text.p98;
                                    }
                                })
                                .catch(error => {
                                    const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                                    modal2.show();
                                    document.getElementById('ERROREMessage').innerHTML=text.p98;
                                });
                            };
                            friendSocket.onclose = function () { ; };
                            friendSocket.onerror = function (error) { ; };
                        });
                    });
                } else if (status == 400){
                    const content = document.getElementById('amicirichieste');
                    content.innerHTML = `
                        <h2 class="text-white text-center">`+text.p87+`</h2>
                        <audio controls id="lonely" style="display: none;"><source src="./../../song/lonely.mp3" type="audio/mp3"></audio>`;
                    const audio = document.getElementById("lonely");
                    audio.play();
                } else if (status == 401){
                    const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                    modal2.show();
                    document.getElementById('ERROREMessage').innerHTML=text.p67;
                    logout();
                } else{
                    const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                    modal2.show();
                    document.getElementById('ERROREMessage').innerHTML=text.p66;
                }
            })
            .catch(error => {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p66;
            });
        } else if(data=="richiesteamicizia"){
            fetch(sessionStorage.getItem("hostapp")+'/users/get_request', {
                method: 'GET',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': 'Bearer '+sessionStorage.getItem('jwtToken'),
                },
            })
            .then(response => {
                const status = response.status;
                if (status == 200) {
                    return response.json().then(data => {
                        let listaamici=data.lista_richiesta;
                        const content = document.getElementById('amicirichieste');
                        content.innerHTML = `<ul id="friendList3" class="list-group mt-3"></ul>`;

                        const friendList = document.getElementById('friendList3');
                        listaamici.forEach(listaamici => {
                            const li = document.createElement("li");
                            li.classList.add("list-group-item", "d-flex", "align-items-center");
                            li.innerHTML = `
                                <span class="point" onclick="accetta_rifuita_richiesta_rimuovi_amico(${listaamici.idrichiesta}, 'rifiuta')"><img src="./../img/amici/rifuita.gif" alt="${listaamici.nome}" class="me-3" width="40" height="40"/></span>
                                <span class="point" onclick="accetta_rifuita_richiesta_rimuovi_amico(${listaamici.idrichiesta}, 'accetta')"><img  src="./../img/amici/accetta.gif" alt="${listaamici.nome}" class="me-3" width="40" height="40"/></span>
                                <span> | </span>
                                <img src="./../img/${listaamici.imgfriend}" alt="${listaamici.nome}" class="rounded-circle me-3" width="40" height="40"/>
                                <span>${listaamici.nome}</span>`;
                            friendList.appendChild(li);
                        });
                    });
                } else if (status == 400){
                    const content = document.getElementById('amicirichieste');
                    content.innerHTML = `<h2 class="text-white text-center">`+text.p88+`</h2>`;
                } else if (status == 401){
                    const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                    modal2.show();
                    document.getElementById('ERROREMessage').innerHTML=text.p67;
                    logout();
                } else{
                    const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                    modal2.show();
                    document.getElementById('ERROREMessage').innerHTML=text.p66;
                }
            })
            .catch(error => {
                const modal2 = new bootstrap.Modal(document.getElementById('ErroriPopUp'));
                modal2.show();
                document.getElementById('ERROREMessage').innerHTML=text.p66;
            });
        } else if(data=="cercaamico"){
            const content = document.getElementById('amicirichieste');
            content.innerHTML = `<div class="container mt-4">
                                    <input type="text" id="searchBar" class="form-control" placeholder="`+text.p91+`" onkeyup="searchFriend()" />
                                    <ul id="friendList" class="list-group mt-3"></ul>
                                </div>`;
        }
    })
}

export function loadFriendPage() {
    if(localStorage.getItem('lingua')==null){localStorage.setItem('lingua', 'it');}
    import(`./../../traduzioni/${localStorage.getItem('lingua')}.js`)
    .then((module) => {
        const text = module.text;
        const content = document.getElementById('main-content');
        content.innerHTML = `
            <div class="d-flex flex-column justify-content-center align-items-center">
                <h1 class="text-white text-center">`+text.p82+`</h1>
                <h2 class="text-white text-center">`+text.p83+`</h2>
                <div class="d-flex justify-content-start mt-3">
                    <a onclick="updatepagefriendo('listaamici')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p80+`</a>
                    <a onclick="updatepagefriendo('richiesteamicizia')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p81+`</a>
                    <a onclick="updatepagefriendo('cercaamico')" class="btn btn-primary h4 px-2 link-secondary text-white mt-3">`+text.p89+`</a>
                </div>
                <br><br>
                <div id="amicirichieste" class="d-flex flex-column align-items-center w-100"></div>
            </div>
            <div class="modal fade" id="boxmessaggi" tabindex="-1" aria-labelledby="gameOverModalLabel" aria-hidden="true" data-bs-backdrop="true" data-bs-keyboard="false">
                <div class="modal-dialog modal-dialog-centered w-70">
                    <div class="modal-content mybg">
                        <div class="modal-header d-flex align-items-center">
                            <span id="needonclick" class="d-flex align-items-center flex-grow-1">
                                <img id="dickpic" src="" class="rounded-circle me-3" width="40" height="40" />
                                <h1 class="text-white mb-0" id="nomeamicomes"></h1>
                            </span>
                            <h2 class="text-white ms-auto mb-0" id="statoblocca"></h2>
                        </div>
                        <div class="modal-body">
                            <div id="chatContainer" class="h-50 chatbox"></div>
                            <div class="d-flex align-items-center mt-3">
                                <input id="messageInput" type="text" class="form-control me-2">
                                <h2 onclick="sendMessage()" style="cursor: pointer;"><img src="./../img/amici/send.png" width="25" height="25" /></h2>
                            </div>
                        </div>
                    </div>
                </div>
            </div>`;
    })
}