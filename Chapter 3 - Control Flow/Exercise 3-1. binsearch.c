/*
Exercise  3-1. Our binary search makes two tests inside the loop, when one would
suffice (at the price of more tests outside.) Write a version with only one test
inside the loop and measure the difference in run-time.

To change version of function comment out either line 30 or 31.
Tested with linux command 'time':
    binsearch     ~= 16s
    binsearch_new ~= 15s

matxo
*/

#include <stdio.h>

int binsearch(int x, int v[], int n);
int binsearch_new(int x, int v[], int n);

int main()
{
    int x = 32;
    int n = 1000000;
    int v[n];
    for (int i = 0; i < n; i++)
        v[i] = i;
    printf("binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]\n");
    //printf("result:\t%i\n", binsearch(x, v, n));
    printf("result:\t%i\n", binsearch_new(x, v, n));
    return 0;
}

// binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] (original version)
int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high)/2;
        if (x < v[mid])
            high = mid - 1;
        else if (x  > v[mid])
            low = mid + 1;
        else    // found match
            return mid;
    }
    return -1;  // no match
}

// binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] (new version)
int binsearch_new(int x, int v[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high && x != v[mid]) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    if ( x == v[mid])
        return mid;
    else
        return -1;
}
