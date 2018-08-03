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

    // 该算法的空间复杂度是O(nk)，时间复杂度是O(nk^2)
    // n = eggs, k = floors

    // 14 循环次数5049=(2-1)*(2+100)(100-2+1)/2 = 51 * 99 = (eggs-1)*(2+floors)*(floors-2+1)/2
    // eggs = 2;
    // floors = 100;

    // 3  循环次数60=(4-1)*(2+6)(6-2+1)/2 = 3 * 4 * 5 = (eggs-1)*(2+floors)*(floors-2+1)/2
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


    // 先考虑eggs边界，eggs为0，则为0；eggs为1，肯定从第0层往上依次实验
    for (unsigned int i = 0; i <= floors; ++i)
    {
        matrix[0][i] = 0;
        matrix[1][i] = i;
    }
    // 考虑floor的边界，floors为0即为0，floors为1即为1
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
            // 还有egg个鸡蛋，一共有floor层楼的子问题
            // 定义一个变量来存储最终结果，找到在哪里扔能达到所扔次数最少的目标
            unsigned int result = UINT_MAX;

            for (unsigned int i = 1; i <= floor; ++i)
            {
                ++count;

                // 碎了，剩下的问题即如何在i-1层，用egg-1个鸡蛋寻找最优解
                unsigned int broken = matrix[egg - 1][i - 1];
                // 没碎，在floor-i层，用egg个鸡蛋找最优解
                unsigned int unbroken = matrix[egg][floor - i];
                // 两种情况取最大值，因为根本不知道鸡蛋会不会碎
                unsigned int value = (broken > unbroken ? broken : unbroken) + 1;

                // 不断和上一次结果做比较，得到最少的扔次数
                if (value < result)
                    result = value;

                /*printf("循环次数:%lld (%u, %u, %u), :%u %u %u %u\n",
                    count, egg, floor, i,
                    broken, unbroken, value, result);*/
            }

            matrix[egg][floor] = result;
        }
    }

    minStep = matrix[eggs][floors];

    printMatrix(matrix, eggs, floors);

    printf("循环次数:%lld, 起始尝试楼层数:%u\n",
        count, minStep);

    // 释放内存
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