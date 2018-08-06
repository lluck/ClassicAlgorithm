#include <limits>
#include<stdio.h>
#include "EggFloor.h"


EggFloor::EggFloor()
{
}


EggFloor::~EggFloor()
{
}

unsigned int EggFloor::getMinSteps(const unsigned int eggs, const unsigned int floors)
{

    // ���㷨�Ŀռ临�Ӷ���O(nk)��ʱ�临�Ӷ���O(nk^2)
    // n = eggs, k = floors

    // 14 ѭ������5049=(2-1)*(2+100)(100-2+1)/2 = 51 * 99 = (eggs-1)*(2+floors)*(floors-2+1)/2
    // eggs = 2;
    // floors = 100;

    // 3  ѭ������60=(4-1)*(2+6)(6-2+1)/2 = 3 * 4 * 5 = (eggs-1)*(2+floors)*(floors-2+1)/2
    // eggs = 4;
    // floors = 6;

    if (eggs < 1 || floors < 1)
    {
        return 0;
    }

    unsigned int minStep = 0;
    unsigned int** matrix = new unsigned int*[eggs + 1];
    for (unsigned int i = 0; i <= eggs; ++i)
    {
        matrix[i] = new unsigned int[floors + 1];
    }


    // �ȿ���eggs�߽磬eggsΪ0����Ϊ0��eggsΪ1���϶��ӵ�0����������ʵ��
    for (unsigned int i = 0; i <= floors; ++i)
    {
        matrix[0][i] = 0;
        matrix[1][i] = i;
    }
    // ����floor�ı߽磬floorsΪ0��Ϊ0��floorsΪ1��Ϊ1
    for (unsigned int i = 1; i <= eggs; ++i)
    {
        matrix[i][0] = 0;
        matrix[i][1] = 1;
    }

    /*
    *    | 0  1  2  3  4  5  6
    * ---|---------------------floor
    *  0 | 0  0  0  0  0  0  0
    *  1 | 0  1  2  3  4  5  6
    *  2 | 0  1  2  2  3  3  3
    *  3 | 0  1  2  2  3  3  3
    *  4 | 0  1  2  2  3  3  3
    *    e
    *    g
    *    g
    */

    long long unsigned int count = 0L;

    for (unsigned int egg = 2; egg <= eggs; ++egg)
    {
        for (unsigned int floor = 2; floor <= floors; ++floor)
        {
            // ����egg��������һ����floor��¥��������
            // ����һ���������洢���ս�����ҵ����������ܴﵽ���Ӵ������ٵ�Ŀ��
            unsigned int result = UINT_MAX;

            for (unsigned int i = 1; i <= floor; ++i)
            {
                ++count;

                // ���ˣ�ʣ�µ����⼴�����i-1�㣬��egg-1������Ѱ�����Ž�
                unsigned int broken = matrix[egg - 1][i - 1];
                // û�飬��floor-i�㣬��egg�����������Ž�
                unsigned int unbroken = matrix[egg][floor - i];
                // �������ȡ���ֵ����Ϊ������֪�������᲻����
                unsigned int value = (broken > unbroken ? broken : unbroken) + 1;

                // ���Ϻ���һ�ν�����Ƚϣ��õ����ٵ��Ӵ���
                if (value < result)
                    result = value;

                /*printf("ѭ������:%lld (%u, %u, %u), :%u %u %u %u\n",
                    count, egg, floor, i,
                    broken, unbroken, value, result);*/
            }

            matrix[egg][floor] = result;
        }
    }

    minStep = matrix[eggs][floors];

    printMatrix(matrix, eggs, floors);

    printf("ѭ������:%lld, ��ʼ����¥����:%u\n",
        count, minStep);

    // �ͷ��ڴ�
    for (unsigned int i = 0; i <= eggs; ++i)
    {
        delete [] matrix[i];
    }
    delete [] matrix;

    return minStep;
}


void EggFloor::printMatrix(unsigned int **matrix, const unsigned int rows, const unsigned int cols)
{
    for (unsigned int i = 0; i <= rows; ++i)
    {
        for (unsigned int j = 0; j <= cols; ++j)
        {
            printf("%2u ", matrix[i][j]);
        }

        printf("\n");
    }
}


unsigned int EggFloor::droppingMax(unsigned int eggs, unsigned times)
{
    if (eggs == 1)
    {
        return times;
    }

    if (eggs >= times)
    {
        return (unsigned int)pow(2, times) - 1;
    }

    return droppingMax(eggs, times - 1) + droppingMax(eggs - 1, times - 1) + 1;
}


unsigned int EggFloor::droppingEggsPuzzle(unsigned int eggs, unsigned int floors)
{
    unsigned int times = 1;

    unsigned int maxTestFloors = droppingMax(eggs, times);

    while (maxTestFloors < floors)
    {
        ++times;
    }

    printf("eggs:%u, maxTestFloors:%u, floors:%u\n",
        eggs, maxTestFloors, floors);

    return times;
}