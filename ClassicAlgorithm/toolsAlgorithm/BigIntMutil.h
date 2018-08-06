#pragma once

#include<string>

using namespace std;

class BigIntMutil
{
public:
    BigIntMutil(string intAstr, string intBStr);
    ~BigIntMutil();

    void doMuti();
    void printResultStr();

private:
    string intAStr;
    string intbStr;
    int* resulIntArray;
    int resultIntArrayLen;
};


