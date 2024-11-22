#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define MAX_VALUE 999
#define STACK_SIZE 100

int comparisonCount = 0;
int moveCount = 0;
double totalComparisons = 0;
double totalMoveCount = 0;
int isFirst = 0;
int rounds = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    moveCount += 3;
}

// 퀵 정렬의 파티션 함수
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // 피벗을 배열의 마지막 요소로 선택
    int i = (low - 1);      // 작은 요소의 인덱스

    // 피벗보다 작은 모든 요소를 왼쪽으로 이동
    for (int j = low; j <= high - 1; j++) {
        comparisonCount++;  // 비교 횟수 증가
        if (arr[j] < pivot) {
            i++;  // 작은 요소의 인덱스 증가
            swap(&arr[i], &arr[j]);  // 현재 요소를 작은 요소 영역으로 swap
        }
    }
    swap(&arr[i + 1], &arr[high]);  // 피벗을 올바른 위치로 이동
    return (i + 1);  // 피벗의 최종 위치 반환
}

// 반복적 퀵 정렬 함수
void doQuickSort(int arr[], int low, int high) {
    int stack[STACK_SIZE];  // 스택을 사용하여 재귀 호출 대신 반복 구현
    int top = -1;  // 스택의 top 인덱스

    // 초기 하위 배열 범위를 스택에 push
    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {  // 스택이 비어있지 않은 동안 반복
        high = stack[top--];  // 현재 하위 배열의 high 인덱스
        low = stack[top--];   // 현재 하위 배열의 low 인덱스

        int pi = partition(arr, low, high);  // 파티션 수행

        // 매 10번째 라운드마다 배열의 일부를 출력 (디버깅 또는 진행 상황 확인용)
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n\n");
        }
        rounds++;  // 라운드 수 증가

        // 왼쪽 하위 배열이 존재하면 스택에 push
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        // 오른쪽 하위 배열이 존재하면 스택에 push
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % (MAX_VALUE + 1);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);
            
            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        } else {
            doQuickSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
