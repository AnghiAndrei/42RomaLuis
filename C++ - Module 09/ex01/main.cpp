#include "RPN.hpp"

int main(int argc, char **argv){
	if(argc!=2){
		std::cout<<"Error"<<std::endl;
		return -1;
	}
	std::stack<int> stackd;
	int n=5;
	if(strlen(argv[1])==0){
		std::cout<<"Error"<<std::endl;
		return -1;
	}else if(strlen(argv[1])==2){
		if(argv[1][1]==' '){
			std::cout<<argv[1]<<std::endl;
			return 0;
		}else{
			std::cout<<"Error"<<std::endl;
			return -1;
		}
	}else if(strlen(argv[1])==1){
		std::cout<<argv[1]<<std::endl;
		return 0;
	}else if(strlen(argv[1])==3 || strlen(argv[1])==4){
		std::cout<<"Error"<<std::endl;
		return -1;
	}
	else{
		int op1=argv[1][0]-'0';
		int op2=argv[1][2]-'0';
		if(argv[1][4]=='/')stackd.push(op1/op2);
		else if(argv[1][4]=='*')stackd.push(op1*op2);
		else if(argv[1][4]=='-')stackd.push(op1-op2);
		else if(argv[1][4]=='+')stackd.push(op1+op2);
		else{
			size_t i=2;
			if(i+6>=strlen(argv[1])){
				std::cout<<"Error"<<std::endl;
				return -1;
			}
			int op3=argv[1][i]-'0';
			int op4=argv[1][i+2]-'0';
			int op5=argv[1][0]-'0';
			int ris=0;
			if(argv[1][i+4]=='/')ris=op3/op4;
			else if(argv[1][i+4]=='*')ris=op3*op4;
			else if(argv[1][i+4]=='-')ris=op3-op4;
			else if(argv[1][i+4]=='+')ris=op3+op4;
			else{
				std::cout<<"Error"<<std::endl;
				return -1;
			}
			if(argv[1][i+6]=='/')stackd.push(op5/ris);
			else if(argv[1][i+6]=='*')stackd.push(op5*ris);
			else if(argv[1][i+6]=='-')stackd.push(op5-ris);
			else if(argv[1][i+6]=='+')stackd.push(op5+ris);
			else{
				std::cout<<"Error"<<std::endl;
				return -1;
			}
			n=9;
		}
	}
	for (size_t i=n;1;i++){
		if(strlen(argv[1])<=i)break;
		if(argv[1][i]==' ')continue;
		int op1=stackd.top();
		int op2=argv[1][i]-'0';
		if(argv[1][i+2]=='/')stackd.push(op1/op2);
		else if(argv[1][i+2]=='*')stackd.push(op1*op2);
		else if(argv[1][i+2]=='-')stackd.push(op1-op2);
		else if(argv[1][i+2]=='+')stackd.push(op1+op2);
		else{
			if(i+6>=strlen(argv[1])){
				std::cout<<"Error"<<std::endl;
				return -1;
			}
			int op3=argv[1][i]-'0';
			int op4=argv[1][i+2]-'0';
			int ris=0;
			if(argv[1][i+4]=='/')ris=op3/op4;
			else if(argv[1][i+4]=='*')ris=op3*op4;
			else if(argv[1][i+4]=='-')ris=op3-op4;
			else if(argv[1][i+4]=='+')ris=op3+op4;
			else{
				std::cout<<"Error"<<std::endl;
				return -1;
			}
			if(argv[1][i+6]=='/')stackd.push(stackd.top()/ris);
			else if(argv[1][i+6]=='*')stackd.push(stackd.top()*ris);
			else if(argv[1][i+6]=='-')stackd.push(stackd.top()-ris);
			else if(argv[1][i+6]=='+')stackd.push(stackd.top()+ris);
			else{
				std::cout<<"Error"<<std::endl;
				return -1;
			}
			i+=7;
			continue;
		}
		i+=3;
	}
	std::cout<<stackd.top()<<std::endl;
	return 0;
}
