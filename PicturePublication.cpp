#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include"PicturePublication.hpp"

const unsigned WIDTH = 500;
const unsigned HEIGHT = 333;

PicturePubl::PicturePubl()
	:Publication()
{
	
}

PicturePubl::PicturePubl(char * content)
	:Publication(content)
{
}

void PicturePubl::createHTML(char* fileName)
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

	ofs << "<h2> HTML Image </h2> \n";
	ofs << "<img src=\"" << text << "\" alt=\"Image\" width=\"" << WIDTH << "\" height=\"" << HEIGHT << "\"> \n\n";

	ofs << "</body>\n";
	ofs << "</html>";

	if (ofs.good()) {
		std::cout << "Successfully created HTML file of post. " << std::endl;
	}
	else {
		std::cout << "File is not created" << std::endl;
	}

	ofs.close();
	delete[] text;
}
