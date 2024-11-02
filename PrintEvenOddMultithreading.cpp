#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int counter = 0;
std::mutex counterMutex;
std::condition_variable counterCV;

void printEven()
{
	while (counter < 100)
	{
		std::unique_lock lock(counterMutex);
		counterCV.wait(lock, []() { return counter % 2 == 0; });
		std::cout << "Even thread: " << counter++ << std::endl;

		counterCV.notify_one();
	}
}

void printOdd()
{
	while (counter < 100)
	{
		std::unique_lock lock(counterMutex);
		counterCV.wait(lock, []() { return counter % 2 == 1; });
		std::cout << "Odd thread: " << counter++ << std::endl;

		counterCV.notify_one();
	}
}

int main()
{
	

	return 0;
}
