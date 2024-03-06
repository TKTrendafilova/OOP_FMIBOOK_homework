#pragma warning(disable:4996)
#include<iostream>
#include<cstring>
#include<fstream>
#include "EngineProgram.hpp"

void testPublications() {
	Publication p;
	p.createHTML("testFile.html");
	std::cout << "Publication p ID is " << p.getID() << std::endl;

	Text tP("My first test publication");
	tP.createHTML("testWhithoutPtr.html");
	std::cout << "Publication tP ID is " << tP.getID() << std::endl;

	PicturePubl pP("This PC/Pictures/5.jpeg");
	pP.createHTML("pic.html");
	std::cout << "Publication pP ID is " << pP.getID() << std::endl;

	URL UP("https://docs.google.com/document/d/1I3QZKCfwLKUxJ7tAoDmJhvkgbp25kaobI5Q5I1dXjBQ/edit", "Second OOP homework");
	UP.createHTML("myURL.html");
	std::cout << "Publication UP ID is " << UP.getID() << std::endl;
}


void testEngineFunction() {
	char name[20];
	unsigned age;
	std::cout << "Name: ";
	std::cin.getline(name, 20);

	std::cout << "Age: ";
	std::cin >> age;


	Engine engine;
	std::cout << "Number of users is " << engine.getNumberOfUsers() << std::endl;
	engine.printUser();
	engine.addUser(name, age);
	engine.addUser("User3", 23);
	engine.addModerator("Moderator1", 45);
	engine.addModerator("Moderator2", 37);
	engine.addUser("User4", 21);
	std::cout << std::endl << "Info: " << std::endl;
	engine.info();
	std::cout<< std::endl;

	std::cout << std::endl << "After adding user: " << std::endl;
	engine.printUser();
	std::cout << "Number of users is " << engine.getNumberOfUsers() << std::endl << std::endl;
	std::cout << std::endl << "Info: " << std::endl;
	engine.info();
	std::cout << std::endl;


	engine.removeUser("User3");
	engine.removeUser("Moderator1");
	engine.removeUser("User2");
	std::cout << std::endl << "After remove: " << std::endl;
	engine.printUser();
	std::cout << "Number of users is " << engine.getNumberOfUsers() << std::endl << std::endl;
	std::cout << std::endl << "Info: " << std::endl;
	engine.info();
	std::cout << std::endl;


	engine.block("Moderator2");
	engine.block("User4");
	engine.block("Moderator2");
	std::cout << std::endl << "After block users: " << std::endl;
	engine.printUser();
	std::cout << std::endl << "Info: " << std::endl;
	engine.info();
	std::cout << std::endl;

	engine.unblock("Moderator2");
	engine.unblock("User4");
	engine.unblock("user100");
	engine.unblock("User4");
	std::cout << std::endl << "After unblock users: " << std::endl;
	engine.printUser();
	std::cout << std::endl << "Info: " << std::endl;
	engine.info();
	std::cout << std::endl;
}

int main() {
	
//	testPublications();
//	testEngineFunction();
	
	Engine engine;
	engine.runProgram();

	return 0;
	
}