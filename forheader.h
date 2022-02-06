#pragma once
namespace eshop {
	struct User {
		bool blacklist;
		int money_balance=0;
		int id;
		char login[20];
		char password[20];
		User(char const* login,char const* password);

	};

	struct Thing {
		int price;
		int id;
		int category;
		char name[20];
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
		void buy_thing(Thing* data);
		void print_out_a_bill(Thing* data);
		void pring_out_an_order(Thing* data);
	};
	void add_to_black_list();
	void add_new_thing();
	void create_new_catagory();
}
void startprog();
FILE* f_category;
FILE* f_things;
FILE* f_users;