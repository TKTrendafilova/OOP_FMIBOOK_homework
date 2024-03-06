#pragma warning(disable:4996)
#include<iostream>
#include<cstring>
#include<typeinfo>
#include "EngineProgram.hpp"

const unsigned START_CAPACITY = 8;
const unsigned MAX_LEN = 50;
const unsigned MAX_CONTENT = 300;
const unsigned LEN_OF_WORD_POST = 4;
const unsigned LEN_EXTENSION = 5;

Engine::Engine()
	:m_users(nullptr), m_numberOfUser(0),m_capacityOfUsers(START_CAPACITY),
	m_publications(nullptr), m_numberOfPublication(0), m_capacityOfPublication(START_CAPACITY)
{
	//Заделяне на памет за списъкът с потребители.
	m_users = new(std::nothrow) User*[m_capacityOfUsers];
	if (m_users == nullptr) {
		std::cout << "Not enought memory for user in Engine(). Error!" << std::endl;
		return;
	}

	//Добавяне на администратор.
	m_users[0] = new (std::nothrow) Admin("Admin", 50);
	if (m_users[0] == nullptr) {
		std::cout << "Not enoght memory for admin." << std::endl;
		return;
	}
	++m_numberOfUser;


	//Заделяне на памет за всикчи публикаци на програмата.
	m_publications = new(std::nothrow) Publication*[m_capacityOfPublication];
	if (m_publications == nullptr) {
		std::cout << "Not enought momory for publications. Error!" << std::endl;
		return;
	}
}

Engine::~Engine()
{
	delete[]m_users;
	m_users = nullptr;
}

void Engine::printUser()
{
	for (int i = 0; i < m_numberOfUser; ++i) {
		std::cout << m_users[i]->getNickname() << ", " << m_users[i]->getAge()<<", "<<m_users[i]->getBlocked() << std::endl;
	}
}

unsigned Engine::getNumberOfUsers() const
{
	return m_numberOfUser;
}

void Engine::addUser(char* nickname, unsigned age)
{
	//Проверка дали вече не същестува потребител със същото име.
	if (isUniqueNickname(nickname) == false) {
		std::cout << "The nickname " << nickname << " is already in use. Please, try another nickname." << std::endl << std::endl;
		return;
	}

	if (m_numberOfUser >= m_capacityOfUsers) {
		resizeUserList();
	}
	m_users[m_numberOfUser] = new (std::nothrow) User(nickname, age);
	if (m_users[m_numberOfUser] == nullptr) {
		std::cout << "New user is not added. Error!" << std::endl;
		return;
	}
	++m_numberOfUser;
	std::cout <<std::endl<<"The user "<<nickname<<" has added." << std::endl << std::endl;
}

void Engine::addModerator(char *nickname, unsigned age)
{
	//Проверка дали вече не съществева потребител със същото име.
	if (isUniqueNickname(nickname) == false) {
		std::cout << "The nickname " << nickname << " is already in use. Please, try another nickname." << std::endl << std::endl;
		return;
	}
	
	if (m_numberOfUser >= m_capacityOfUsers) {
		resizeUserList();
	}

	m_users[m_numberOfUser] = new (std::nothrow) Moderator(nickname, age);
	if (m_users[m_numberOfUser] == nullptr) {
		std::cout << "New moderator is not added. Error!" << std::endl;
		return;
	}
	++m_numberOfUser;
	std::cout << std::endl<<"The moderator "<<nickname<<" has added."<< std::endl << std::endl;
}

void Engine::removeUser(char * name)
{
	int posOfTheUser = returnPositionOfUser(name);
	
	//Проверка дали е намерен кокретния потребител.
	if (posOfTheUser == -1) {
		std::cout << "The user " << name << " is not exist. Try again." << std::endl;
		return;
	}


	//Изтриване на всички публикации на потребителя.
	m_numberOfPublication -= m_users[posOfTheUser]->getNumberOfPublication();
	m_users[posOfTheUser]->deleteAllPost();

	//Изтриване на потребителя на позиция posOfTheUser.
	m_users[posOfTheUser] = m_users[m_numberOfUser - 1];
	--m_numberOfUser;
}

void Engine::block(char * nickname)
{
	int posOfTheUser = returnPositionOfUser(nickname);
	
	//Проверка дали е намерен кокретния потребител.
	if (posOfTheUser == -1) {
		std::cout << "The user " << nickname << " is not exist. Try again." << std::endl;
		return;
	}

	m_users[posOfTheUser]->setBlocked();

}

void Engine::unblock(char * nickname)
{
	int posOfTheUser = returnPositionOfUser(nickname);

	//Проверка дали е намерен кокретния потребител.
	if (posOfTheUser == -1) {
		std::cout << "The user " << nickname << " is not exist. Try again." << std::endl;
		return;
	}

	m_users[posOfTheUser]->setUnblocked();
}

void Engine::addImagePost(char*nameUser, char* content)
{
	int posOfTheUser= returnPositionOfUser(nameUser);
	//Проверка дали е намерен такъв потребител.
	if(posOfTheUser == -1) {
		std::cout << "The user " << nameUser << " is not exist. Try again." << std::endl;
		return;
	}
	
	Publication* post=new(std::nothrow) PicturePubl(content);
	if (post == nullptr) {
		std::cout << "Not enought mempry in addImagePost().Error!" << std::endl;
		return;
	}
	m_users[posOfTheUser]->addPublication(post);

	//Добавяне на публикацията към списъка с публикации на програмата.
	if (m_numberOfPublication >= m_capacityOfPublication) {
		resizePublicationList();
	}
	m_publications[m_numberOfPublication] = post;
	++m_numberOfPublication;
	
}

void Engine::addURLPost(char* nameUser, char*content, char* description)
{
	int posOfTheUser = returnPositionOfUser(nameUser);
	//Проверка дали е намерен такъв потребител.
	if (posOfTheUser == -1) {
		std::cout << "The user " << nameUser << " is not exist. Try again." << std::endl;
		return;
	}

	Publication* post = new(std::nothrow) URL(content,description);
	if (post == nullptr) {
		std::cout << "Not enought mempry in addURLPost().Error!" << std::endl;
		return;
	}
	m_users[posOfTheUser]->addPublication(post);

	//Добавяне на публикацията към списъка с публикации на програмата.
	if (m_numberOfPublication >= m_capacityOfPublication) {
		resizePublicationList();
	}
	m_publications[m_numberOfPublication] = post;
	++m_numberOfPublication;
}

void Engine::addTextPost(char* nameUser, char* content)
{
	int posOfTheUser = returnPositionOfUser(nameUser);
	//Проверка дали е намерен такъв потребител.
	if (posOfTheUser == -1) {
		std::cout << "The user " << nameUser << " is not exist. Try again." << std::endl;
		return;
	}

	Publication* textPubl=new (std::nothrow) Text(content);
	if (textPubl == nullptr) {
		std::cout << "Not enought memory in addTextPost().Error!" << std::endl;
		return;
	}
	m_users[posOfTheUser]->addPublication(textPubl);

	//Добавяне на публикацията към списъка с публикации на програмата.
	if (m_numberOfPublication >= m_capacityOfPublication) {
		resizePublicationList();
	}
	m_publications[m_numberOfPublication] = textPubl;
	++m_numberOfPublication;
}

void Engine::removePost(unsigned id)
{
	int posOfPubl = -1;

	//Намиране на позицията на публикацията с id.
	for (int i = 0; i < m_numberOfPublication; ++i) {
		if (m_publications[i]->getID() == id) {
			posOfPubl = i;
			break;
		}
	}

	//Проверка дали съществува такава публикация.
	if (posOfPubl == -1) {
		std::cout << "Piblication with ID= " << id << " is not exist. Try again." << std::endl;
		return;
	}

	m_publications[posOfPubl] = m_publications[m_numberOfPublication - 1];
	--m_numberOfPublication;

}

void Engine::viewPost(unsigned id)
{
	int posOfPubl = -1;

	//Намиране на позицията на публикацията с id.
	for (int i = 0; i < m_numberOfPublication; ++i) {
		if (m_publications[i]->getID() == id) {
			posOfPubl = i;
			break;
		}
	}

	//Проверка дали съществува такава публикация.
	if (posOfPubl == -1) {
		std::cout << "Piblication with ID= " << id << " is not exist. Try again." << std::endl;
		return;
	}

	//Създавене име на файла
	char buffer[MAX_CONTENT];
	int base = 10;
	char* idInName = itoa(id, buffer, base);

	unsigned lenOfFileName = LEN_OF_WORD_POST + strlen(idInName) + LEN_EXTENSION;

	char* fileName=new(std::nothrow) char[lenOfFileName+1];
	if (fileName == nullptr) {
		std::cout << "Not enought memory for file name in viewPost()" << std::endl;
		return;
	}
	strcpy(fileName, "post");
	strcat(fileName, idInName);
	strcat(fileName, ".html");

	//Създаване на HTML файл със съдържанието на публикацията с идентификационен номер id.
	m_publications[posOfPubl]->createHTML(fileName);
}

void Engine::viewAllPost(char* username)
{
	unsigned posOfUser = returnPositionOfUser(username);
	if (posOfUser == -1) {
		std::cout << "The user " << username << " is not exist." << std::endl << std::endl;
		return;
	}

	m_users[posOfUser]->viewAllPosts();

}

void Engine::info()
{
	numberOfUsers();
	numberOfModerators();
	findUser();
	blockedUsers();
	theYoungestUser();
	theOldestUser();
}

void Engine::quit()
{
	std::cout << "Exiting the program. " << std::endl;
}

void Engine::changeNickname(char * oldNickname, char* newNickname)
{
	if (isUniqueNickname(newNickname) == false) {
		std::cout<< "There is already a user with the name " << newNickname << ". " << std::endl;
		return;
	}

	unsigned posOfUser = returnPositionOfUser(oldNickname);
	if (posOfUser == -1) {
		std::cout << "The user " << oldNickname << " is not exist and you can not change your nickname." << std::endl;
		return;
	}
	
	m_users[posOfUser]->setNickname(newNickname);
	std::cout << std::endl << "The user " << oldNickname << " changed his/her nickname to " << newNickname << ". " << std::endl << std::endl;
	
}

void Engine::runProgram()
{
	char command[MAX_LEN];
	char actor[MAX_LEN];

	for (;;) {
		std::cout << "Actor: ";
		std::cin.getline(actor, MAX_LEN);

		std::cout << "Command: ";
		std::cin.getline(command, MAX_LEN);

		//Добавяне на нов потребител.
		if (strcmp(command, "add_user") ==0 ) {
			int pos = returnPositionOfUser(actor);
			if (pos == -1) {
				std::cout << actor << " is not exist in program." << std::endl;
				continue;
			}

			if (typeid(*m_users[pos]) == typeid(Admin)) {
				char nickname[MAX_LEN];
				unsigned age;

				std::cout << "nickname: ";
				std::cin.getline(nickname, MAX_LEN);

				std::cout << "Age: ";
				std::cin >> age;

				addUser(nickname, age);
			}
			else {
				std::cout << actor << " is not administrator." << std::endl<<std::endl;
			}
		}

		//Добавяне на нов модератор
		if (strcmp(command, "add_moderator") == 0) {
			int pos = returnPositionOfUser(actor);
			if (pos == -1) {
				std::cout << actor << " is not exist in program." << std::endl<<std::endl;
				continue;
			}

			if (typeid(*m_users[pos]) == typeid(Admin)) {
				char nickname[MAX_LEN];
				unsigned age;

				std::cout << "nickname: ";
				std::cin.getline(nickname, MAX_LEN);

				std::cout << "Age: ";
				std::cin >> age;

				addModerator(nickname, age);
				
			}
			else {
				std::cout << actor << " is not administrator." << std::endl<<std::endl;

			}
			
		}

		//Прeмахване на потребител
		if (strcmp(command, "remove_user") == 0) {
			int pos = returnPositionOfUser(actor);
			if (pos == -1) {
				std::cout << actor << " is not exist in program." << std::endl<<std::endl;
				continue;
			}

			if (typeid(*m_users[pos])== typeid(Admin)) {
				char name[MAX_LEN];
				std::cout << "Nickname: ";
				std::cin.getline(name, MAX_LEN);

				if (strcmp(name, "Admin") == 0) {
					std::cout << std::endl << "You can not remove administrator." << std::endl << std::endl;
					continue;
				}

				removeUser(name);
				std::cout << std::endl << actor << " remove user " << name << ". " << std::endl<<std::endl;
			}
			else{
				std::cout << actor << " is not administrator." << std::endl<<std::endl;

			}
			
		}

		//Блокиране на потребител
		if (strcmp(command, "block") == 0) {
			int pos = returnPositionOfUser(actor);
			if (pos == -1) {
				std::cout << actor << " is not exist in program." << std::endl<<std::endl;
				continue;
			}

			char name[MAX_LEN];
			std::cout << "Nickname: ";
			std::cin.getline(name, MAX_LEN);

			if (typeid(*m_users[pos]) == typeid(Admin) || typeid(*m_users[pos]) == typeid(Moderator)) {
				block(name);
			}
			else {
				std::cout << "You can not block " << name << ". " << std::endl << std::endl;

			}
			
		}

		//Разблокиране на потребител
		if(strcmp(command, "unblock")==0){
			int pos = returnPositionOfUser(actor);
			if (pos == -1) {
				std::cout << actor << " is not exist in program." << std::endl << std::endl;
				continue;
			}

			char name[MAX_LEN];
			std::cout << "Nickname: ";
			std::cin.getline(name, MAX_LEN);

			if (typeid(*m_users[pos]) == typeid(Admin) || typeid(*m_users[pos]) == typeid(Moderator)) {
				unblock(name);
			}
			else {
				std::cout << "You can not block " << name << ". " << std::endl<<std::endl;
			}
		}

		//Добавяне на публикация.
		if (strcmp(command, "post") == 0) {
			int pos = returnPositionOfUser(actor);
			if (pos == -1) {
				std::cout << actor << " is not exist in program." << std::endl<<std::endl;
				continue;
			}

			//Проверка дали потребителят, който иска да дабави публикация е блокиран.
			if (m_users[pos]->getBlocked() == true) {
				std::cout <<"Post not cteated. "<< actor << " is blocked."<<std::endl<<std::endl;
				continue;
			}

			char typePost[MAX_LEN];
			std::cout << "Type of piblication: ";
			std::cin.getline(typePost, MAX_LEN);

			if (strcmp(typePost, "image") == 0) {
				char content[MAX_CONTENT];
				std::cout << "Enter content: ";
				std::cin.getline(content,MAX_CONTENT);

				addImagePost(actor, content);
				std::cout << std::endl << actor << " add image post: " << content << std::endl<<std::endl;

			}
			if (strcmp(typePost, "url") == 0) {
				char urlAdress[MAX_CONTENT];
				char description[MAX_CONTENT];

				std::cout << "URL adress: ";
				std::cin.getline(urlAdress, MAX_CONTENT);

				std::cout << "Description: ";
				std::cin.getline(description, MAX_CONTENT);

				addURLPost(actor, urlAdress, description);
				std::cout << std::endl << actor << " add URL post: " << urlAdress << std::endl<<std::endl;
			}
			if (strcmp(typePost, "text") == 0) {
				char content[MAX_LEN];
				std::cout << "Enter text: ";
				std::cin.getline(content, MAX_CONTENT);

				addTextPost(actor, content);
				std::cout << std::endl << actor << " add post: " << content << std::endl<<std::endl;
			}
			else {
				std::cout << "Involid type of post. Try again" << std::endl<<std::endl;
			}

		}

		//Премахване на публикация
		if (strcmp(command, "remove_post") == 0) {
			int pos = returnPositionOfUser(actor);
			if (pos == -1) {
				std::cout << actor << " is not exist in program." << std::endl<<std::endl;
				continue;
			}
			unsigned id;
			std::cout << "ID of publication: ";
			std::cin >> id;

			// Ако actor е модератор или администратор.
			if (typeid(*m_users[pos]) == typeid(Moderator) || typeid(*m_users[pos])==typeid(Admin)) {
				int posOfOwnerWhichPublWillBeDeleted = -1;
				//Намиране на собственика на публикацията, коиято требва да се изтрие.
				for (int i = 0; i < m_numberOfUser; ++i) {
					if (m_users[i]->isOwnPubl(id) == true) {
						posOfOwnerWhichPublWillBeDeleted = i;
						break;
					}
				}
				//Проверка дали е намерен собственика на публикацията.
				if (posOfOwnerWhichPublWillBeDeleted == -1) {
					std::cout << std::endl << "Owner of post " << id << " is not exist. " << std::endl << std::endl;
					continue;
				}

				//Изтроване на публикацията от списъка с всички публикаци на потребителя.
				m_users[posOfOwnerWhichPublWillBeDeleted]->deletePost(id);

				
				//Изтриване на публикацията от списъка с публикации в програмата.
				removePost(id);
				std::cout << actor << " remove post " << id << ". " << std::endl<<std::endl;
			}

			//Ако actor е обикновен потребител.
			if (typeid(*m_users[pos]) == typeid(User)) {
				//Проверка дали публикацията, която иска да изтрие потребителя е негова.
				bool isUserPubl = m_users[pos]->isOwnPubl(id);
				if (isUserPubl == true) {
					//Изтроване на публикацията от списъка с всички публикаци на потребителя.
					m_users[pos]->deletePost(id);

					//Изтриване на публикацията от списъка с публикации в програмата.
					removePost(id);
					std::cout << actor << " remove post " << id << ". " << std::endl << std::endl;
				}
				else {
					std::cout << "Post " << id << " is not own." << std::endl<<std::endl;
				}
			}
		}

		//Преглеждане на публикация.
		if (strcmp(command, "view_post") == 0) {
			unsigned id;
			std::cout << "Enter ID of post: ";
			std::cin >> id;
			viewPost(id);
			//std::cout << "HTML view for post " << id << " created." << std::endl<<std::endl;
		}

		//Преглеждане на всички публикации на даден потребител.
		if (strcmp(command, "view_all_post") == 0) {
			char nickname[MAX_LEN];
			std::cout << "Nickname: ";
			std::cin.getline(nickname, MAX_LEN);

			viewAllPost(nickname);
		//	std::cout <<std::endl << "HTML view all " << nickname << "'s post created." << std::endl << std::endl;
		}

		//Промяна на името.
		if (strcmp(command, "change_nickname") == 0) {
			char newNickname[MAX_LEN];
			std::cout << "New nickname: ";
			std::cin.getline(newNickname, MAX_LEN);

			changeNickname(actor, newNickname);
		}

		//Извеждане на статистики.
		if (strcmp(command, "info") == 0) {
			info();
		}

		//Край на програмата.
		if (strcmp(command, "quit") == 0) {
			quit();
			break;
		}
	}
}

void Engine::resizeUserList()
{
	unsigned newCapacity = m_capacityOfUsers * 2;
	User** newUsers = new (std::nothrow) User* [newCapacity];

	if (newUsers == nullptr) {
		std::cout << "Not enought memory for resize! Error!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_capacityOfUsers; ++i) {
		newUsers[i] = m_users[i];
	}
	m_capacityOfUsers = newCapacity;
	delete[] m_users;
	m_users = newUsers;
}

void Engine::resizePublicationList()
{
	unsigned newCapacity = m_capacityOfPublication * 2;
	Publication** newPubl = new (std::nothrow) Publication*[newCapacity];

	if (newPubl == nullptr) {
		std::cout << "Not enought memory for resize! Error!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_capacityOfPublication; ++i) {
		newPubl[i] = m_publications[i];
	}
	m_capacityOfPublication = newCapacity;
	delete[] m_publications;
	m_publications = newPubl;
}

int Engine::returnPositionOfUser(char * name)
{
	int posOfTheUser = -1;
	for (int i = 0; i < m_numberOfUser; ++i) {
		if (strcmp(m_users[i]->getNickname(), name) == 0) {
			posOfTheUser = i;
		}
	}

	return posOfTheUser;
}

void Engine::numberOfUsers()
{
	unsigned count = 0;
	for (int i = 0; i < m_numberOfUser; ++i) {
		if (typeid(*m_users[i]) == typeid(User)) {
			++count;
		}
	}

	std::cout << "There are " << count << " users." << std::endl;
}

void Engine::numberOfModerators()
{
	unsigned count = 0;
	for (int i = 0; i < m_numberOfUser; ++i) {
		if (typeid(*m_users[i]) == typeid(Moderator)) {
			++count;
		}
	}

	std::cout << "There are " << count << " moderators." << std::endl;
}

void Engine::findUser()
{
	User* tempUser=m_users[0];

	for (int i = 0; i < m_numberOfUser; ++i) {
		if (tempUser->getNumberOfPublication() < m_users[i]->getNumberOfPublication()) {
			tempUser = m_users[i];
		}
	}

	tempUser->printUserInfo();
}

void Engine::blockedUsers()
{
	unsigned count = 0;
	
	//Проверка дали има блокирани потребители.
	for (int i = 0; i < m_numberOfUser; ++i) {
		if (m_users[i]->getBlocked() == true) {
			++count;
		}
	}

	if (count != 0) {
		//Ако има блокирани потребители, ги извеждаме.
		std::cout << "Blocked users are: " << std::endl;
		for (int i = 0; i < m_numberOfUser; ++i) {
			if (m_users[i]->getBlocked() == true) {
				m_users[i]->printUserInfo();
				++count;
			}
		}
	}
	else {
		std::cout << "There are no blocked users." << std::endl;
	}
	
}

void Engine::theYoungestUser()
{
	User* tempUser = m_users[0];

	for (int i = 0; i < m_numberOfUser; ++i) {
		if (tempUser->getAge() > m_users[i]->getAge()) {
			tempUser = m_users[i];
		}
	}

	std::cout << "The youngest user is: ";
	tempUser->printUserInfo();
}

void Engine::theOldestUser()
{
	User* tempUser=m_users[0];

	for (int i = 0; i < m_numberOfUser; ++i) {
		if (tempUser->getAge() < m_users[i]->getAge()) {
			tempUser = m_users[i];
		}
	}

	std::cout << "The oldest user is: ";
	tempUser->printUserInfo();
	std::cout<< std::endl;
}

bool Engine::isUniqueNickname(char * name)
{
	for (int i = 0; i < m_numberOfUser; ++i) {
		if (strcmp(name, m_users[i]->getNickname()) == 0) {
			return false;//Има потребител със същото име.
		}
	}
	return true;
}
