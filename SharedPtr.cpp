#pragma once

#include <iostream>

template<typename T>
class Shared_ptr final
{
public:
	Shared_ptr(T* ptr_) : ptr(ptr_)
	{
		counter = new size_t();
		*counter = 1;
	}

	Shared_ptr(const Shared_ptr& obj) : ptr(obj.ptr), counter(obj.counter)
	{
		++(*counter);
	}

	~Shared_ptr()
	{
		cleanup();
	}

	Shared_ptr& operator=(const Shared_ptr& obj)
	{
		cleanup();
		ptr = obj.ptr;
		counter = obj.counter;
		++(*counter);
		return *this;
	}

	void cleanup()
	{
		if (--(*counter) == 0)
		{
			delete ptr;
			delete counter;
		}
	}

	T& operator*()
	{
		return *ptr;
	}

	T* operator->()
	{
		return ptr;
	}

	T* get()
	{
		return ptr;
	}

	size_t use_count()
	{
		return *counter;
	}

private:
	T* ptr;
	size_t* counter;
};

int main()
{
	

	return 0;
}
