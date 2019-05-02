#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;
template<class T>
class BTree
{
	struct Node
	{
		Node* left;
		Node* right;
		T data;
		Node(){}
		Node(T val) :data(val), left(NULL), right(NULL) {
			left = NULL;
			right = NULL;
			data = val;
		}
	};
	Node* root;
public:
	BTree()
	{
		root = NULL;
	}
	~BTree() {
		Destroy(root);
	}
	bool isEmpty() const { return root == NULL; }
	void Add(T);
	void Remove(T);
	bool Search(T);
	void Destroy(Node*);
	void MakeEmpty();
	void Show();
	void Order(Node*);
	template<class T> friend ostream	&operator << (ostream &out, BTree <T>*node);
};

template<class T>
void BTree<T>::Show()
{
	Order(root);
}

template<class T>
void BTree<T>::MakeEmpty()
{
	Destroy(root);
}

template<class T>
void BTree<T>::Order(Node* p)
{
	if (p != NULL)
	{
		cout << " " << p->data << " ";
		if (p->right) Order(p->right);
		if (p->left) Order(p->left);
	}
	else 
		cout << " Tree is empty!";
}

template <class T>
void BTree<T>::Destroy(Node *node)
{
	if (node == nullptr)
		cout << " Tree is empty!\n";
		return;
	Destroy(node->left);
	Destroy(node->right);
	delete node;
}


template <class T> ostream &operator<<(ostream &out, BTree <T>*node) {
	
	out << " Value: " << node.data;
	//if (node.parent) output << " parent: " << node.parent->data;
	if (node->left) out << " Left: " << node.left->data;
	if (node->right) out << " Right: " << node.right->data;
	out << "\n";
	return out;
}

template <class T>
void BTree<T>::Add(T d)
{
	Node* t = new Node;
	Node* parent;
	t->data = d;
	t->left = NULL;
	t->right = NULL;
	parent = NULL;
	// is this a new tree?
	if (isEmpty()) root = t;
	else
	{
		//Note: ALL insertions are as leaf nodes
		Node* curr;
		curr = root;
		// Find the Node's parent
		while (curr)
		{
			parent = curr;
			if (t->data > curr->data) curr = curr->right;
			else curr = curr->left;
		}

		if (t->data < parent->data)
			parent->left = t;
		else
			parent->right = t;
	}
}

template <class T>
bool BTree<T>::Search(T d)
{
	//Locate the element
	bool found = false;
	if (isEmpty())
	{
		cout << " This Tree is empty! " << endl;
		return false;
	}
	Node* curr;
	Node* parent;
	curr = root;
	parent = (Node*)NULL;
	while (curr != NULL)
	{
		if (curr->data == d)
		{
			found = true;
			break;
		}
		else
		{
			parent = curr;
			if (d>curr->data) curr = curr->right;
			else curr = curr->left;
		}
	}
	if (!found)
	{
		cout << " Element not found! " << endl;
	}
	else
	{
		cout << " Element found! " << endl;
	}

	return found;
}

template <class T>
void BTree<T>::Remove(T d)
{
	bool found = false;
	if (isEmpty())
	{
		cout << " Tree is empty! " << endl;
		return;
	}
	Node* curr;
	Node* parent;
	curr = root;
	parent = (Node*)NULL;
	while (curr != NULL)
	{
		if (curr->data == d)
		{
			found = true;
			break;
		}
		else
		{
			parent = curr;
			if (d>curr->data) curr = curr->right;
			else curr = curr->left;
		}
	}
	if (!found)
	{
		cout << " Element not found! " << endl;
		return;
	}

	// Node with single child
	if ((curr->left == NULL && curr->right != NULL) || (curr->left != NULL
		&& curr->right == NULL))
	{
		if (curr->left == NULL && curr->right != NULL)
		{
			if (parent->left == curr)
			{
				parent->left = curr->right;
				delete curr;
			}
			else
			{
				parent->right = curr->right;
				delete curr;
			}
		}
		else // left child present, no right child
		{
			if (parent->left == curr)
			{
				parent->left = curr->left;
				delete curr;
			}
			else
			{
				parent->right = curr->left;
				delete curr;
			}
		}
		return;
	}

	//We're looking at a leaf node
	if (curr->left == NULL && curr->right == NULL)
	{
		if (parent == NULL)
		{
			delete curr;

		}
		else
			if (parent->left == curr) parent->left = NULL;
			else parent->right = NULL;
			delete curr;
			return;
	}


	//Node with 2 children
	// replace node with smallest value in right subtree
	if (curr->left != NULL && curr->right != NULL)
	{
		Node* chkr;
		chkr = curr->right;
		if ((chkr->left == NULL) && (chkr->right == NULL))
		{
			curr = chkr;
			delete chkr;
			curr->right = NULL;
		}
		else // right child has children
		{
			//if the node's right child has a left child
			// Move all the way down left to locate smallest element

			if ((curr->right)->left != NULL)
			{
				Node* lcurr;
				Node* lcurrp;
				lcurrp = curr->right;
				lcurr = (curr->right)->left;
				while (lcurr->left != NULL)
				{
					lcurrp = lcurr;
					lcurr = lcurr->left;
				}
				curr->data = lcurr->data;
				delete lcurr;
				lcurrp->left = NULL;
			}
			else
			{
				Node* tmp;
				tmp = curr->right;
				curr->data = tmp->data;
				curr->right = tmp->right;
				delete tmp;
			}

		}
		return;
	}

}


