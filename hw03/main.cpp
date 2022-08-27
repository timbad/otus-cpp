
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
        std::map<int, int, std::less<int>, my_allocator_t<std::pair<const int, int>, n>> m;
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

        // заполнение 10 элементами от 0 до 9
    }

    {
        // создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
        // ограниченным 10 элементами

        // заполнение 10 элементами от 0 до 9

        // вывод на экран всех значений, хранящихся в контейнере

    }
}
