#ifndef __USER_HPP
#define __USER_HPP

#include<fstream>
#include"Publication.hpp"

class User {
protected:
	char* m_nickname;
	unsigned m_age;
	bool m_isBlocked;

	//Всеки потребител има свой публикации.
	Publication** m_publications;
	unsigned m_countPubl;
	unsigned m_capacityPubl;

public:
	User();
	User(char*, unsigned, bool = false); //Когато админитстраторът добавя нов потребител.
	User(char*, unsigned,bool, Publication**, unsigned,unsigned);
	User(const User&)=delete;
	User& operator=(const User&)=delete;

	//Виртуален деструктор, за да може правилно да се изтрие паметта.
	virtual ~User();

	void setNickname(char*);
	void setAge(unsigned);
	
	//Функция, която блокира потребител.
	void setBlocked();

	//Функция, която разблокира потребител.
	void setUnblocked();

	char* getNickname()const;
	unsigned getAge()const;
	bool getBlocked()const;
	unsigned getNumberOfPublication()const;

	//addPublication не е virtual, защото всички останали видове потребители могат да го правят по един и същи начин.
	void addPublication(Publication*&);

	void deleteAllPost();

	void deletePost(unsigned);

	//Функция, която създава HTML файл с всички публикации на потребителя.
	void viewAllPosts();

	//Функция, която проверяа дали публикация по дадено ID е публикация на потребителя.
	bool isOwnPubl(unsigned);

	//Функция, която извежда информацията за потребителя.
	void printUserInfo();

private: 
	void resize();
};

#endif
