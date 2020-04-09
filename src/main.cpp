
/* @author: Evren Çetinkaya
		ID: 150170118
	"PLEASE COMPILE WITH -std=c++11 !!!!"
	Comments are right side of the page
*/
#include <iostream>
#include <cstring>

#include "pizza.h"
#include "order.h"
#include "orderlist.h"


#define MAX 20
#define MAX_ING 7

using namespace std;



int main(){

	OrderList* my_order=new OrderList;														//New OrderList is created dynamically
	int choice;
	do{
		choice=my_order->print_menu();																//Prints the menu
		switch(choice){
			case 1:	
				my_order->takeOrder();														//If choice is 1, takeOrder function is invoked pointed by my_order
				break;

			case 2:
				my_order->listOrders();														//If choice is 2, listOrders function is invoked pointed by my_order
				break;
			case 3:
				my_order->deliverOrders();													//If choice is 3, deliverOrders function is invoked pointed by my_order
				break;

			default:																		//If nothing except 4, ask again
				break;
		}
	}while(choice!=4);																		//If choice is 4, exit the program
	cout<<"Goodbye..."<<endl;
	delete my_order;																		//Deletes my_order created dynamically
	return 0;
}


