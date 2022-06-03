#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation
	this->current = nullptr;
	for (int i = 0; i < this->map.cap; i++)
	{
		Node* prev = this->current;
		Node* currentIterated = this->map.table[i];
		Node* headList = nullptr;
		Node* list = nullptr;

		while (this->current != nullptr && currentIterated != nullptr)
		{
			Node* newNode = new Node;
			delete[] newNode->values;

			if (this->map.relation(this->current->key, currentIterated->key))
			{
				newNode->key = this->current->key;
				newNode->values = this->current->values;
				newNode->length = this->current->length;
				newNode->cap = this->current->cap;
				this->current = this->current->next;
			}
			else
			{
				newNode->key = currentIterated->key;
				newNode->values = currentIterated->values;
				newNode->length = currentIterated->length;
				newNode->cap = currentIterated->cap;
				currentIterated = currentIterated->next;
			}

			if (list == nullptr)
			{
				list = newNode;
				headList = newNode;
			}
			else
			{
				list->next = newNode;
				list = list->next;
			}
		}

		while (this->current != nullptr)
		{
			Node* newNode = new Node;
			delete[] newNode->values;

			newNode->key = this->current->key;
			newNode->values = this->current->values;
			newNode->length = this->current->length;
			newNode->cap = this->current->cap;
			this->current = this->current->next;

			if (list == nullptr)
			{
				list = newNode;
				headList = newNode;
			}
			else
			{
				list->next = newNode;
				list = list->next;
			}
		}

		while (currentIterated != nullptr)
		{
			Node* newNode = new Node;
			delete[] newNode->values;

			newNode->key = currentIterated->key;
			newNode->values = currentIterated->values;
			newNode->length = currentIterated->length;
			newNode->cap = currentIterated->cap;
			currentIterated = currentIterated->next;


			if (list == nullptr)
			{
				list = newNode;
				headList = newNode;
			}
			else
			{
				list->next = newNode;
				list = list->next;
			}
		}
		this->current = headList;

		while (prev != nullptr)
		{
			Node* next = prev->next;
			delete prev;
			prev = next;
		}
	}

	this->head = this->current;
	this->pos = 0;

}

void SMMIterator::first(){
	//TODO - Implementation
	this->current = this->head;
	this->pos = 0;
}

void SMMIterator::next(){
	//TODO - Implementation
	if (this->current == nullptr)
		throw std::exception();

	if (this->pos + 1 == this->current->length) {
		this->current = this->current->next;
		this->pos = 0;
	}

	else
		this->pos++;
}//theta(1)

bool SMMIterator::valid() const{
	//TODO - Implementation
	return this->current != nullptr;
}//theta(1)

TElem SMMIterator::getCurrent() const{
	//TODO - Implementation
	if (this->current == nullptr)
		throw std::exception();

	return make_pair(this->current->key, this->current->values[this->pos]);
}// theta(1)


