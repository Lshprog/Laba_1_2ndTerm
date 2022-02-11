#include "forheader.h"
#include <string>
#include <iostream>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
FILE* f_category;
FILE* f_things;
FILE* f_users;
FILE* f_blackl;

const char filecategory[]= "dats\\category.dat";
const char filethings[] = "dats\\things.dat";
const char fileusers[] = "dats\\users.dat";
const char fileblackl[] = "dats\\blackl.dat"; 

std::ostream& operator<<(std::ostream& out, const eshop::Thing& c) {
	out << "Name: " << c.name<< "    ";
	out << "ID: " << c.id<<"    ";
	out << "Price:  " << c.price<<"  ";
	out << "Category: " << c.category.name;
	out << '\n';
	return out;
}

void eshop::NodeList::add_to_order_thing(int id, char const* name)
{	
	char tempname[] = "";
	Category* category = new Category();
	Thing* temp =new Thing(tempname,category,0,0,true);
	int temp_size = sizeof(eshop::Thing);
	f_things = fopen(filethings, "rb+");
	if (!fseek(f_things, temp_size * id, SEEK_SET)) {
		fseek(f_things, temp_size *(id-1),SEEK_SET);
		fread(temp, temp_size, 1, f_things);
		fclose(f_things);
		if ((temp->id == id)&&(!strcmp(temp->name,name))) {
			if (temp->available) {
				Node* node = new Node(temp);
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
				
				std::cout << "Thing with name : " << node->data->name << " and id " << node->data->id << " and price " << node->data->price << " is in your order" << std::endl;
				return;
			}
		}
	}
	std::cout << "There is no such thing in our shop\n";
	fclose(f_things);
	

}


void eshop::NodeList::print_out_a_bill(User* user)
{
	Node* iter = head;
	while (iter != nullptr) {

	}
}

void eshop::NodeList::print_out_an_order(User* user)
{
	if ((tail == nullptr) && (head == nullptr)) {
		std::cout << "Your order is empty" << std::endl;
		return;
	}
	Node* iter = head;
	while (true) {

		std::cout << *(iter->data);

		if (iter == tail)
			break;
		iter = iter->next;
	}
}

void eshop::NodeList::remove_from_order(int id,const char* name)
{
	Node* node = head;
	Node* iter;
	while (node != nullptr) {

		if (node->data->id==id) {
			std::cout << "Thing with name : " << node->data->name << " and id " << node->data->id << " and price" << node->data->price << " was removed from your order" << std::endl;
			if (head == tail) {
				head = nullptr;
				tail = nullptr;
							
			}
			else if (node == head) {
				(node->next)->prev = nullptr;
				head = node->next;
								
			}
			else if (node == tail) {
				(node->prev)->next = nullptr;
				tail = node->prev;

			}
			else {
							
				(node->prev)->next = node->next;
				(node->next)->prev = node->prev;

			}

			delete node;
			return;
		}
		if (node == tail) {
			std::cout << "Thing with name : " << node->data->name << " and id " << node->data->id << " and price" << node->data->price << " is not in your order" << std::endl;
			return;
		}
		node = node->next;
	}
}

void eshop::add_to_black_list(int id)
{
	char templogin[]="";
	char temppass[]="";
	int temp_size_new = sizeof(User);
	eshop::User bluser = eshop::User(templogin, temppass, 0, false, 0, false);
	f_blackl=fopen(fileblackl,"r+b");
	f_users=fopen(fileusers, "r+b");
	if (!fseek(f_users, temp_size_new * id, SEEK_SET)) {
		fseek(f_users, temp_size_new *(id-1),SEEK_SET);
		fread(&bluser, temp_size_new, 1, f_users);
		if (!bluser.blacklist) {
			bluser.blacklist = true;
			fseek(f_users,temp_size_new*(id-1),SEEK_SET);
			fwrite(&bluser,temp_size_new,1,f_users);
			fseek(f_blackl,0,SEEK_END);
			fwrite(&bluser, temp_size_new,1,f_blackl);
		}
	}
	

	fclose(f_blackl);
	fclose(f_users);
}

void eshop::delete_thing(int id, const char* name)
{
	char tempname[] = "";
	Category* category = new Category();
	Thing temp = Thing(tempname,category,0, 0, true);
	f_things= fopen(filethings,"r+b");
	if (!fseek(f_things, sizeof(Thing) * id, SEEK_SET)) {
		fseek(f_things, sizeof(Thing)*(id-1), SEEK_SET);
		fread(&temp, sizeof(Thing), 1, f_things);
		if (!strcmp(temp.name, name)) {
			if (temp.available) {
				temp.available = false;
				long int temp_size = sizeof(Thing);
				fseek(f_things, -temp_size, SEEK_CUR);
				fwrite(&temp,sizeof(Thing),1,f_things);
				fclose(f_things);
				return;
			}
		}
	}
	std::cout << "Error \n";
	fclose(f_things);
	
}
eshop::Category eshop::check_category(char const* category) {
	char temp_category[20] = "";
	eshop::Category struct_category = eshop::Category();
	int temp_size = sizeof(eshop::Category);
	int temp_id=0;
	f_category = fopen(filecategory, "r+b");
	fseek(f_category, -temp_size, SEEK_END);
	fread(&struct_category, temp_size, 1, f_category);
	temp_id = struct_category.id;
	fseek(f_category, 0, SEEK_SET);
	for (int i = 0; i < temp_id; i++) {
		fread(&struct_category, temp_size, 1, f_category);
		if (!strcmp(struct_category.name, category)) {
			fclose(f_category);
			return struct_category;
		}
	}
	struct_category.id = temp_id + 1;
	strcpy_s(struct_category.name, category);
	fseek(f_category, 0, SEEK_END);
	fwrite(&struct_category, temp_size, 1, f_category);
	fclose(f_category);
	return struct_category;
}
	

void eshop::add_new_thing(int price, const char* name,const char* temp_category)
{
	int temp_size = sizeof(Thing);
	int temp_last_id;
	char tempname[] = "";
	Category *category=new Category;
	Thing temp = Thing(tempname, category, 0, 0, true);

	f_things = fopen(filethings, "r+b");
	if (feof(f_things)) {
		*category = eshop::check_category(temp_category);
		temp = Thing(name, category, price, 1, true);
		fwrite(&temp, sizeof(Thing), 1, f_things);
		std::cout << "This thing is now available in our shop \n";
		std::cout << *(&temp);
		fclose(f_things);
		
		return;
	}

	fseek(f_things, -temp_size, SEEK_END);
	fread(&temp, sizeof(Thing), 1, f_things);
	temp_last_id = temp.id;
	for (int i = 0; i < temp_last_id; i++) {
		fseek(f_things, temp_size * i, SEEK_SET);
		fread(&temp, temp_size, 1, f_things);
		if (!strcmp(temp.name, name) && (temp.price == price)&&(!strcmp(temp.category.name,temp_category))) {
			if (temp.available) {
				std::cout << "Such thing is already in the list!!! \n";
				fclose(f_things);
				return;
			}
			else if (!temp.available) {
				temp.available = true;
				fseek(f_things, temp_size * (temp.id - 1), SEEK_SET);
				fwrite(&temp, temp_size, 1, f_things);
				fclose(f_things);
				std::cout << "This thing is now available in our shop \n";
				return;

			}
		}
	}
	fseek(f_things, 0, SEEK_END);
	*category = check_category(temp_category);
	temp = Thing(name,category,price,temp_last_id+1,true);
	fwrite(&temp, sizeof(Thing), 1, f_things);
	std::cout << "This thing is now available in our shop \n";
	std::cout << *(&temp);
	fclose(f_things);
	

}




void eshop::create_new_catagory(const char* category)
{
	char temp_category[20] = "";
	eshop::Category struct_category = eshop::Category();

	int temp_size = sizeof(eshop::Category);
	int temp_id;
	f_category = fopen(filecategory, "r+b");
	fseek(f_category,-temp_size,SEEK_END);
	fread(&struct_category,temp_size,1,f_category);
	temp_id = struct_category.id;
	fseek(f_category,0,SEEK_SET);
	for (int i = 0; i < temp_id; i++) {
		fread(&struct_category, temp_size, 1, f_category);
		if (!strcmp(struct_category.name, category)) {
			std::cout << "Such category already exist \n";
			fclose(f_category);
			return;
		}
	}
	struct_category.id = temp_id + 1;
	strcpy_s(struct_category.name,category);
	fseek(f_category, 0, SEEK_END);
	fwrite(&struct_category, temp_size, 1, f_category);
	std::cout <<"Category: "<<category<<" is now available in our shop \n";
	fclose(f_category);
	
}






void startprog()
{
	char login[20];
	char password[20];
	char c[2];
	bool incorrect_login = false;
	int temp_c;
	char templogin[]="";
	char temppass[]="";
	
	
	eshop::User temp=eshop::User(templogin,temppass,0,false,0,false);
	
	f_users=fopen(fileusers, "r+b");
		
	int temp_size = sizeof(temp);
	fseek(f_users, -temp_size, SEEK_END);
	fread(&temp, temp_size, 1, f_users);
	temp_c = temp.id;
	std::cout << "Enter 1 to sign up\n";
	std::cout << "Enter 2 to sign in\n";
	std::cin >> c;

	if(c[0]=='1'){
		while (true) {
			std::cout << "Enter your login:        ";
			std::cin >> login;

			for (int i = 0; i <= temp_c; i++) {
				fread(&temp, temp_size, 1, f_users);
				if (!strcmp(temp.login, login)) {
					incorrect_login = true;
					break;
				}
			}
			if (!incorrect_login) {
				break;
			}
			else {
				incorrect_login = false;
				continue;
				
			}
		}

		std::cout << '\n';
		std::cout << "Create your password:     ";
		std::cin >> password;
		eshop::User newuser = eshop::User(login,password,temp_c + 1,true,2000,false);
		fseek(f_users, 0, SEEK_END);
		fwrite(&newuser, sizeof(eshop::User), 1, f_users);
		fclose(f_users);	
		go_to_menu(&newuser);
		
	
	}
	else if(c[0]=='2')
	{
		while (true) {
			std::cout << "Enter your login:        ";
			std::cin >> login;
			std::cout << '\n';
			std::cout << "Enter your password:     ";
			std::cin >> password;

			for (int i = 0; i <= temp_c; i++) {
				fread(&temp, temp_size, 1, f_users);
				if (!strcmp(temp.login, login)) {
					if (!strcmp(temp.password, password)) {
						std::cout << "Welcome\n";
						if (!temp.blacklist) {
							if (temp.admin)
								go_to_menu_admin(&temp);
							else
								go_to_menu(&temp);
							return;
						}
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

eshop::User::User(char const* login, char const* password,int id,bool admin,int money_balance,bool blackl)
{
	this->blacklist = blackl;
	this->money_balance = money_balance;
	this->admin = admin;
	this->id = id;
	strcpy_s(this->login,login);
	strcpy_s(this->password, password);
}
void go_to_menu(eshop::User* user) {
	int k;
	eshop::NodeList list = eshop::NodeList();
	char name_of_thing[20];
	int id;

	std::cout << "Enter 1 to show categories of things\n";
	std::cout << "Enter 2 to show the full list of things\n";
	std::cout << "Enter 3 to add a thing to your order\n";
	std::cout << "Enter 4 to remove a thing from your order\n";
	std::cout << "Enter 5 to show your order\n";
	std::cout << "Enter 6 to print out a bill in a .txt file\n";
	std::cout << '\n';
	while (true) {
		std::cin >> k;
		if (k == 1) {
			show_all_categories();
			std::cout << "Something else?\n";
		}
		else if (k == 2) {

			show_all_things_available();
			std::cout << "Something else?\n";
		}

		else if (k == 3) {
			std::cout << "Name of the thing:   ";
			std::cin >> name_of_thing;
			std::cout << "Id of the thing:    ";
			std::cin >> id;
			list.add_to_order_thing(id, name_of_thing);
			std::cout << "What else? \n";
			continue;
		}
		else if (k == 4) {
			std::cout << "Name of the thing:   ";
			std::cin >> name_of_thing;
			std::cout << "Id of the thing:    ";
			std::cin >> id;
			list.remove_from_order(id, name_of_thing);
			std::cout << "What else? \n";
			continue;
	}
		else if (k == 5) {
			list.print_out_an_order(user);
			std::cout << "What else? \n";
			continue;
		}
		else if (k == 6) {
			list.print_out_a_bill(user);
			std::cout << "What else? \n";
			continue;
		}
		}

	
}

void go_to_menu_admin(eshop::User* user)
{
	char temp_category[20];
	int k;
	
	char name_of_thing[20];
	int id;
	int temp_price;
	

	std::cout << "Enter 1 to show categories of things\n";
	std::cout << "Enter 2 to show the full list of things\n";
	std::cout << "Enter 3 to add a thing to the list of available things\n";
	std::cout << "Enter 4 to remove a thing from your list of available things\n";
	std::cout << "Enter 5 to add user to a blacklist\n";
	std::cout << "Enter 6 to create new category\n";
	std::cout << '\n';
	while (true) {
		std::cin >> k;
		if (k == 1) {
			show_all_categories();
			std::cout << "Something else?\n";
		}
		else if (k == 2) {
			show_all_things_available();
			std::cout << "Something else?\n";
		}

		else if (k == 3) {
			std::cout << "Name of the thing:   ";
			std::cin >> name_of_thing;
			std::cout << "Price of the thing:    ";
			std::cin >> temp_price;
			std::cout << "Category of the thing:    ";
			std::cin >> temp_category;
			eshop::add_new_thing(temp_price, name_of_thing, temp_category);
			std::cout << "What else? \n";
			continue;
		}
		else if (k == 4) {
			std::cout << "Name of the thing:   ";
			std::cin >> name_of_thing;
			std::cout << "Id of the thing:    ";
			std::cin >> id;
			eshop::delete_thing(id, name_of_thing);
			std::cout << "What else? \n";
			continue;
		}
		else if (k == 5) {
			std::cout << "Id of the user:    ";
			std::cin >> id;
			eshop::add_to_black_list(id);
			std::cout << "What else? \n";
			continue;
		}
		else if (k==6){
			std::cout << "Category of the thing:    ";
			std::cin >> temp_category;
			eshop::create_new_catagory(temp_category);
			std::cout << "What else? \n";
			continue;
		}
	}
}

void show_all_categories()
{
	char temp_category[20] = "";
	eshop::Category struct_category = eshop::Category();
	int temp_size = sizeof(eshop::Category);
	int temp_id;
	f_category = fopen(filecategory, "r+b");
	if (feof(f_category)) {
		std::cout << "No categories avialable \n";
		fclose(f_category);
		return;
	}
	fseek(f_category, -temp_size, SEEK_END);
	fread(&struct_category, temp_size, 1, f_category);
	temp_id = struct_category.id;
	fseek(f_category, 0, SEEK_SET);
	for (int i = 0; i<temp_id; i++) {
		fread(&struct_category,temp_size,1,f_category);
		std::cout << "Category: " << struct_category.name << "  Id: " << struct_category.id << '\n';
	}
	fclose(f_category);

}

void show_all_things_available()
{
	char tempch[]="";
	eshop::Category* temps =new eshop::Category;
	eshop::Thing temp = eshop::Thing(tempch,temps , 0, 0, false);
	f_things=fopen(filethings,"r+b");
	int temp_size = sizeof(eshop::Thing);
	if (feof(f_things)) {
		std::cout << "No things avialable \n";
		fclose(f_things);
		return;
	}
	fseek(f_things,-temp_size,SEEK_END);
	fread(&temp,temp_size,1,f_things);
	int temp_id= temp.id;
	fseek(f_things,0,SEEK_SET);
	for (int i = 0; i<temp_id; i++) {

		fread(&temp, temp_size, 1, f_things);
		if(temp.available)
			std::cout << *(&temp);
	}
	fclose(f_things);
	
}

eshop::Thing::Thing(char const* name,Category* category, int price,int id,bool available)
{
	
	this->id = id;
	this->price = price;
	this->available = available;
	strcpy_s(this->name,name);
}

