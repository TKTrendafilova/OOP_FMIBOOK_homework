#ifndef __ADMIN_HPP
#define __ADMIN_HPP

#include"Moderator.hpp"

class Admin : public Moderator {
	//���� ��������� ����-�����.

public:
	Admin();
	Admin(char*, unsigned, bool = false);
	Admin(char*, unsigned, bool, Publication**, unsigned, unsigned);
	Admin(const Admin&)=delete;//������ ��� ���� ���� �������������.
	Admin& operator=(const Admin&)=delete; //������ ��� ���� ���� �������������.
	
};

#endif
