#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct defNode
{
	string definition = "definition";
};

class trieNode
{
	public:
		trieNode();
		trieNode(char);
		bool addElement(string s);
		string search(string s);
		~trieNode();
	//private:
		vector<trieNode*> children;
		defNode d;
		char c;
		bool word;
};		

class Trie
{
	public:
		Trie();
		bool addElement(string s);
		string search(string s);
		~Trie();
	//private:
		trieNode* root;
};

Trie::Trie()
{
	root = new trieNode();
}

bool Trie::addElement(string s)
{
	return root->addElement(s);
}

string Trie::search(string s)
{
	return root->search(s);
}

Trie::~Trie()
{
	//delete all nodes
}

trieNode::trieNode()
{
	c = ' ';
	word = false;
	children.reserve(1000);
}

trieNode::trieNode(char ch)
{
	c=ch;
	word=false;
	children.reserve(1000);
}

bool trieNode::addElement(string s)
{
	if(s.length() == 0)
	{	
		//set word=true and return true
		word = true;
		return true;
	}
	//search if element already exits
	bool found = false;
	int i;
	for(i=0;i<children.size();i++)
	{
		if(children[i]->c == s[0])
		{
			found = true;
			break;
		}
	}
	if(found)
	{
		children[children.size()-1]->addElement(s.substr(1));
	}
	else
	{
		trieNode *node = new trieNode(s[0]);
		children.push_back(node);
		node->addElement(s.substr(1));
	}
}

string trieNode::search(string s)
{
	bool found = false;
	if(s.length() == 0)
	{
		if(word)
		{
			return d.definition;
		}
		else
		{
			return "word was not found";
		}
	}
	int i;
	for(i=0;i<children.size();i++)
	{
		if(children[i]->c == s[0])
		{	
			found = true;
			break;	
		}
	}
	if(found)
	{
		return children[i]->search(s.substr(1));
	}
	else
	{
		return NULL;
	}
}

//for testing purposes
/*int main()
{
	string temp;
	ifstream fin;
	fin.open("dictionary.txt");
	trie *t = new trie();
	int count = 0;
	while(getline(fin, temp))
	{
		if(t->addElement(temp))
		{
			cout << temp << " added" << endl;
		}
		count++;
	}
	fin.close();	
	t->addElement("aardvark");
	t->addElement("apple");
	t->addElement("bark");
	t->addElement("banana");
	t->addElement("citrus");
	t->addElement("cork");
	cout << "RESULT: " << t->search("apple") << endl;
	cout << "RESULT: " << t->search("bark") << endl;
	cout << "RESULT: " << t->search("banana") << endl;
	cout << "RESULT: " << t->search("cork") << endl;
	return 0;	
}*/
