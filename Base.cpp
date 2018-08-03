#include <algorithm>
#include "Base.h"



template <class elemType>
void swap(elemType & lhs, elemType & rhs)
{
    std::swap(lhs, rhs);
}


template <typename elemType>
void printArr(elemType* arr, uint size)
{
    if (size < 1)
        return;

    int type = 1;

    /*if (typeid(arr[0]).name() == typeid(1).name())
    type = 1;
    else if (typeid(arr[0]).name() == typeid(1.0).name())
    type = 2;
    else
    {
    printf("unsupport type\n");
    return;
    }*/

    for (uint i = 0; i < size; ++i)
    {
        if (type == 1)
            printf("%d ", arr[i]);
        else if (type == 2)
            printf("%f ", arr[i]);
    }
    printf("\n");

    return;
}


int aaaaa(int argc, char* argv[])
{
    int arr[10] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2 };
    int size = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, size);

    return 0;
}
