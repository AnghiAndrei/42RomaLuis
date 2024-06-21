#include "PmergeMe.hpp"

int main(int argc, char **argv){
	if(argc==1){
		std::cout<<"Error"<<std::endl;
		return -1;
	}
	if(strlen(argv[1])==0){
		std::cout<<"Error"<<std::endl;
		return -1;
	}
	std::deque<int> dequen;
	std::vector<int> listan;
	if(argc==2)
		for (size_t i=0;strlen(argv[1])>i;i++)
		{
			std::string temp="";
			for (i=i;argv[1][i]!=' ' && argv[1][i]!='\0';i++){
				if((argv[1][i]-'0')>=0 && (argv[1][i]-'0')<=9)
					temp+=argv[1][i];
				else{
					std::cout<<"Error"<<std::endl;
					return -1;
				}
			}
			if(atoi(temp.c_str()) < 0){
				std::cout<<"Error"<<std::endl;
				return -1;
			}
			if(easyFind(listan, atoi(temp.c_str()))==-1){
				listan.push_back(atoi(temp.c_str()));
				dequen.push_back(atoi(temp.c_str()));
			}else{
				std::cout<<"Error"<<std::endl;
				return -1;
			}
		}
	else
		for (size_t i2=1; argv[i2];i2++){
			for (size_t i=0;strlen(argv[i2])>i;i++)
			{
				std::string temp="";
				for (i=i;argv[i2][i]!=' ' && argv[i2][i]!='\0';i++){
					if((argv[i2][i]-'0')>=0 && (argv[i2][i]-'0')<=9)
						temp+=argv[i2][i];
					else{
						std::cout<<"Error"<<std::endl;
						return -1;
					}
				}
				if(atoi(temp.c_str()) < 0){
					std::cout<<"Error"<<std::endl;
					return -1;
				}
				if(easyFind(listan, atoi(temp.c_str()))==-1){
					listan.push_back(atoi(temp.c_str()));
					dequen.push_back(atoi(temp.c_str()));
				}else{
					std::cout<<"Error"<<std::endl;
					return -1;
				}
			}
		}
	std::cout<<"Before:  ";
	for (size_t i=0;listan.size()!=i;i++)
		std::cout<<listan[i]<<" ";
	std::cout<<std::endl;

	std::clock_t start = std::clock();
	sort(&listan);
	std::clock_t end = std::clock();
	double listat = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	start = std::clock();
	sort(&dequen);
	end = std::clock();
	double dequet = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	std::cout<<"After:   ";
	for (size_t i=0;listan.size()!=i;i++)
		std::cout<<listan[i]<<" ";
	std::cout<<std::endl;
	std::cout<<"Time to process a range of "<<listan.size()<<" elements with std::vector : "<<listat<<" us"<<std::endl;
	std::cout<<"Time to process a range of "<<listan.size()<<" elements with std::deque : "<<dequet<<" us"<<std::endl;
	return 0;
}
