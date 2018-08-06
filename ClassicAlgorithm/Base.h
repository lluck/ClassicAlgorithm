#pragma once
#include <stdio.h>
#include <algorithm>


typedef unsigned int uint;
typedef unsigned long long int ullint;


template <class elemType>
void swap(elemType & lhs, elemType & rhs);


template <typename elemType>
void printArr(elemType* arr, uint size);


template <typename elemType>
elemType max(elemType arr[], uint size);



template <class elemType>
void swap(elemType & lhs, elemType & rhs)
{
    std::swap(lhs, rhs);
}



//---------------------------------------------------------------------------


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

    /*printf("------------------------------------\n");

    for (uint i = 0; i < size; ++i)
    {
    printf("%2d ", i);
    }
    printf("\n");*/

    for (uint i = 0; i < size; ++i)
    {
        if (type == 1)
            printf("%c ", arr[i]);
        else if (type == 2)
            printf("%2d ", arr[i]);
    }
    printf("\n");

    return;
}


template <typename elemType>
elemType max(elemType arr[], uint size)
{
    if (!arr || size < 1)
        return 0;

    elemType maxValue = arr[0];

    for (uint i = 1; i < size; ++i)
    {
        if (arr[i] > maxValue)
            maxValue = arr[i];
    }

    return maxValue;
}



