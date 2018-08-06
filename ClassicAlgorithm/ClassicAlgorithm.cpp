// ClassicAlgorithm.cpp : 定义控制台应用程序的入口点。
//

#include<stdio.h>
#include<map>
#include<vector>

#include "BigIntMutil.h"
#include "EggFloor.h"
#include "ACAutomation.h"


// 大整数乘法
void testBigIntMutil();
// 楼上扔鸡蛋
void testEggsFloors();
// ac自助机
void testACAutomation();


int main2(int argc, char* argv[])
{
    // 大整数乘法
    //testBigIntMutil();

    // 楼上扔鸡蛋
    //testEggsFloors();

    // ac自助机
    testACAutomation();

	return 0;
}

// ac自助机
void testACAutomation()
{
    ACAutomation ac;
    Node* root = new Node();
    root->value = '/';
    printf("root:%c-%p\n", root->value, root);

    ac.insert("say", root);
    ac.insert("she", root);
    ac.insert("shr", root);
    ac.insert("he", root);
    ac.insert("her", root);

    // 
    //ac.build_ac_automation(root);

    //
    ac.build_ac_automation_deque(root);

    ac.printACAutomation(root);


    const char* str = "sayhersheshrheshe";

    str = "aahesh";
    str = "sayhersheshrheshe";

    int result = ac.query(str, root);

    printf("str:%s, 匹配结果数量:%d\n", str, result);


}

// 楼上扔鸡蛋
void testEggsFloors()
{
    EggFloor ef;
    unsigned int eggs = 6;
    unsigned int floors = 4;

    // 6
    eggs = 3;
    floors = 39;

    // 9
    eggs = 2;
    floors = 39;

    // 14 循环次数5049=(2-1)*(2+100)(100-2+1)/2 = 51 * 99 = (eggs-1)*(2+floors)*(floors-2+1)/2
    eggs = 2;
    floors = 100;

    // 3  循环次数60=(4-1)*(2+6)(6-2+1)/2 = 3 * 4 * 5 = (eggs-1)*(2+floors)*(floors-2+1)/2
    eggs = 4;
    floors = 6;

    // 6  循环次数3822=(4-1)*(2+50)(50-2+1)/2 = 3 * 26 * 49 = (eggs-1)*(2+floors)*(floors-2+1)/2
    eggs = 4;
    floors = 200;
    
    eggs = 10;
    floors = 5000;

    unsigned int result = ef.getMinSteps(eggs, floors);

    printf("鸡蛋数:%u, 楼层数:%u, 最小尝试次数:%u\n",
        eggs, floors, result);

    eggs = 4;
    floors = 5;

    result = ef.droppingMax(eggs, floors);

    printf("鸡蛋数:%u, 楼层数:%u, 最大能测试的楼层数:%u\n",
        eggs, floors, result);


    eggs = 10;
    floors = 5000;

    result = ef.droppingEggsPuzzle(eggs, floors);

    printf("鸡蛋数:%u, 楼层数:%u, 最小尝试次数:%u\n",
        eggs, floors, result);

}


// 大整数乘法
void testBigIntMutil()
{
    string a = "123456789";
    string b = "987654321";

    

    // 8,991
    a = "999";
    b = "9";

    // 998,001
    a = "999";
    b = "999";

    

    // 121,932,631,112,635,269
    a = "123456789";
    b = "987654321";

    // 11,100
    a = "111";
    b = "100";

    BigIntMutil mutil(a, b);

    mutil.doMuti();
    mutil.printResultStr();
}
