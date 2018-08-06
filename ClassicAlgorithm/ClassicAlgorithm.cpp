// ClassicAlgorithm.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include<stdio.h>
#include<map>
#include<vector>

#include "BigIntMutil.h"
#include "EggFloor.h"
#include "ACAutomation.h"


// �������˷�
void testBigIntMutil();
// ¥���Ӽ���
void testEggsFloors();
// ac������
void testACAutomation();


int main2(int argc, char* argv[])
{
    // �������˷�
    //testBigIntMutil();

    // ¥���Ӽ���
    //testEggsFloors();

    // ac������
    testACAutomation();

	return 0;
}

// ac������
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

    printf("str:%s, ƥ��������:%d\n", str, result);


}

// ¥���Ӽ���
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

    // 14 ѭ������5049=(2-1)*(2+100)(100-2+1)/2 = 51 * 99 = (eggs-1)*(2+floors)*(floors-2+1)/2
    eggs = 2;
    floors = 100;

    // 3  ѭ������60=(4-1)*(2+6)(6-2+1)/2 = 3 * 4 * 5 = (eggs-1)*(2+floors)*(floors-2+1)/2
    eggs = 4;
    floors = 6;

    // 6  ѭ������3822=(4-1)*(2+50)(50-2+1)/2 = 3 * 26 * 49 = (eggs-1)*(2+floors)*(floors-2+1)/2
    eggs = 4;
    floors = 200;
    
    eggs = 10;
    floors = 5000;

    unsigned int result = ef.getMinSteps(eggs, floors);

    printf("������:%u, ¥����:%u, ��С���Դ���:%u\n",
        eggs, floors, result);

    eggs = 4;
    floors = 5;

    result = ef.droppingMax(eggs, floors);

    printf("������:%u, ¥����:%u, ����ܲ��Ե�¥����:%u\n",
        eggs, floors, result);


    eggs = 10;
    floors = 5000;

    result = ef.droppingEggsPuzzle(eggs, floors);

    printf("������:%u, ¥����:%u, ��С���Դ���:%u\n",
        eggs, floors, result);

}


// �������˷�
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
