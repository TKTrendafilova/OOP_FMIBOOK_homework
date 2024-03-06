#pragma warning(disable:4996)
#include<fstream>
#include<iostream>
#include<cstring>
#include"Publication.hpp"
#include "TextPublication.hpp"

Text::Text()
	:Publication()
{
}

Text::Text(char * content)
	:Publication(content)
{
}

void Text::createHTML(char* fileName)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open()) {
		std::cout << "File is not open. Error!" << std::endl;
		return;
	}
	

	char* text = new(std::nothrow) char[strlen(m_content) + 1];
	if (text == nullptr) {
		std::cout << "Not enought memory for text. Error!" << std::endl;
		return;
	}
	strcpy(text, m_content);

	ofs << "<!DOCTYPE html>\n";
	ofs << "<html>\n";
	ofs << "<body>\n";

	ofs << "<p>" << text << "</p>\n";

	ofs << "</body> \n";
	ofs << "</html>";

	if (ofs.good()) {
		std::cout << "Successfully created HTML file for text post." << std::endl;
	}
	else {
		std::cout << "File is not created. Error!" << std::endl;
	}
	ofs.close();
	delete[] text;
	
}
