#include <stdio.h>
#include <stdlib.h>

// 두 값을 교환하는 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 힙을 재정렬하는 함수
void resortHeap(int inputData[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 왼쪽 자식이 더 크면 가장 큰 값 갱신
    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    // 오른쪽 자식이 더 크면 가장 큰 값 갱신
    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    // 가장 큰 값이 루트가 아니면 교환하고 재귀적으로 힙 재정렬
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// 힙을 만드는 함수
void BuildMaxHeap(int inputData[], int n) {
    // 배열의 중간부터 시작해서 힙을 재정렬
    for (int i = n / 2 - 1; i >= 0; i--) {
        resortHeap(inputData, n, i);
    }
}

// 삽입 과정을 출력하는 함수
void InsertAndPrint(int inputData[], int n) {
    for (int i = 0; i < n; i++) {
        // 각 노드를 삽입할 때 힙 재정렬
        BuildMaxHeap(inputData, i + 1);
        // 삽입 후 힙 상태 출력
        for (int j = 0; j <= i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

// 힙 정렬 및 상태 출력 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    // 삽입 과정 출력
    InsertAndPrint(inputData, n);

    // 하나씩 힙에서 루트(최대값)를 제거하고 정렬
    for (int i = n - 1; i > 0; i--) {
        // 현재 루트(최대값)와 끝 값 교환
        swap(&inputData[0], &inputData[i]);

        // 힙을 재정렬
        resortHeap(inputData, i, 0);

        // 힙 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main() {
    int inputData[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86};
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}