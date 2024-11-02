#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <vector>

class Task
{
public:
	virtual ~Task() = default;
	virtual void execute() = 0;
};

class TaskScheduler
{
public:
	TaskScheduler(size_t worker = std::thread::hardware_concurrency())
		: numThreads(worker), shutDown(false)
	{
		init();
	}

	~TaskScheduler()
	{
		shutDown = true;

		for (size_t i = 0; i < numThreads; i++)
		{
			pool[i].join();
		}
	}

	void addTask(std::unique_ptr<Task> task)
	{
		std::unique_lock lock(queueMutex);
		queue.push(std::move(task));
	}

private:
	void init()
	{
		pool.reserve(numThreads);
		for (size_t i = 0; i < numThreads; i++)
		{
			pool.emplace_back(std::thread(&TaskScheduler::run, this));
		}
	}

	void run()
	{
		while (true)
		{
			std::unique_lock lock(queueMutex);
			if (!queue.empty())
			{
				auto task = std::move(queue.front());
				queue.pop();
				lock.unlock();

				task->execute();
			}
			else if (shutDown)
			{
				break;
			}
		}
	}

private:
	size_t numThreads;
	std::queue<std::unique_ptr<Task>> queue;
	std::vector<std::thread> pool;
	std::mutex queueMutex;
	bool shutDown;
};

class PrintTask1 : public Task
{
public:
	void execute() override
	{
		std::cout << "I am Anudeep\n";
	}
};

class PrintTask2 : public Task
{
public:
	void execute() override
	{
		std::cout << "I am Nandi\n";
	}
};

class PrintTask3 : public Task
{
public:
	void execute() override
	{
		std::cout << "I am Shanmukanand\n";
	}
};

int main()
{
	

	return 0;
}
