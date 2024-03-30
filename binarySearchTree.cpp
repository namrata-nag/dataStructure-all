#include <iostream>
#include <string>

class BinarySearchTree
{
public:
    int value;
    BinarySearchTree *left;
    BinarySearchTree *right;
};

BinarySearchTree *head = NULL;


//create binary search tree
BinarySearchTree *insert(BinarySearchTree *node, int val)
{
    // If head is null i.e no node in the tree
    // then initialize the head
    if (node == NULL && head == NULL)
    {
        BinarySearchTree *new_node = new BinarySearchTree();
        new_node->value = val;
        new_node->left = NULL;
        new_node->right = NULL;
        head = new_node;
        return new_node;
    }

    // If the value inserted is less than the node value
    //then insert in left
    if (node->value > val)
    {
        if (node->left == NULL)
        {
            BinarySearchTree *new_node = new BinarySearchTree();
            new_node->value = val;
            new_node->left = NULL;
            new_node->right = NULL;
            node->left = new_node;
            return new_node;
        }
        return insert(node->left, val);
    }
    else
    {
        // If the value inserted is greater than the node value
        //then insert in the right
        if (node->right == NULL)
        {
            BinarySearchTree *new_node = new BinarySearchTree();
            new_node->value = val;
            new_node->left = NULL;
            new_node->right = NULL;
            node->right = new_node;
            return new_node;
        }
        return insert(node->right, val);
    }
}

// Inorder traversal of Binary Search tree
void traverseInOrder(BinarySearchTree *node)
{
    if (node == NULL)
        return;
    traverseInOrder(node->left);
    std::cout << node->value << "\n";
    traverseInOrder(node->right);
}

// Find the poarent of the predecessor
BinarySearchTree *findPredecessorParent(BinarySearchTree *node)
{
    if (node == NULL)
        return NULL;
    if (node->right == NULL)
        return node;
    if (node->right && node->right->right == NULL)
        return node;
    return findPredecessorParent(node->right);
}

// Delete node from binary search tree
BinarySearchTree *deleteNode(BinarySearchTree *node, int val)
{
    if (node == NULL)
        return NULL;
    if (node->value == val)
    {
        BinarySearchTree *tmpParent = findPredecessorParent(node->left);
        BinarySearchTree *tmp = tmpParent->right;
        // no left child present then swap with right else mark head as NULL
        if (tmpParent == NULL)
        {
            if (node->right == NULL)
            {
                head = NULL;
                return head;
            }
            head = node->right;
            return head;
        }
        // if immediate next child is the predecessor then right of the deleted node become right of predecessor 
        else if (tmp == NULL)
        {
            tmpParent->right = node->right;
            delete node;
            return tmpParent;
        }

        BinarySearchTree *tmp1 = tmp->left;

        tmp->left = node->left;
        tmp->right = node->right;
        tmpParent->right = tmp1;
        delete node;
        return tmp;
    }

    if (node->value > val)
    {
        if (node->left == NULL)
        {
            std::cout << "No Node exist \n";
            return NULL;
        }
        node->left = deleteNode(node->left, val);
    }
    if (node->value < val)
    {
        if (node->right == NULL)
        {
            std::cout << "No Node exist \n";
            return NULL;
        }
        node->right = deleteNode(node->right, val);
    }
    return node;
}

int main()
{

    int array[] = {40, 60, 20, 80, 50, 10, 30, 15, 5, 35, 25, 45, 55, 70, 90, 32, 33, 48, 46};
    int arrLen = 19;
    for (int i = 0; i < 19; i++)
    {
        insert(head, array[i]);
    }
    std::cout << "In oreder Travesal of binary search tree \n";
    traverseInOrder(head);
    // Delete 40 from Binary search tree
    std::cout << "In oreder Travesal after removing 40 from binary search tree \n";
    head = deleteNode(head, 40);
    traverseInOrder(head);
    // Delete 20 from Binary search tree
    head = deleteNode(head, 20);
    std::cout << "In oreder Travesal after removing 20 from binary search tree \n";
    traverseInOrder(head);
}
