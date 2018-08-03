#include "BigIntMutil.h"

BigIntMutil::BigIntMutil(string intAstr, string intBStr)
{
    this->intAStr = intAstr;
    this->intbStr = intBStr;
    this->resulIntArray = nullptr;
    this->resultIntArrayLen = 0;
}

BigIntMutil::~BigIntMutil()
{
    if (this->resulIntArray)
    {
        delete[] this->resulIntArray;
        this->resulIntArray = nullptr;
    }
        
}

void BigIntMutil::doMuti()
{
    int aIntsLen = this->intAStr.length();
    int bIntsLen = this->intbStr.length();
    int maxLen = aIntsLen + bIntsLen;

    int* resultInts = new int[maxLen];

    for (int i = 0; i < maxLen; ++i)
    {
        // 区分有效位数
        *(resultInts + i) = -1;
    }

    int currPosi = 0;
    int g, s, value;

    for (int i = 0; i < aIntsLen; ++i)
    {
        currPosi = i;
        for (int j = 0; j < bIntsLen; ++j)
        {
            // 数值置为0, 防止-1影响计算结果
            if (*(resultInts + currPosi) < 0)
                *(resultInts + currPosi) = 0;

            value = (this->intAStr.at(i) - '0') * (this->intbStr.at(j) - '0') + *(resultInts + currPosi);
            g = value % 10;
            s = value / 10;

            *(resultInts + currPosi) = g;
            ++currPosi;

            // 数值置为0, 防止-1影响计算结果
            if (s > 0 && *(resultInts + currPosi) < 0) {
                *(resultInts + currPosi) = 0;
            }

            *(resultInts + currPosi) += s;

        }

        //this->resultIntArrayLen = maxLen;
        //this->resulIntArray = resultInts;
        //this->printResultStr();
    }

    // 释放之前的内存
    if (this->resulIntArray)
    {
        delete [] this->resulIntArray;
    }
    this->resulIntArray = resultInts;
    this->resultIntArrayLen = maxLen;
}


void BigIntMutil::printResultStr()
{
    printf("正向: ");
    // 0 0 1 1 1 -1 -1 -1 -1 -1  >> 00, 111
    for (int i = resultIntArrayLen - 1; i >= 0; --i)
    {
        int value = *(this->resulIntArray + i);

        if (value < 0)
        {
            continue;
        }

        if (i % 3 == 0 && i > 0)
            printf("%d,", this->resulIntArray[i] = value);
        else
            printf("%d", this->resulIntArray[i] = value);
    }

    printf("\n");

    //return;

    printf("反向: ");

    // 0 0 1 1 1 -1 -1 -1 -1 -1 << 111, 00
    for (int i = 0; i < resultIntArrayLen; ++i)
    {
        int value = *(this->resulIntArray + i);

        if (value < 0)
        {
            break;
        }

        if ((i + 1) % 3 == 0 && i < resultIntArrayLen - 1)
            printf("%d,", this->resulIntArray[i] = value);
        else
            printf("%d", this->resulIntArray[i] = value);
    }

    printf("\n");

}

