#pragma once
#define _CRT_SECURE_NO_WARNINGS

namespace eshop {
	struct User {
		bool blacklist;
		bool admin;
		int money_balance;
		char login[20];
		char password[20];
		int id;
		User(char const* login,char const* password,int id,bool admin,int money_balance,bool blacklist);

	};

	struct Category {
		int id;
		char name[20];
		Category(int id,const char* name);
	};

	struct Thing {
		int price;
		Category category;
		char name[20];
		int id;
		bool available;
		Thing(char const* name,Category* category,int price,int id,bool available);
	};
	struct NodeList {
	private:
		struct Node{
			Thing* data;
			Node* next;
			Node* prev;
			Node(Thing* data);
		};
		Node* head = nullptr;
		Node* tail = nullptr;
	public:
		void add_to_order_thing(int,char const*);
		void print_out_a_bill(User*);
		void print_out_an_order(User*);
		void remove_from_order(int,const char*);
	};
	void delete_thing(int,char const*);
	void add_new_thing(int price,const char* name,const char* category);
	void add_to_black_list(int);
	void create_new_catagory(const char*);
	Category check_category(const char*);
}
void startprog();
void go_to_menu(eshop::User*);
void go_to_menu_admin(eshop::User*);
void show_all_categories();
void show_all_things_available();
