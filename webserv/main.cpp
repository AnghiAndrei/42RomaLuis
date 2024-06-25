#include"webserv.hpp"

int main(int argc, char **argv){
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
	webserv webservv;
	std::string temp;
	bool server=false;
	while(std::getline(conf, temp)){
		if(temp.empty())
			continue;
		if(server==false && temp[0]=='{'){
			server=true;
			continue;
		}
		if(server==true && temp[0]=='}'){
			server=false;
			webservv.crea_server();
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
			webservv.servers[serv].set_name(valore);
		else if(chiave=="host")
			webservv.servers[serv].set_host(valore);
		else if(chiave=="port")
			webservv.servers[serv].set_port(valore);
		else if(chiave=="body_size")
			webservv.servers[serv].set_body_size(valore);
		else if(chiave=="error404")
			webservv.servers[serv].set_error404(valore);
		else if(chiave=="error418")
			webservv.servers[serv].set_error418(valore);
		else if(chiave=="index")
			webservv.servers[serv].set_index(valore);
		else if(chiave=="showdir")
			webservv.servers[serv].set_showdir(valore);
		else if(chiave=="root")
			webservv.servers[serv].set_root(valore);
		else if(chiave=="medallow"){
			std::vector<std::string> valore_vec;
			for (size_t i4=0;i4<valore.size();i4++){
				std::string val="";
				for (i4=i4;valore[i4]!='-' && valore[i4]!='\0';i4++){
					val+=valore[i4];
				}
				valore_vec.push_back(val);
			}
			webservv.servers[serv].set_medallow(valore_vec);
		}
		else if(chiave=="redict"){
			std::vector<std::string> valore_vec;
			for (size_t i4=0;i4<valore.size();i4++){
				std::string val="";
				for (i4=i4;valore[i4]!=' ' && valore[i4]!='\0';i4++){
					val+=valore[i4];
				}
				valore_vec.push_back(val);
			}
			webservv.servers[serv].set_redict(valore_vec);
		}
	}
	if(serv==0){
		std::cout<<"Marshal: Configurazione di un server assente"<<std::endl;
		return -1;
	}
	for (size_t i=0;i!=serv;i++){
		if(webservv.servers[i].get_lredict()==1 || webservv.servers[i].get_lredict()>=3 || webservv.servers[i].get_lmedallow()==0 || webservv.servers[i].get_body_size()=="" || webservv.servers[i].get_host()=="" || webservv.servers[i].get_port()==""){
			std::cout<<"Marshal: Nancano delle configurazione"<<std::endl;
			return -1;
		}
	}
	webservv.set_nserv(serv);

	for (size_t i=0;i!=serv;i++){
		std::cout<<"Server      : "<<i<<std::endl;
		std::cout<<"Name        : "<<webservv.servers[i].get_name()<<std::endl;
		std::cout<<"Body_size   : "<<webservv.servers[i].get_body_size()<<std::endl;
		std::cout<<"Host        : "<<webservv.servers[i].get_host()<<std::endl;
		std::cout<<"Port        : "<<webservv.servers[i].get_port()<<std::endl;
		std::cout<<"Error 404   : "<<webservv.servers[i].get_error404()<<std::endl;
		std::cout<<"Error 418   : "<<webservv.servers[i].get_error418()<<std::endl;
		std::cout<<"Show dir    : "<<webservv.servers[i].get_showdir()<<std::endl;
		std::cout<<"Root        : "<<webservv.servers[i].get_root()<<std::endl;
		std::cout<<"Method allow: ";
		for (size_t i2=0;i2<webservv.servers[i].get_lmedallow();i2++)
			std::cout<<webservv.servers[i].get_medallow(i2)<<" ";
		std::cout<<std::endl;
		std::cout<<"Redirect    : ";
		for (size_t i2=0;i2<webservv.servers[i].get_lredict();i2++)
			std::cout<<webservv.servers[i].get_redict(i2)<<" ";
		std::cout<<std::endl;
		std::cout<<"Index       : "<<webservv.servers[i].get_index()<<std::endl;

		std::cout<<std::endl;
	}
    return 0;
}
