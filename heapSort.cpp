#include <iostream>
#include <string>
#include <math.h>

// max heap
void heapify(int arr[], int index)
{

    int left = 2 * index;
    int right = left + 1;
    if (left > arr[0] && right > arr[0])
    {
        return;
    }
    int node_count = arr[0];
    int middle = index;
    int large = arr[middle];
    int largeIndex = middle;

    if (left <= node_count && arr[left] < arr[middle])
    {

        large = arr[left];
        largeIndex = left;
    };
    if (right <= node_count && arr[right] < large)
    {

        large = arr[right];
        largeIndex = right;
    }
    if (large != arr[middle])
    {
        arr[largeIndex] = arr[middle];
        arr[middle] = large;

        heapify(arr, largeIndex);
    }
    else
    {
        return;
    }
}

void heapSort(int arr[], int index)
{
    int last = arr[0];
    if (last < 1)
    {
        return;
    }

    int temp = arr[last];
    arr[last] = arr[1];
    arr[1] = temp;
    arr[0] = last - 1;
    heapify(arr, 1);
    return heapSort(arr, 1);
}

void printArray(int arr[], int index)
{
    int node_count = index;
    for (int i = 1; i <= node_count; i++)
    {
        std::cout << arr[i] << "\n";
    }
}
int main()
{
    int arr[] = {19, 40, 60, 20, 80, 50, 10, 30, 15, 5, 35, 25, 45, 55, 70, 90, 32, 33, 48, 46};
    int node_count = arr[0];
    int middle = floor(node_count / 2);
    for (int i = middle; i > 0; i--)
    {
        heapify(arr, i);
    }

    std::cout << "about to print the array after hapify"
              << "\n";
    printArray(arr, 19);

    std::cout << "about to print the array after heap sort"
              << "\n";
    heapSort(arr, 1);
    printArray(arr, 19);
}