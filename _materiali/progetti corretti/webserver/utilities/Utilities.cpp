#include "Utilities.hpp"

std::string Utilities::join(std::vector<std::string> lines, std::string delims)
{
	std::string joined = "";
	
	for(unsigned int i = 0; i < lines.size(); i++)
	{
		joined += lines.at(i);
		if ( i < lines.size()-1)
			joined += delims;
	}
	
	return joined;
}

std::string Utilities::to_lower(std::string str)
{
	std::string lower_str = "";
	
	for(unsigned int i = 0; i < str.size(); i++)
	{
		lower_str += tolower(str.at(i));
	}
	
	return lower_str;
}

std::vector<std::string> Utilities::split(std::string req, std::string delims, bool skip_empty = 0)
{
    size_t start = 0;
    size_t end;
    std::vector<std::string> lines;
    
    do {
        end = req.find(delims, start);
		std::string line;
		if(end != std::string::npos)
			line = req.substr(start, end-start);
		else
			line = req.substr(start);
		
		if(skip_empty && line.size() > 0)
			lines.push_back(line);
		else if(!skip_empty)
			lines.push_back(line);
		
		start = end + delims.size();        
    } while(end != std::string::npos);
	return lines;
}

std::string Utilities::trim(std::string str)
{
	std::string trimmed = "";
	
	for(unsigned int i = 0; i < str.size(); i++)
	{
		if(str.at(i) != ' ' && str.at(i) != '\t')
			trimmed += str.at(i);
	}
	
	return trimmed;
}