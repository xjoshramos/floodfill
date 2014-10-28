// interview.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
using namespace std;

int binOnes(int number){
	int count = 0;
	
	while(number) {
		if(number & 1) count++;
		number = number >> 1;
	}

	return count;
}

int minimum( int x[], int length){

	
	if (x == NULL | length == NULL) return 0;
	int min = x[0];
	for ( int i = 0; i < length; i++) {
		if (x[i] < min){
			min = x[i];
		}
	}

	return min;
}


bool palindromeCheck(string str){
	bool palindrome = true; 
	int i = 0;
	int j = str.length()-1;
	
	while(i <= j){
		
		if(str[i] == str[j]){
			i++;
			j--;
		}else{
			palindrome = false;
			break;
		}
	}

	return palindrome;
}
int LengthOfIncreasing(int* data, int length)
{
    if(data == NULL || length < 0)
        return 0;

    int* longest = new int[length];
    longest[0] = 1;

    int max = 0;
    for(int i = 1; i < length; ++ i)
    {
        max = 0;
        for(int j = 0; j < i; ++ j)
        {
            if(data[j] < data[i] && longest[j] > max)
                max = longest[j];
        }

        longest[i] = max + 1;
    }

    max = 0;
    for(int i = 0; i < length; ++ i)
        if(longest[i] > max)
            max = longest[i];
                                                                  
    return max;   
}

struct node
{
  int key_value;
  node *left;
  node *right;
};

class btree
{
    public:
        btree();
        ~btree();

        void insert(int key);
        node *search(int key);
        void destroy_tree();

    private:
        void destroy_tree(node *leaf);
        void insert(int key, node *leaf);
        node *search(int key, node *leaf);
        
        node *root;
};

btree::btree()
{
  root=NULL;
}

void btree::destroy_tree(node *leaf)
{
  if(leaf!=NULL)
  {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}


void btree::insert(int key, node *leaf)
{
  if(key< leaf->key_value)
  {
    if(leaf->left!=NULL)
     insert(key, leaf->left);
    else
    {
      leaf->left=new node;
      leaf->left->key_value=key;
      leaf->left->left=NULL;    //Sets the left child of the child node to null
      leaf->left->right=NULL;   //Sets the right child of the child node to null
    }  
  }
  else if(key>=leaf->key_value)
  {
    if(leaf->right!=NULL)
      insert(key, leaf->right);
    else
    {
      leaf->right=new node;
      leaf->right->key_value=key;
      leaf->right->left=NULL;  //Sets the left child of the child node to null
      leaf->right->right=NULL; //Sets the right child of the child node to null
    }
  }
}


node *btree::search(int key, node *leaf)
{
  if(leaf!=NULL)
  {
    if(key==leaf->key_value)
      return leaf;
    if(key<leaf->key_value)
      return search(key, leaf->left);
    else
      return search(key, leaf->right);
  }
  else return NULL;
}

void btree::insert(int key)
{
  if(root!=NULL)
    insert(key, root);
  else
  {
    root=new node;
    root->key_value=key;
    root->left=NULL;
    root->right=NULL;
  }
}

node *btree::search(int key)
{
  return search(key, root);
}

void btree::destroy_tree()
{
  destroy_tree(root);
}

/*
struct node{
	 int number;
	 node *next;
};

bool isEmpty( node *head)
{
	if(head == NULL)
		return true;
	else
		return false;

}

char menu()
{
	char choice;
	cout << "menu \n";
	cout << "1. add an item \n";
	cout << "2. Remove an item \n";
	cout << "3. show the list \n";
	cout << "4. exit \n";

	cin >> choice;
	return choice;
	
}

void insertAsFirstElement(node *&head, node *&last, int number)
{
	node *temp = new node;
	temp->number = number;
	temp->next = NULL;
	head = temp;
	last = temp;

}

void insert(node *&head, node *&last, int number)
{
	if(isEmpty(head))
		insertAsFirstElement(head,last,number);
	else
	{
		node *temp = new node;
		temp->number = number;
		temp->next = NULL;
		last->next = temp;
		last = temp;

	}
}

void remove(node *&head, node *&last)
{
	if(isEmpty(head))
		cout << " the list empty \n" << endl;
	else if (head == last)
	{
		delete head;
		head == NULL;
		last == NULL;
	}
	else
	{
		node *temp = head;
		head = head->next;
		delete temp;

	}
}

void showList(node *current)
{
	if(isEmpty(current))
		cout << "list empty \n " << endl;
	else
	{
		cout << " the list contains: \n";
		while(current != NULL)
		{
			cout<< current->number << endl;
			current = current->next;
		}


	}
}
*/
//int _tmain(int argc, _TCHAR* argv[])
class Items{
public:
	Items();
	void purchased(string str);
	int getNumberPurchased(string str);
	list<string> getTopTen();

	map<string,int> myMap;
private:
	
};
Items::Items(){
	myMap["itemA"] = 0;
	myMap["itemB"] = 0;
	myMap["itemC"] = 0;
}
list<string> Items::getTopTen(){
	list<string> topTen;
	
	int value = 0;
	map<string,int>::iterator it = myMap.begin();
	cout<<"saddsafaalkjf" <<myMap.at("itemA")<<endl;
	//if(it++->second > it->second){
		///cout << "this is greater "<<it->second << endl;
	//}else{
		//cout << "this is greater" << (it++)->second << endl;
	//}

	for(it = myMap.begin(); it != myMap.end(); it++){
	
		pair<string,int> myPair1 = *it;
		
			//cout <<" THE POSITION" << std::distance(it,myMap.begin()) << endl;
			//cout << "max of the list " <<  << endl;
			
	
			
		//pair<string,int> myPair2 = *it++;
		//if(myPair1.second > myPair2.second){
		//	value = myPair1.second;
		//}else{
		//	value = myPair2.second;
		//}
		//if(myPair.first == str){
			//myMap[str] = myPair.second++;
			//cout<< myPair1.first << " was just purchased" << " making a total number this item purchased to = " << myPair1.second << "\n" << endl;
			//cout<<"the key \"myKey"" maps to the value of "<<myMap["myKey"]<<endl;
		//}
	}
	//cout <<" the value is " << value<<endl;
	return topTen;
}
int Items::getNumberPurchased(string str){
	int number;
	number = myMap[str];
	return number;
}
void Items::purchased(string str){
	myMap[str] += 1;
	/*
	map<string,int>::iterator it = myMap.begin();
	for(it = myMap.begin(); it != myMap.end(); it++){
		pair<string,int> myPair = *it;
		if(myPair.first == str){
			//myMap[str] = myPair.second++;
			cout<< myPair.first << " was just purchased" << " making a total number this item purchased to = " << myPair.second << "\n" << endl;
			//cout<<"the key \"myKey"" maps to the value of "<<myMap["myKey"]<<endl;
		}
	}*/
}


	//map<string,int>::iterator it = list.myMap.begin();
	//for(it = list.myMap.begin(); it != list.myMap.end(); it++){
		//pair<string,int> myPair = *it;
		//cout<<"purchase"<<myPair.first<<" has total number of purchases = "<<myPair.second<< "\n"<<endl;
		//cout<<"the key \"myKey"" maps to the value of "<<myMap["myKey"]<<endl;
	//}

	//purchasedItem("itemA");
	//node *head = NULL;
	//node *last = NULL;	

	//linked list 
	/*
	struct node {
		int x;
		node *next;
	};

	node *root; // the root never changes
	node *conductor; // the conductor to walk down the train

	root = new node; // set the root 
	root->next = 0; // points the next to not point to anything , point the next to the end
	root->x = 1; // set x to 12 

	conductor = root; // point the conductor to the root
	conductor->next = new node; // create new node at the end of the list
	conductor = conductor->next; // point to that node
	conductor->next = 0; // prevents from going any further
	conductor->x = 2; // set x to 45

	conductor->next = new node;
	conductor = conductor->next;
	conductor->next = 0;
	conductor->x = 3;
	

	conductor = root; // points the conductor where to start 
	while( conductor != NULL ){
		cout << conductor->x; // print 
		conductor = conductor->next; // traverse linked list
	}
	*/	

class Box {
  public:
    Box();
    void write(string boxId, double weight);
    double getWeightByBoxId(string BoxId);
    double getWeightAtPercentile(double percentile);
    vector< pair<string, double>> boxInformation;
    
  private:
    
    
};

Box::Box(){
    //constructor intialization
}
void Box::write(string boxId, double weight){
    
    pair< string, double> weightInformation; // pair given from the user
    weightInformation.first = boxId;
    weightInformation.second = weight;
    bool pushFlag = false;
    if(boxInformation.size() == 0){
        //if this is the first write
        boxInformation.push_back(weightInformation);
    }
    
    for(size_t i = 0; i < boxInformation.size(); i++){
		
        if(boxInformation[i].first == boxId){
            boxInformation[i].second = weight;
			pushFlag = true;
            //cout << "writing new box weight" << boxInformation[i].first << "=" << boxInformation[i].second << endl;
        }
       
    }

	if(pushFlag = false){
		cout << "inside" << endl;
		boxInformation.push_back(weightInformation);
	}

	for(size_t i = 0; i < boxInformation.size(); i++){
		cout << "writing new box weight" << boxInformation[i].first << "=" << boxInformation[i].second << endl;
	}
}

double Box::getWeightByBoxId(string BoxId){
    
    double weight = 0;
    
    
    for(size_t i =0; i < boxInformation.size(); i++){
		
        if(boxInformation[i].first == BoxId){
            // only grab the weight of the box in question
            weight = boxInformation[i].second;
            cout << boxInformation[i].first <<" has a weight = " << boxInformation[i].second << endl;             
        }   
    }
    
    return weight;
    
}

double Box::getWeightAtPercentile(double percentile){ 
     
   
    double weightPercentile = 0;
    double totalWeight = 0;
    
    for(size_t i =0; i < boxInformation.size(); i++){
        totalWeight += boxInformation[i].second;
    }
    weightPercentile = (percentile/100)*totalWeight;
    cout << " the total weight of all the boxes added together = " << totalWeight << "\n" << endl;
    cout << " weight at percentile " << percentile << " is = " << weightPercentile << endl;
    return weightPercentile;
    
}






struct Image
{

	int width, height;
	int *data;
	Image(int w, int h)
	{
		width = w;
		height = h;
		data = NULL;
		Init();

	}
	~Image()
	{
		delete[] data;
	}
	void Display() const
	{
		for(int i=0; i<height; i++)
		{
			for(int j=0; j<width; j++)
			{
				std::cout << data[i*width +j] << " ";
			}
			std::cout << std::endl;
		}
	}
	void Example()
	{
		width  = 8;
		height = 6;
		Init();
		Image &self = *this;
		for(int i=1; i<height; i++)
			self(o,i) = 1;
		for(int i=1; i<height; ++i)
			self(i,0) = 1;
		self(2,2) = 1;
		self(3,3) = 3;
		self(4,4) = 1;
		self(3,5) = 1;
		self(2,5) = 2;
		self(1,5) = 3;
		self(5,5) = 2
	}
	
	void Init()
	{
		if(data) delete[] data;
		data = new int[width*height];
		memset(data, 0, width*height*sizeof(int));
	}
	inline int& operator()(int i, int j)
	{
		return data[i*width +j];
	}
	boot operator==(Image const& rhs) const
	{
		Image const& self = *this;
		for(int i =0; i<height; i++)
		{
			for(int j =0; j<width; j++)
			{
				if(self(i,j) != rhs(i,j))
				{
					return false;
				}
			}
		}
		return true;
	}

	void floodfill( int x, int y, int color)
	{
	}
};


int main()
{
	std::cout << "Input: " <<std::endl;
	Image in(1,1);
	in.Example1();
	in.Display();
	std::cout << "solution: "<<std::endl;
	Image out(1,1);
	out.Solution1();
	out.display();

	Image sanity(1,1);
	sanity.Solution1();

	in.floodfill(2.3.5);

	/*	
	Box boxInfo;
    boxInfo.write("box1", 100);
    boxInfo.write("box2", 200);
    boxInfo.write("box3", 300);
	boxInfo.write("box4", 400);
    //double box1Weight = boxInfo.getWeightByBoxId("box1");
    //double percentileWeight = boxInfo.getWeightAtPercentile(100);

	*/
	system("PAUSE");
	return 0;
}



