#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

struct linkedListNode
{
	string key;
	string def;
	linkedListNode * next;
};

template <class T>
class linkedListHashTable
{
	public:
		linkedListHashTable(int, T);
		void addElement(string s, string d);
	        linkedListNode* search(string s);
		void print();	
	//private:
		//private function to help with hashing
		double convertHexStringToDecimal(string);
		linkedListNode* *table;//an array of linkedListNode pointers
		int size;
		T hasher;
};

template <class T>
linkedListHashTable<T>::linkedListHashTable(int s, T h)
{
	size = s*2;//standard practice is to make a hash table twice the
		   //size of the data that is stored in it
	table = new linkedListNode*[size];
	hasher = h;
}

template <class T>
double linkedListHashTable<T>::convertHexStringToDecimal(string s)
{
	string num = "";
	for(int i=0;i<s.length();i++)
	{
		//cout << "processing " << s[i] << endl;
		switch(s[i])
		{
			case '1': num+="1";
				  //cout << "num+=1" << endl;
				break;
			case '2': num+="2";
				  //cout << "num+=2" << endl;
				break;
			case '3': num+="3";
				  //cout << "num+=3" << endl;
				break;
			case '4': num+="4";
				  //cout << "num+=4" << endl;
				break;
			case '5': num+="5";
				  //cout << "num+=5" << endl;
				break;	
			case '6': num+="6";
				  //cout << "num+=6" << endl;
				break;
			case '7': num+="7";
				  //cout << "num+=7" << endl;
				break;
			case '8': num+="8";
				  //cout << "num+=8" << endl;
				break;		
			case '9': num+="9";
				  //cout << "num+=9" << endl;
				break;	
			case 'a': num+="10";
				//cout << "num+=10" << endl;
			        break;	
			case 'b': num+="11";
				//cout << "num+=11" << endl;
				break;
			case 'c': num+="12";
				//cout << "num+=12" << endl;
				break;
			case 'd':	num+="13";
				//cout << "num+=13" << endl;
				break;
			case 'e':	num+="14";
				//cout << "num+=14" << endl;
				break;
			case 'f':	num+="15";
				//cout << "num+=15" << endl;
				break;
		}
	}
	return stod(num);
}

template <class T>
void linkedListHashTable<T>::addElement(string s, string d)
{
	linkedListNode *n = new linkedListNode();
	string temp = hasher(s);
	int index = fmod(convertHexStringToDecimal(temp), size);
	n->key = s;
	n->def = d;
	n->next = NULL;
	if(table[index] == NULL)
	{
		table[index] = n;
	}
	else
	{
		//need to find the last linkedListNode in this bucket
		linkedListNode * temp = table[index];
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		//now temp is pointing to the linkedListNode after the last linkedListNode
		temp->next = n;
	}
}

template <class T>
linkedListNode* linkedListHashTable<T>::search(string s)
{
	string temp = hasher(s);
	int index = fmod(convertHexStringToDecimal(temp), size);
	if(table[index]->key == s)
	{
		return table[index];
	}
	else
	{
		//need to find the last linkedListNode in this bucket
		linkedListNode * temp = table[index];
		while(temp != NULL && temp->key != s)
		{
			temp = temp->next;
		}
		//temp will be null if linkedListNode found, or be the value if found
		return temp;
	}
}

template <class T>
void linkedListHashTable<T>::print()
{
	for(int i=0;i<size;i++)
	{
		if(table[i] != NULL)
		{
			cout << i << ": " << table[i]->key << " def: " << table[i]->def;
		}
	}
}
