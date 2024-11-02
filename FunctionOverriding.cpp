#pragma once

#include <iostream>

/* Demonstrates following:
* 1. Function Overriding
* 2. virtual destructor
* 3. mutable keyword
* 4. Data Slicing
* 5. Casting
*/

class Base
{
public:
	virtual void display()
	{
		std::cout << "Base::display" << std::endl;
	}

	void setVar(int var_) const
	{
		var = var_;
		std::cout << "Var = " << var << std::endl;
	}

	virtual ~Base()
	{
		std::cout << "Base Destructor\n";
	}

public:
	mutable int var;
	int m_final;
};

class Derived : public Base
{
public:
	void display() override
	{
		std::cout << "Derived::display" << std::endl;
	}

	void display1()
	{
		std::cout << "Derive::display1" << std::endl;
	}

	~Derived()
	{
		std::cout << "Derived Destructor\n";
	}
};

int main()
{
	Derived d1;
	d1.display(); // Derived::display
	// Sets var to 20 as it is decalred as mutable eventhough setVar is marked as const
	d1.setVar(20); // Var = 20

	// Function Overriding 1
	Base* d2 = new Derived();
	d2->display(); // Derived::display
	delete d2;

	// Function Overriding 2
	Base* d3 = &d1;
	d3->display(); // Derived::display

	// Function Overriding 3
	Base& d4 = d1;
	d4.display(); // Derived::display

	// Data Slicing, only properties of B1 will remain
	Base b1 = d1;

	//d4.display(); Cannot access since d4 is of type Base
	Derived& d5 = dynamic_cast<Derived&>(d4); // After Down casting it's accessible
	d5.display1(); // Derive::display1

	// Note:
	// 1. If cast is not feasible dynamic casts returns nullptr if the type is pointer
	// 2. In case of reference it throws std::bad_cast exception
	// 3. Always use dynamic_cast for Up/Down cast to check the feasibility of the cast and not to go with static_cast as it casts at compile time and the state might be undefined

	/* Output as follows:
	Derived::display
	Var = 20
	Derived::display
	Derived Destructor
	Base Destructor
	Derived::display
	Derived::display
	Derive::display1
	Base Destructor
	Derived Destructor
	Base Destructor
	*/

	return 0;
}
