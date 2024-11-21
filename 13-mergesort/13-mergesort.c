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
    int curr_size;     // 현재 병합할 부분 배열의 크기
    int left_start;    // 부분 배열의 시작 인덱스

    // 단계적으로 부분 배열의 크기를 1에서부터 점점 2배씩 증가시키며 정렬
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        // 각 병합 단계에서 부분 배열의 시작 위치를 순차적으로 진행
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            // 부분 배열의 중간 지점을 계산
            int mid = left_start + curr_size - 1;

            // 병합할 오른쪽 부분 배열의 끝 지점을 계산
            // 배열의 끝을 초과하지 않도록 조건 추가
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? 
                            (left_start + 2 * curr_size - 1) : (n - 1);

            // 부분 배열을 병합
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

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}