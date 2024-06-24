#include "BitcoinExchange.hpp"

bool bisestile(int year) {
    if (year % 4 != 0) return false;
    if (year % 100 == 0 && year % 400 != 0) return false;
    return true;
}

bool isValidDate(int day, int month, int year) {
    if (year < 1) return false;
    if (month < 1 || month > 12) return false;
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if(bisestile(year))
        daysInMonth[1]=29;
    if (day < 1 || day > daysInMonth[month - 1]) return false;
    return true;
}

int main(int argc, char **argv){
	if(argc!=2){
		std::cout<<"Error: could not open file."<<std::endl;
		return -1;
	}
	std::ifstream dataf("data.csv");
	if (!dataf.is_open())
        return (std::cout<<"Error: could not open file."<<std::endl, 1);
	std::string temp;
	std::map<std::string, float> diz;
	while(std::getline(dataf, temp)){
		std::string temp2="";
		std::string temp3="";
		size_t i=0;
		for(i=0;temp[i]!=',' && temp.size()!=i; i++)
			temp2+=temp[i];
		i++;
		for(size_t i2=i;temp.size()!=i2; i2++)
			temp3+=temp[i2];
		diz[temp2]=atof(temp3.c_str());
    }
	std::ifstream inputf(argv[1]);
	if (!inputf.is_open())
        return (std::cout<<"Error: could not open file."<<std::endl, 1);
	std::getline(inputf, temp);
	while(std::getline(inputf, temp)){
		std::string temp2="";
		std::string temp3="";
		size_t i=0;
		for(i=0;temp[i]!=' ' && temp.size()!=i; i++)
			temp2+=temp[i];
		if (temp.size()>=i+3)
			for(size_t i2=i+3;temp.size()!=i2; i2++)
				temp3+=temp[i2];
		else{
			std::cout<<"Error: bad input => "<<temp<<std::endl;
			continue;
		}
		if(atoi(temp3.c_str()) <= -1)
			std::cout<<"Error: not a positive number."<<std::endl;
		else if(atoi(temp3.c_str()) > 1000)
			std::cout<<"Error: too large a number."<<std::endl;
		else if(diz.find(temp2) != diz.end())
			std::cout<<temp2<<" => "<<temp3<<" = "<<diz[temp2]*atof(temp3.c_str())<<std::endl;
		else{
			std::string day;
			std::string mont;
			std::string year;
			size_t i2=0;
			for(i2=0;temp2[i2]!='-' && temp2.size()!=i2; i2++)
				year+=temp2[i2];
			i2++;
			for(i2=i2;temp2[i2]!='-' && temp2.size()!=i2; i2++)
				mont+=temp2[i2];
			i2++;
			for(i2=i2;temp2.size()!=i2; i2++)
				day+=temp2[i2];
			bool stampa=true;
			while (diz.find(year+"-"+mont+"-"+day) == diz.end()){
				if(isValidDate(atoi(day.c_str()), atoi(mont.c_str()),atoi(year.c_str()))==false){
					std::cout<<"Error: bad input => "<<temp2<<std::endl;
					stampa=false;
					break;
				}
				std::ostringstream convertitore;
				convertitore << atoi(day.c_str())-1;
				day=convertitore.str();
				if(atoi(day.c_str())==0){
					std::ostringstream cy;
					switch (atoi(mont.c_str())){
						case 1:
							cy << atoi(year.c_str())-1;
							year=cy.str();
							mont="12";
							day="31";
							break;
						case 2:
							mont="01";
							day="31";
							break;
						case 3:
							mont="02";
							day="28";
							if(bisestile(atoi(year.c_str())))
								day="29";
							break;
						case 4:
							mont="03";
							day="31";
							break;
						case 5:
							mont="04";
							day="30";
							break;
						case 6:
							mont="05";
							day="31";
							break;
						case 7:
							mont="06";
							day="30";
							break;
						case 8:
							mont="07";
							day="31";
							break;
						case 9:
							mont="08";
							day="31";
							break;
						case 10:
							mont="09";
							day="30";
							break;
						case 11:
							mont="10";
							day="31";
							break;
						case 12:
							mont="11";
							day="30";
							break;
					}
				}
				switch (atoi(day.c_str())){
					case 1:
						day="01";
						break;
					case 2:
						day="02";
						break;
					case 3:
						day="03";
						break;
					case 4:
						day="04";
						break;
					case 5:
						day="05";
						break;
					case 6:
						day="06";
						break;
					case 7:
						day="07";
						break;
					case 8:
						day="08";
						break;
					case 9:
						day="09";
						break;
				}
				if(atoi(year.c_str())<0)
					break;
				if(year.size()==3)
					year="0"+year;
				if(year.size()==2)
					year="00"+year;
				if(year.size()==1)
					year="000"+year;
			}
			if(stampa==true)
				std::cout<<temp2<<" => "<<temp3<<" = "<<diz[year+"-"+mont+"-"+day]*atof(temp3.c_str())<<std::endl;
		}
    }
	return 0;
}
