#include "forheader.h"
#include <string>
#include <iostream>



void eshop::NodeList::buy_thing(Thing* data)
{
}

void eshop::NodeList::print_out_a_bill(Thing* data)
{
	Node* iter = head;
	while (iter != nullptr) {

	}
}

void eshop::add_to_black_list()
{
}

void eshop::add_new_thing()
{

}

void startprog()
{
	char login[20];
	char password[20];
	char c;
	
	std::cout << "Enter 1 to sign in\n";
	std::cout << "Enter 2 to sign up\n";
	std::cin >> c;

	switch (c){
	case 1:
		while(true)
			std::cout << "Enter your login:        ";
			std::cin >> login;
			//check if login already used in database
		std::cout << '\n';
		std::cout << "Enter your password:     ";
		std::cin >> password;
	case 2:
		std::cout << "Enter your login:        ";
		std::cin >> login;
		std::cout << '\n';
		std::cout << "Enter your password:     ";
		std::cin >> password;
	}

	
	
}

eshop::NodeList::Node::Node(Thing* data)
{
	this->data = data;
}

eshop::User::User(char const* login, char const* password)
{
	strcpy_s(this->login,login);
	strcpy_s(this->password, password);
}
