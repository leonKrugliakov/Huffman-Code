//****************************************************************************************************
//
//      File:                Stock.h
//
//      Student:             Leon Krugliakov
//
//      Assignment:          Program #3
//
//      Course Name:         Data Structures II
//
//      Course Number:       COSC 3100 - 11
//
//      Due:                 November 10, 2020
//
//
//      This program creates a tree with random items and tests out the different
//		functions in the binary tree class. Then it imports a list of 20 stocks
//		from a file into a binary tree. Then, it gives the user the option to
//		search for a stock by it's symbol to find either the price or the name
//		of the stock. It also allows the user to insert another stock into the
//		tree. Finally, it allows the user to quit the program.
//
//      Other files required:
//		    1.    BinarySearchTree.cpp - contains the main function
//			2.	  Stock. - Contains the Stock structure
//			3.	  Node.h - Contains the Node structure
//
//****************************************************************************************************

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

//****************************************************************************************************

#include <algorithm> 
#include "Node.h"

//****************************************************************************************************

template <typename T>
class BinarySearchTree
{
private:
	Node<T>* root;
	int height(Node<T>* r) const;
	void destroy(Node<T>*& r);
	void insert(Node<T>*& r, const T& item);
	T* search(Node<T>* r, const T& item) const;
	void inorder(Node<T>* r, std::ostream& os) const;
	void preorder(Node<T>* r, std::ostream& os) const;
	void postorder(Node<T>* r, std::ostream& os) const;
	void searchD(const T& item, bool& found, Node<T>*& locPtr, Node<T>*& parent) const;
public:
	BinarySearchTree();
	~BinarySearchTree();
	void destory();
	void insert(const T& item);
	void inorder(std::ostream& os = std::cout) const;
	void preorder(std::ostream& os = std::cout) const;
	void postorder(std::ostream& os = std::cout) const;
	T* search(const T& item) const;
	int height() const;
	int max(int a, int b) const;
	void deleteNode(const T& item);
};

//****************************************************************************************************

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = nullptr;
}

//****************************************************************************************************

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	destroy(root);
}

//****************************************************************************************************

template <typename T>
int BinarySearchTree<T>::max(int a, int b) const
{
	return (a > b) ? a : b;
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::destory()
{
	destroy(root);
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::destroy(Node<T>*& r)
{
	if (r != nullptr)
	{
		destroy(r->left);
		destroy(r->right);
		delete r;
		r = nullptr;
	}
}

//****************************************************************************************************

template <typename T>
int BinarySearchTree<T>::height() const
{
	return height(root);
}

//****************************************************************************************************

template <typename T>
int BinarySearchTree<T>::height(Node<T>* r) const
{
	int result;

	if (r == nullptr)
	{
		result = 0;
	}
	else
	{
		result = 1 + max(height(r->left), height(r->right));
	}

	return result;
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::insert(const T& item)
{
	insert(root, item);
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::insert(Node<T>*& r, const T& item)
{
	using namespace std;
	if (r == nullptr)
	{
		r = new Node<T>;
		r->info = item;
		r->left = nullptr;
		r->right = nullptr;
	}
	else if (item < r->info)
	{
		insert(r->left, item);
	}
	else if (item > r->info)
	{
		insert(r->right, item);
	}
	else
	{
		cout << "The node already exists!" << endl;
	}
}

//****************************************************************************************************

template <typename T>
T* BinarySearchTree<T>::search(const T& item) const
{
	return search(root, item);
}

//****************************************************************************************************

template <typename T>
T* BinarySearchTree<T>::search(Node<T>* r, const T& item) const
{
	using namespace std;

	T* result;

	if (r == nullptr)
	{
		result = nullptr;
	}
	else if (item < r->info)
	{
		result = search(r->left, item);
	}
	else if (item > r->info)
	{
		result = search(r->right, item);
	}
	else
	{
		result = new T(r->info);
	}

	return result;
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::inorder(std::ostream& os) const
{
	inorder(root, os);
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::inorder(Node<T>* r, std::ostream& os) const
{
	using namespace std;

	if (r != nullptr)
	{
		inorder(r->left, os);
		os << r->info << endl;
		inorder(r->right, os);
	}
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::preorder(std::ostream& os) const
{
	preorder(root, os);
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::preorder(Node<T>* r, std::ostream& os) const
{
	using namespace std;

	if (r != nullptr)
	{
		os << r->info << endl;
		preorder(r->left, os);
		preorder(r->right, os);
	}
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::postorder(std::ostream& os) const
{
	postorder(root, os);
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::postorder(Node<T>* r, std::ostream& os) const
{
	using namespace std;

	if (r != nullptr)
	{
		postorder(r->left, os);
		postorder(r->right, os);
		os << r->info << endl;
	}
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::searchD(const T& item, bool& found, Node<T>*& locPtr, Node<T>*& parent) const
{
	using namespace std;

	locPtr = root;
	parent = nullptr;
	found = false;

	while (!found && locPtr != nullptr)
	{
		//cout << (item > locPtr->info) << endl;

		if (item < locPtr->info)
		{
			//cout << "Inside less then" << endl;
			//cout << "Parent: " << parent->info << endl;
			//cout << "Current: " << locPtr->info << endl << endl;
			parent = locPtr;
			locPtr = locPtr->left;
		}
		else if (item > locPtr->info)
		{
			//cout << "Inside greater then" << endl;
			//cout << "Parent: " << parent->info << endl;
			//cout << "Current: " << locPtr->info << endl << endl;
			parent = locPtr;
			locPtr = locPtr->right;
		}
		else
		{
			//cout << "Inside else" << endl;
			//cout << "Parent: " << parent->info << endl;
			//cout << "Current: " << locPtr->info << endl << endl;
			found = true;
		}
	}
}

//****************************************************************************************************

template <typename T>
void BinarySearchTree<T>::deleteNode(const T& item)
{
	using namespace std;

	bool found;
	Node<T>* current;
	Node<T>* parent;
	searchD(item, found, current, parent);

	if (!found)
	{
		cout << "Item not in tree" << endl;
	}
	else if ((current->left != nullptr) && (current->right != nullptr))
	{
		Node<T>* currentSucc = current->right;
		parent = current;

		while (currentSucc->left != nullptr)
		{
			parent = currentSucc;
			currentSucc = currentSucc->left;
		}

		current->info = currentSucc->info;
		current = currentSucc;
	}
	Node<T>* subtree = current->left;

	if (subtree == nullptr)
	{
		subtree = current->right;
	}

	if (parent == nullptr)
	{
		root = subtree;
	}
	else if (parent->left == current)
	{
		parent->left = subtree;
	}
	else
	{
		parent->right = subtree;
	}

	delete current;

}


//****************************************************************************************************

#endif BIANRYSEARCHTREE_H