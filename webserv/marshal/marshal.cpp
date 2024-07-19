#include"../webserv.hpp"

bool isValidIPv4(const std::string &ip){
    std::vector<std::string> parts;
    std::stringstream ss(ip);
    std::string part;

    while (std::getline(ss, part, '.'))
        parts.push_back(part);
    if(parts.size()!=4){
        return false;
	}
	for (size_t i=0;i!=4;i++){
        if (parts[i].empty() || parts[i].size() > 3)
            return false;
		for (size_t i2=0;'\0'!=parts[i][i2];i2++){
			if (!isdigit(parts[i][i2]))
                return false;
		}
        int num = std::atoi(parts[i].c_str());
        if (num < 0 || num > 255)
            return false;
	}
    return true;
}

bool isValidPort(const std::string &port){
    if (port.empty() || port.size()>=6){
        return false;
	}
	for (size_t i2=0;'\0'!=port[i2];i2++){
		if (!isdigit(port[i2]))
            return false;
	}
	int num = std::atoi(port.c_str());
    if (num < 0 || num > 65535)
        return false;
    return true;
}

bool isValidBody_Size(const std::string &port){
    if (port.empty() || port.size()>=21){
        return false;
	}
	for (size_t i2=0;'\0'!=port[i2];i2++){
		if (!isdigit(port[i2]))
            return false;
	}
	unsigned long long int num = stoull(port.c_str());
    if (num > 18446744073709551614ULL)
        return false;
    return true;
}

bool isValidDirectory(const std::string &path){
	DIR *dir=opendir(path.c_str());
	if(dir==NULL){
        std::cout<<"Marshal: La cartella: "<<path.c_str()<<"; non esiste"<<std::endl;
		return false;
    }
	closedir(dir);
	return true;
}

int check(int argc, char **argv, webserv *webservv){
    std::string conffile="";
    if(argc>2){
        std::cout<<"Marshal: numero di argomenti sbagliato"<<std::endl;
        return -1;
    }else if(argc==1)
        conffile="conf/default.conf";
    else{
        conffile=argv[1];
	}
	std::ifstream conf(conffile.c_str());
	if(!conf.is_open()){
        std::cout<<"Marshal: Errore nel aprire il file conf: "<<conffile<<std::endl;
		return -1;
	}
	std::string temp;
	bool server=false;
	while(std::getline(conf, temp)){
		if(temp.empty())
			continue;
		if(server==false && temp[0]!='{'){
	        std::cout<<"Marshal: Trovati carattiri al di fuori delle parantesi"<<std::endl;
			return -1;
		}
		if((temp[0]=='{' || temp[0]=='}') && temp.size()!=1){
	        std::cout<<"Marshal: Trovati altri caratteri nelle linee di apertura e chiusura server"<<std::endl;
			return -1;
		}
		if(server==false && temp[0]=='{'){
			server=true;
			continue;
		}
		if(server==true && temp[0]=='}'){
			server=false;
			webservv->crea_server();
			continue;
		}
		if(server==true && temp[0]=='{'){
	        std::cout<<"Marshal: Errore nel file di configurazione"<<std::endl;
			return -1;
		}
		if(server==false && temp[0]=='}'){
	        std::cout<<"Marshal: Errore nel file di configurazione"<<std::endl;
			return -1;
		}
	}
	conf.close();
	if(server==true){
		std::cout<<"Marshal: Errore nel file di configurazione"<<std::endl;
		return -1;
	}
	temp.clear();
	conf.open(conffile.c_str());
	if(!conf.is_open()){
        std::cout<<"Marshal: Errore nel aprire il file conf: "<<conffile<<std::endl;
		return -1;
	}
	server=false;
	size_t serv=0;
	while(std::getline(conf, temp)){
		if(temp.empty())
			continue;
		if(server==false && temp[0]=='{'){
			server=true;
			continue;
		}
		if(server==true && temp[0]=='}'){
			server=false;
			serv++;
			continue;
		}
		int i=0;
		std::string chiave="";
		std::string valore="";
		while(temp[i]!='\0' && (temp[i]==' ' || temp[i]=='\t'))
			i++;
		while(temp[i]!='\0' && temp[i]!='='){
			chiave+=temp[i];
			i++;
		}
		if(temp[i]!='='){
			std::cout<<"Marshal: Errore nel file di configurazione"<<std::endl;
			return -1;
		}
		i++;
		while(temp[i]!='\0'){
			valore+=temp[i];
			i++;
		}
		if(chiave=="server_name"){
			for(size_t i3=0;i3!=valore.size();i3++){
				if(valore[i3]==' '){
					std::cout<<"Marshal: Trovato uno ' ', nel server_name"<<std::endl;
					return -1;
				}
			}
			for (size_t i7=0;i7!=webservv->get_n_server();i7++){
				if(valore==webservv->servers[i7].get_name()){
					std::cout<<"Marshal: Il nome: "<<valore<<" e gia usato"<<std::endl;
					return -1;
				}
			}
			webservv->servers[serv].set_name(valore);
		}
		else if(chiave=="host")
			if(isValidIPv4(valore)==true){
				webservv->servers[serv].set_host(valore);
			}else{
				std::cout<<"Marshal: Host invalido"<<std::endl;
				return -1;
			}
		else if(chiave=="port")
			if(isValidPort(valore)==true){
				webservv->servers[serv].set_port(std::atoi(valore.c_str()));
			}else{
				std::cout<<"Marshal: Porta invalida"<<std::endl;
				return -1;
			}
		else if(chiave=="error404")
			webservv->servers[serv].set_error404(valore);
		else if(chiave=="error405")
			webservv->servers[serv].set_error405(valore);
		else if(chiave=="error418")
			webservv->servers[serv].set_error418(valore);
		else if(chiave=="error413")
			webservv->servers[serv].set_error413(valore);
		else if(chiave=="error500")
			webservv->servers[serv].set_error500(valore);
		else if(chiave=="body_size")
			if(isValidBody_Size(valore)==true){
				webservv->servers[serv].locations["/"].set_body_size(valore);
			}else{
				std::cout<<"Marshal: Body_size invalido"<<std::endl;
				return -1;
			}
		else if(chiave=="index")
			webservv->servers[serv].locations["/"].set_index(valore);
		else if(chiave=="showdir"){
			if(valore=="yes" || valore=="no")
				webservv->servers[serv].locations["/"].set_showdir(valore);
			else{
				std::cout<<"Marshal: Valore non riconosciuto in showdir"<<std::endl;
				return -1;
			}
		}
		else if(chiave=="root"){
			if(valore[0]!='/' || valore[0]=='.' || valore[valore.size()-1]!='/'){
				std::cout<<"Marshal: Il percorso non e un percorso statico"<<std::endl;
				return -1;
			}
			webservv->servers[serv].locations["/"].set_root(valore);
		}else if(chiave=="medallow"){
			std::vector<std::string> valore_vec;
			for (size_t i4=0;i4<valore.size();i4++){
				std::string val="";
				for (;valore[i4]!='-' && valore[i4]!='\0';i4++){
					val+=valore[i4];
				}
				if(val!="GET" && val!="POST" && val!="DELETE"){
					std::cout<<"Marshal: Metodo non riconosciuto"<<std::endl;
					return -1;
				}
				std::vector<std::string>::iterator temp = std::find(valore_vec.begin(), valore_vec.end(), val);
				if(temp!=valore_vec.end()){
					std::cout<<"Marshal: Trovato un metodo doppione"<<std::endl;
					return -1;
				}
				valore_vec.push_back(val);
			}
			webservv->servers[serv].locations["/"].set_medallow(valore_vec);
		}else if(chiave=="gci"){
			std::string chiavecgi, valorecgi;
			size_t i4=0;
			for (; valore[i4] != ' ' && valore[i4] != '\0'; i4++)
				chiavecgi += valore[i4];
			if (chiavecgi.empty() || chiavecgi[0] != '.') {
				std::cout << "Marshal: Errore nella configurazione delle cgi" << std::endl;
				return -1;
			}
			if (valore[i4] == ' ')
				i4++;
			for (; valore[i4] != '\0'; i4++) {
				if (valore[i4] == ' ') {
					std::cout << "Marshal: Errore nella configurazione delle cgi" << std::endl;
					return -1;
				}
				valorecgi += valore[i4];
			}
			if (valorecgi.empty()) {
				std::cout << "Marshal: Errore nella configurazione delle cgi" << std::endl;
				return -1;
			}
			webservv->servers[serv].locations["/"].gci[chiavecgi]=valorecgi;
		}else if(chiave=="ridirect"){
			std::vector<std::string> valore_vec;
			for (size_t i4=0;i4<valore.size();i4++){
				std::string val="";
				for (;valore[i4]!=' ' && valore[i4]!='\0';i4++){
					val+=valore[i4];
				}
				std::vector<std::string>::iterator temp = std::find(valore_vec.begin(), valore_vec.end(), val);
				if(temp!=valore_vec.end()){
					std::cout<<"Marshal: rindirizzamento nella stessa risorsa"<<std::endl;
					return -1;
				}
				valore_vec.push_back(val);
			}
			if(valore_vec.size()!=2){
				std::cout<<"Marshal: Numero di parametri in redicetion errati"<<std::endl;
				return -1;
			}
			webservv->servers[serv].locations["/"].set_ridirect(valore_vec);
		}else if(chiave=="location"){
			std::string location;
			if(valore[valore.size()-1]=='{' && valore[valore.size()-2]==' ')
				location = valore.substr(0, valore.size()-2);
			else{
				std::cout<<"Marshal: Error in location"<<std::endl;
				return -1;
			}
			if (location[location.size()-1]=='/'){
				std::cout<<"Marshal: Error in location"<<std::endl;
				return -1;
			}
			while(std::getline(conf, temp)){
				if(temp.empty())
					continue;
				int i=0;
				chiave="";
				valore="";
				while(temp[i]!='\0' && (temp[i]==' ' || temp[i]=='\t'))
					i++;
				while(temp[i]!='\0' && temp[i]!='='){
					chiave+=temp[i];
					i++;
				}
				if(chiave=="}"){
					chiave="location";
					break;
				}
				if(chiave=="}")
					break;
				if(temp[i]!='='){
					std::cout<<"Marshal: Errore nel file di configurazione"<<std::endl;
					return -1;
				}
				i++;
				while(temp[i]!='\0'){
					valore+=temp[i];
					i++;
				}
				if(chiave=="body_size")
					if(isValidBody_Size(valore)==true){
						webservv->servers[serv].locations[location].set_body_size(valore);
					}else{
						std::cout<<"Marshal: Body_size invalido"<<std::endl;
						return -1;
					}
				else if(chiave=="index")
					webservv->servers[serv].locations[location].set_index(valore);
				else if(chiave=="showdir"){
					if(valore=="yes" || valore=="no")
						webservv->servers[serv].locations[location].set_showdir(valore);
					else{
						std::cout<<"Marshal: Valore non riconosciuto in showdir"<<std::endl;
						return -1;
					}
				}else if(chiave=="root"){
					if(valore[0]!='/' || valore[0]=='.' || valore[valore.size()-1]!='/'){
						std::cout<<"Marshal: Il percorso non e un percorso statico"<<std::endl;
						return -1;
					}
					webservv->servers[serv].locations[location].set_root(valore);
				}else if(chiave=="medallow"){
					std::vector<std::string> valore_vec;
					for (size_t i4=0;i4<valore.size();i4++){
						std::string val="";
						for (;valore[i4]!='-' && valore[i4]!='\0';i4++){
							val+=valore[i4];
						}
						if(val!="GET" && val!="POST" && val!="DELETE"){
							std::cout<<"Marshal: Metodo non riconosciuto"<<std::endl;
							return -1;
						}
						std::vector<std::string>::iterator temp = std::find(valore_vec.begin(), valore_vec.end(), val);
						if(temp!=valore_vec.end()){
							std::cout<<"Marshal: Trovato un metodo doppione"<<std::endl;
							return -1;
						}
						valore_vec.push_back(val);
					}
					webservv->servers[serv].locations[location].set_medallow(valore_vec);
				}else if(chiave=="gci"){
					std::string chiavecgi, valorecgi;
					size_t i4=0;
					for (; valore[i4] != ' ' && valore[i4] != '\0'; i4++)
						chiavecgi += valore[i4];
					if (chiavecgi.empty() || chiavecgi[0] != '.') {
						std::cout << "Marshal: Errore nella configurazione delle cgi" << std::endl;
						return -1;
					}
					if (valore[i4] == ' ')
						i4++;
					for (; valore[i4] != '\0'; i4++) {
						if (valore[i4] == ' ') {
							std::cout << "Marshal: Errore nella configurazione delle cgi" << std::endl;
							return -1;
						}
						valorecgi += valore[i4];
					}
					if (valorecgi.empty()) {
						std::cout << "Marshal: Errore nella configurazione delle cgi" << std::endl;
						return -1;
					}
					webservv->servers[serv].locations[location].gci[chiavecgi]=valorecgi;
				}else if(chiave=="ridirect"){
					std::vector<std::string> valore_vec;
					for (size_t i4=0;i4<valore.size();i4++){
						std::string val="";
						for (;valore[i4]!=' ' && valore[i4]!='\0';i4++){
							val+=valore[i4];
						}
						std::vector<std::string>::iterator temp = std::find(valore_vec.begin(), valore_vec.end(), val);
						if(temp!=valore_vec.end()){
							std::cout<<"Marshal: rindirizzamento nella stessa risorsa"<<std::endl;
							return -1;
						}
						valore_vec.push_back(val);
					}
					if(valore_vec.size()!=2){
						std::cout<<"Marshal: Numero di parametri in redicetion errati"<<std::endl;
						return -1;
					}
					webservv->servers[serv].locations[location].set_ridirect(valore_vec);
				}else{
					std::cout<<"Marshal: Trovato una configrazione sconosciuta"<<std::endl;
					return -1;
				}
			}
		}
	}
	if(serv==0){
		std::cout<<"Marshal: Assente configurazione di un server"<<std::endl;
		return -1;
	}
	for (size_t i=0;i!=serv;i++){
		if(webservv->servers[i].locations["/"].get_root()=="")
			webservv->servers[i].locations["/"].set_root("/nfs/homes/aanghi/Desktop/42RomaLuis/webserv/marshal/dsite/");
		if(webservv->servers[i].locations["/"].get_body_size()=="-1" || webservv->servers[i].get_host()=="" || webservv->servers[i].get_port()==-1){
			std::cout<<"Marshal: Nancano delle configurazione"<<std::endl;
			return -1;
		}
		for (std::map<std::string, location>::iterator it = webservv->servers[i].locations.begin(); it != webservv->servers[i].locations.end(); ++it){
			std::vector <std::string> medotdefaul;
			medotdefaul.push_back("GET");
			medotdefaul.push_back("POST");
			medotdefaul.push_back("DELETE");
			if(it->second.get_lmedallow()==0)it->second.set_medallow(medotdefaul);
			if(it->second.get_body_size()=="-1")it->second.set_body_size(webservv->servers[i].locations["/"].get_body_size());
			if(it->second.get_index()=="")it->second.set_index(webservv->servers[i].locations["/"].get_index());
			if(it->second.get_root()=="")it->second.set_root(webservv->servers[i].locations["/"].get_root());
			if(isValidDirectory(it->second.get_root())==false)return -1;
		}
	}
	webservv->set_nserv(serv);
    return 0;
}