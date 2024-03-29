
#include <map>
#include <iostream>
#include <stdexcept>

#include "my_allocator.h"
#include "my_container.h"


constexpr int fact(const int val) {
    if (val < 0) {
        throw std::invalid_argument("Factorial of negative numbers cannot be calculated!");
    }
    int ret = 1;
    for (int i = 1; i <= val; i++) {
        ret *= i;
    }
    return ret;
}


int main(int, char const* [])
{
    constexpr int n = 10;

    {
        // создание экземпляра std::map<int, int>
        std::map<int, int> m;
        // заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
        for (int i = 0; i < n; i++) {
            m[i] = fact(i);
        }
    }

    {
        // создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
        std::map<int, int, std::less<>, my_allocator_t<std::pair<const int, int>, n>> m;
        // заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
        for (int i = 0; i < n; i++) {
            m[i] = fact(i);
        }
        // вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
        for (int i = 0; i < n; i++) {
            std::cout << i << " " << m[i] << "\n";
        }
    }

    {
        // создание экземпляра своего контейнера для хранения значений типа int
        my_list_t<int> my_list;
        // заполнение 10 элементами от 0 до 9
        for(int i = 0; i < n; i++) {
            my_list.push_back(i);
        }
    }

    {
        // создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
        // ограниченным 10 элементами
        my_list_t<int, my_allocator_t<int, n>> my_list;
        // заполнение 10 элементами от 0 до 9
        for(int i = 0; i < n; i++) {
//        for(int i = 0; i < 20; i++) {  // реаллокация сработает на 10 элементе
            my_list.push_back(i);
        }
        // вывод на экран всех значений, хранящихся в контейнере
#if 0
        for (auto it = my_list.begin(); it != my_list.end(); ++it) {
            std::cout << *it << " ";
        }
#else
        for (auto i : my_list) {
            std::cout << i << " ";
        }
#endif
        std::cout << "\n";
    }
}
