
/* @author: Evren Çetinkaya
		ID: 150170118
	"PLEASE COMPILE WITH -std=c++11 !!!!"
	Comments are right side of the page
*/

#ifndef _orderlist_
#define _orderlist_

#include <iostream>
#include "order.h"
#include "pizza.h"

using namespace std;


class OrderList{									//OrderList Class
	static int n;									//Number of orders are taken as static.
	Order* head;									//Head pointer for orders which are kept into the linked list
	int my_amount;									//Amount of the orders.
public:
	OrderList();									//Default Constructor
	void takeOrder();								//Takes the order from client
	string* take_ingredient(int);					//Returns the ingredient of the pizza chosen by client
	int print_ingredient(int);						//Prints the ingredient of the pizza chosen by client
	int print_menu();								//Prints the pizza menu
	void listOrders();								//Lists all the orders
	void deliverOrders();							//Deliver the required order and removes from linked list;
	void add_order(Order*);							//Adding the Orders in the linked list
	void remove(char*);								//Removes object into the linked list
	~OrderList();									//OrderList destructor;
};


#endif