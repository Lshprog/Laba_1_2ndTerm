#include "forheader.h"
#include <string>
#include <iostream>



void eshop::NodeList::add_to_order_thing(Thing* data)
{
}
void eshop::NodeList::delete_thing(Thing* data)
{
}
void eshop::NodeList::print_out_a_bill(Thing* data,User* user)
{
	Node* iter = head;
	while (iter != nullptr) {

	}
}

void eshop::NodeList::pring_out_an_order(Thing* data)
{
}

void eshop::add_to_black_list()
{
	f_blackl = fopen("black_list.dat","r+b");
	f_users = fopen("users.dat","r+b");

	fclose(f_blackl);
}

void eshop::add_new_thing()
{

}

void eshop::create_new_catagory()
{
}



void startprog()
{
	char login[20];
	char password[20];
	char c;
	bool incorrect_login = false;
	int temp_c;
	eshop::User* temp;

	f_users = fopen("users.dat", "r+b");
	
	std::cout << "Enter 1 to sign up\n";
	std::cout << "Enter 2 to sign in\n";
	std::cin >> c;
	fseek(f_users, -sizeof(eshop::User), SEEK_END);
	fread(temp, sizeof(eshop::User), 1, f_users);
	temp_c = temp->id;

	switch (c) {
	case 1:
		while (true) {
			std::cout << "Enter your login:        ";
			std::cin >> login;

			for (int i = 1; i < temp_c; i++) {
				fseek(f_users, sizeof(eshop::User) * i, SEEK_SET);
				fread(temp, sizeof(eshop::User), 1, f_users);
				if (!strcmp(temp->login, login)) {
					incorrect_login = true;
					break;
				}
			}
			if (!incorrect_login) {
				break;
			}
			else
				continue;
		}

		std::cout << '\n';
		std::cout << "Create your password:     ";
		std::cin >> password;
		eshop::User newuser = { login,password };
		fseek(f_users, 0, SEEK_END);
		fwrite(&newuser, sizeof(eshop::User), 1, f_users);
		fclose(f_users);
		go_to_menu(&newuser);
	case 2:
		while (true) {
			std::cout << "Enter your login:        ";
			std::cin >> login;
			std::cout << '\n';
			std::cout << "Enter your password:     ";
			std::cin >> password;

			for (int i = 1; i < temp_c; i++) {
				fseek(f_users, sizeof(eshop::User) * i, SEEK_SET);
				fread(temp, sizeof(eshop::User), 1, f_users);
				if (!strcmp(temp->login, login)) {
					if (!strcmp(temp->password, password)) {
						std::cout << "Welcome\n";
						if (temp->admin)
							go_to_menu_admin();
						else
							go_to_menu(temp);
						return;
					}
					else {
						std::cout << "Incorrect login or password\n";
						break;
					}
				}
				else {
					std::cout << "Incorrect login or password\n";
					break;
				}
			}
		}
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
void go_to_menu(eshop::User* user) {
	std::cout << "Enter 1 to show categories of things\n";
	std::cout << "Enter 2 to show the full list of things\n";
	std::cout << "Enter 3 to add a thing to your order\n";
	std::cout << "Enter 4 to show your order\n";
	std::cout << "Enter 5 to print out a bill in a .txt file\n";
	
}

void go_to_menu_admin()
{
}
