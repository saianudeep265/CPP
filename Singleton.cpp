#pragma once

#include <iostream>
#include <cstring>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <future>
#include <atomic>
#include <memory>

// Note:
// From C++17, all static variables can be declared as inline to initialize it at the declaration
// Please compile with C++17 standard

// Singleton using std::call_once and std::once_flag
namespace CallOnce
{
	class Singleton
	{
	private:
		Singleton()
		{
			std::cout << "ctor\n";
		}

		~Singleton() = default;

	public:
		static Singleton* getInstance()
		{
			std::call_once(initFlag, &Singleton::init);

			return instance;
		}

		void release()
		{
			delete instance;
			instance = nullptr;
		}

	private:
		static void init()
		{
			instance = new Singleton();
		}

	private:
		static inline Singleton* instance = nullptr;
		static inline std::once_flag initFlag;
	};
}// namespace Callonce

namespace DoubleCheck
{
	class Singleton
	{
	private:
		Singleton()
		{
			std::cout << "ctor\n";
		}

		~Singleton() = default;

	public:
		static Singleton* getInstance()
		{
			if (!instance)
			{
				std::lock_guard<std::mutex> lock(instanceMutex);
				if (!instance)
				{
					init();
				}
			}

			return instance;
		}

		void release()
		{
			delete instance;
			instance = nullptr;
		}

	private:
		static void init()
		{
			instance = new Singleton();
		}

	private:
		static inline Singleton* instance = nullptr;
		static inline std::mutex instanceMutex;
	};
}// namespace DoubleCheck

namespace ScottMeyers
{
	class Singleton
	{
	private:
		Singleton()
		{
			std::cout << "ctor\n";
		}

		~Singleton() = default;

	public:
		static Singleton& getInstance()
		{
			static Singleton instance;
			return instance;
		}
	};
}// namespace ScottMeyers

int main()
{
	

	return 0;
}
