
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


Pizza::Pizza(){												//Default Pizza constructor
	next_pizza=NULL;										//Next pizza pointer is assigned as NULL
	ingredients=new string[MAX_ING];						//Creates ingredients array dynamically
	name=new char;											//Pizza name is created dynamically
	size= new char;											//Pizza size is created dynamically
	crust_type= new char;									//Crust type is created dynamically
	strcpy(name,"Margerita");															
	strcpy(size, "medium");									//Default parameters are assigned
	strcpy(crust_type, "normal");
	ingredients[0]="mozarella";
	ingredient_size=1;										//Number of ingredients is assigned as 1
}



Pizza::Pizza(char* my_size,char* my_crust, int my_type,string* our_ing){		//Pizza constructor
	next_pizza=NULL;															//Next pizza pointer is assigned as NULL
	ingredients=new string[MAX_ING];							//Creates ingredients array dynamically
	name=new char;												//Pizza name is created dynamically
	size= new char;												//Pizza size is created dynamically
	crust_type= new char;
	int my_size_ing;
	strcpy(crust_type,my_crust);								//Default parameters are assigned
	strcpy(size,my_size);

	if(my_type == 1){											//According to required pizza, 
		my_size_ing=7;											//class variables are assigned with coming parameters
		ingredient_size=my_size_ing;													
		strcpy(name,"Chicken Pizza");													
		for(int i=0;i<my_size_ing;i++){
			ingredients[i]=our_ing[i];
		}
	}
	else if (my_type == 2){										//According to required pizza, 
		my_size_ing=6;											//class variables are assigned with coming parameters
		ingredient_size=my_size_ing;
		strcpy(name,"Broccoli Pizza");
		for(int i=0;i<my_size_ing;i++){
			ingredients[i]=our_ing[i];
		}
	
	}
	else if (my_type == 3){										//According to required pizza, 
		my_size_ing=6;											//class variables are assigned with coming parameters
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


Pizza::Pizza(const Pizza* my_pizza,string* our_ing,int ing_size){	//Copy COnstructor of the pizza class
	next_pizza=NULL;
	ingredients=new string[MAX_ING];						//Ingredient array is created dynamically
	name = new char;										//Pizza name is created dynamically
	size= new char;											//Pizza size is created dynamically
	crust_type= new char;									//Crust type is created dynamically
	ingredient_size=ing_size;
	strcpy(name,my_pizza->name);							//Parameters are assigned
	strcpy(size,my_pizza->size);
	strcpy(crust_type,my_pizza->crust_type);
	for(int k=0;k<ing_size;k++){							//Acoording to number of ingredients, these are assigned
		ingredients[k]=our_ing[k];
	}
}


Pizza::~Pizza(){											//Pizza destructor (deletes the dynamically created variable)
	delete name;																
	delete size;
	delete crust_type;
	delete[] ingredients;
}


