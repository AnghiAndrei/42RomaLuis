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
    if (port.empty() || port.size()>=6){
        return false;
	}
	for (size_t i2=0;'\0'!=port[i2];i2++){
		if (!isdigit(port[i2]))
            return false;
	}
	int num = std::atoi(port.c_str());
    if (num < 0 || num > 10000)
        return false;
    return true;
}

bool isValidDirectory(const std::string &path){
    struct stat info;

    if(stat(path.c_str(), &info)!=0) {
        std::cout<<"Marshal: "<<path<<"; non esiste"<<std::endl;
		return false;
    }else if (info.st_mode)
        return true;
    else{
        std::cout<<"Marshal: "<<path<<"; non e una cartella"<<std::endl;
        return false;
    }
	return false;
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
		if(chiave=="server_name")
			webservv->servers[serv].set_name(valore);
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
		else if(chiave=="body_size")
			if(isValidBody_Size(valore)==true){
				webservv->servers[serv].set_body_size(valore);
			}else{
				std::cout<<"Marshal: Body_size invalido"<<std::endl;
				return -1;
			}
		else if(chiave=="error404")
			webservv->servers[serv].set_error404(valore);
		else if(chiave=="error418")
			webservv->servers[serv].set_error418(valore);
		else if(chiave=="index")
			webservv->servers[serv].set_index(valore);
		else if(chiave=="showdir")
			webservv->servers[serv].set_showdir(valore);
		else if(chiave=="root")
			webservv->servers[serv].set_root(valore);
		else if(chiave=="root_assets")
			webservv->servers[serv].set_root_assets(valore);
		else if(chiave=="medallow"){
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
			webservv->servers[serv].set_medallow(valore_vec);
		}
		else if(chiave=="ridirect"){
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
			webservv->servers[serv].set_ridirect(valore_vec);
		}else{
			std::cout<<"Marshal: Trovato una configrazione sconosciuta"<<std::endl;
			return -1;
		}
	}
	if(serv==0){
		std::cout<<"Marshal: Assente configurazione di un server"<<std::endl;
		return -1;
	}
	for (size_t i=0;i!=serv;i++){
		std::ifstream file1(webservv->servers[i].get_error418().c_str());
		if(!file1.is_open()){
			std::cout<<"Marshal: Errore nella apertura del file: "<<webservv->servers[i].get_error418()<<std::endl;
			return -1;
		}
		std::ifstream file2(webservv->servers[i].get_error404().c_str());
		if(!file2.is_open()){
			std::cout<<"Marshal: Errore nella apertura del file: "<<webservv->servers[i].get_error404()<<std::endl;
			return -1;
		}
		if(webservv->servers[i].get_lridirect()==1 || webservv->servers[i].get_lridirect()>=3 || webservv->servers[i].get_lmedallow()==0 || webservv->servers[i].get_body_size()=="" || webservv->servers[i].get_host()=="" || webservv->servers[i].get_port()==-1){
			std::cout<<"Marshal: Nancano delle configurazione"<<std::endl;
			return -1;
		}
		if(isValidDirectory(webservv->servers[i].get_root_assets())==false)return -1;
		if(isValidDirectory(webservv->servers[i].get_root())==false)return -1;
	}
	webservv->set_nserv(serv);
    return 0;
}