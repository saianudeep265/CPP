#pragma once

#include <iostream>

template<typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node<T>* previous;
};

template<typename T>
class LinkedList
{
public:
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	
	~LinkedList()
	{
		auto it = head;
		while (it)
		{
			auto next = it->next;
			it->previous = nullptr;
			delete it;
			it = next;
		}
	}

	void push_back(T data)
	{
		auto newNode = new Node<T>();
		newNode->data = data;
		newNode->next = nullptr;
		newNode->previous = tail;

		if (tail)
			tail->next = newNode;
		tail = newNode;
		++count;
		if (!head)
			head = tail;
	}

	void push_front(T data)
	{
		auto newNode = new Node<T>();
		newNode->data = data;
		newNode->next = head;
		newNode->previous = nullptr;

		if (head)
			head->previous = newNode;
		head = newNode;
		++count;
		if (!tail)
			tail = head;
	}

	void pop_back()
	{
		if (tail)
		{
			auto currTail = tail;
			tail = tail->previous;
			tail->next = nullptr;
			delete currTail;
			--count;
			if (!tail)
				head = nullptr;
		}
	}

	void pop_front()
	{
		if (head)
		{
			auto currHead = head;
			head = head->next;
			head->previous = nullptr;
			delete currHead;
			--count;
			if (!head)
				tail = nullptr;
		}
	}

	void insertAfter(std::size_t nodeNum, T data)
	{
		if (head)
		{
			auto it = head;
			while (nodeNum - 1 > 0)
			{
				it = it->next;
				--nodeNum;
			}

			auto newNode = new Node<T>();
			newNode->data = data;
			newNode->previous = it;
			newNode->next = it->next;

			it->next = newNode;
			++count;
		}
	}

	void reverse()
	{
		if (head)
		{
			auto next = head->next;
			tail = head;
			while (next)
			{
				auto it = head;
				head = next;
				next = head->next;

				it->previous = head;

				head->previous = nullptr;
				head->next = it;
			}
			tail->next = nullptr;
		}
	}

	void display()
	{
		for (auto it = head; it != nullptr; it = it->next)
		{
			std::cout << "Value: " << it->data << " ";
		}
		std::cout << std::endl;
	}

private:
	Node<T>* head;
	Node<T>* tail;
	std::size_t count;
};

int main()
{
	

	return 0;
}
