#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->length = 0;
	this->cap = 1;

	// if the load factor of the table after an insertion is greater than 
	// or equal to 0.7, we double the size of the table
	this->loadFactor = 0.7;

	this->table = new Node* [this->cap];
	for (int index = 0; index < this->cap; index++)
		this->table[index] = nullptr;

	this->relation = r;
}//Theta(1)

int SortedMultiMap::hash(int key) const
{	
	if (key < 0)
		key = this->cap + key % this->cap;
	return key % this->cap;
}//Theta(1)

void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	int pos = this->hash(c);
	
	Node* node = this->table[pos];
	Node* prev = nullptr;

	while (node != nullptr)
	{
		if (node->key == c)
		{
			//resize
			if (node->cap == node->length)
			{
				node->cap *= 2;
				TValue* aux = new TValue[node->cap];

				for (int i = 0; i < node->length; i++)
					aux[i] = node->values[i];
				
				delete[] node->values;
				node->values = aux;
			}
			//add the value
			node->values[node->length] = v;
			node->length++;
			this->length++;
			break;
		}
		// if the key is not in the singly linked list for this position in the table, 
		// keep track of the position of the node where it should be added
		if (node->key != c && !this->relation(c, node->key))
				prev = node;

		node = node->next;
	}

	//if no node was found with the searched key
	if (node == nullptr)
	{
		//resize hashtable

		if (this->loadFactor <= double(this->length + 1) / this->cap)
		{
			this->cap *= 2;
			Node** auxTable = new Node * [this->cap];

			for (int i = 0; i < this->cap; i++)
				auxTable[i] = nullptr;

			for (int i = 0; i < this->cap / 2; i++)
			{
				Node* current = this->table[i];
				while (current != nullptr)
				{
					int auxPos = this->hash(current->key);
					Node* next = current->next;
					current->next = auxTable[auxPos];
					auxTable[auxPos] = current;
					current = next;
				}
			}
			delete[] this->table;
			this->table = auxTable;
			// recalculates the hash for the key to be added after resizing the table
			pos = this->hash(c);
		}

		Node* newNode = new Node;
		newNode->length = 1;
		newNode->key = c;
		newNode->values[0] = v;

		//if the node should be added first
		if (prev == nullptr)
		{
			newNode->next = this->table[pos];
			this->table[pos] = newNode;
		}
		//anywhere else
		else
		{
			newNode->next = prev->next;
			prev->next = newNode;
		}
		this->length++;
	}
}// WC: theta(n); AC: theta(1); BC: theta(1); Total: O(n) time complexity (where n<-number of values with key=c)

vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	vector<TValue> values;
	int pos = this->hash(c);
	Node* node = this->table[pos];

	while (node != nullptr)
	{
		if (node->key == c) 
		{
			for (int i = 0; i < node->length; i++)
				values.push_back(node->values[i]);

			break;
		}	
		node = node->next;
	}

	return values;
}//theta(n) (where n<-number of values with key=c)

bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	int pos = this->hash(c);
	Node* node = this->table[pos];
	Node* prev = nullptr;

	while (node != nullptr)
	{	
		//found the node with the given key in the corresponding singly linked list from the hash table
		if (node->key == c)
		{
			bool removed = false;
			for (int i = 0; i < node->length; i++)
			{
				//found the value for which we are searching, for the corresponding key
				if (node->values[i] == v)
				{
					for (int j = i; j < node->length - 1; j++)
						node->values[j] = node->values[j + 1];

					node->length--;
					this->length--;
					removed = true;
					break;
				}
			}

			if (node->length == 0)
			{
				delete[]node->values;
				
				//remove it if it is the first in the list
				if (prev == nullptr)
				{
					this->table[pos] = node->next;
					delete node;
				}
				else
				{
					Node* next = node->next;
					prev->next = next;
					delete node;
				}
			}
			return removed;
		}
		prev = node;
		node = node->next;
	}

    return false;
}//WC: theta(n); AC: theta(1); BC: theta(1); Total: O(n) time complexity (where n<-number of different keys pairs)


int SortedMultiMap::size() const {
	//TODO - Implementation
	return this->length;
}//Theta(1)

bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	if (this->length == 0)
		return true;
	return false;
}//Theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}//O(tableCap*nrKeyValuePairs)


void SortedMultiMap::replace(TKey k, TValue oldVal, TValue newVal)
{
	int pos = this->hash(k);
	Node* node = this->table[pos];
	while (node != nullptr)
	{
		for (int i = 0; i < node->length; i++)
			if (node->values[i] == oldVal)
				node->values[i] = newVal;

		node = node->next;
	}
}


SortedMultiMap::~SortedMultiMap() 
{
	//TODO - Implementation
	for (int index = 0; index < this->cap; index++) {

		Node* node = this->table[index];
		Node* next = this->table[index];

		while (node != nullptr) {
			// delete all the values from each node
			delete[] node->values;

			// delete all nodes from each position in the hashtable
			next = next->next;
			delete node;

			node = next;
		}
	}

	// delete the pointer of the hashtable
	delete[] this->table;

}// theta(n)

Node::Node()
{
	this->key = 0;
	this->length = 0;
	this->cap = 1;
	this->values = new TValue[this->cap];
	this->next = nullptr;
}
