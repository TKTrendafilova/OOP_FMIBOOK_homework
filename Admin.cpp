#include "Admin.hpp"

Admin::Admin():Moderator()
{
}

Admin::Admin(char * name, unsigned age, bool isBlocked):Moderator(name, age,isBlocked)
{
}

Admin::Admin(char *nickname, unsigned age, bool isBlocked, Publication ** publ, unsigned count, unsigned capacity)
	:Moderator(nickname, age, isBlocked, publ,count,capacity)
{
}
