#include <iostream>
#include <string>

// create Node
class Node
{
public:
    int value;
    Node *next;
};

Node *createNewNodeInFront(int x, Node *headNode)
{
    Node *new_node = new Node();
    new_node->value = x;
    new_node->next = headNode;
    return new_node;
}

// print the node vlaue
void printNode(Node *tmp)
{
    if (tmp == NULL)
    {
       std::cout << "Node not found";
    }
    while (tmp != NULL)
    {
        std::cout << tmp->value << "\n";
        tmp = tmp->next;
    }
}

// swap two node
struct Node *swap(struct Node *currentNode, struct Node *nextNode)
{
    struct Node *tmpNode = nextNode->next;
    nextNode->next = currentNode;
    currentNode->next = tmpNode;

    return nextNode;
}

// bubble sort
struct Node *bubbleSort(struct Node *node, int count)
{

    if (node == NULL)
    {
        printf("No node to sort");
        return NULL;
    }
    if (node->next == NULL || count <= 1)
    {
        return node;
    }

    if (node->value > node->next->value)
    {

        // swap
        struct Node *swappedNode = swap(node, node->next);

        // iterate
        swappedNode->next = bubbleSort(swappedNode->next, count - 1);

        return swappedNode;
        
    }

    // iterate
    node->next = bubbleSort(node->next, count - 1);
    return node;
}

// sort an linked list
Node *sort(struct Node *tmp, int unsortedNodeCount)
{
    if (tmp == NULL)
        return NULL;
    if (tmp->next == NULL)
        return tmp;
    if (unsortedNodeCount <= 1)
    {
        return tmp;
    }
    struct Node *updatedList = bubbleSort(tmp, unsortedNodeCount);

    unsortedNodeCount = unsortedNodeCount - 1;
    return sort(updatedList, unsortedNodeCount);
}

int main()
{
    int arr_len;
    int value;
    Node *head = NULL;
    std::cout << "Type length of linked list \n";
    std::cin >> arr_len;
    int counter = arr_len;
    while (counter > 0)
    {
        std::cout << "Enter value to insert in linked list \n";
        std::cin >> value;
        head = createNewNodeInFront(value, head);
        counter = counter - 1;
    }

    head = sort(head, 16);
    std::cout << "Printing sorted nodes \n";
    printNode(head);
    return 0;
}