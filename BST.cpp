#pragma once

#include <iostream>

template<typename T>
struct BSTNode
{
	BSTNode(T data_) :
		left(nullptr), right(nullptr), parent(nullptr), data(data_)
	{ }

	BSTNode<T>* left;
	BSTNode<T>* right;
	BSTNode<T>* parent;

	T data;
};

template<typename T>
class BST
{
public:
	BST() : head(nullptr), size(0), height(0) { }

	~BST()
	{
		clear(head);
	}

	void insert(T data)
	{
		auto newNode = new BSTNode<T>(data);
		if (!head)
			head = newNode;
		else
		{
			auto temp = head;
			while (!temp)
			{
				if (data < temp->data)
					temp = temp->left;
				else if (data > temp->data)
					temp = temp->right;
				else
					break;
			}
		}
	}

	void inOrderTreeWalk()
	{
		inOrderTreeWalk(head);
	}

	void clear(BSTNode<T>* node)
	{

	}

private:
	void inOrderTreeWalk(BSTNode<T>* node)
	{
		if (!node)
		{
			inOrderTreeWalk(node->left);
			std::cout << node->data << " ";
			inOrderTreeWalk(node->right);
		}
	}

private:
	BSTNode<T>* head;
	size_t size;
	size_t height;
};

int main()
{
	

	return 0;
}
