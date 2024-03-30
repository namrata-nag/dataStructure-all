#include <iostream>
#include <cmath>

/**
 * Do ternary search on an array
 * arry - input array
 * start -  start index
 * itemCount - total item 
*/
int ternarySearch(int arry[], int start, int itemCount, int number)
{

    if (itemCount <= 0)
    {
        return -1;
    }
    if(itemCount == 1 && arry[start] != number ){
        return -1;
    }
    if(itemCount == 1 && arry[start] == number ){
        return start;
    }
    

    int tmp = floor(itemCount / 3);
    int secondIndex = start + tmp;
    int thirdIndex = secondIndex + floor((itemCount - tmp) / 2);
    if (arry[secondIndex] == number)
        return secondIndex;
    if (arry[thirdIndex] == number)
        return thirdIndex;
   
    if (number < arry[secondIndex])
    {
        // iterate throgh first part of the array 
        // itemCount is tmp+1 cause we are using floor to calculate tmp
        return ternarySearch(arry, start, tmp + 1, number);
    }
    else if (number < arry[thirdIndex])
    {
        // iterate throgh second part of the array 
        return ternarySearch(arry, secondIndex + 1, thirdIndex - secondIndex, number);
    }

    // iterate throgh last part of the array 
    return ternarySearch(arry, thirdIndex + 1, itemCount - tmp - 1 - thirdIndex + secondIndex, number);
}

int main()
{
    int array[] = {3, 4, 7, 10, 11, 13, 19, 22, 25, 34, 34, 56, 77, 84, 84, 91};
    int searchNumber;
    std::cout << "Enter the number you want to search\n";
    std::cin >> searchNumber;
    int indexValue = ternarySearch(array, 0, 16, searchNumber);
    if (indexValue >= 0)
    {
        std::cout << "Index is :" << indexValue ;
    }
    else
    {
        std::cout << "Number not present in array";
    }
    std::cout << "\n\nEnter the number you want to search\n";
    std::cin >> searchNumber;
    indexValue = ternarySearch(array, 0, 16, searchNumber);
    if (indexValue >= 0)
    {
        std::cout << "Index is :" << indexValue;
    }
    else
    {
        std::cout << "Number not present in array";
    }
    return 0;
}