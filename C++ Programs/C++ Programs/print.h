#pragma once

#include <iostream>

template <typename T>
void print(T t)
{
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void print(T t, Args... args) // ���� ����� 1 ��������
{
    std::cout << t;
    print(args...);
}