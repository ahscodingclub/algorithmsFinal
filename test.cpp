#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <time.h>
#include "trees/BTree.h"
#include "trees/Trie.h"
#include "sha256.cpp"
#include "sha256.h"
#include "hashes/linkedListHashTable.h"
#include "hashes/linearProbingHashTable.h"

using namespace std;

int size;
vector<string> data;
SHA256 hasher;
clock_t t1, t2;
float linkedListHashTableAverageAddTime;
float linkedListHashTableAverageSearchTime;
float linearProbingHashTableAverageAddTime;
float linearProbingHashTableAverageSearchTime;
float BTreeAverageAddTime;
float BTreeAverageSearchTime;
float TrieAverageAddTime;
float TrieAverageSearchTime;

void testLinkedListHashTable()
{
	linkedListHashTable<SHA256> *hashTable;
	t1 = clock();
	int count;
	for(int i=0;i<10;i++)
	{
		hashTable = new linkedListHashTable<SHA256>(size, hasher);
		count = 0;
		while(count < data.size())
		{
			cout << "adding " << data[count] << " to linkedListHashTable" << endl;
			hashTable->addElement(data[count], "definition");
			count++;
		}
	}
	t2 = clock();
	linkedListHashTableAverageAddTime = (((float)t2 - (float)t1)/size)/(CLOCKS_PER_SEC*10);
	//now accesing all elements
	t1 = clock();
	for(int i=0;i<10;i++)
	{
		count = 0;
		while(count < data.size())
		{
			cout << "searching for " << data[count] << " in linkedListHashTable" << endl;
			hashTable->search(data[count]);
			count++;
		}
	} 
	t2 = clock();
	linkedListHashTableAverageSearchTime = (((float)t2-(float)t1)/size)/(CLOCKS_PER_SEC*10);
}

void testLinearProbingHashTable()
{
	linearProbingHashTable<SHA256> *hashTable;
	t1 = clock();
	int count;
	for(int i=0;i<10;i++)
	{
		count = 0;
		hashTable = new linearProbingHashTable<SHA256>(size, hasher);
		while(count < data.size())
		{
			cout << "adding " << data[count] << " to linearProbingHashTable" << endl;
			hashTable->addElement(data[count], "definition");
			count++;
		}
	}
	t2 = clock();
	linearProbingHashTableAverageAddTime = (((float)t2-(float)t1)/size)/(CLOCKS_PER_SEC*10);
	//now accesing all elements
	t1 = clock();
	for(int i=0;i<10;i++)
	{
		count = 0;
		while(count < data.size())
		{
			cout << "searching for " << data[count] << " in linearProbingHashTable" << endl;
			hashTable->search(data[count]);
			count++;
		}
	} 
	t2 = clock();
	linearProbingHashTableAverageSearchTime = (((float)t2-(float)t1)/size)/(CLOCKS_PER_SEC*10);
}

void testBTree()
{
	BTree *tree;
	t1 = clock();
	int count;
	for(int i=0;i<10;i++)
	{
		count = 0;
		tree = new BTree(3);
		while(count < data.size())
		{
			cout << "adding " << data[count] << " to BTree" << endl;
			tree->addElement(data[count]);
			count++;
		}
		t2 = clock();
		BTreeAverageAddTime = (((float)t2-(float)t1)/size)/(CLOCKS_PER_SEC*10);
	}
	//now accesing all elements
	t1 = clock();
	for(int i=0;i<10;i++)
	{
		count = 0;
		while(count < data.size()-5)
		{
			cout << "searching for " << data[count] << " in BTree" << endl;
			if(tree->search(data[count])!=NULL)
			{
				count++;	
			}
		}
	} 
	t2 = clock();
	BTreeAverageSearchTime = (((float)t2-(float)t1)/size)/(CLOCKS_PER_SEC*10);
}

void testTrie()
{
	int count = 0;
	Trie *tree;
	t1 = clock();
	for(int i=0;i<10;i++)
	{
		count = 0;
		tree = new Trie();
		while(count < data.size())
		{ 
			cout << "adding " << data[count] << " to Trie" << endl;
			tree->addElement(data[count]);
			count++;
		}
	}
	t2 = clock();
	TrieAverageAddTime = (((float)t2-(float)t1)/size)/(CLOCKS_PER_SEC*10);	
	//now accesing all elements
	t1 = clock();
	for(int i=0;i<10;i++)
	{
		count = 0;
		while(count < data.size())
		{	
			cout << "searching for " << data[count] << " in Trie" << endl;
			count++;
		}
	} 
	t2 = clock();
	TrieAverageSearchTime = (((float)t2-(float)t1)/size)/(CLOCKS_PER_SEC*10);
}

int main()
{	
	size = 0;
	string line;
	ifstream fin;
	fin.open("dictionary.txt");
	while(getline(fin, line))
	{
		size++;
		data.push_back(line);
		cout << "adding: " << line << " to data list" << endl;
	}
	cout << "the size is: " << size << " lines" << endl;
	testLinkedListHashTable();
	testLinearProbingHashTable();
	testBTree();
	testTrie();
	cout << fixed << setprecision(10) << "Average add time for linkedListHashTable is: " << linkedListHashTableAverageAddTime*100 << " milliseconds" << endl;
	cout << fixed << setprecision(10) <<  "Average search time for linkedListHashTable is: " << linkedListHashTableAverageSearchTime*100 << " milliseconds" << endl;
	cout << fixed << setprecision(10) <<  "Average add time for linearProbingHashTable is: " << linearProbingHashTableAverageAddTime*100 << " milliseconds" << endl;
	cout << fixed << setprecision(10) <<  "Average search time for linearProbingHashTable is: " << linearProbingHashTableAverageSearchTime*100 << " milliseconds" << endl;
	cout << fixed << setprecision(10) <<  "Average add time for BTree is: " << BTreeAverageAddTime*100 << " milliseconds" << endl;
	cout << fixed << setprecision(10) <<  "Average search time for BTree is: " << BTreeAverageSearchTime*100 << " milliseconds" << endl;	
	cout << fixed << setprecision(10) <<  "Average add time for Trie is: " << TrieAverageAddTime*100 << " milliseconds" << endl;
	cout << fixed << setprecision(10) <<  "Average search time for Trie is: " << TrieAverageSearchTime*100 << " milliseconds" << endl;
	
	return 0;	
}
