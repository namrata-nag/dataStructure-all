# Execution

To compile the bubblesort code run the bellow command in the Terminal

```
$ gcc bubbleSort.cpp -lstdc++ -o bubbleSort.out
```
![Alt text](./CompileCode.png?raw=true)


It will create an a.out file in the same folder. Run the file.

```
$ ./bubbleSort.out
```

It will prompt the user to enter the length of the linked list. Enter the length say x.
![Alt text](./EnterLengthOfList.png?raw=true)


It will prompt the user x times to enter the values for nodes.
![Alt text](./EnterValueInList.png?raw=true)

After all the value is entered. It will sort the linked list using bubble sort and print the value in the console.
![Alt text](./OutputValue.png?raw=true)

# Code

sort function is keeping pointer to the first Node(tmp) and the count of unsorted Node (unsortedNodeCount)

Base case will be 
* when there is no node to sort then return NULL
* when only one Node is left to sort then return the Node address

If none of the above cases match then iterate the sort function by passing tmp and (unsortedNodeCount -1) in  the argument.



bubbleSort function is used to traverse the linkedlist till the unsortedNodeCount value.
Base case will be
* No node to sort
* When we have reached the last node or when the value  of unsortedNodeCount is 1 or less

If the current value of the node is greater than the next node then swap using swap function and  call  bubbleSort with the address of next node and  (unsortedNodeCount - 1) as an argument.
