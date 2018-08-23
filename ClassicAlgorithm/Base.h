#pragma once
#include <stdio.h>
#include <algorithm>
#include <typeinfo>

typedef unsigned int uint;
typedef unsigned long long int ullint;


template <typename elemType>
void swap(elemType & lhs, elemType & rhs);


template <typename elemType>
void printArr(elemType* arr, uint size);

template <typename elemType>
void printArrByIndex(elemType* arr, uint size, uint* indexArr);


template <typename elemType>
elemType max(elemType arr[], uint size);


template <typename elemType>
void swap(elemType & lhs, elemType & rhs)
{
    if (lhs != rhs)
        std::swap(lhs, rhs);
}


template <typename elemType>
void reverse(elemType arr[], uint size);



#define log(format, ...) \
do \
{ \
    fprintf(stdout, format, ##__VA_ARGS__); \
} while (0);



//---------------------------------------------------------------------------


template <typename elemType>
void printArr(elemType* arr, uint size)
{
    if (size < 1)
        return;

    int type = 1;

    if (typeid(arr[0]).name() == typeid(int).name())
        type = 1;
    else if (typeid(arr[0]).name() == typeid(uint).name())
        type = 11;
    else if (typeid(arr[0]).name() == typeid(double).name())
        type = 2;
    else if (typeid(arr[0]).name() == typeid(char).name())
        type = 3;
    else
    {
        printf("unsupport type, type=%d, [%s]\n", type, typeid(arr[0]).name());
    return;
    }

    /*printf("------------------------------------\n");
    for (uint i = 0; i < size; ++i)
    {
    printf("%2d ", i);
    }
    printf("\n");*/

    for (uint i = 0; i < size; ++i)
    {
        if (type == 1)
            printf("%2d ", arr[i]);
        else if (type == 11)
            printf("%2u ", arr[i]);
        else if (type == 2)
            printf("%2f ", arr[i]);
        else if (type == 3)
            printf("%c ", arr[i]);
    }
    printf("\n");

    return;
}


template <typename elemType>
void printArrByIndex(elemType* arr, uint size, uint* indexArr)
{
    if (size < 1)
        return;

    int type = 1;

    if (typeid(arr[0]).name() == typeid(1).name())
        type = 1;
    else if (typeid(arr[0]).name() == typeid(1.0).name())
        type = 2;
    else if (typeid(arr[0]).name() == typeid('a').name())
        type = 3;
    else
    {
        printf("unsupport type, type=%d, [%s]\n", type, typeid(arr[0]).name());
        return;
    }

    /*printf("------------------------------------\n");
    for (uint i = 0; i < size; ++i)
    {
    printf("%2d ", i);
    }
    printf("\n");*/

    for (uint i = 0; i < size; ++i)
    {
        if (type == 1)
            printf("%2d ", arr[indexArr[i]]);
        else if (type == 2)
            printf("%2d ", arr[indexArr[i]]);
        else if (type == 3)
            printf("%c ", arr[indexArr[i]]);
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


template <typename elemType>
void reverse(elemType arr[], uint size)
{
    if (!arr || size < 2)
        return;

    for (uint left = 0, right = size - 1; left < right; ++left, --right)
        swap(arr[left], arr[right]);
}
