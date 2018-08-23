#include <deque>
#include <stack>
#include "Tree.h"


/*
https://blog.csdn.net/xiaoquantouer/article/details/65631708            AAAAAA      二叉树基础知识总结
https://www.cnblogs.com/33debug/p/7252371.html                          AAAAAA      二叉树常见题（进阶）
https://www.cnblogs.com/weiyi-mgh/p/6616008.html                        AAAAAA      二叉树的前序中序后序遍历相互求法


二叉树遍历分为三种：前序、中序、后序，中序遍历最为重要。根据根节点的所在位置顺序命名。
前序:DLR
中序:LDR
后序:LRD
*/

Tree::Tree()
{
}


Tree::~Tree()
{
    if (this->root)
        free(this->root);
}



// 已知前序和中序序列，构建二叉树
TreeNode* Tree::buildTreePreIn(int *preOrder, int* inOrder, int len)
{
    if (len < 1 || !preOrder || !inOrder)
        return nullptr;
    // 前序序列的第一个节点就是根节点
    TreeNode* root = new TreeNode(*preOrder);
    int rootIndex = 0;
    // 在中序序列中找到根节点的位置，根节点之前是其左子树，之后是右子树
    while (rootIndex < len && inOrder[rootIndex] != *preOrder)
        ++rootIndex;
    if (rootIndex >= len)
        return root;
    // 继续构建左子树:从前序序列的第2个字符开始, 中序序列使用根节点之前的部分, 长度为rootIndex
    root->left = buildTreePreIn(preOrder + 1, inOrder, rootIndex);
    // 继续构建右子树:从前序序列的第[rootIndex+1]个字符开始, 中序序列使用根节点之后的部分, 长度为len - (rootIndex + 1)
    root->right = buildTreePreIn(preOrder + rootIndex + 1, inOrder + rootIndex + 1, len - rootIndex - 1);
    return root;
}


// 已知后序和中序序列，构建二叉树
TreeNode* Tree::buildTreePostIn(int *postOrder, int* inOrder, int len)
{
    if (len < 1 || !postOrder || !inOrder)
        return nullptr;
    // 后序序列的第一个节点就是根节点
    TreeNode* root = new TreeNode(postOrder[len - 1]);
    int rootIndex = 0;
    // 在中序序列中找到根节点的位置，根节点之前是其左子树，之后是右子树
    while (rootIndex < len && inOrder[rootIndex] != postOrder[len - 1])
        ++rootIndex;
    if (rootIndex >= len)
        return root;
    // 继续构建左子树:从后序序列的第1个字符开始, 中序序列使用根节点之前的部分, 长度为rootIndex
    root->left = buildTreePostIn(postOrder, inOrder, rootIndex);
    // 继续构建右子树:从后序序列的第[rootIndex]个字符开始, 中序序列使用根节点之后的部分, 长度为len - (rootIndex + 1)
    root->right = buildTreePostIn(postOrder + rootIndex, inOrder + rootIndex + 1, len - rootIndex - 1);
    return root;
}


// 释放节点及子结点
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


// 前序遍历输出--递归
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


// 前序遍历输出--非递归
void Tree::printPreOrderIter(TreeNode *root)
{
    if (!root)
        return;

    TreeNode* curNode = nullptr;
    std::stack<TreeNode*> nodeStack;
    // 从根节点开始, 将节点入栈
    nodeStack.push(root);

    while (!nodeStack.empty())
    {
        // 前序遍历, 首先遍历父节点, 所以在此循环中先从根节点开始遍历栈中节点, 向左走到叶子节点
        curNode = nodeStack.top();
        while (curNode)
        {
            curNode->printNode();           // 输出当前结点值
            nodeStack.push(curNode->left);
            curNode = nodeStack.top();
        }
        nodeStack.pop();                    // 当前节点的左子树为空, 弹出空的左子树
        if (!nodeStack.empty())
        {
            curNode = nodeStack.top();      // 弹出当前节点, 因为上面已经遍历过了
            nodeStack.pop();
            nodeStack.push(curNode->right); // 向右走一步, 下次循环自此开始, 遍历右结点
        }
    }
    // end of while loop
    return;
}



// 中序遍历输出--递归
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


// 中序遍历输出--非递归
void Tree::printInOrderIter(TreeNode *root)
{
    if (!root)
        return;

    TreeNode* curNode = nullptr;
    std::stack<TreeNode*> nodeStack;
    // 从根节点开始, 将节点入栈
    nodeStack.push(root);

    while (!nodeStack.empty())
    {
        curNode = nodeStack.top();
        while (curNode)
        {
            nodeStack.push(curNode->left);
            curNode = nodeStack.top();
        }
        nodeStack.pop();                    // 当前节点的左子树为空, 弹出空的左子树
        if (!nodeStack.empty())
        {
            curNode = nodeStack.top();      // 弹出当前节点, 因为上面已经遍历过了
            curNode->printNode();           // 输出当前结点值
            nodeStack.pop();
            nodeStack.push(curNode->right); // 向右走一步, 下次循环自此开始, 遍历右结点
        }
    }
}


// 后序遍历输出--递归
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


// 后序遍历输出--非递归
void Tree::printPostOrderIter(TreeNode *root)
{
    if (!root)
        return;

    TreeNode* lastVisitedNode = root;               // 上次访问过的结点, 初始设置为root, 如果设置为nullptr, 输出结点时需要判断
    TreeNode* curNode = nullptr;                    // 当前结点
    std::stack<TreeNode*> nodeStack;                // 结点栈
    nodeStack.push(root);                           // 从根节点开始, 将节点入栈

    while (!nodeStack.empty())
    {
        curNode = nodeStack.top();
        // 后续遍历, LRD, 当前结点D已经在栈中, 根据栈先入后出的性质, 先入栈右结点R, 然后入栈左结点L
        // 通过lastVisitedNode是否是当前结点的直接子结点, 判断是否已经访问过当前结点, 未访问时才入栈
        if (curNode && curNode->hasRight() && !curNode->isChildren(lastVisitedNode))
            nodeStack.push(curNode->right);
        if (curNode && curNode->hasLeft() && !curNode->isChildren(lastVisitedNode))
            nodeStack.push(curNode->left);

        if (!nodeStack.empty())
        {
            curNode = nodeStack.top();
            // 3种情况可以输出当前结点值, 并出栈:
            // 1.当前结点是叶子结点
            // 2.当前结点非叶子结点, 并且在父节点的左子树上, 上次访问的结点是当前结点的直接左结点, 此时正在左子树上回朔
            // 3.当前结点非叶子结点, 并且在父节点的右子树上, 上次访问的结点是当前结点的直接右结点, 此时正在右子树上回朔
            if (
                (curNode->hasLeft() == false && curNode->hasRight() == false) ||
                (lastVisitedNode == curNode->left) ||
                (lastVisitedNode == curNode->right)
                )
            {
                curNode->printNode();           // 输出当前结点值
                nodeStack.pop();
                lastVisitedNode = curNode;      // 记录上次访问结点
            }
        }
        // end of if loop:栈非空
    }
    // end of while loop
}


// 层级输出
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
    // 若value关键字不在root中出现，则插入
    if (!keyNode)
    {
        if (!root)
            root = new TreeNode(value);
        else if (root->value > value)
        {
            // 插入左子树
            insert(root->left, value);
        }
        else
        {
            // 插入右子树
            insert(root->right, value);
        }
    }
}


// 两个节点的最近公共祖先
TreeNode* Tree::getNearestAncestor(TreeNode* root, TreeNode* fir, TreeNode* sec)
{
    if (!root || !fir || !sec)
        return nullptr;

    if (fir->value <= root->value && sec->value <= root->value)
        //两个节点都小于根节点，最近公共祖先在左子树中
        return getNearestAncestor(root->left, fir, sec);
    else if (fir->value > root->value && sec->value > root->value)
        //两个节点都大于根节点，最近公共祖先在右子树中
        return getNearestAncestor(root->right, fir, sec);
    else
        //一个在左子树，一个在右子树，找到公共祖先
        return root;
}


// 二叉树的宽度, 二叉树各层节点个数的最大值
/*
对于特定某一层的节点的个数，因此我们需要从头结点开始，记录每一层的个数，对于当前层的每一个节点，
在弹出自身之后把其左右子树压入 queue，当把当前层全部弹出队列之后，在队列中剩下的就是下一层的节点。
然后比较队列的size和之前得到的maxWidth，取最大值即为队列的宽度。最终队列为空，得到的maxWidth就是二叉树的宽度！
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


// 二叉树的高度, 叶子节点的最大深度值
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


// 查找二叉树中元素
TreeNode* Tree::search(TreeNode* root, int value)
{
    if (!root)
        return nullptr;

    TreeNode* keyNode = nullptr;
    if (root->value == value)
        keyNode = root;
    else if (root->value > value)
        // value小于当前节点的关键字，则查找左子树
        keyNode = search(root->left, value);
    else
        // 查找右子树
        keyNode = search(root->right, value);
    return keyNode;
}


// 中序遍历时, 排序二叉树的相邻节点的最大差值
int Tree::inOrderMaxDiff(TreeNode* root, int & maxDiff, int lastValue)
{
    if (!root)
        return 0;
    
    // 左结点处理:递归到首个叶子节点, 在返回时处理, 记录上次结点的值, 使用当前结点值减去上次结点值
    if (root->hasLeft())
        lastValue = inOrderMaxDiff(root->left, maxDiff, lastValue);
    
    // 跳过排序的首个叶子节点
    if (lastValue > 0)
        maxDiff = std::max(maxDiff, root->value - lastValue);
    
    log("cur:%d, lastValue:%d, maxDiff:%d\n", root->value, lastValue, maxDiff);
    lastValue = root->value;
    
    // 右结点处理:递归处理, 右结点只能减去上次结点的值
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

    printf("两个节点的最近公共祖先:\n");
    TreeNode a(0 + '0');
    TreeNode b(3 + '0');
    TreeNode* ancestor = t.getNearestAncestor(t.root, &a, &b);
    t.printTree(ancestor);

    printf("二叉树的宽度:%d\n", t.width(t.root));
    printf("二叉树的高度:%d\n", t.height(t.root));
    
    log("前序遍历输出:\n");
    t.printPreOrder(t.root);
    log("\n");
    t.printPreOrderIter(t.root);
    log("\n");
    log("中序遍历输出:\n");
    t.printInOrder(t.root);
    log("\n");
    t.printInOrderIter(t.root);
    log("\n");
    log("后序遍历输出:\n");
    t.printPostOrder(t.root);
    log("\n");
    t.printPostOrderIter(t.root);
    log("\n");
    
    int maxDiff = 0;
    t.inOrderMaxDiff(t.root, maxDiff);
    printf("二叉树相邻节点的最大差值:%d\n", maxDiff);

    /*printf("------------ 已知前序和中序序列，构建二叉树 begin ---------------\n");
    int preArr[] = {'A', 'B', 'D', 'E', 'C', 'F', 'G'};
    int inArr[] = {'D', 'B', 'E', 'A', 'F', 'C', 'G'};
    int preArrLen = sizeof(preArr) / sizeof(int);
    TreeNode *newTree = Tree::buildTreePreIn(preArr, inArr, preArrLen);
    t.printTree(newTree);
    Tree::free(newTree);
    printf("------------ 已知前序和中序序列，构建二叉树 end ---------------\n");

    printf("------------ 已知后序和中序序列，构建二叉树 begin ---------------\n");
    int postArr[] = { 'D', 'E', 'B', 'F', 'G', 'C', 'A' };
    int inArr2[] = { 'D', 'B', 'E', 'A', 'F', 'C', 'G' };
    int postArrLen = sizeof(postArr) / sizeof(int);
    newTree = Tree::buildTreePostIn(postArr, inArr2, postArrLen);
    t.printTree(newTree);
    Tree::free(newTree);
    printf("------------ 已知后序和中序序列，构建二叉树 end ---------------\n");*/

    printf("main end\n");
}