#include "List.h"

void List::insertAtBeginning(int value)
{
	Node* newNode = new Node(value);
	newNode->next = head;
	head = newNode;
}

void List::insertAtEnd(int value)
{
	if (head == NULL) {//if the list is emppty then inserAtBeginning
		insertAtBeginning(value);
		return;
	}
	Node* newNode = new Node(value);
	Node* iterator = head; // iterator used to find the tail of the list
	while (iterator->next != NULL) {//moves through the list until it reaches a node who's next points to NULL
		iterator = iterator->next;
	}
	if (iterator->next == NULL) { // if the iterator is at the end set the next pointer to the new Node
		iterator->next = newNode;
	}
}

void List::deleteFromBeginning()
{
	if (head == NULL) // if the list is empty do nothing and exit the function
		return;
	Node* iterator = head; //points to the beginning to delte that node
	//if (head->next != NULL)
		head = head->next; //sets the head's pointer to the next node to create a new head
	delete iterator; // deletes the old head
}

void List::deleteFromEnd()
{
	if (head == NULL) // exit the function if the list is empty
		return;
	if (head->next == NULL) {
		delete head; // deletes the node
		head = NULL; // sets head to null
		return;
	}
	//2 node pointers that point to the head
	Node* iterator = head; 
	Node* previous = head;
	while (iterator->next != NULL) {
		//set previous to the current iterator's pointer
		//then set the iterator to point to the next node
		previous = iterator;
		iterator = iterator->next;
	}
	//double checking that the iterator's next points to NULL
	if (iterator->next == NULL) {
		previous->next = NULL;
		delete iterator;
	}
}
