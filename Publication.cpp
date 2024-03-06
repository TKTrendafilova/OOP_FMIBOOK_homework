#pragma warning(disable:4996)
#include<iostream>
#include<cstring>
#include<fstream>
#include"Publication.hpp"

unsigned Publication:: m_counterID = 1;

Publication::Publication()
	:m_content(nullptr)
{
	m_ID = m_counterID;
	++m_counterID;
}

Publication::Publication(char * content)
	:m_content(nullptr)
{
	setContent(content);
	m_ID = m_counterID;
	++m_counterID;
}

Publication::Publication(const Publication & other)
{
	if (this != &other) {
		setContent(other.m_content);
	}
}

Publication & Publication::operator=(const Publication & other)
{
	if (this != &other) {
		delete[]m_content;
		setContent(other.m_content);
	}
	return *this;
}

Publication::~Publication()
{
	delete[] m_content;
	m_content = nullptr;
}

void Publication::setContent(char * content)
{
	if (m_content != nullptr) {
		delete[] m_content;
		m_content = nullptr;
	}

	m_content = new(std::nothrow) char[strlen(content) + 1];
	if (m_content == nullptr) {
		std::cout << "Not enought memory for set content. Error!" << std::endl;
		return;
	}
	strcpy(m_content, content);
}

char * Publication::getContent() const
{
	return m_content;
}

unsigned Publication::getID() const
{
	return m_ID;
}

bool Publication::operator==(const Publication & publ)
{
	if (strcmp(this->m_content, publ.m_content) == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Publication::createHTML(char*fileName )
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open()) {
		std::cout << "File is not open. Error!" << std::endl;
		return;
	}

	ofs << "<!DOCTYPE html> \n <html> \n <body> \n";
	ofs << "<h2>" << "Default publication" << "</h2> \n";
	ofs << "</body> \n </html> \n";
}
