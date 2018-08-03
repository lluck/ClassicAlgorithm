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


// д������
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

    //�ڵ��ʵ����һ���ڵ�count+1������һ������
    p->count++;

}


/*
*    ����ʧ��ָ��Ĺ��̸���������һ�仰��������ڵ��ϵ���ĸΪC�����������׵�ʧ��ָ���ߣ�ֱ���ߵ�һ���ڵ㣬���Ķ�����Ҳ����ĸΪC�Ľڵ㡣
*    Ȼ��ѵ�ǰ�ڵ��ʧ��ָ��ָ���Ǹ���ĸҲΪC�Ķ��ӡ����һֱ�ߵ���root��û�ҵ����ǾͰ�ʧ��ָ��ָ��root��
*    �����������ֻ��Ҫ���Ȱ�root�������(root��ʧ��ָ��ָ���Լ�����NULL)�����Ժ�����ÿ����һ���㣬�Ͱ��������ж��Ӽ�����У�����Ϊ�ա�
*/
// ����ʧ��ָ��:ʹ�ö�������
void ACAutomation::build_ac_automation(Node* root)
{
    Node* queue[AC_AUTOMATION_MAX_QUEUE_LEN];               // FIFO����
    int head, tail;                                         // ���е�ͷβָ��
    head = 0;
    tail = 0;

    // root�ڵ�failָ��Ϊnull
    root->fail = NULL;
    // root�ڵ������:FIFO, ��ͷ����У���β������
    queue[head++] = root;

    while (head > tail)
    {
        // �Ӷ���ĩβ����
        Node* curr = queue[tail++];
        Node* p = NULL;

        for (int i = 0; i < AC_AUTOMATION_KIND; ++i)
        {
            if (curr->next[i])
            {
                if (curr == root)
                {
                    // root�ӽ��ʧ��ָ��ָ��root
                    curr->next[i]->fail = root;
                }
                else
                {
                    // ��root�ӽ��, ��ѯ������ʧ��ָ��, ֱ��root���
                    p = curr->fail;
                    while (p)
                    {
                        if (p->next[i])
                        {
                            // ��ʧ��ָ�����ҵ�����
                            curr->next[i]->fail = p->next[i];
                            break;
                        }

                        // δ�ҵ�, ָ���ϼ�ʧ��ָ��
                        p = p->fail;
                    }

                    if (!p)
                    {
                        // δ�ҵ�ʧ�ܽ��, ָ��root���
                        curr->next[i]->fail = root; 
                    }
                }

                // �ӽ��Ӷ���ǰ��������
                queue[head++] = curr->next[i];
            }
            // end of loop:i �ӽ�㲻Ϊnull����
        }
        // end of for 26 loop
    }
    // end of while loop:���д���
}


/*
*    ����ʧ��ָ��Ĺ��̸���������һ�仰��������ڵ��ϵ���ĸΪC�����������׵�ʧ��ָ���ߣ�ֱ���ߵ�һ���ڵ㣬���Ķ�����Ҳ����ĸΪC�Ľڵ㡣
*    Ȼ��ѵ�ǰ�ڵ��ʧ��ָ��ָ���Ǹ���ĸҲΪC�Ķ��ӡ����һֱ�ߵ���root��û�ҵ����ǾͰ�ʧ��ָ��ָ��root��
*    �����������ֻ��Ҫ���Ȱ�root�������(root��ʧ��ָ��ָ���Լ�����NULL)�����Ժ�����ÿ����һ���㣬�Ͱ��������ж��Ӽ�����У�����Ϊ�ա�
*/
// ����ʧ��ָ��:ʹ��deque
void ACAutomation::build_ac_automation_deque(Node* root)
{
    // root�ڵ�failָ��Ϊnull
    root->fail = NULL;
    // root�ڵ������:FIFO, ��ͷ����У���β������
    deque<Node*> queue;
    queue.push_front(root);

    while (queue.size() > 0)
    {
        // �Ӷ���β����
        Node* curr = queue.back();
        Node* p = NULL;

        queue.pop_back();

        for (int i = 0; i < AC_AUTOMATION_KIND; ++i)
        {
            if (curr->next[i])
            {
                if (curr == root)
                {
                    // root�ӽ��ʧ��ָ��ָ��root
                    curr->next[i]->fail = root;
                }
                else
                {
                    // ��root�ӽ��, �Ӹ��ڵ�ʧ��ָ�뿪ʼ�����α�����ֱ��root���Ϊֹ
                    p = curr->fail;
                    while (p)
                    {
                        if (p->next[i])
                        {
                            // ʧ��ָ���������ֵ
                            curr->next[i]->fail = p->next[i];
                            break;
                        }

                        // ʧ��ָ���ӽ�㲻����, �������ϼ�ʧ��ָ��Ѱ��
                        p = p->fail;
                    }

                    if (!p)
                    {
                        // ʧ��ָ�벻����, ָ��root���
                        curr->next[i]->fail = root;
                    }
                }

                // �ӽ��Ӷ���ǰ��������
                queue.push_front(curr->next[i]);
            }
            // end of loop:i �ӽ�㲻Ϊnull, ����
        }
        // end of for 26 loop

        
    }
    // end of while loop:���д���
}


/*
*   ƥ����̷����������(1)��ǰ�ַ�ƥ�䣬��ʾ�ӵ�ǰ�ڵ�����������һ��·�����Ե���Ŀ���ַ�����ʱֻ���ظ�·��������һ���ڵ����ƥ�伴�ɣ�
*   Ŀ���ַ���ָ�������¸��ַ�����ƥ�䣻(2)��ǰ�ַ���ƥ�䣬��ȥ��ǰ�ڵ�ʧ��ָ����ָ����ַ�����ƥ�䣬ƥ���������ָ��ָ��root������
*   �ظ���2�������е�����һ����ֱ��ģʽ���ߵ���βΪֹ��
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

        // ��ѯ�״�ƥ���λ��:���β�ѯʧ��ָ��, ֱ��ָ��root���
        while (p->next[indexValue] == NULL && p != root)
            p = p->fail;

        // �жϽ��ֵ�Ƿ����, ������ʹ��root���
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

