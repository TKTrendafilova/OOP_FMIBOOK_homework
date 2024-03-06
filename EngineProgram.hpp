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

	//Списък с всички публикации на програмата.
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
	//Функция за смяна на името но потребител.
	void changeNickname(char*, char*);
	void runProgram();

private:
	void resizeUserList();
	void resizePublicationList();
	//Функция, която връща позицията на търсен потребител по име.
	int returnPositionOfUser(char*);

	//Функция, която намира броя на обикновените потребители.
	void numberOfUsers();

	//Функция, която намира броя на модераторите.
	void numberOfModerators();

	//Функция, която намира потребителя с най-много постове.
	void findUser();

	//Функция, която намира броя на блокираните потребители и ги извежда.
	void blockedUsers();

	//Функция, която намира най-младия потребител.
	void theYoungestUser();

	//Функция, която намира най-стария потребител.
	void theOldestUser();

	//Функция, която проверява дали дадено име е уникално.
	bool isUniqueNickname(char*);


};

#endif