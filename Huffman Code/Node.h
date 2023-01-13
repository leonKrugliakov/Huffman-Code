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
//			3.	  Huffman Code.cpp - Contains the main function
//
//****************************************************************************************************

#ifndef NODE_H
#define NODE_H

//****************************************************************************************************

template <typename T>
struct Node
{
	T info;
	double frequency;
	Node<T>* left;
	Node<T>* right;
};

//****************************************************************************************************

#endif NODE_H