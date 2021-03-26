#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "pugixml.hpp"

std::vector<std::string> parse_string(std::string);

int main(int argc, char **argv) {

	if(argc != 2){
		return 1;
	}

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(argv[1]);

	int count = 0;

	if(result) {
		std::cout << "File loaded : " << argv[1] << std::endl;	
	} else {
		std::cout << "Error loading file" << argv[1] << std::endl;	
		return 1;
	}

	pugi::xml_node xournal = doc.first_child();

	for(pugi::xml_node page = xournal.child("page"); page; page = page.next_sibling("page"))
	{
		count++;
		for(pugi::xml_node stroke = page.child("layer").first_child(); stroke; stroke = stroke.next_sibling("stroke"))
		{
			std::string width_stroke = stroke.attribute("width").value();
			std::string point_stroke = stroke.child_value();
			std::vector<std::string> vector_width = parse_string(width_stroke);
			std::vector<std::string> vector_point = parse_string(point_stroke);
		
			std::vector<std::string>::size_type size_width = vector_width.size();
			std::vector<std::string>::size_type size_point = vector_point.size();
			std::cout << "page : " << count << " ; division : " << size_point / size_width << std::endl;

			//std::cout << "page : " << count << " ; width : " << size_width 
		        //		  << " ; point : " << size_point << std::endl;	
		}
	}

	//std::cout << count << " pages" << std::endl;	
	//std::cout << pages.first_attribute().name();	

	return 0;	
}

std::vector<std::string> parse_string(std::string string) {
	std::vector<std::string> result;
	std::istringstream iss(string);
	for(std::string s; iss >> s; )	
		result.push_back(s);
	return result;
}
