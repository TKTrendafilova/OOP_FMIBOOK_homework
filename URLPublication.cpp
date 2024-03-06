#pragma warning(disable:4996)
#include<iostream>
#include<cstring>
#include<fstream>
#include "URLPublication.hpp"

const unsigned EXTENTION_LEN = 6;

URL::URL()
	:Publication(),m_description(nullptr)
{
}

URL::URL(char * content, char* desc)
	:Publication(content), m_description(nullptr)
{
	m_description = new(std::nothrow) char[strlen(desc) + 1];
	if (m_description == nullptr) {
		std::cout << "Not enought memory for description. Error!" << std::endl;
		return;
	}
	strcpy(m_description, desc);
}

URL::~URL()
{
	delete[] m_description;
	m_description = nullptr;
}

void URL::createHTML( char* fileName)
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

	ofs << "<!DOCTYPE html> \n";
	ofs << "<html>\n";
	ofs << "<body>\n\n";
	
	ofs << "<h2> HTML Links </h2> \n";
	ofs << "<p> <a href=\"" << text << "\">" << m_description << "</a></p> \n\n";
	
	ofs << "</body> \n ";
	ofs<<"</html> \n";

	if (ofs.good()) {
		std::cout << "Successfully created URL post." << std::endl;
	}
	else {
		std::cout << "URL post is not created. Error!" << std::endl;
	}
	
	ofs.close();
	delete[] text;
}

char * URL::getDescription() const
{
	return m_description;
}
