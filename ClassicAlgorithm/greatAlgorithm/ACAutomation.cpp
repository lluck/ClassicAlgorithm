#include "ACAutomation.h"
#include "stdio.h"
#include <deque>

using namespace std;


ACAutomation::ACAutomation()
{
}


ACAutomation::~ACAutomation()
{
}


// 写入数据
void ACAutomation::insert(const char* str, Node* root)
{
    Node* p = root;

    if (!p || !str)
        return;

    int strPosi = 0;
    int indexValue = 0;

    while (str[strPosi])
    {
        indexValue = str[strPosi] - 'a';
        if (p->next[indexValue] == NULL)
        {
            p->next[indexValue] = new Node();
            p->next[indexValue]->value = str[strPosi];
        }

        p = p->next[indexValue];
        ++strPosi;
    }

    //在单词的最后一个节点count+1，代表一个单词
    p->count++;

}


/*
*    构造失败指针的过程概括起来就一句话：设这个节点上的字母为C，沿着他父亲的失败指针走，直到走到一个节点，他的儿子中也有字母为C的节点。
*    然后把当前节点的失败指针指向那个字母也为C的儿子。如果一直走到了root都没找到，那就把失败指针指向root。
*    具体操作起来只需要：先把root加入队列(root的失败指针指向自己或者NULL)，这以后我们每处理一个点，就把它的所有儿子加入队列，队列为空。
*/
// 构造失败指针:使用定长队列
void ACAutomation::build_ac_automation(Node* root)
{
    Node* queue[AC_AUTOMATION_MAX_QUEUE_LEN];               // FIFO队列
    int head, tail;                                         // 队列的头尾指针
    head = 0;
    tail = 0;

    // root节点fail指针为null
    root->fail = NULL;
    // root节点入队列:FIFO, 从头入队列，从尾出队列
    queue[head++] = root;

    while (head > tail)
    {
        // 从队列末尾处理
        Node* curr = queue[tail++];
        Node* p = NULL;

        for (int i = 0; i < AC_AUTOMATION_KIND; ++i)
        {
            if (curr->next[i])
            {
                if (curr == root)
                {
                    // root子结点失败指针指向root
                    curr->next[i]->fail = root;
                }
                else
                {
                    // 非root子结点, 查询父结点的失败指针, 直到root结点
                    p = curr->fail;
                    while (p)
                    {
                        if (p->next[i])
                        {
                            // 在失败指针结点找到数据
                            curr->next[i]->fail = p->next[i];
                            break;
                        }

                        // 未找到, 指向上级失败指针
                        p = p->fail;
                    }

                    if (!p)
                    {
                        // 未找到失败结点, 指向root结点
                        curr->next[i]->fail = root; 
                    }
                }

                // 子结点从队列前面加入队列
                queue[head++] = curr->next[i];
            }
            // end of loop:i 子结点不为null处理
        }
        // end of for 26 loop
    }
    // end of while loop:队列处理
}


/*
*    构造失败指针的过程概括起来就一句话：设这个节点上的字母为C，沿着他父亲的失败指针走，直到走到一个节点，他的儿子中也有字母为C的节点。
*    然后把当前节点的失败指针指向那个字母也为C的儿子。如果一直走到了root都没找到，那就把失败指针指向root。
*    具体操作起来只需要：先把root加入队列(root的失败指针指向自己或者NULL)，这以后我们每处理一个点，就把它的所有儿子加入队列，队列为空。
*/
// 构造失败指针:使用deque
void ACAutomation::build_ac_automation_deque(Node* root)
{
    // root节点fail指针为null
    root->fail = NULL;
    // root节点入队列:FIFO, 从头入队列，从尾出队列
    deque<Node*> queue;
    queue.push_front(root);

    while (queue.size() > 0)
    {
        // 从队列尾处理
        Node* curr = queue.back();
        Node* p = NULL;

        queue.pop_back();

        for (int i = 0; i < AC_AUTOMATION_KIND; ++i)
        {
            if (curr->next[i])
            {
                if (curr == root)
                {
                    // root子结点失败指针指向root
                    curr->next[i]->fail = root;
                }
                else
                {
                    // 非root子结点, 从父节点失败指针开始，依次遍历，直到root结点为止
                    p = curr->fail;
                    while (p)
                    {
                        if (p->next[i])
                        {
                            // 失败指针存在数据值
                            curr->next[i]->fail = p->next[i];
                            break;
                        }

                        // 失败指针子结点不存在, 继续向上级失败指针寻找
                        p = p->fail;
                    }

                    if (!p)
                    {
                        // 失败指针不存在, 指向root结点
                        curr->next[i]->fail = root;
                    }
                }

                // 子结点从队列前面加入队列
                queue.push_front(curr->next[i]);
            }
            // end of loop:i 子结点不为null, 处理
        }
        // end of for 26 loop

        
    }
    // end of while loop:队列处理
}


/*
*   匹配过程分两种情况：(1)当前字符匹配，表示从当前节点沿着树边有一条路径可以到达目标字符，此时只需沿该路径走向下一个节点继续匹配即可，
*   目标字符串指针移向下个字符继续匹配；(2)当前字符不匹配，则去当前节点失败指针所指向的字符继续匹配，匹配过程随着指针指向root结束。
*   重复这2个过程中的任意一个，直到模式串走到结尾为止。
*/
int ACAutomation::query(const char* str, Node* root)
{
    Node* p = root;

    if (!p || !str)
        return 0;

    int result = 0;
    int strPosi = 0;
    int indexValue = 0;

    while (str[strPosi])
    {
        printf("11 ----------strPosi:%d, str:%c, result:%d\n",
            strPosi, str[strPosi], result);

        indexValue = str[strPosi] - 'a';

        // 查询首次匹配的位置:依次查询失败指针, 直到指向root结点
        while (p->next[indexValue] == NULL && p != root)
            p = p->fail;

        // 判断结点值是否存在, 不存在使用root结点
        p = p->next[indexValue];
        if (p == NULL)
            p = root;

        Node* match = p;
        while (match->count > 0)
        {
            printf("----------match:\n");
            printACAutomation(match);

            result += match->count;
            match->count = 0;
            match = match->fail;

            printf("----------match after point 2 fail:\n");
            printACAutomation(match);
        }

        printf("12----------strPosi:%d, str:%c, result:%d\n",
            strPosi, str[strPosi], result);
        printACAutomation(match);

        ++strPosi;
    }

    return result;
}


void ACAutomation::printACAutomation(Node* root)
{
    Node* p = root;

    if (p)
    {
        Node* fail = p->fail;
        char failc = '|';
        if (fail)
            failc = fail->value;

        printf("%c-%c-%d-%p-%p ", p->value, failc,
            p->count,
            p, fail);

        for (int i = 0; i < AC_AUTOMATION_KIND; ++i)
        {
            if (p->next[i])
            {
                printACAutomation(p->next[i]);
            }

            //printACAutomation(p->next[i]);
        }

        printf("\n");
    }
    else
    {
        printf("  ");
    }
}

