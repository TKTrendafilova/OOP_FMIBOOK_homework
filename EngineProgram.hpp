#ifndef __ENGINE_PROGRAM_HPP
#define __ENGINE_PROGRAM_HPP

#include "Publication.hpp"
#include "PicturePublication.hpp"
#include "TextPublication.hpp"
#include "URLPublication.hpp"
#include "User.hpp"
#include "Moderator.hpp"
#include "Admin.hpp"

class Engine {
private:
	User** m_users;
	unsigned m_numberOfUser;
	unsigned m_capacityOfUsers;

	//������ � ������ ���������� �� ����������.
	Publication **m_publications;
	unsigned m_numberOfPublication;
	unsigned m_capacityOfPublication;

public:
	Engine();
	//Engine(User**, unsigned, unsigned);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	~Engine();

public:

	void printUser();
	unsigned getNumberOfUsers()const;

	void addUser(char*, unsigned);
	void addModerator(char* , unsigned);
	void removeUser(char* );
	void block(char* nickname);
	void unblock(char* nickname);
	void addImagePost(char*nameUser, char* conatent);
	void addURLPost(char* nameUser, char* content, char* description);
	void addTextPost(char* nameUser, char*content);
	void removePost(unsigned);
	void viewPost(unsigned);
	void viewAllPost(char* username);
	void info();
	void quit();
	//������� �� ����� �� ����� �� ����������.
	void changeNickname(char*, char*);
	void runProgram();

private:
	void resizeUserList();
	void resizePublicationList();
	//�������, ����� ����� ��������� �� ������ ���������� �� ���.
	int returnPositionOfUser(char*);

	//�������, ����� ������ ���� �� ������������ �����������.
	void numberOfUsers();

	//�������, ����� ������ ���� �� ������������.
	void numberOfModerators();

	//�������, ����� ������ ����������� � ���-����� �������.
	void findUser();

	//�������, ����� ������ ���� �� ����������� ����������� � �� �������.
	void blockedUsers();

	//�������, ����� ������ ���-������ ����������.
	void theYoungestUser();

	//�������, ����� ������ ���-������ ����������.
	void theOldestUser();

	//�������, ����� ��������� ���� ������ ��� � ��������.
	bool isUniqueNickname(char*);


};

#endif