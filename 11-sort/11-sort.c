#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define MAX_VALUE 999

void swap(int *a, int *b){ // 스왑 함수
    int temp = *a;
    *a = *b;
    *b = temp;
}

void generateRandomData(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE + 1);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

void doSelectionSort(int randomData[]) {
    int comparisons = 0, swaps = 0;
    int tempData[SIZE];
    for (int i = 0; i < SIZE; i++) {
        tempData[i] = randomData[i];
    }
    
    printf("Selection Sort:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < SIZE; j++) {
            comparisons++;
            if (tempData[j] < tempData[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&tempData[i], &tempData[min_idx]);
            swaps++;
        }
        if ((i + 1) % 20 == 10 || i == SIZE - 2) {
            printf("Step %d: ", i + 1);
            printArray(tempData, SIZE);
        }
    }
}

void doInsertionSort(int randomData[]) {
    int totalComparisons = 0;
    int insert_sortedData[SIZE];
    srand(time(NULL)); // 랜덤 시드 생성
    
    for (int k = 0; k < 20; k++) {
        int tempData[SIZE];
        generateRandomData(tempData); // 랜덤 배열 생성 20번 반복
        int comparisons = 0;
        for (int i = 1; i < SIZE; i++) {
            int key = tempData[i];
            int j = i - 1;
            while (j >= 0 && tempData[j] > key) {
                tempData[j + 1] = tempData[j];
                j--;
                comparisons++;
            }
            tempData[j + 1] = key;
            comparisons++;
        }
        totalComparisons += comparisons;
    }
    
    // 원래 배열을 정렬
    for (int i = 0; i < SIZE; i++) {
        insert_sortedData[i] = randomData[i]; // 기존 배열 값 저장
    }
    for (int i = 1; i < SIZE; i++) {
        int key = insert_sortedData[i];
        int j = i - 1;
        while (j >= 0 && insert_sortedData[j] > key) {
            insert_sortedData[j + 1] = insert_sortedData[j];
            j--;
        }
        insert_sortedData[j + 1] = key;
    }
    
    printf("Insertion Sort Compare Average: %d\n", totalComparisons / 20);
    printf("Insertion Sort Result:\n");
    printArray(insert_sortedData, SIZE);
}

void doBubbleSort(int randomData[]) {
    int totalSwaps = 0;
    int bubble_sortedData[SIZE];
    srand(time(NULL)); // 랜덤 시드 생성
    
    for (int k = 0; k < 20; k++) {
        int tempData[SIZE];
        generateRandomData(tempData); // 랜덤 배열 생성 20번 반복
        int swaps = 0;
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (tempData[j] > tempData[j + 1]) {
                    swap(&tempData[j], &tempData[j + 1]);
                    swaps += 3;
                }
            }
        }
        totalSwaps += swaps;
    }
    
    // 원래 배열을 정렬
    for (int i = 0; i < SIZE; i++) {
        bubble_sortedData[i] = randomData[i]; // 기존 배열 값 저장
    }
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (bubble_sortedData[j] > bubble_sortedData[j + 1]) {
                swap(&bubble_sortedData[j], &bubble_sortedData[j + 1]);
            }
        }
    }
    
    printf("Bubble Sort Swap Average: %d\n", totalSwaps / 20);
    printf("Bubble Sort Result:\n");
    printArray(bubble_sortedData, SIZE);
}

int main() {
    int randomData[SIZE];
    
    generateRandomData(randomData);
    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);
    
    return 0;
}