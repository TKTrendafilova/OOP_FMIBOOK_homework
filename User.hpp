#ifndef __USER_HPP
#define __USER_HPP

#include<fstream>
#include"Publication.hpp"

class User {
protected:
	char* m_nickname;
	unsigned m_age;
	bool m_isBlocked;

	//����� ���������� ��� ���� ����������.
	Publication** m_publications;
	unsigned m_countPubl;
	unsigned m_capacityPubl;

public:
	User();
	User(char*, unsigned, bool = false); //������ ���������������� ������ ��� ����������.
	User(char*, unsigned,bool, Publication**, unsigned,unsigned);
	User(const User&)=delete;
	User& operator=(const User&)=delete;

	//��������� ����������, �� �� ���� �������� �� �� ������ �������.
	virtual ~User();

	void setNickname(char*);
	void setAge(unsigned);
	
	//�������, ����� ������� ����������.
	void setBlocked();

	//�������, ����� ���������� ����������.
	void setUnblocked();

	char* getNickname()const;
	unsigned getAge()const;
	bool getBlocked()const;
	unsigned getNumberOfPublication()const;

	//addPublication �� � virtual, ������ ������ �������� ������ ����������� ����� �� �� ������ �� ���� � ���� �����.
	void addPublication(Publication*&);

	void deleteAllPost();

	void deletePost(unsigned);

	//�������, ����� ������� HTML ���� � ������ ���������� �� �����������.
	void viewAllPosts();

	//�������, ����� �������� ���� ���������� �� ������ ID � ���������� �� �����������.
	bool isOwnPubl(unsigned);

	//�������, ����� ������� ������������ �� �����������.
	void printUserInfo();

private: 
	void resize();
};

#endif
