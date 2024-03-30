#include <iostream>

class Node
{
public:
    int value;
    Node *left;
    Node *right;
    int height;
};

Node *newNode(int val)
{
    Node *tmp = new Node();
    tmp->value = val;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->height = 1;

    return tmp;
}

int height(Node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

int checkBalance(Node *parent)
{

    if (parent == NULL)
        return 0;
    return height(parent->left) - height(parent->right);

}

int maxheight(Node *left, Node *right)
{

    int leftH = height(left);
    int rightH = height(right);
    return (leftH > rightH) ? leftH : rightH;
}

Node *leftRotate(Node *tmp)
{
    Node *middle = tmp->right;
    Node *middleLeft = middle->left;
    middle->left = tmp;
    tmp->right = middleLeft;
    middle->height = 1 + maxheight(middle->left, middle->right);
    tmp->height = 1 + maxheight(tmp->left, tmp->right);
    return middle;
}

Node *rightRotate(Node *tmp)
{

    Node *middle = tmp->left;
    Node *leftRightChild = middle->right;
    middle->right = tmp;
    tmp->left = leftRightChild;
    middle->height = 1 + maxheight(middle->left, middle->right);
    tmp->height = 1 + maxheight(tmp->left, tmp->right);
    return middle;
}

Node *insert(Node *tmp, int val)
{

    if (tmp == NULL)
    {
        return newNode(val);
    }
    else if (val > tmp->value)
    {
        tmp->right = insert(tmp->right, val);
    }
    else
    {
        tmp->left = insert(tmp->left, val);
    }

    tmp->height = 1 + maxheight(tmp->left, tmp->right);
    int heightDiff = checkBalance(tmp);

    if (heightDiff > 1 && val < tmp->left->value)
    {

        std::cout << "LL " << heightDiff << "\n";
        return rightRotate(tmp);
    }
    else if (heightDiff > 1 && val > tmp->left->value)
    {
        std::cout << "LR " << heightDiff << "\n";
        tmp->left = leftRotate(tmp->left);
        return rightRotate(tmp);
    }
    else if (heightDiff < -1 && val > tmp->right->value)
    {
        std::cout << "RR " << heightDiff << "\n";
        return leftRotate(tmp);
    }
    else if (heightDiff < -1 && val < tmp->right->value)
    {
        std::cout << "RL " << heightDiff << "\n";
        tmp->right = rightRotate(tmp->right);
        return leftRotate(tmp);
    }
    else
    {
        return tmp;
    }
}

void preOrder(Node *root)
{
    if (root != NULL)
    {
        std::cout << "{"
                  << "\n";
        std::cout << "       " << root->value << "\n";
        std::cout << "       " << root->height << "\n";
        std::cout << "}"
                  << "\n";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    Node *root = NULL;

    /* Constructing tree given in
    the above figure */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);

    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    preOrder(root);
}