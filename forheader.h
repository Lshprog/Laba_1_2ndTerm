#pragma once
namespace eshop {
	struct User {
		bool admin;
		bool blacklist;
		int money_balance=0;
		char login[20];
		char password[20];
		int id;
		User(char const* login,char const* password);

	};

	struct Thing {
		int price;
		int category;
		char name[20];
		int id;
		Thing(char const* name,int category,int price,int id);
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
		void add_to_order_thing(Thing* data);
		void print_out_a_bill(User*);
		void print_out_an_order(User*);
		void remove_from_order(int,const char*);
	};
	void delete_thing(Thing*);
	void add_new_thing(Thing*);
	void add_to_black_list(int);
	void create_new_catagory(const char*);
}
void startprog();
void go_to_menu(eshop::User*);
void go_to_menu_admin(eshop::User*);
void show_all_categories();
void show_all_things_available();
FILE* f_category;
FILE* f_things;
FILE* f_users;
FILE* f_blackl;