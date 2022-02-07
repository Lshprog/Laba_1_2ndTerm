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
		void print_out_a_bill(Thing* data,User*);
		void pring_out_an_order(Thing* data);
		void delete_thing(Thing* data);
	};
	void add_to_black_list();
	void add_new_thing();
	void create_new_catagory();
}
void startprog();
void go_to_menu(eshop::User*);
void go_to_menu_admin();
FILE* f_category;
FILE* f_things;
FILE* f_users;
FILE* f_blackl;