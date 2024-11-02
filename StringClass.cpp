#pragma once

#include <iostream>

class String 
{
	friend void swap(String& lhs, String& rhs) noexcept;
public:
	String(const char* str)
	{
		size = strlen(str);
		m_str = new char[size + 1];
		strcpy(m_str, str);
	}

	String(const String& obj)
	{
		// Normal way
		delete[] m_str;
		size = strlen(obj.m_str);
		m_str = new char[size + 1];
		strcpy(m_str, obj.m_str);
	}

	String(String&& obj) noexcept
	{
		moveFrom(obj);
	}

	String& operator=(const String& obj)
	{
		if (this == &obj)
			return *this;

		// Copy
		String obj1(obj);

		// Swap
		swap(*this, obj1);

		return *this;
	}

	String& operator=(String&& obj) noexcept
	{
		if (this == &obj)
			return *this;

		cleanup();
		moveFrom(obj);

		return *this;
	}

	void moveFrom(String& obj) noexcept
	{
		size = obj.size;
		m_str = obj.m_str;

		obj.size = 0;
		obj.m_str = nullptr;
	}

	void display() const
	{
		std::cout << m_str;
	}

	void cleanup()
	{
		delete[] m_str;
		m_str = nullptr;
		size = 0;
	}

	~String()
	{
		cleanup();
	}

private:
	char* m_str;
	size_t size;
};

void swap(String& lhs, String& rhs) noexcept
{
	std::swap(lhs.m_str, rhs.m_str);
	std::swap(lhs.size, rhs.size);
}

int main()
{
	

	return 0;
}
