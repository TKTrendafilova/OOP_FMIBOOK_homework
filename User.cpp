#pragma warning(disable:4996)
#include<cstring>
#include<fstream>
#include<iostream>
#include<typeinfo>
#include "User.hpp"
#include"TextPublication.hpp"
#include"PicturePublication.hpp"
#include"URLPublication.hpp"

const unsigned START_CAPACITY = 8;

User::User()
	:m_nickname(nullptr), m_age(0),m_isBlocked(false),m_publications(nullptr),m_countPubl(0),m_capacityPubl(START_CAPACITY)
{
	m_publications = new(std::nothrow) Publication*[m_capacityPubl];
	if (m_publications == nullptr) {
		std::cout << "Not enought memory for publications in default caonstructor of user. Error!" << std::endl;
		
	}
}

User::User(char * nickname, unsigned age, bool isBlock)
	:m_nickname(nullptr), m_age(age), m_isBlocked(isBlock)
	,m_publications(nullptr), m_countPubl(0), m_capacityPubl(START_CAPACITY)
{
	m_publications = new(std::nothrow) Publication*[m_capacityPubl];
	if (m_publications == nullptr) {
		std::cout << "Not enought memory for publications in default caonstructor of user. Error!" << std::endl;

	}
	setNickname(nickname);
}

User::User(char * nickname, unsigned age,bool isBlock, Publication** publ, unsigned count, unsigned capacity)
	:m_nickname(nullptr), m_age(age), m_isBlocked(isBlock) ,m_publications(nullptr), m_countPubl(count), m_capacityPubl(capacity)
{
	setNickname(nickname);

	m_publications = new(std::nothrow) Publication*[m_capacityPubl];
	
	if (m_publications == nullptr) {
		std::cout << "Not enought memory for publications in default caonstructor of user. Error!" << std::endl;

	}
	for (int i = 0; i < m_countPubl; ++i) {
		m_publications[i] = publ[i];
	}
}

User::~User()
{
	delete[] m_nickname;
	m_nickname = nullptr;

	delete[] m_publications;
	m_publications = nullptr;
}

void User::setNickname(char * newNickname)
{
	if (m_nickname != nullptr) {
		delete[] m_nickname;
	}

	m_nickname = new (std::nothrow) char[strlen(newNickname) + 1];
	if (m_nickname == nullptr) {
		std::cout << "Not enought memory to set nickname. Error!" << std::endl;
		return;
	}

	strcpy(m_nickname, newNickname);
}

void User::setAge(unsigned age)
{
	m_age = age;
}

void User::setBlocked()
{
	if (m_isBlocked == true) {
		std::cout << "User " <<m_nickname<<" is already blacked." << std::endl;
	}
	else {
		m_isBlocked = true;
	}
}

void User::setUnblocked()
{
	if (m_isBlocked == false) {
		std::cout << "User " << m_nickname << " is already unblocked." << std::endl;
	}
	else {
		m_isBlocked = false;
	}
}

char * User::getNickname() const
{
	return m_nickname;
}

unsigned User::getAge() const
{
	return m_age;
}

bool User::getBlocked() const
{
	return m_isBlocked;
}

unsigned User::getNumberOfPublication() const
{
	return m_countPubl;
}

void User::addPublication(Publication*& publ)
{
	if (m_countPubl >= m_capacityPubl) {
		resize();
	}
	m_publications[m_countPubl] = publ;
	++m_countPubl;
}

void User::deleteAllPost()
{
	delete[]m_publications;
	m_countPubl = 0;
	m_capacityPubl = START_CAPACITY;
	m_publications = nullptr;
}

void User::deletePost(unsigned id)
{
	int posOfPubl = -1;

	for (int i = 0; i < m_countPubl; ++i) {
		if (m_publications[i]->getID() == id) {
			posOfPubl = i;
			break;
		}
	}

	if (posOfPubl == -1) {
		std::cout << std::endl << m_nickname << " has no post " << id << ". " << std::endl << std::endl;
		return;
	}
	
	m_publications[posOfPubl] = m_publications [m_countPubl - 1];
	--m_countPubl;
	
}

void User::viewAllPosts()
{
	const unsigned WIDTH = 500;
	const unsigned HEIGHT = 333;
	const char* ext = ".html";
	const char* secondPartOfFileName = "_posts";
	unsigned fileNameLen = strlen(m_nickname) + strlen(secondPartOfFileName) + strlen(ext) + 1;//+1 за '\0'

	char* fileName = new(std::nothrow) char[fileNameLen];
	if (fileName == nullptr) {
		std::cout << "Not enought memory for fileName in User::viewAllPost(). Error!" << std::endl;
		return;
	}

	strcpy(fileName, m_nickname);
	strcat(fileName, secondPartOfFileName);
	strcat(fileName, ext);

	std::ofstream ofs(fileName);
	if (!ofs.is_open()) {
		std::cout << "In User::viewAllPost() file is not opened. Error!" << std::endl;
		return;
	}
	ofs << "<!DOCTYPE html>\n";
	ofs << "<html>\n";
	ofs << "<body>\n\n";
	ofs << "<h2>" << m_nickname << "'s all post.</h2>\n";

	for (int i = 0; i < m_countPubl; ++i) {
		if (typeid(*m_publications[i]) == typeid(Text)) {
			ofs << "<p>" << m_publications[i]->getContent() << "</p>\n";
		}
		if (typeid(*m_publications[i]) == typeid(PicturePubl)) {
			ofs << "<img src=\"" << m_publications[i]->getContent()<< "\" alt=\"Image\" width=\"" << WIDTH << "\" height=\"" << HEIGHT << "\"> \n";
		}
		if (typeid(*m_publications[i]) == typeid(URL)) {
			ofs << "<p> <a href=\"" << m_publications[i]->getContent() << "\">" << "description"<< "</a></p> \n";
		}
	}

	ofs << "\n";
	ofs << "</body>\n";
	ofs << "</html>\n";
}


bool User::isOwnPubl(unsigned id)
{
	for (int i = 0; i < m_countPubl; ++i) {
		if (id == m_publications[i]->getID()) {
			return true;
		}
	}
	return false;
}

void User::printUserInfo()
{
	std::cout << m_nickname << ", " << m_age << " years old, " << m_countPubl << " posts." << std::endl;
}

void User::resize()
{
	unsigned newCapacity = m_capacityPubl * 2;
	Publication** newPubl = new (std::nothrow) Publication*[newCapacity];

	if (newPubl == nullptr) {
		std::cout << "Not enought memory for resize! Error!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_capacityPubl; ++i) {
		newPubl[i] = m_publications[i];
	}
	m_capacityPubl = newCapacity;
	delete[] m_publications;
	m_publications = newPubl;
}
