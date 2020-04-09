
/* @author: Evren Çetinkaya
		ID: 150170118
	"PLEASE COMPILE WITH -std=c++11 !!!!"
	Comments are right side of the page
*/

#ifndef _order_
#define _order_

#include <iostream>
#include "pizza.h"

using namespace std;

class Order{										//Order Class
	char* customer;									//Customer name
	Pizza* my_pizza_head;							//Pizzas are listed into linked list, this parameter keeps the head of the pizza list
	string* drink;									//Drinks are stored by dynamic array
	Order* next;									//Orders are kept into linked list, this next pointer keeps the next order
	int amount;										//Amount of the pizza into the pizza list
	int drink_amount;								//Amount of the drink into the drink array

public:
	Order(char*,Pizza*,int*,int);					//Order constructor with drinks.
	Order(char*,Pizza*);							//Order constructor without drinks.
	bool is_drink= false;							//Boolean expression whether drink is available or not
	~Order();										//Order destructor
	double getPrice();								//Returns the price of the order
	void printOrder();								//Prints the order as customer name, ordered pizzas and drinks
	void get_amount(int);							//Takes amount of the pizza, and assigned into amount where the Order class
	friend class OrderList;							//OrderList class can reach the Order class

};

#endif