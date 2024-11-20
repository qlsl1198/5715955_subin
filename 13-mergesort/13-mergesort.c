#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100
#define MAX_VALUE 999

int comparisonCount, moveCount, isFirst = 0, totalComparisons = 0, totalMoves = 0, rounds = 0;

void generateRandomArray(int randomData[]) {
    srand(time(NULL));
    sleep(1);
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE + 1);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

int sorted[SIZE];

void merge(int list[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        comparisonCount++;
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        } else {
            sorted[k++] = list[j++];
        }
        moveCount++;
    }

    while (i <= mid) {
        sorted[k++] = list[i++];
        moveCount++;
    }

    while (j <= right) {
        sorted[k++] = list[j++];
        moveCount++;
    }

    for (int l = left; l <= right; l++) {
        list[l] = sorted[l];
        moveCount++;
    }

    rounds++;

    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 0; i < 10; i++)
            printf("%3d ", list[i]);
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++)
            printf("%3d ", list[i]);
        printf("\n\n");
    }
}

// 재귀적 방법
void doMergeSort(int list[], int left, int right){
    int mid;
    
    if(left<right){
        mid = (left+right)/2;              // 리스트의 균등분할
        doMergeSort(list, left, mid); // 부분리스트 정렬
        doMergeSort(list, mid+1, right); //부분리스트 정렬
        merge(list, left, mid, right);   // 합병
    }
}

// bonus code
void iterativeMergeSort(int list[], int n) {
    int curr_size;
    int left_start;

    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1;
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? 
                            (left_start + 2 * curr_size - 1) : (n - 1);

            merge(list, left_start, mid, right_end);
        }
    }
}

int main() {
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            iterativeMergeSort(array, SIZE);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        } else {
            iterativeMergeSort(array, SIZE);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\n\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}