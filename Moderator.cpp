#include<iostream>
#include"Moderator.hpp"

Moderator::Moderator()
	:User()
{
}

Moderator::Moderator(char * name, unsigned age, bool isBlocked)
	:User(name, age,isBlocked)
{
}

Moderator::Moderator(char * name, unsigned age, bool isBlocked, Publication ** publications, unsigned count, unsigned capacity)
	:User(name, age,isBlocked, publications, count,capacity)
{
}
