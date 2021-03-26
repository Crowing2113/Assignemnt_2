#include <chrono>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "List.h"

using namespace std;
//Declaring functions
void printVector(vector<int> arr, int size);
void bubbleSort(vector<int>& arr, int size, int order);
void merge(vector<int>& arr, vector<int>& left, vector<int>& right, int order);
void mergeSort(vector<int>& arr, int order);
void questionOne();
void questionTwo();

void main() {
	questionOne();
	questionTwo();
	system("pause");
}

//Question one of assessment 2
void questionOne() {
	int sortingOrder;
	int sortingComplexity;
	int numberOfNumbers;
	vector<int> numbersToSort;
	chrono::steady_clock::time_point begin, end;
	//opening input file.
	ifstream readFile;
	readFile.open("input-a1q1.txt");
	//sets the sorting order, if number is not 0 or 1 will return an error
	readFile >> sortingOrder;
	if (sortingOrder != 0 && sortingOrder != 1) {
		cout << "ERROR--First number MUST be 0 or 1--";
		return;
	}
	//checks which sorting algorithm to use, if number is not 0 or 1 will return an error
	readFile >> sortingComplexity;
	if (sortingComplexity != 0 && sortingComplexity != 1) {
		cout << "ERROR--Second number MUST be 0 or 1--";
		return;
	}
	//number of numbers to sort in the array, if the number is negative return an error
	readFile >> numberOfNumbers;
	if (numberOfNumbers < 0) {
		cout << "ERROR--Third number cannot be negative" << endl;
		return;
	}
	//adding all the numbers into the vector and checking that there aren't less numbers than specified
	for (int i = 1; i <= numberOfNumbers; i++)
	{
		if (readFile.eof()) {
			cout << "ERROR--Run out of numbers, please adjust size of numbers or add more numbers" << endl;
			return;
		}
		int temp;
		readFile >> temp;
		numbersToSort.push_back(temp);
	}
	readFile.close();
	//checking which sort to use depending on complexity
	begin = chrono::steady_clock::now();
	cout << "sorting order : " << sortingOrder << endl;
	switch (sortingComplexity) {
	case 0:
		bubbleSort(numbersToSort, numberOfNumbers, sortingOrder);
		cout << "BUBBLE" << endl;
		break;
	case 1:
		mergeSort(numbersToSort, sortingOrder);
		cout << "MERGE" << endl;
		break;
	}
	end = chrono::steady_clock::now();
	chrono::duration<float, milli> timeDifference = end - begin;
	//float timeDifference = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	cout << timeDifference.count() << endl;
	//write sorted array to file
	ofstream writeFile;
	writeFile.open("output-a1q1.txt");
	writeFile << timeDifference.count() << "[ms]" << endl;
	for (int i = 0; i < numberOfNumbers; i++) {
		writeFile << numbersToSort[i] << " ";
	}
	writeFile.close();
}

//Question two of assessment 2
void questionTwo() {
	int maxRand = 500; //the high limit for the random numbers
	int numbersToGenerate;
	//Initialize a random seed
	srand(time(NULL));
	//creating the 2 lists
	List list1;
	List list2;
	//creating the begin and end variables to record time.
	//Creating the time difference varaiables for each function
	chrono::steady_clock::time_point begin, end;
	chrono::duration<float, milli> timeInsertAtBeginning, timeInsertAtEnd, timeDeleteAtBeginning, timeDeleteAtEnd;

	ifstream readFile;
	readFile.open("input-a1q2.txt");
	readFile >> numbersToGenerate;
	readFile.close();
	//if the numbers to generate is 0 or negative then return
	if (numbersToGenerate <= 0) {
		cout << "Please use a number greater than 0 for generating numbers" << endl;
		return;
	}
	//insert at beginning loop
	begin = chrono::steady_clock::now();
	for (int i = 0; i < numbersToGenerate; i++) {
		int randNum = rand() % maxRand;
		list1.insertAtBeginning(randNum);
	}
	end = chrono::steady_clock::now();
	cout << endl;
	timeInsertAtBeginning = end - begin;
	//insert at end loop
	begin = chrono::steady_clock::now();
	for (int j = 0; j <= numbersToGenerate; j++) {
		int randNum = rand() % maxRand;
		list2.insertAtEnd(randNum);
		//cout << j << " - Inserted " << randNum << " to the end of the list." << endl;
	}
	end = chrono::steady_clock::now();
	timeInsertAtEnd = end - begin;
	//delete from beginning
	begin = chrono::steady_clock::now();
	while (list1.head != NULL) {
		list1.deleteFromBeginning();
	}
	end = chrono::steady_clock::now();
	timeDeleteAtBeginning = end - begin;
	cout << endl;
	//delete from end
	begin = chrono::steady_clock::now();
	int counter = 0;
	while (list2.head != NULL) {
		list2.deleteFromEnd();
		counter++;
	}	end = chrono::steady_clock::now();
	timeDeleteAtEnd = end - begin;
	ofstream writeFile;
	writeFile.open("output-a1q2.txt");
	//write all the times into the file
	writeFile << timeInsertAtBeginning.count() << "[ms]" << endl
		<< timeInsertAtEnd.count() << "[ms]" << endl
		<< timeDeleteAtBeginning.count() << "[ms]" << endl
		<< timeDeleteAtEnd.count() << "[ms]" << endl;
	writeFile.close();
}
//prints vector
//mostly for 
void printVector(vector<int> arr, int size) {
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

//Bubble sort for partially sorted numbers
void bubbleSort(vector<int>& arr, int size, int order) {
	bool sorted = false;
	int lastUnsorted = size - 1; //storing array size-1 in a variable
	while (!sorted) {
		sorted = true;
		for (int i = 0; i < lastUnsorted; i++) {
			//check to see if sorting in ascending or descending
			if (order == 0) { //ascending
				if (arr[i] > arr[i + 1]) {
					swap(arr[i], arr[i + 1]);
					sorted = false;
				}
			}
			else if (order == 1) { //descending
				if (arr[i] < arr[i + 1]) {
					swap(arr[i], arr[i + 1]);
					sorted = false;
				}
			}
		}
		lastUnsorted--;
	}
	cout << "sorted" << endl;
}

//Merges 2 vectors into 1
void merge(vector<int>& left, vector<int>& right, vector<int>& arr, int order) {
	//create indexes for each vector
	int arrIndex = 0;
	int leftIndex = 0;
	int rightIndex = 0;
	//keeps looping until the left or right side indexes have reached the end of their respective vector
	while (leftIndex < left.size() && rightIndex < right.size()) {
		//checks for the order to be sorted
		if (order == 0) { //0 for ascending sorting order
			if (left[leftIndex] < right[rightIndex]) {
				arr[arrIndex++] = left[leftIndex++];
			}
			else {
				arr[arrIndex++] = right[rightIndex++];
			}
		}
		else if (order == 1) { //1 for descending sorting order
			if (left[leftIndex] > right[rightIndex]) {
				arr[arrIndex++] = left[leftIndex++];
			}
			else {
				arr[arrIndex++] = right[rightIndex++];
			}
		}
	}
	//if there's any elements in the left or right vector that haven't been merge, add them
	while (leftIndex < left.size()) {
		arr[arrIndex++] = left[leftIndex++];
	}
	while (rightIndex < right.size()) {
		arr[arrIndex++] = right[rightIndex++];
	}
}

//Merge sort for unsorted numbers
void mergeSort(vector<int>& arr, int order) {
	if (arr.size() <= 1) //retun if the vector has either 0 or 1 element
		return;
	//create 2 vectors for the left and right side
	vector<int> leftSide;
	vector<int> rightSide;
	int middle = arr.size() / 2; //calculate where to chop the vector in 2
	//inserting the left and right side numbers into their own vectors that we created earlier
	for (int i = 0; i < middle; i++) {
		leftSide.push_back(arr[i]);
	}
	for (int j = middle; j < arr.size(); j++) {
		rightSide.push_back(arr[j]);
	}
	mergeSort(leftSide, order);
	mergeSort(rightSide, order);
	merge(leftSide, rightSide, arr, order); // this merges the left and right side vectors into the original vector
}