#include"webserv.hpp"

int main(int argc, char **argv){
	webserv webservv;
	if(check(argc, argv, &webservv)==-1)
		return -1;

	for (size_t i=0;i!=webservv.get_n_server();i++){
		std::cout<<"Start | Server "<<i+1<<std::endl;
		std::cout<<"Name        : "<<webservv.servers[i].get_name()<<std::endl;
		std::cout<<"Host        : "<<webservv.servers[i].get_host()<<std::endl;
		std::cout<<"Port        : "<<webservv.servers[i].get_port()<<std::endl;
		std::cout<<"Body_size   : "<<webservv.servers[i].get_body_size()<<std::endl;
		std::cout<<"Error 404   : "<<webservv.servers[i].get_error404()<<std::endl;
		std::cout<<"Error 418   : "<<webservv.servers[i].get_error418()<<std::endl;
		std::cout<<"Show dir    : "<<webservv.servers[i].get_showdir()<<std::endl;
		std::cout<<"Root        : "<<webservv.servers[i].get_root()<<std::endl;
		std::cout<<"Root_assets : "<<webservv.servers[i].get_root_assets()<<std::endl;
		std::cout<<"Index       : "<<webservv.servers[i].get_index()<<std::endl;
		std::cout<<"Method allow: ";
		for (size_t i2=0;i2<webservv.servers[i].get_lmedallow();i2++)
			std::cout<<webservv.servers[i].get_medallow(i2)<<" ";
		std::cout<<std::endl;
		if(webservv.servers[i].get_lridirect()!=0)
			std::cout<<"Redirect    : "<<webservv.servers[i].get_ridirect(0)<<" -> "<<webservv.servers[i].get_ridirect(1)<<std::endl;
		std::cout<<std::endl<<std::endl;
	}
    return 0;
}
