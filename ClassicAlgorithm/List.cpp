#include "List.h"



List::List()
{
    head = new ListNode(0);
}


List::~List()
{
    ListNode* cur = head->next;
    ListNode* next;
    while (cur)
    {
        next = cur->next;
        delete cur;
        cur = next;
    }
    delete head;
}

void List::printList()
{
    if (isEmpty())
        return;

    ListNode* p = head->next;
    while (p)
    {
        p->printNode();
        p = p->next;
    }
    log("\n");
}

void List::addValue(int value)
{
    ListNode* cur = head->next;
    ListNode* prev = head;
    while (cur && cur->value < value)
    {
        prev = cur;
        cur = cur->next;
    }

    ListNode* newNode = new ListNode(value);
    if (prev)
    {
        prev->next = newNode;
        newNode->next = cur;
    }
    else if(cur && cur->value <= value)
    {
        cur->next = newNode;
    }
    else
    {
        head->next = newNode;
    }
    ++_size;
}

void List::reverse()
{
    ListNode *prev, *cur, *next;
 
    if (size() < 2)
        return;

    prev = head->next;
    cur = prev->next;

    while (cur)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    head->next->next = nullptr;
    head->next = prev;
}


int main_list(void)
{
    log("main begin\n");

    List list;
    list.addValue(2);
    list.addValue(1);
    list.addValue(0);
    list.addValue(3);

    list.printList();

    list.reverse();
    list.printList();

    log("main end\n");
    return 0;
}


