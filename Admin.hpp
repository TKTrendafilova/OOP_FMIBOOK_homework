#ifndef __ADMIN_HPP
#define __ADMIN_HPP

#include"Moderator.hpp"

class Admin : public Moderator {
	//Няма собствени член-данни.

public:
	Admin();
	Admin(char*, unsigned, bool = false);
	Admin(char*, unsigned, bool, Publication**, unsigned, unsigned);
	Admin(const Admin&)=delete;//Защото има само едни администратор.
	Admin& operator=(const Admin&)=delete; //Защото има само едни администратор.
	
};

#endif
