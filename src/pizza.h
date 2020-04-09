
/* @author: Evren Çetinkaya
		ID: 150170118
	"PLEASE COMPILE WITH -std=c++11 !!!!"
	Comments are right side of the page
*/

#ifndef _pizza_
#define _pizza_
#include <iostream>

using namespace std;


class Pizza{
	char* name;										//Pizza name
	char* size;										//Pizza size
	string* ingredients;							//Ingredients of the pizza
	char* crust_type;								//Crust type of the pizza
	Pizza* next_pizza;								//Assigning the next pizza in the linked list;
	int ingredient_size;							//Size of the ingredient for ingredient array
	friend class Order;								//Order class can reach the Pizza class
	friend class OrderList;							//OrderList class can reach the Pizza class
public:
	Pizza();										//Default Pizza Constructor
	Pizza(char*, char*, int, string*);				//Created constructor for adding pizza according to given parameters
	Pizza(const Pizza*, string*,int);				//Copy constructor
	~Pizza();										//Pizza destructor
};

#endif