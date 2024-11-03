#pragma once

#include <iostream>
#include <initializer_list>
#include <queue>

template<typename T>
struct BSTNode
{
	BSTNode(T data_) :
		left(nullptr), right(nullptr), data(data_)
	{ }

	BSTNode<T>* left;
	BSTNode<T>* right;

	T data;
};

template<typename T>
class BST
{
public:
	BST() : head(nullptr), size(0), height(0) { }

	BST(std::initializer_list<T> list)
	{
		std::cout << "Constructing BST using Initializer list ctor..." << std::endl;
		for (auto elem : list)
		{
			insert(elem);
		}
		std::cout << "Constructed successfully using Initializer list ctor." << std::endl;
	}

	~BST()
	{
		std::cout << "\n\nInvoking BST Destructor... Deallocating in Pre-Order Tree walk fashion.\n";
		clear(head);
		head = nullptr;
		std::cout << "\nBST deallocation successfull!!" << std::endl;
	}

	void insert(T data)
	{
		BSTNode<T>* node = nullptr;
		auto temp = head;
		while (temp)
		{
			node = temp;
			if (data < temp->data)
				temp = temp->left;
			else if (data > temp->data)
				temp = temp->right;
			else
			{
				node = nullptr;
				break;
			}
		}

		if (head == nullptr)
		{
			head = new BSTNode<T>(data);
		}
		else if (node != nullptr)
		{
			auto newNode = new BSTNode<T>(data);
			if (data < node->data)
				node->left = newNode;
			else
				node->right = newNode;
		}
	}

	void inOrderTreeWalk()
	{
		std::cout << "\nIn-Order Tree Walk...\n";
		inOrderTreeWalk(head);
	}

	void preOrderTreeWalk()
	{
		std::cout << "\nPre-Order Tree Walk...\n";
		preOrderTreeWalk(head);
	}

	void postOrderTreeWalk()
	{
		std::cout << "\nPost-Order Tree Walk...\n";
		postOrderTreeWalk(head);
	}

	// Also known as Breadth First Search(BFS)
	void levelOrderTreeWalk()
	{
		std::cout << "\nLevel-Order Tree Walk...\n";
		levelOrderTreeWalk(head);
	}

	void clear(BSTNode<T>* node)
	{
		if (node == nullptr)
			return;

		auto left = node->left;
		auto right = node->right;
		std::cout << node->data << " ";
		delete node;
		clear(left);
		clear(right);
	}

private:
	void inOrderTreeWalk(BSTNode<T>* node)
	{
		if (node == nullptr)
			return;

		inOrderTreeWalk(node->left);
		std::cout << node->data << " ";
		inOrderTreeWalk(node->right);
	}

	void preOrderTreeWalk(BSTNode<T>* node)
	{
		if (node == nullptr)
			return;

		std::cout << node->data << " ";
		inOrderTreeWalk(node->left);
		inOrderTreeWalk(node->right);
	}

	void postOrderTreeWalk(BSTNode<T>* node)
	{
		if (node == nullptr)
			return;

		inOrderTreeWalk(node->left);
		inOrderTreeWalk(node->right);
		std::cout << node->data << " ";
	}

	void levelOrderTreeWalk(BSTNode<T>* node)
	{
		if (node == nullptr)
			return;

		std::queue<BSTNode<T>*> bstQueue;
		bstQueue.push(node);

		while (!bstQueue.empty())
		{
			auto node = bstQueue.front();
			bstQueue.pop();

			std::cout << node->data << " ";
			if (node->left != nullptr)
				bstQueue.push(node->left);
			if (node->right != nullptr)
				bstQueue.push(node->right);
		}
	}

private:
	BSTNode<T>* head;
	size_t size;
	size_t height;
};

int main()
{
	BST<int> bst{ 25, 17, 20, 30, 35, 26, 7 };

	bst.inOrderTreeWalk();
	bst.preOrderTreeWalk();
	bst.postOrderTreeWalk();
	bst.levelOrderTreeWalk();

	return 0;
}
