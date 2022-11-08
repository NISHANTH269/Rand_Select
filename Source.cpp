#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;
void Sort(int A[], int initial, int end)
{
    for (int i = initial + 1; i <= end; i++) {
        if (A[i - 1] > A[i]) {
            int tmp = A[i];
            int r = i;
            while (r > initial && A[r - 1] > tmp)
            {
                A[r] = A[r - 1];
                r = r - 1;
            }A[r] = tmp;
        }
    }
}

int tM(int A[], int initial, int end) {
    int i = 0, num1 = 0;
    if (initial == end) return A[initial];
    for (i = initial; i < end - 5; i = i + 5) {
        Sort(A, i, i + 4);
        num1 = i - initial;
        swap(A[initial + num1 / 5], A[i + 2]);
    }
    int num2 = end - i + 1;
    if (num2 > 0)
    {
        Sort(A, i, i + num2 - 1);
        num1 = i - initial;
        swap(A[initial + num2 / 5], A[i + num2 / 2]);
    }
    num1 = num1 / 5;
    if (num1 == initial)
        return A[initial];
    return tM(A, initial, initial + num1);
}

int tM_Index(int A[], int initial, int end, int num)
{
    for (int i = initial; i <= end; i++)
        if (A[i] == num)
            return i;
    return -1;
}

int sort_partition(int A[], int initial, int end, int mid_index)
{
    swap(A[mid_index], A[initial]);
    int i = initial;
    int j = end;
    int pivot = A[initial];
    while (i < j) {
        while (A[j] >= pivot && i < j)
            j = j - 1;
        A[i] = A[j];
        while (A[i] <= pivot && i < j)
            i = i + 1;
        A[j] = A[i];
    }
    A[i] = pivot;
    return i;
}

int rs_worst(int A[], int initial, int end, int k) {
    //rand_select_worst
    int num = tM(A, initial, end); //will tack Mid
    int mid_index = tM_Index(A, initial, end, num);
    int i = sort_partition(A, initial, end, mid_index);
    int new_pivot = i - initial + 1;
    if (new_pivot == k)
        return A[i];
    if (new_pivot > k)
        return rs_worst(A, initial, i - 1, k);
    return rs_worst(A, i + 1, end, k - new_pivot);
}

int get_pivot_expected(int A[], int initial, int end)
{ //expected_pivot
    int pivot = A[initial];
    while (initial < end) { //compare
        while (initial < end && A[end] >= pivot) {
            --end;
        }
        A[initial] = A[end];
        while (initial < end && A[initial] <= pivot) {
            ++initial;
        }
        A[end] = A[initial];
    }
    A[initial] = pivot;
    return initial;
}

void rs_expected(int A[], int initial, int end, int k) {
    //rand_select_expected
    int index;
    if (end < initial) //compare
        return;
    index = get_pivot_expected(A, initial, end);
    if (index == k - 1) {
        printf("For rand_select_expected, the 88th element is %d.\n", A[index]);
        return;
    }
    if (index > k - 1) {
        rs_expected(A, initial, index - 1, k);
    }
    if (index < k - 1) {
        rs_expected(A, index + 1, end, k);
    }
}

int main() {
    int A1[100], A2[100];
    int A[100] = { 0 };
    int A_index = 0;
    srand(time(NULL));
    std::clock_t rand_select_expected_time, rand_select_worst_time;
    double rand_select_expected_duration, rand_select_worst_duration;
    for (int i = 1; i <= 100; i++) {
        do {
            A_index = rand() % 100;
            //generate a random index 0-99 and insert i if A[A_index] is empty
        } while (A[A_index] != 0);
        A[A_index] = i;
    }
    for (int i = 0; i < 100; i++) {
        A1[i] = A[i];
        A2[i] = A[i];
    }
    rand_select_expected_time = std::clock();
    rs_expected(A1, 0, 99, 88);
    rand_select_expected_duration = (std::clock() - rand_select_expected_time) / (double)CLOCKS_PER_SEC;
    rand_select_worst_time = std::clock();
    std::cout << "rand_select_expected running time: " << rand_select_expected_duration << std::endl;
    printf("For rand_select_worst, the 23th element is %d.\n", rs_worst(A2, 0, 99, 23));
    rand_select_worst_duration = (std::clock() - rand_select_expected_time) / (double)CLOCKS_PER_SEC;
    std::cout << "rand_select_worst running time: " << rand_select_worst_duration << std::endl;
    return 0;
}





