// xml_xournal.cpp

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "pugixml.hpp"

struct point_struct {
	double x;
	double y;
};

typedef struct point_struct point_t;

std::vector<point_t> parse_string(std::string);

std::string point_to_string(std::vector<point_t>&);

int main(int argc, char **argv) {

	if(argc != 2){
		return 1;
	}
	
	// load xml file 
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

	// iterate to every page
	for(pugi::xml_node page = xournal.child("page"); page; page = page.next_sibling("page"))
	{
		count++;
		
		// iterate to every stroke
		for(pugi::xml_node stroke = page.child("layer").first_child(); stroke; stroke = stroke.next_sibling("stroke"))
		{
			std::string point_stroke = stroke.child_value();
			std::vector<point_t> vector_point = parse_string(point_stroke);
			
			std::vector<point_t>::size_type size_point = vector_point.size();
			
			// odd number of points only
			if (size_point % 2 != 0) {
				std::cout << "page : " << count << " ; point : " << size_point << std::endl;	
				vector_point.push_back(vector_point.back());
				std::string point_stroke_new = point_to_string(vector_point);
				stroke.first_child().set_value(point_stroke_new.c_str());
			}
		}
	}

	std::cout << count << " pages" << std::endl;	

	// save changes to xml file	
	doc.save_file(argv[1]);
	return 0;	
}

// white spaced string to vector of point_t type
std::vector<point_t> parse_string(std::string string) {
	std::vector<point_t> result;
	point_t point;
	std::istringstream iss(string);
	std::string::size_type sz;
	int count = 0;	

	for(std::string s; iss >> s; ) {
		if((count%2) == 0){
			point.x = std::stod(s,&sz);
		} else {
			point.y = std::stod(s,&sz);
			result.push_back(point);
		}

		count++;
	}
	return result;
}

// vector of point_t type to a white spaced string 
std::string point_to_string(std::vector<point_t>& v_point) {
	std::ostringstream oss;	
	
	for(std::vector<point_t>::iterator it = v_point.begin(); 
	    it != v_point.end();
	    ++it) {
		if(it < v_point.end() - 1){
			oss << it->x << " "
			    << it->y << " "; 
		} else {
			oss << it->x << " "
			    << it->y; 
		}
	}

	return oss.str();
}

