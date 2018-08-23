#include <deque>
#include <stack>
#include "Tree.h"


/*
https://blog.csdn.net/xiaoquantouer/article/details/65631708            AAAAAA      ����������֪ʶ�ܽ�
https://www.cnblogs.com/33debug/p/7252371.html                          AAAAAA      �����������⣨���ף�
https://www.cnblogs.com/weiyi-mgh/p/6616008.html                        AAAAAA      ��������ǰ�������������໥��


������������Ϊ���֣�ǰ�����򡢺������������Ϊ��Ҫ�����ݸ��ڵ������λ��˳��������
ǰ��:DLR
����:LDR
����:LRD
*/

Tree::Tree()
{
}


Tree::~Tree()
{
    if (this->root)
        free(this->root);
}



// ��֪ǰ����������У�����������
TreeNode* Tree::buildTreePreIn(int *preOrder, int* inOrder, int len)
{
    if (len < 1 || !preOrder || !inOrder)
        return nullptr;
    // ǰ�����еĵ�һ���ڵ���Ǹ��ڵ�
    TreeNode* root = new TreeNode(*preOrder);
    int rootIndex = 0;
    // �������������ҵ����ڵ��λ�ã����ڵ�֮ǰ������������֮����������
    while (rootIndex < len && inOrder[rootIndex] != *preOrder)
        ++rootIndex;
    if (rootIndex >= len)
        return root;
    // ��������������:��ǰ�����еĵ�2���ַ���ʼ, ��������ʹ�ø��ڵ�֮ǰ�Ĳ���, ����ΪrootIndex
    root->left = buildTreePreIn(preOrder + 1, inOrder, rootIndex);
    // ��������������:��ǰ�����еĵ�[rootIndex+1]���ַ���ʼ, ��������ʹ�ø��ڵ�֮��Ĳ���, ����Ϊlen - (rootIndex + 1)
    root->right = buildTreePreIn(preOrder + rootIndex + 1, inOrder + rootIndex + 1, len - rootIndex - 1);
    return root;
}


// ��֪������������У�����������
TreeNode* Tree::buildTreePostIn(int *postOrder, int* inOrder, int len)
{
    if (len < 1 || !postOrder || !inOrder)
        return nullptr;
    // �������еĵ�һ���ڵ���Ǹ��ڵ�
    TreeNode* root = new TreeNode(postOrder[len - 1]);
    int rootIndex = 0;
    // �������������ҵ����ڵ��λ�ã����ڵ�֮ǰ������������֮����������
    while (rootIndex < len && inOrder[rootIndex] != postOrder[len - 1])
        ++rootIndex;
    if (rootIndex >= len)
        return root;
    // ��������������:�Ӻ������еĵ�1���ַ���ʼ, ��������ʹ�ø��ڵ�֮ǰ�Ĳ���, ����ΪrootIndex
    root->left = buildTreePostIn(postOrder, inOrder, rootIndex);
    // ��������������:�Ӻ������еĵ�[rootIndex]���ַ���ʼ, ��������ʹ�ø��ڵ�֮��Ĳ���, ����Ϊlen - (rootIndex + 1)
    root->right = buildTreePostIn(postOrder + rootIndex, inOrder + rootIndex + 1, len - rootIndex - 1);
    return root;
}


// �ͷŽڵ㼰�ӽ��
void Tree::free(TreeNode* p)
{
    if (p)
    {
        printf("free:");
        p->printNode();
        if (p->hasLeft())
            free(p->left);
        if (p->hasRight())
            free(p->right);
        delete p;
    }
    printf("\n");
}


// ǰ��������--�ݹ�
void Tree::printPreOrder(TreeNode* root)
{
    if (!root)
        return;
    root->printNode();
    if (root->hasLeft())
        printPreOrder(root->left);
    if (root->hasRight())
        printPreOrder(root->right);
}


// ǰ��������--�ǵݹ�
void Tree::printPreOrderIter(TreeNode *root)
{
    if (!root)
        return;

    TreeNode* curNode = nullptr;
    std::stack<TreeNode*> nodeStack;
    // �Ӹ��ڵ㿪ʼ, ���ڵ���ջ
    nodeStack.push(root);

    while (!nodeStack.empty())
    {
        // ǰ�����, ���ȱ������ڵ�, �����ڴ�ѭ�����ȴӸ��ڵ㿪ʼ����ջ�нڵ�, �����ߵ�Ҷ�ӽڵ�
        curNode = nodeStack.top();
        while (curNode)
        {
            curNode->printNode();           // �����ǰ���ֵ
            nodeStack.push(curNode->left);
            curNode = nodeStack.top();
        }
        nodeStack.pop();                    // ��ǰ�ڵ��������Ϊ��, �����յ�������
        if (!nodeStack.empty())
        {
            curNode = nodeStack.top();      // ������ǰ�ڵ�, ��Ϊ�����Ѿ���������
            nodeStack.pop();
            nodeStack.push(curNode->right); // ������һ��, �´�ѭ���Դ˿�ʼ, �����ҽ��
        }
    }
    // end of while loop
    return;
}



// ����������--�ݹ�
void Tree::printInOrder(TreeNode* root)
{
    if (!root)
        return;
    if (root->hasLeft())
        printInOrder(root->left);
    root->printNode();
    if (root->hasRight())
        printInOrder(root->right);
}


// ����������--�ǵݹ�
void Tree::printInOrderIter(TreeNode *root)
{
    if (!root)
        return;

    TreeNode* curNode = nullptr;
    std::stack<TreeNode*> nodeStack;
    // �Ӹ��ڵ㿪ʼ, ���ڵ���ջ
    nodeStack.push(root);

    while (!nodeStack.empty())
    {
        curNode = nodeStack.top();
        while (curNode)
        {
            nodeStack.push(curNode->left);
            curNode = nodeStack.top();
        }
        nodeStack.pop();                    // ��ǰ�ڵ��������Ϊ��, �����յ�������
        if (!nodeStack.empty())
        {
            curNode = nodeStack.top();      // ������ǰ�ڵ�, ��Ϊ�����Ѿ���������
            curNode->printNode();           // �����ǰ���ֵ
            nodeStack.pop();
            nodeStack.push(curNode->right); // ������һ��, �´�ѭ���Դ˿�ʼ, �����ҽ��
        }
    }
}


// ����������--�ݹ�
void Tree::printPostOrder(TreeNode* root)
{
    if (!root)
        return;
    if (root->hasLeft())
        printPostOrder(root->left);
    if (root->hasRight())
        printPostOrder(root->right);
    root->printNode();
}


// ����������--�ǵݹ�
void Tree::printPostOrderIter(TreeNode *root)
{
    if (!root)
        return;

    TreeNode* lastVisitedNode = root;               // �ϴη��ʹ��Ľ��, ��ʼ����Ϊroot, �������Ϊnullptr, ������ʱ��Ҫ�ж�
    TreeNode* curNode = nullptr;                    // ��ǰ���
    std::stack<TreeNode*> nodeStack;                // ���ջ
    nodeStack.push(root);                           // �Ӹ��ڵ㿪ʼ, ���ڵ���ջ

    while (!nodeStack.empty())
    {
        curNode = nodeStack.top();
        // ��������, LRD, ��ǰ���D�Ѿ���ջ��, ����ջ������������, ����ջ�ҽ��R, Ȼ����ջ����L
        // ͨ��lastVisitedNode�Ƿ��ǵ�ǰ����ֱ���ӽ��, �ж��Ƿ��Ѿ����ʹ���ǰ���, δ����ʱ����ջ
        if (curNode && curNode->hasRight() && !curNode->isChildren(lastVisitedNode))
            nodeStack.push(curNode->right);
        if (curNode && curNode->hasLeft() && !curNode->isChildren(lastVisitedNode))
            nodeStack.push(curNode->left);

        if (!nodeStack.empty())
        {
            curNode = nodeStack.top();
            // 3��������������ǰ���ֵ, ����ջ:
            // 1.��ǰ�����Ҷ�ӽ��
            // 2.��ǰ����Ҷ�ӽ��, �����ڸ��ڵ����������, �ϴη��ʵĽ���ǵ�ǰ����ֱ������, ��ʱ�����������ϻ�˷
            // 3.��ǰ����Ҷ�ӽ��, �����ڸ��ڵ����������, �ϴη��ʵĽ���ǵ�ǰ����ֱ���ҽ��, ��ʱ�����������ϻ�˷
            if (
                (curNode->hasLeft() == false && curNode->hasRight() == false) ||
                (lastVisitedNode == curNode->left) ||
                (lastVisitedNode == curNode->right)
                )
            {
                curNode->printNode();           // �����ǰ���ֵ
                nodeStack.pop();
                lastVisitedNode = curNode;      // ��¼�ϴη��ʽ��
            }
        }
        // end of if loop:ջ�ǿ�
    }
    // end of while loop
}


// �㼶���
void Tree::printTree(TreeNode* p)
{
    if (!p && !root)
        return;

    TreeNode* printNode = root;
    if (p)
        printNode = p;

    for (int i = 0; i < 60; ++i)
        log("%d", i % 10);
    log("\n");

    int queLen = 0;
    int width = this->width(printNode) * TREE_NODE_SPACE * 2;
    std::deque<TreeNode*>   queue;
    printNode->xpos = width;
    queue.push_front(printNode);
    TreeNode* cur = nullptr;

    printNode->printNode();
    log("\n");

    int lastXPos = 0;

    while (queue.size() > 0)
    {
        lastXPos = 0;
        queLen = queue.size();
        while (queLen-- > 0)
        {
            cur = queue.back();
            if (cur->hasLeft())
            {
                cur->left->xpos = cur->xpos - TREE_NODE_SPACE * 2;
                cur->left->printNode(lastXPos);
                lastXPos = cur->left->xpos;
                queue.push_front(cur->left);
            }
            if (cur->hasRight())
            {
                cur->right->xpos = cur->xpos + TREE_NODE_SPACE * 2;
                cur->right->printNode(lastXPos);
                lastXPos = cur->right->xpos;
                queue.push_front(cur->right);
            }

            queue.pop_back();
        }

        log("\n");
    }
}


void Tree::insert(TreeNode * & root, int value)
{
    TreeNode* keyNode = nullptr;
    keyNode = search(root, value);
    // ��value�ؼ��ֲ���root�г��֣������
    if (!keyNode)
    {
        if (!root)
            root = new TreeNode(value);
        else if (root->value > value)
        {
            // ����������
            insert(root->left, value);
        }
        else
        {
            // ����������
            insert(root->right, value);
        }
    }
}


// �����ڵ�������������
TreeNode* Tree::getNearestAncestor(TreeNode* root, TreeNode* fir, TreeNode* sec)
{
    if (!root || !fir || !sec)
        return nullptr;

    if (fir->value <= root->value && sec->value <= root->value)
        //�����ڵ㶼С�ڸ��ڵ㣬���������������������
        return getNearestAncestor(root->left, fir, sec);
    else if (fir->value > root->value && sec->value > root->value)
        //�����ڵ㶼���ڸ��ڵ㣬���������������������
        return getNearestAncestor(root->right, fir, sec);
    else
        //һ������������һ�������������ҵ���������
        return root;
}


// �������Ŀ��, ����������ڵ���������ֵ
/*
�����ض�ĳһ��Ľڵ�ĸ��������������Ҫ��ͷ��㿪ʼ����¼ÿһ��ĸ��������ڵ�ǰ���ÿһ���ڵ㣬
�ڵ�������֮�������������ѹ�� queue�����ѵ�ǰ��ȫ����������֮���ڶ�����ʣ�µľ�����һ��Ľڵ㡣
Ȼ��Ƚ϶��е�size��֮ǰ�õ���maxWidth��ȡ���ֵ��Ϊ���еĿ�ȡ����ն���Ϊ�գ��õ���maxWidth���Ƕ������Ŀ�ȣ�
*/
int Tree::width(TreeNode* root)
{
    if (!root)
        return 0;

    size_t maxWidth = 1;
    std::deque<TreeNode*> queue;
    queue.push_front(root);
    
    while (!queue.empty())
    {
        int length = queue.size();
        while (length-- > 0)
        {
            TreeNode* p = queue.back();
            queue.pop_back();
            if (p->left)
                queue.push_front(p->left);
            if (p->right)
                queue.push_front(p->right);
        }

        maxWidth = std::max(maxWidth, queue.size());
    }

    return maxWidth;
}


// �������ĸ߶�, Ҷ�ӽڵ��������ֵ
int Tree::height(TreeNode* root)
{
    if (!root)
        return 0;

    int maxHeight = 0;
    int leftHeight = 0, rightHeight = 0;

    if (root->hasLeft())
        leftHeight = height(root->left);
    if (root->hasRight())
        rightHeight = height(root->right);

    maxHeight = std::max(leftHeight, rightHeight) + 1;
    return maxHeight;
}


// ���Ҷ�������Ԫ��
TreeNode* Tree::search(TreeNode* root, int value)
{
    if (!root)
        return nullptr;

    TreeNode* keyNode = nullptr;
    if (root->value == value)
        keyNode = root;
    else if (root->value > value)
        // valueС�ڵ�ǰ�ڵ�Ĺؼ��֣������������
        keyNode = search(root->left, value);
    else
        // ����������
        keyNode = search(root->right, value);
    return keyNode;
}


// �������ʱ, ��������������ڽڵ������ֵ
int Tree::inOrderMaxDiff(TreeNode* root, int & maxDiff, int lastValue)
{
    if (!root)
        return 0;
    
    // ���㴦��:�ݹ鵽�׸�Ҷ�ӽڵ�, �ڷ���ʱ����, ��¼�ϴν���ֵ, ʹ�õ�ǰ���ֵ��ȥ�ϴν��ֵ
    if (root->hasLeft())
        lastValue = inOrderMaxDiff(root->left, maxDiff, lastValue);
    
    // ����������׸�Ҷ�ӽڵ�
    if (lastValue > 0)
        maxDiff = std::max(maxDiff, root->value - lastValue);
    
    log("cur:%d, lastValue:%d, maxDiff:%d\n", root->value, lastValue, maxDiff);
    lastValue = root->value;
    
    // �ҽ�㴦��:�ݹ鴦��, �ҽ��ֻ�ܼ�ȥ�ϴν���ֵ
    if (root->hasRight())
        lastValue = inOrderMaxDiff(root->right, maxDiff, lastValue);
    
    return lastValue;
}


int main(void)
{
    printf("main begin\n");

    Tree t;
    int arr[] = {40, 25, 72, 16, 15, 20, 31, 50, 52, 69};
    int brr[] = { 5, 4, 7, 1, 0, 2, 6, 3, 8, 9 };
    for (int i = 1; i < 11; ++i)
    {
        //t.insert(t.root, arr[i - 1]);
        t.insert(t.root, brr[i - 1]);
    }

    t.printTree();

    printf("�����ڵ�������������:\n");
    TreeNode a(0 + '0');
    TreeNode b(3 + '0');
    TreeNode* ancestor = t.getNearestAncestor(t.root, &a, &b);
    t.printTree(ancestor);

    printf("�������Ŀ��:%d\n", t.width(t.root));
    printf("�������ĸ߶�:%d\n", t.height(t.root));
    
    log("ǰ��������:\n");
    t.printPreOrder(t.root);
    log("\n");
    t.printPreOrderIter(t.root);
    log("\n");
    log("����������:\n");
    t.printInOrder(t.root);
    log("\n");
    t.printInOrderIter(t.root);
    log("\n");
    log("����������:\n");
    t.printPostOrder(t.root);
    log("\n");
    t.printPostOrderIter(t.root);
    log("\n");
    
    int maxDiff = 0;
    t.inOrderMaxDiff(t.root, maxDiff);
    printf("���������ڽڵ������ֵ:%d\n", maxDiff);

    /*printf("------------ ��֪ǰ����������У����������� begin ---------------\n");
    int preArr[] = {'A', 'B', 'D', 'E', 'C', 'F', 'G'};
    int inArr[] = {'D', 'B', 'E', 'A', 'F', 'C', 'G'};
    int preArrLen = sizeof(preArr) / sizeof(int);
    TreeNode *newTree = Tree::buildTreePreIn(preArr, inArr, preArrLen);
    t.printTree(newTree);
    Tree::free(newTree);
    printf("------------ ��֪ǰ����������У����������� end ---------------\n");

    printf("------------ ��֪������������У����������� begin ---------------\n");
    int postArr[] = { 'D', 'E', 'B', 'F', 'G', 'C', 'A' };
    int inArr2[] = { 'D', 'B', 'E', 'A', 'F', 'C', 'G' };
    int postArrLen = sizeof(postArr) / sizeof(int);
    newTree = Tree::buildTreePostIn(postArr, inArr2, postArrLen);
    t.printTree(newTree);
    Tree::free(newTree);
    printf("------------ ��֪������������У����������� end ---------------\n");*/

    printf("main end\n");
}