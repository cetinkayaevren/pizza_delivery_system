
/* @author: Evren Çetinkaya
		ID: 150170118
	"PLEASE COMPILE WITH -std=c++11 !!!!"
*/
#include <iostream>
#include <cstring>

#define MAX 20
#define MAX_ING 7

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


class OrderList{									//OrderList Class
	static int n;									//Number of orders are taken as static.
	Order* head;									//Head pointer for orders which are kept into the linked list
	int my_amount;									//Amount of the orders.
public:
	OrderList();									//Default Constructor
	void takeOrder();								//Takes the order from client
	void listOrders();								//Lists all the orders
	void deliverOrders();							//Deliver the required order and removes from linked list;
	void add_order(Order*);							//Adding the Orders in the linked list
	void remove(char*);								//Removes object into the linked list
	~OrderList();									//OrderList destructor;
};

int OrderList::n;									//Allocating memory for n


//------------OrderList Class Functions-----------------------

OrderList::OrderList(){								//Constructor Function
	head=NULL;										//Head is assigned as NULL
	n=0;											//Number of orders are started with zero 
}

OrderList::~OrderList(){							//OrderList destructor
	delete head;									//Deletes head after all of the dynamic expressions are deleted.
}


//------------Order Class Functions---------------------------

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

Order::~Order(){																		//Order destructor (Deletes dynamically created variables into the Order class)
	delete customer;																	//Deletes customer	
	delete[] drink;																		//Deletes the drink array
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

//----------------------------Pizza Class Functions-------------------------
Pizza::Pizza(){																			//Default Pizza constructor
	next_pizza=NULL;																	//Next pizza pointer is assigned as NULL
	ingredients=new string[MAX_ING];													//Creates ingredients array dynamically
	name=new char;																		//Pizza name is created dynamically
	size= new char;																		//Pizza size is created dynamically
	crust_type= new char;																//Crust type is created dynamically
	strcpy(name,"Margerita");															
	strcpy(size, "medium");																//Default parameters are assigned
	strcpy(crust_type, "normal");
	ingredients[0]="mozarella";
	ingredient_size=1;																	//Number of ingredients is assigned as 1
}

Pizza::Pizza(char* my_size,char* my_crust, int my_type,string* our_ing){				//Pizza constructor
	next_pizza=NULL;																	//Next pizza pointer is assigned as NULL
	ingredients=new string[MAX_ING];													//Creates ingredients array dynamically
	name=new char;																		//Pizza name is created dynamically
	size= new char;																		//Pizza size is created dynamically
	crust_type= new char;
	int my_size_ing;
	strcpy(crust_type,my_crust);														//Default parameters are assigned
	strcpy(size,my_size);

	if(my_type == 1){																	//According to required pizza, 
		my_size_ing=7;																	//class variables are assigned with coming parameters
		ingredient_size=my_size_ing;													
		strcpy(name,"Chicken Pizza");													
		for(int i=0;i<my_size_ing;i++){
			ingredients[i]=our_ing[i];
		}
	}
	else if (my_type == 2){																//According to required pizza, 
		my_size_ing=6;																	//class variables are assigned with coming parameters
		ingredient_size=my_size_ing;
		strcpy(name,"Broccoli Pizza");
		for(int i=0;i<my_size_ing;i++){
			ingredients[i]=our_ing[i];
		}
	
	}
	else if (my_type == 3){																//According to required pizza, 
		my_size_ing=6;																	//class variables are assigned with coming parameters
		ingredient_size=my_size_ing;
		strcpy(name,"Sausage Pizza");
		for(int i=0;i<my_size_ing;i++){
			ingredients[i]=our_ing[i];
		}
	}

	else{
		cout<<"Ooops, wrong choice !!"<<endl;
	}
}

Pizza::Pizza(const Pizza* my_pizza,string* our_ing,int ing_size){				//Copy COnstructor of the pizza class
	next_pizza=NULL;
	ingredients=new string[MAX_ING];											//Ingredient array is created dynamically
	name = new char;															//Pizza name is created dynamically
	size= new char;																//Pizza size is created dynamically
	crust_type= new char;														//Crust type is created dynamically
	ingredient_size=ing_size;
	strcpy(name,my_pizza->name);												//Parameters are assigned
	strcpy(size,my_pizza->size);
	strcpy(crust_type,my_pizza->crust_type);
	for(int k=0;k<ing_size;k++){												//Acoording to number of ingredients, these are assigned
		ingredients[k]=our_ing[k];
	}
}

Pizza::~Pizza(){																//Pizza destructor (deletes the dynamically created variable)
	delete name;																
	delete size;
	delete crust_type;
	delete[] ingredients;
}
//---------------------------------------------------------------------------------

int print_menu(){																//Prints the main menu
	int choice;
	cout<<"Welcome to Unicorn Pizza!"<<endl;
	cout<<"1. Add an order"<<endl;
	cout<<"2. List orders"<<endl;
	cout<<"3. Deliver order"<<endl;
	cout<<"4. Exit"<<endl;
	cout<<"Choose what to do: ";
	cin>>choice;
	return choice;																//Returns the chioce

}

int print_ingredient(int choice){												//Takes the chioce, returns the number of ingredients of the chosen pizza
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
	return my_size;																//Returns the number of ingredients
}

void OrderList::add_order(Order* my_order){										//Adding the order into the linked list, takes the order adress 
	if(head==NULL){																//If the OrderLsist has no any order, the first order is added
		head=my_order;															//Head is assigned
		head->next=NULL;
		n++;																	//Number of the orders is increased
	}
	else{																		//If the OrderList has the orders 
		Order* traverse;
		traverse=head;
		while(traverse->next!=NULL){											//Travelling and trying to find NULL pointer for adding the order
			traverse=traverse->next;
		}
		traverse->next=my_order;												//New order is addded into the linked list
		n++;																	//Number of the orders is increased
	}
	return;
}

void OrderList::remove(char* my_name){											//Removing the order from the linked list
	char answer;
	double total;
	string my_code;
	Order* traverse;															//Traverse pointer is created
	Order* previous;															//Previous pointer is created for travel with traverse pointer one step back
	traverse=head;																//Traverse and previous assigned with head pointer first
	previous=traverse;
	if(head==NULL){																//If the Orderlist has no order
		cout<<"There is no order for delivering"<<endl<<endl;					
	}
	else{																		//If the Orderlist has order
		while(true){															//For finding the true order, traverse and previous 
			if(strcmp(traverse->customer,my_name)==0){							//Make traversing
				break;
			}
			else{
				if(traverse->next==NULL){										//If the name cannot be found
					cout<<"Wrong name"<<endl;
					return;
				}
				else{															//If there is a order, continue to traverse
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
	
	traverse->printOrder();														//After finding the required order, print order function is invoked
	total=traverse->getPrice();													//Then getPrice function is invoked and total is keeps the total price
		cout<<"Total price: "<<total<<endl;
	do{																			//Promotion code is asked for making discount
		cout<<"Do you have a promotion code? (y/n)"<<endl;
		cin>>answer;

		if(answer=='y' || answer== 'Y'){										//If answer is 'yes', waiting for the entering code
			cout<<"Please enter your code: ";
			getchar();
			getline(cin,my_code);
			if(my_code.compare("I am a student")==0){							//If code is true, %10 discount operation is applying
				cout<<"Discounted price: "<< (90*total)/100<<endl;
				break;
			}
			else{																//If not, continue to ask same question until the answer is 'no'
				continue;
			}
		}
	}while(answer!='n' && answer !='N');

	cout<<"The order is delivered successfully!"<<endl;							//Order delivered message and removing operation is starting
	cout<<endl;	

	if(traverse==head){															//If the order is first element of the linked list
		if(traverse->next==NULL){												//If the element number is 1
			head=NULL;
			}
		else{																	//If the element number is more than 1
			traverse=traverse->next;
				head->next=NULL;
				head=traverse;
		}
	}
	else if(traverse!= head && traverse->next !=NULL){							//If the order is among into the linked list
		previous->next=traverse->next;
		traverse->next=	NULL;
		traverse=previous;
	}
	else if(traverse!=head && traverse->next==NULL){							// If this order is the last item of the linked list..
		traverse=previous;
		previous->next=NULL;
		}
	}
	return;
}

void OrderList::deliverOrders(){															//Deliver order menu for main function
	char* my_name;
	my_name= new char;																		//name created dynamically
	listOrders();																			//List orders
	cout<<"Please write the customer name in order to deliver his/her order: ";
	cin>>my_name;																			//Name is taken
	cout<<"Following order is delivering..."<<endl;
	remove(my_name);																		//And sending the remove function

	delete my_name;																			//Deletes the name created dynamically
	return;
}

string* take_ingredient(int choice){														//According to choice, takes the ingredient and returns to the takeOrder function 

	string* chicken_inc=new string[MAX_ING]{"mozarella","chicken","mushroom","corn","olive","onion","tomato"};
	string* broccoli_inc=new string[MAX_ING]{"mozarella","broccoli","pepperoni","olive","corn","onion"};
	string* sausage_inc=new string[MAX_ING]{"mozarella","sausage","tomato","olive","mushroom","corn"};


	if(choice==1){
		delete[] broccoli_inc;
		delete[] sausage_inc;

		return chicken_inc;																	//Returns chicken ingredient
	}
	else if(choice==2){
		delete[] chicken_inc;
		delete[] sausage_inc;

		return broccoli_inc;																//Returns broccoli ingredient
	}
	else if(choice==3){
		delete[] broccoli_inc;
		delete[] chicken_inc;

		return sausage_inc;																	//Returns sausage ingredient
	}

	delete[] broccoli_inc;
	delete[] sausage_inc;

	return chicken_inc;																		//If there is no true choice, returns chicken (it is done just for preventing compilation error)
}


void OrderList::takeOrder(){																//Takes the order, creates class according to required variables
	int choice;
	int amount;
	int drink;
	int number;
	int ing_size;
	int drink_size=0;

	Pizza* pizza_my_head=NULL;																//Linked list head for pizza list;
	
	string* our_ing= new string[MAX_ING];													//string array created dynamically for taking the ingredients

	int* ordered_drinks= new int[MAX_ING];													//ordered drinks are taken as integer

	char* name;	
	name=new char;																			//Name is created dynamically

	char* size;			
	size= new char; 																		//Size is created dynamically

	char* crust_type;
	crust_type= new char;																	//Crust type is created dynamically


	cout<<"Pizza Menu"<<endl;																//Prints the pizza menu
	cout<<"1. Chicken Pizza (mozarella, chicken, mushroom, corn, olive, onion, tomato)"<<endl;
	cout<<"2. Broccoli Pizza (mozarella, broccoli, pepperoni, olive, corn, onion)"<<endl;
	cout<<"3. Sausage Pizza (mozarella, sausage, tomato, olive, mushroom, corn)"<<endl;
	cout<<"0. Back to main menu"<<endl;
	cin>>choice;																			//Takes the choice
	if(choice ==0){
		return;
	}
	cout<<"Select size: small (15 TL), medium (20 TL), big (25 TL)"<<endl;
	cin>>size;																				//Takes the size

	cout<<"Select crust type: thin, normal, thick"<<endl;
	cin>>crust_type;																		//Takes the crust type
	
	our_ing=take_ingredient(choice);														//This function is assigned with the our ingredient array for taking the ingredients according to choices

	cout<<"Enter the amount:";
	cin>>amount;																			//Enters the amount of the pizza
	Pizza* ordered_pizza= new Pizza(size,crust_type,choice,our_ing);						//Firstly one pizza is created with non-default constructor
	pizza_my_head=ordered_pizza;															//First pizza is assigned as head of the linked list
	if(amount>1){																			//If the amount is more than 1, pizza is created with copy constructor
		for(int a=0;a<amount-1;a++){
			//clean(our_ing);
			our_ing=take_ingredient(choice);												//Ingredients are refreshs because of the subtracted elements
			cout<<endl;
			cout<<"Please enter the number of the ingredient you want to remove from your pizza."<<endl;
			ing_size=print_ingredient(choice);												//Ingredients are printed
			for(int i=0;i<MAX_ING;i++){
				cin>>number;
				if(number==0){
					break;
				}
				our_ing[number-1]="-";														//According to non-required ingredient, '-' is added into the array'
			}
			bool find=false;
			for(int k=0;k<ing_size;k++){													
				if(find){																	//If it found, index has to be one step back not for escaping the '-'
					k--;
					find=false;
				}
				if(our_ing[k].compare("-")==0){												//If the '-' is find, removing operation is applied
					if(k==ing_size-1){
						ing_size--;															//size is decreased becuause of the remove operation
						find=true;
					}
					else{
						for(int c=k;c<ing_size-1;c++){
							our_ing[c]=our_ing[c+1];										//Next index is added into the removed element
						}
						ing_size--;															//size is decreased becuause of the remove operation
						find=true;		
					}

				}
			}
			if(our_ing[ing_size-1].compare("-")==0){										//Finally, last index of the array is controlled
				ing_size--;																	//If there is a '-' item, size is decreased
			}

			Pizza* copy_pizza = new Pizza(ordered_pizza,our_ing,ing_size);					//Copy constructor is invoked with prepared parameters


			if(pizza_my_head==NULL){														//Pizza list is added into the linked list
				pizza_my_head=copy_pizza;													//If there is no pizza, head keeps the pizza 
			}
			else{																			//If not, traverse is trying to find empty (NULL) place
				Pizza* my_traverse;
				my_traverse=pizza_my_head;
				
				while(my_traverse->next_pizza!=NULL){
					my_traverse=my_traverse->next_pizza;
				}
				my_traverse->next_pizza=copy_pizza;											//After finding the NULL place, copy pizza is added into linked list
			}
		}
	}
	cout<<"Please choose a drink:"<<endl;													//Drinks are prepared
	cout<<"0. no drink"<<endl<<"1. cola 4 TL"<<endl<<"2. soda 2 TL"<<endl<<"3. ice tea 3 TL"<<endl<<"4. fruit juice 3.5 TL"<<endl;
	cout<<"Press -1 for save your order"<<endl;

	for(int k=0;k<MAX_ING;k++){															
		cin>>drink;
		if(drink==-1 || drink==0){
			break;
		}
		ordered_drinks[k]=drink;															//Drinks are assigned according to input as integer
		drink_size++;																		//Drink size is increased
	}

	cout<<endl;
	cout<<"Please enter your name:"<<endl;
	cin>>name;																				//Fİnally, name is taken fromm client
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



void OrderList::listOrders(){																//List the orders into the linked list
	Order* traverse;
	traverse=head;
	if(head==NULL){																			//If there is no order
		cout<<endl;
		cout<<"empty"<<endl;																//Printing empty
		cout<<endl;
		return;
	}
	for(int k=0;k<n;k++){																	//If there is an order
		cout<<k+1<<endl;
		traverse->printOrder();																//printing the order pointed by traverse
		if(traverse->next==NULL){
			break;
		}else{
			traverse=traverse->next;														//And then traverse is traversing into the order linked list
		}
	}
	return;
}

//-----------------------------------------------------------------------
int main(){

	OrderList* my_order=new OrderList;														//New OrderList is created dynamically
	int choice;
	do{
		choice=print_menu();																//Prints the menu
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


