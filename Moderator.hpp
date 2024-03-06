#ifndef __MODERATOR_HPP
#define __MODERATOR_HPP

#include"User.hpp"

class Moderator:public User {
	//Няма собствени член-данни.
public:
	//Голяма четворка.
	Moderator();
	Moderator(char*, unsigned, bool = false);
	Moderator(char*, unsigned, bool, Publication**, unsigned, unsigned);
	Moderator(const Moderator&) = delete;
	Moderator& operator=(const Moderator&) = delete;
	
};

#endif
