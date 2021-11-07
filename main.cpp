#include <iostream>
#include "array.hpp"


int main()
{
    Array<int> array;

    for (int i = 0; i < 14; ++i)
    {
        array.pushBack(i + 1);
    }

    for (int i = 13; i > 6; --i)
    {
        std::cout << array[i] << std::endl;
        array.popBack();
    }

    for (int i = 14; i < 18; ++i)
    {
        array.pushBack(i + 1);
    }

    for (int i = 14; i < 18; ++i)
    {
        std:: cout << array[i + 1] << std::endl;
    }

    return 0;
}