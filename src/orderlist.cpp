
/* @author: Evren Çetinkaya
		ID: 150170118
	"PLEASE COMPILE WITH -std=c++11 !!!!"
	Comments are right side of the page
*/

#include <iostream>
#include <cstring>

#include "orderlist.h"
#include "order.h"
#include "pizza.h"

using namespace std;

#define MAX 20
#define MAX_ING 7

int OrderList::n;

OrderList::OrderList(){							//Constructor Function
	head=NULL;									//Head is assigned as NULL
	n=0;										//Number of orders are started with zero 
}

OrderList::~OrderList(){						//OrderList destructor
	delete head;								//Deletes head after all of the dynamic expressions are deleted.
}

void OrderList::add_order(Order* my_order){					//Adding the order into the linked list, takes the order adress 
	if(head==NULL){											//If the OrderLsist has no any order, the first order is added
		head=my_order;										//Head is assigned
		head->next=NULL;
		n++;												//Number of the orders is increased
	}
	else{													//If the OrderList has the orders 
		Order* traverse;
		traverse=head;
		while(traverse->next!=NULL){						//Travelling and trying to find NULL pointer for adding the order
			traverse=traverse->next;
		}
		traverse->next=my_order;							//New order is addded into the linked list
		n++;												//Number of the orders is increased
	}
	return;
}

void OrderList::remove(char* my_name){						//Removing the order from the linked list
	char answer;
	double total;
	string my_code;
	Order* traverse;										//Traverse pointer is created
	Order* previous;										//Previous pointer is created for travel with traverse pointer one step back
	traverse=head;											//Traverse and previous assigned with head pointer first
	previous=traverse;
	if(head==NULL){													//If the Orderlist has no order
		cout<<"There is no order for delivering"<<endl<<endl;					
	}
	else{															//If the Orderlist has order
		while(true){												//For finding the true order, traverse and previous 
			if(strcmp(traverse->customer,my_name)==0){				//Make traversing
				break;
			}
			else{
				if(traverse->next==NULL){							//If the name cannot be found
					cout<<"Wrong name"<<endl;
					return;
				}
				else{												//If there is a order, continue to traverse
					if(traverse==head){
						traverse=traverse->next;
					}
					else{
						traverse=traverse->next;
						previous=previous->next;
					}
				}
			}
		}
	
	traverse->printOrder();											//After finding the required order, print order function is invoked
	total=traverse->getPrice();										//Then getPrice function is invoked and total is keeps the total price
		cout<<"Total price: "<<total<<endl;
	do{																//Promotion code is asked for making discount
		cout<<"Do you have a promotion code? (y/n)"<<endl;
		cin>>answer;

		if(answer=='y' || answer== 'Y'){							//If answer is 'yes', waiting for the entering code
			cout<<"Please enter your code: ";
			getchar();
			getline(cin,my_code);
			if(my_code.compare("I am a student")==0){				//If code is true, %10 discount operation is applying
				cout<<"Discounted price: "<< (90*total)/100<<endl;
				break;
			}
			else{													//If not, continue to ask same question until the answer is 'no'
				continue;
			}
		}
	}while(answer!='n' && answer !='N');

	cout<<"The order is delivered successfully!"<<endl;				//Order delivered message and removing operation is starting
	cout<<endl;	

	if(traverse==head){												//If the order is first element of the linked list
		if(traverse->next==NULL){									//If the element number is 1
			traverse->~Order();										//Order Destructor
			head=NULL;
			}
		else{														//If the element number is more than 1
			head=head->next;
			traverse->~Order();										//Order Destructor
		}
	}
	else if(traverse!= head && traverse->next !=NULL){				//If the order is among into the linked list
		previous->next=traverse->next;
		traverse->next=	NULL;
		traverse->~Order();											//Order Destructor
	}
	else if(traverse!=head && traverse->next==NULL){				// If this order is the last item of the linked list..
		previous->next=NULL;
		traverse->~Order();											//Order Destructor
		}
	}
	return;
}

void OrderList::deliverOrders(){													//Deliver order menu for main function
	char* my_name;
	my_name= new char;																//name created dynamically
	listOrders();																	//List orders
	cout<<"Please write the customer name in order to deliver his/her order: ";
	cin>>my_name;																		//Name is taken
	cout<<"Following order is delivering..."<<endl;
	remove(my_name);													//And sending the remove function

	delete my_name;														//Deletes the name created dynamically
	return;
}

string* OrderList::take_ingredient(int choice){							//According to choice, takes the ingredient and returns to the takeOrder function 

	string* chicken_inc=new string[MAX_ING]{"mozarella","chicken","mushroom","corn","olive","onion","tomato"};
	string* broccoli_inc=new string[MAX_ING]{"mozarella","broccoli","pepperoni","olive","corn","onion"};
	string* sausage_inc=new string[MAX_ING]{"mozarella","sausage","tomato","olive","mushroom","corn"};


	if(choice==1){
		delete[] broccoli_inc;
		delete[] sausage_inc;

		return chicken_inc;												//Returns chicken ingredient
	}
	else if(choice==2){
		delete[] chicken_inc;
		delete[] sausage_inc;

		return broccoli_inc;											//Returns broccoli ingredient
	}
	else if(choice==3){
		delete[] broccoli_inc;
		delete[] chicken_inc;

		return sausage_inc;												//Returns sausage ingredient
	}

	delete[] broccoli_inc;
	delete[] sausage_inc;

	return chicken_inc;													//If there is no true choice, returns chicken (it is done just for preventing compilation error)
}

int OrderList::print_menu(){											//Prints the main menu
	int choice;
	cout<<"Welcome to Unicorn Pizza!"<<endl;
	cout<<"1. Add an order"<<endl;
	cout<<"2. List orders"<<endl;
	cout<<"3. Deliver order"<<endl;
	cout<<"4. Exit"<<endl;
	cout<<"Choose what to do: ";
	cin>>choice;
	return choice;														//Returns the chioce

}


int OrderList::print_ingredient(int choice){							//Takes the chioce, returns the number of ingredients of the chosen pizza
	int my_size=0;
	if(choice == 1){
		cout<<"1. mozarella"<<endl<<"2. chicken"<<endl<<"3. mushroom"<<endl<<"4. corn"<<endl<<"5. olive"<<endl<<"6. onion"<<endl<<"7. tomato"<<endl;
		cout<<"Press 0 to save it"<<endl;
		my_size=7;
	}
	else if(choice == 2){
		cout<<"1. mozarella"<<endl<<"2. broccoli"<<endl<<"3. pepperoni"<<endl<<"4. olive"<<endl<<"5. corn"<<endl<<"6. onion"<<endl;
		cout<<"Press 0 to save it"<<endl;
		my_size=6;
	}
	else if(choice == 3){
		cout<<"1. mozarella"<<endl<<"2. sausage"<<endl<<"3. tomato"<<endl<<"4. olive"<<endl<<"5. mushroom"<<endl<<"6. corn"<<endl;
		cout<<"Press 0 to save it"<<endl;
		my_size=6;
	}
	return my_size;														//Returns the number of ingredients
}




void OrderList::takeOrder(){											//Takes the order, creates class according to required variables
	int choice;
	int amount;
	int drink;
	int number;
	int ing_size;
	int drink_size=0;

	Pizza* pizza_my_head=NULL;											//Linked list head for pizza list;
	
	string* our_ing= new string[MAX_ING];								//string array created dynamically for taking the ingredients

	int* ordered_drinks= new int[MAX_ING];								//ordered drinks are taken as integer

	char* name;	
	name=new char;														//Name is created dynamically

	char* size;			
	size= new char; 													//Size is created dynamically

	char* crust_type;
	crust_type= new char;												//Crust type is created dynamically


	cout<<"Pizza Menu"<<endl;											//Prints the pizza menu
	cout<<"1. Chicken Pizza (mozarella, chicken, mushroom, corn, olive, onion, tomato)"<<endl;
	cout<<"2. Broccoli Pizza (mozarella, broccoli, pepperoni, olive, corn, onion)"<<endl;
	cout<<"3. Sausage Pizza (mozarella, sausage, tomato, olive, mushroom, corn)"<<endl;
	cout<<"0. Back to main menu"<<endl;
	cin>>choice;																//Takes the choice
	if(choice ==0){
		return;
	}
	cout<<"Select size: small (15 TL), medium (20 TL), big (25 TL)"<<endl;
	cin>>size;																	//Takes the size

	cout<<"Select crust type: thin, normal, thick"<<endl;
	cin>>crust_type;															//Takes the crust type
	
	our_ing=take_ingredient(choice);											//This function is assigned with the our ingredient array for taking the ingredients according to choices

	cout<<"Enter the amount:";
	cin>>amount;																//Enters the amount of the pizza
	Pizza* ordered_pizza= new Pizza(size,crust_type,choice,our_ing);			//Firstly one pizza is created with non-default constructor
	pizza_my_head=ordered_pizza;												//First pizza is assigned as head of the linked list
	if(amount>1){																//If the amount is more than 1, pizza is created with copy constructor
		for(int a=0;a<amount-1;a++){
			//clean(our_ing);
			our_ing=take_ingredient(choice);									//Ingredients are refreshs because of the subtracted elements
			cout<<endl;
			cout<<"Please enter the number of the ingredient you want to remove from your pizza."<<endl;
			ing_size=print_ingredient(choice);									//Ingredients are printed
			for(int i=0;i<MAX_ING;i++){
				cin>>number;
				if(number==0){
					break;
				}
				our_ing[number-1]="-";											//According to non-required ingredient, '-' is added into the array'
			}
			bool find=false;
			for(int k=0;k<ing_size;k++){													
				if(find){														//If it found, index has to be one step back not for escaping the '-'
					k--;
					find=false;
				}
				if(our_ing[k].compare("-")==0){									//If the '-' is find, removing operation is applied
					if(k==ing_size-1){
						ing_size--;												//size is decreased becuause of the remove operation
						find=true;
					}
					else{
						for(int c=k;c<ing_size-1;c++){
							our_ing[c]=our_ing[c+1];							//Next index is added into the removed element
						}
						ing_size--;												//size is decreased becuause of the remove operation
						find=true;		
					}

				}
			}
			if(our_ing[ing_size-1].compare("-")==0){							//Finally, last index of the array is controlled
				ing_size--;														//If there is a '-' item, size is decreased
			}

			Pizza* copy_pizza = new Pizza(ordered_pizza,our_ing,ing_size);		//Copy constructor is invoked with prepared parameters


			if(pizza_my_head==NULL){											//Pizza list is added into the linked list
				pizza_my_head=copy_pizza;										//If there is no pizza, head keeps the pizza 
			}
			else{																//If not, traverse is trying to find empty (NULL) place
				Pizza* my_traverse;
				my_traverse=pizza_my_head;
				
				while(my_traverse->next_pizza!=NULL){
					my_traverse=my_traverse->next_pizza;
				}
				my_traverse->next_pizza=copy_pizza;								//After finding the NULL place, copy pizza is added into linked list
			}
		}
	}
	cout<<"Please choose a drink:"<<endl;										//Drinks are prepared
	cout<<"0. no drink"<<endl<<"1. cola 4 TL"<<endl<<"2. soda 2 TL"<<endl<<"3. ice tea 3 TL"<<endl<<"4. fruit juice 3.5 TL"<<endl;
	cout<<"Press -1 for save your order"<<endl;

	for(int k=0;k<MAX_ING;k++){															
		cin>>drink;
		if(drink==-1 || drink==0){
			break;
		}
		ordered_drinks[k]=drink;												//Drinks are assigned according to input as integer
		drink_size++;															//Drink size is increased
	}

	cout<<endl;
	cout<<"Please enter your name:"<<endl;
	cin>>name;																	//Fİnally, name is taken fromm client
	cout<<endl;

	cout<<"Your order is saved, it will be delivered when it is ready..."<<endl;
	if(drink_size==0){																		//If there is no drink
		Order* my_order=new Order(name,pizza_my_head);										//Order constructor without drink is invoked
		my_order->printOrder();																//Printing the last order
		add_order(my_order);																//Adding the order into the linked list
		my_order->get_amount(amount);														//Amount of the pizza is given get_amount and added into the Order class
	}
	else{																					//If there is drink 
		Order* my_order=new Order(name,pizza_my_head,ordered_drinks,drink_size);			//Order constructor with drink is invoked
		my_order->printOrder();																//Printing the last order
		add_order(my_order);																//Adding the order into the linked list
		my_order->get_amount(amount);														//Amount of the pizza is given get_amount and added into the Order class
	}
	delete[] our_ing;																		//Deletes the dynamically create variables
	delete[] ordered_drinks;
	delete name;
	delete size;
	delete crust_type;

	return;
}

void OrderList::listOrders(){								//List the orders into the linked list
	Order* traverse;
	traverse=head;
	if(head==NULL){											//If there is no order
		cout<<endl;
		cout<<"empty"<<endl;								//Printing empty
		cout<<endl;
		return;
	}
	for(int k=0;k<n;k++){									//If there is an order
		cout<<k+1<<endl;
		traverse->printOrder();								//printing the order pointed by traverse
		if(traverse->next==NULL){
			break;
		}else{
			traverse=traverse->next;						//And then traverse is traversing into the order linked list
		}
	}
	return;
}