//****************************************************************************************************
//
//      File:                Huffman Code.cpp
//
//      Student:             Leon Krugliakov
//
//      Assignment:          Program #5
//
//      Course Name:         Data Structures II
//
//      Course Number:       COSC 3100 - 11
//
//      Due:                 November 24, 2020
//
//
//      This program reads a list of frequencies and stocks from a file.
//		Then it proceeds to implement a Huffman Code on the list of stocks
//		and frequencies and then it displayes the result to the user.
//
//      Other files required:
//		    1.    Stock.h - contains the stock structure
//			3.	  Node.h - Contains the Node structure
//
//****************************************************************************************************

#include <iostream>
#include <limits> 
#include <fstream>
#include <string>
#include "Stock.h"
#include "Node.h"

//****************************************************************************************************

using namespace std;

//****************************************************************************************************

void printArray(int path[], int pathLen, Node<Stock>* leaf);
void printPaths(Node<Stock>* node, int path[], int pathLen, int lr);


int main()
{
	ifstream myfile;
	string name,
		symbol;
	double price,
		frequency;
	const int initialSize = 10;
	int size = 0;
	Node<Stock>* elements[initialSize];

	myfile.open("companydata.txt");
	
	if (myfile.is_open())
	{
		while (myfile >> name >> symbol >> price >> frequency)
		{
			Stock s(name, symbol, price);
			elements[size] = new Node<Stock>;
			elements[size]->info = s;
			elements[size]->frequency = frequency;
			elements[size]->left = nullptr;
			elements[size]->right = nullptr;
			size++;
		}
	}

	myfile.close();

	int index1,
		index2;
	double freq1,
		freq2;
	Node<Stock>* newNode;
	int removeIndex;

	while (size > 1)
	{
		index1 = index2 = 0;
		freq1 = freq2 = numeric_limits<double>::max();
		for (int i = 0; i < size; ++i)
		{
			if (elements[i]->frequency < freq1)
			{
				freq2 = freq1;
				freq1 = elements[i]->frequency;
				index1 = i;
			}
			else if ((elements[i]->frequency < freq2) && (i != index1))
			{
				freq2 = elements[i]->frequency;
				index2 = i;
			}
		}

		newNode = new Node<Stock>;
		newNode->left = elements[index1];
		newNode->right = elements[index2];
		newNode->frequency = freq1 + freq2;
		elements[index1] = newNode;

		for (int i = index2; i < size - 1; ++i)
		{
			elements[i] = elements[i + 1];
		}

		--size;

	}

	cout << "Display Tree:" << endl;
	Node<Stock>* rootPtr = elements[0];
	int paths[initialSize];
	printPaths(rootPtr, paths, 0, -1);

	string sentence = "1000001001000111110";

	cout << "\n\nSequence being reviewed:    ";

	for (int i = 0; i < sentence.size(); ++i) 
	{
		cout << sentence[i];
	}

	cout << endl;

	cout << "\n\nStocks that are included: " << endl;
	int i = 0;

	rootPtr = elements[0];

	while (i < sentence.size()) 
	{
		while ((rootPtr->left != nullptr) && (rootPtr->right != nullptr))
		{
			if (sentence[i] == '1') 
			{
				rootPtr = rootPtr->right;
			}
			else 
			{
				rootPtr = rootPtr->left;
			}

			++i;
		}

		cout << "  " << rootPtr->info;
		rootPtr = elements[0];
	}

	cout << endl;

	return 0;
}

//****************************************************************************************************

void printArray(int path[], int pathLen, Node<Stock>* leaf)
{
	cout << leaf->info << " ";

	for (int i = 1; i < pathLen; i++)
	{
		cout << path[i] << " ";
	}

	cout << endl;
}

//****************************************************************************************************

void printPaths(Node<Stock>* node, int path[], int pathLen, int lr)
{
	if (node != nullptr)
	{
		if (lr != -1)
		{
			path[pathLen] = lr;
			++pathLen;
		}
		if ((node->left == nullptr) && (node->right == nullptr))
		{
			printArray(path, pathLen, node);
		}
		else
		{
			printPaths(node->left, path, pathLen, 0);
			printPaths(node->right, path, pathLen, 1);
		}
	}
}

//****************************************************************************************************

/*
Display Tree:
Company Name: Adobe
Symbol:ADBE
Price:495.78
 0
Company Name: Facebook
Symbol:FB
Price:293.58
 1 0 0
Company Name: Coca-Cola
Symbol:KO
Price:49.66
 1 0 1
Company Name: Nike
Symbol:NKE
Price:129.13
 1 1
Company Name: Google
Symbol:GOOG
Price:1769.03
 0
Company Name: Intel
Symbol:INTC
Price:45.45
 1 0
Company Name: Amazon
Symbol:AMZN
Price:3309.75
 1 1 0
Company Name: Microsoft
Symbol:MSFT
Price:223.93
 1 1 1 0 0
Company Name: McDonalds
Symbol:MCD
Price:216.24
 1 1 1 0 1
Company Name: Apple
Symbol:AAPL
Price:118.86
 1 1 1 1


Sequence being reviewed:    1000001001000111110


Stocks that are included:
  Company Name: Google
Symbol:GOOG
Price:1769.03
  Company Name: Adobe
Symbol:ADBE
Price:495.78
  Company Name: Adobe
Symbol:ADBE
Price:495.78
  Company Name: Google
Symbol:GOOG
Price:1769.03
  Company Name: Facebook
Symbol:FB
Price:293.58
  Company Name: Nike
Symbol:NKE
Price:129.13
  Company Name: Amazon
Symbol:AMZN
Price:3309.75
*/