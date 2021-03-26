#pragma once
#include<iostream>
#include<string>
#include "Node.h"

using namespace std;
class List
{
public:
	Node* head = NULL;
	Node* tail = NULL;

	void insertAtBeginning(int value);
	void insertAtEnd(int value);

	void deleteFromBeginning();
	void deleteFromEnd();
};

