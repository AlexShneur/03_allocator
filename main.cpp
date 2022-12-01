// 03_allocator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <vector>
#include "My_Allocator.h"
#include "MyContainer.h"

constexpr int ALLOCATOR_SIZE = 10;
using myAllocator = My_Allocator<std::pair<const int, int>, ALLOCATOR_SIZE>;

int factorial(int n)
{
	if (n == 0)
		return 1;
	else
		return n * factorial(n - 1);
}

int main()
{
	try
	{
		//создание экземпляра std::map<int, int>
		auto m = std::map<const int, int>();

		//заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
		for (int i = 0; i < 10; ++i) {
			m[i] = factorial(i);
		}

		//создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
		auto m_my_alloc = std::map<const int, int, std::less<int>, myAllocator>();

		//заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
		for (int i = 0; i < ALLOCATOR_SIZE; ++i) {
			m_my_alloc[i] = factorial(i);
		}

		//вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
		for (const auto& [key, value] : m_my_alloc)
		{
			std::cout << key << " " << value << std::endl;
		}

		std::cout << std::endl;

		//создание экземпляра своего контейнера для хранения значений типа int
		MyContainer<int> mc;

		//заполнение 10 элементами от 0 до 9
		for (int i = 0; i < 10; ++i)
		{
			mc.push(i);
		}

		//создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором, ограниченным 10 элементами
		MyContainer<int, My_Allocator<int, ALLOCATOR_SIZE>> mc_my_alloc;

		//заполнение 10 элементами от 0 до 9
		for (int i = 0; i < 10; ++i)
		{
			mc_my_alloc.push(i);
		}

		//вывод на экран всех значений, хранящихся в контейнере
		for (const auto& item : mc_my_alloc)
		{
			std::cout << item << std::endl;
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << "Cannot allocate: " << ex.what() << std::endl;
	}
}