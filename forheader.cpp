#include "forheader.h"
#include <string>
#include <iostream>
#include <stdio.h>

std::ostream& operator<<(std::ostream& out, const eshop::Thing& c) {
	out << "Name: " << c.name<< "    ";
	out << "ID: " << c.id<<"    ";
	out << "Price:  " << c.price;
	out << '\n';
	return out;
}

void eshop::NodeList::add_to_order_thing(Thing* data)
{
	Node* node = new Node(data);
	Node* iter = head;
	if (head == nullptr) { head = node; tail = node; }
	else {
		while (true) {
			if (node->data->id == iter->data->id) {
				std::cout << "Thing with the same id and name is already in your order " << std::endl;
				return;
			}
			if (iter == tail) {
				break;
			}
			iter = iter->next;

		}
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
	std::cout << "Thing with name : " << node->data->name << " and id " << node->data->id<<" and price"<<node->data->price<<" is in your order" << std::endl;
}

void eshop::delete_thing(Thing* data)
{
}
void eshop::NodeList::print_out_a_bill(User* user)
{
	Node* iter = head;
	while (iter != nullptr) {

	}
}

void eshop::NodeList::print_out_an_order(User* user)
{
}

void eshop::NodeList::remove_from_order(int id,const char* name)
{
}

void eshop::add_to_black_list(int id)
{
	f_blackl = fopen("black_list.dat","r+b");
	f_users = fopen("users.dat","r+b");

	fclose(f_blackl);
}

void eshop::add_new_thing(Thing* thing)
{

}

void eshop::create_new_catagory(const char* category)
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
	char k;
	eshop::NodeList list = eshop::NodeList();
	char name_of_thing[20];
	int id;
	eshop::Thing* temp;

	std::cout << "Enter 1 to show categories of things\n";
	std::cout << "Enter 2 to show the full list of things\n";
	std::cout << "Enter 3 to add a thing to your order\n";
	std::cout << "Enter 4 to remove a thing from your order\n";
	std::cout << "Enter 5 to show your order\n";
	std::cout << "Enter 6 to print out a bill in a .txt file\n";
	std::cout << '\n';
	while (true) {
		std::cin >> k;
		switch (k) {
		case 1:
			show_all_categories();
			std::cout << "Something else?\n";
		case 2:
			show_all_things_available();
			std::cout << "Something else?\n";

		case 3:
			f_things = fopen("thigns.dat", "r+b");
			std::cout << "Name of the thing:   ";
			std::cin >> name_of_thing;
			std::cout << "Id of the thing:    ";
			std::cin >> id;
			if (!fseek(f_things, sizeof(eshop::Thing) * (id - 1), SEEK_SET)) {
				fread(temp, sizeof(eshop::Thing), 1, f_things);
				if (!strcmp(temp->name, name_of_thing)) {
					list.add_to_order_thing(temp);
					fclose(f_things);
					std::cout << "What else? \n";
					continue;
				}
			}
			std::cout << "There is not thing with such name or id in our shop\n";
			continue;
		case 4:
			std::cout << "Name of the thing:   ";
			std::cin >> name_of_thing;
			std::cout << "Id of the thing:    ";
			std::cin >> id;
			list.remove_from_order(id,name_of_thing);
			std::cout << "What else? \n";
			continue;
		case 5:
			list.print_out_an_order(user);
			std::cout << "What else? \n";
			continue;
		case 6:
			list.print_out_a_bill(user);
			std::cout << "What else? \n";
			continue;
		}


	}
	
	
}

void go_to_menu_admin()
{
}

void show_all_categories()
{
}

void show_all_things_available()
{
}

eshop::Thing::Thing(char const* name, int category, int price,int id)
{
	this->id = id;
	this->category = category;
	this->price = price;
	strcpy_s(this->name,name);
}
