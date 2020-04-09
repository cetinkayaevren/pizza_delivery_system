
/* @author: Evren Çetinkaya
		ID: 150170118
	"PLEASE COMPILE WITH -std=c++11 !!!!"
	Comments are right side of the page
*/

#include <iostream>
#include <cstring>

#include "orderlist.h"
#include "pizza.h"
#include "order.h"

#define MAX 20
#define MAX_ING 7

using namespace std;

Order::Order(char* cust_name, Pizza* my_pizza, int* my_drink,int our_drink_size){		//Order constructor with drinks
	next=NULL;																			//next is assigned as NULL
	drink_amount=our_drink_size;														//drink amount are assigned into the class
	drink=new string[MAX];																//Creating drink array dynamically
	customer= new char;																	//Creating customer dynamically
	strcpy(customer,cust_name);															//Assigned into the class variable
	string* drinks=new string[4]{"cola","soda","ice tea","fruit juice"};				//Default drinks are created dynamically

	my_pizza_head=my_pizza;																//Head of the pizza linked list is added into the order

	for(int i=0;i<drink_amount;i++){													//Drinks are assigned into the drink array
		drink[i]=drinks[my_drink[i]-1];
	}

	is_drink=true;																		//Boolean expression is becoming true
	delete[] drinks;																	//Dynamically created drinks are deleted for preventing leaking
}

Order::Order(char* cust_name, Pizza* my_pizza){											//Order constructor without drinks
	next=NULL;																			//next is assigned as NULL
	customer= new char;																	//Creating customer dynamically
	strcpy(customer,cust_name);															//Assigned into the class variable

	my_pizza_head=my_pizza;																//Head of the pizza linked list is added into the order

	is_drink=false;																		//Boolean expression is becoming false
}

Order::~Order(){																	//Order destructor (Deletes dynamically created variables into the Order class)
	Pizza* traverse;
	traverse=my_pizza_head;
	while(traverse!=NULL){															//Removing the pizza linked list in this order
		traverse=my_pizza_head;
		if(traverse->next_pizza==NULL){
			traverse->~Pizza();														//Pizza destructor is invoked for preventing leaking
			my_pizza_head=NULL;
			break;
		}
		my_pizza_head=my_pizza_head->next_pizza;
		traverse->~Pizza();															//Pizza destructor is invoked for preventing leaking	
	}																				
	delete customer;																//Deletes customer	
	delete[] drink;																	//Deletes the drink array
}

double Order::getPrice(){																//Calculates the Order price
	double total=0;																		//Started with zero
	if (my_pizza_head==NULL){															//If there is no list available into the linked list
		return 0.0;																		//return 0
	}
	else{
		if(strcmp(my_pizza_head->size,"small")==0){										//According the size of the pizza and amount, price is calculated
			total+=15*(amount);
		}
		else if(strcmp(my_pizza_head->size,"medium")==0){
			total+=20*(amount);
		}
		else if(strcmp(my_pizza_head->size,"big")==0){
			total+=25*(amount);
		}
		if(is_drink){																	//If the order has drinks, these drinks are calculated and added tot total according to type and amount
			for(int a=0;a<drink_amount;a++){
			}
			for(int i=0;i<drink_amount;i++){
				if(drink[i].compare("cola")==0){
					total+=4;
				}
				else if(drink[i].compare("soda")==0){
					total+=2;
				}
				else if(drink[i].compare("ice tea")==0){
					total+=3;
				}
				else if(drink[i].compare("fruit juice")==0){
					total+=3.5;
				}
			}
		}
	}
	return total;																		//Returns the total to the previous function
}

void Order::get_amount(int our_amount){													//Takes the amount from the OrdeList class
	amount=our_amount;																	//Assigned into the amount in the Order class
	return;
}

void Order::printOrder(){																//Prints the order comes from the client
	Pizza* traverse;																	//Traverse pointer is assigned for travel into the linked list
	traverse=my_pizza_head;																//Assigned with head of the pizza list, first
	int counter=0;
	cout<<"--------------------------------------------------"<<endl;
	cout<<"Name: "<<customer;															//Customer name
	cout<<endl<<endl;

	while(traverse!=NULL){
		cout<<traverse->name;															//Traverse takes the name into the lists
		cout<<"(";
		for(int k=0;k<traverse->ingredient_size;k++){									//Traverse takes the ingredients into the lists
			cout<<traverse->ingredients[k]<<", ";
		}
		cout<<")"<<endl;
		cout<<"size: "<<traverse->size <<", "<<"crust: "<<traverse->crust_type<<endl;	//Traverse takes the size and crust type of the pizzas
		cout<<endl;
		traverse=traverse->next_pizza;													//Traverse goes to the next pizza
	}

	bool my_count[drink_amount];														//Boolean expression is started with false
	for(int k=0;k<drink_amount;k++){
		my_count[k]=false;
	}
	
	for(int j=0;j<drink_amount;j++){													//Until the  amount of the taken drinks, count the same types and print to the output.
		for(int l=j;l<drink_amount;l++){
			if((drink[j].compare(drink[l])==0) && my_count[l]==false){					//If these are same and didn't count
				counter++;																
				my_count[l]=true;														//This element is counted, don't count again
			}
		}
		if(counter!=0){																	//If there is a drink more than 0
			cout<<counter<<" "<<drink[j]<<", ";											//Print them
			counter=0;
		}
	}
	cout<<endl;
	cout<<"--------------------------------------------------"<<endl;
	return;
}