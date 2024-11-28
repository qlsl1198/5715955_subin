#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000       // 배열 크기 정의
#define MAX_VALUE 10000   // 배열 내 랜덤 값의 최대값 정의

int compareCount = 0;   // 비교 횟수 카운트 변수

// 랜덤 배열 생성 함수
void generateRandomArray(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % (MAX_VALUE); // 0부터 MAX_VALUE 사이의 랜덤 값 생성
    }
}

// 두 값을 교환하는 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 퀵 정렬의 파티션 함수
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // 피벗을 배열의 마지막 요소로 선택
    int i = (low - 1);      // 작은 요소의 인덱스

    // 피벗보다 작은 모든 요소를 왼쪽으로 이동
    for (int j = low; j <= high - 1; j++) {
        compareCount++;  // 비교 횟수 증가
        if (arr[j] < pivot) {
            i++;  // 작은 요소의 인덱스 증가
            swap(&arr[i], &arr[j]);  // 현재 요소를 작은 요소 영역으로 교환
        }
    }
    swap(&arr[i + 1], &arr[high]);  // 피벗을 올바른 위치로 이동
    return (i + 1);  // 피벗의 최종 위치 반환
}

// 퀵 정렬 메인 함수
void QuickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);  // 배열을 분할하고 피벗의 위치 반환
        QuickSort(array, low, pi - 1);  // 피벗 왼쪽 부분 정렬
        QuickSort(array, pi + 1, high);  // 피벗 오른쪽 부분 정렬
    }
}

// 퀵 정렬 수행 후 비교 횟수 계산 함수
void getQuickSortCompareCount(int array[]) {
    compareCount = 0;  // 비교 횟수 초기화
    QuickSort(array, 0, SIZE - 1);  // 퀵 정렬 수행
}

// 이진 탐색 함수
int binarySearch(int array[], int target) {
    int left = 0, right = SIZE - 1, comparisons = 0;  // 탐색 범위 및 비교 횟수 초기화
    while (left <= right) {
        int mid = left + (right - left) / 2;  // 중간값 계산
        comparisons++;  // 비교 횟수 증가
        if (array[mid] == target) return comparisons;  // 타겟 값 찾으면 비교 횟수 반환
        if (array[mid] < target) left = mid + 1;  // 타겟이 중간값보다 크면 오른쪽 탐색
        else right = mid - 1;  // 타겟이 중간값보다 작으면 왼쪽 탐색
    }
    return comparisons;  // 타겟이 없을 경우 비교 횟수 반환
}

// 이진 탐색 평균 비교 횟수 계산 함수
double getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;  // 전체 비교 횟수 초기화
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];  // 랜덤 타겟 값 생성
        totalComparisons += binarySearch(array, target);  // 이진 탐색 수행 및 비교 횟수 합산
    }
    return (double)totalComparisons / SIZE;  // 평균 비교 횟수 반환
}

int InterpolationSearch(int array[], int target){
    int low, high, j, comparisons = 0;

	low = 0;
	high = SIZE - 1;
	while ((array[high] >= target) && (target > array[low])) {
		j = ((float)(target - array[low]) / (array[high] - array[low])
			*(high - low)) + low;
		
        comparisons++; //비교횟수 증가
        if (target == array[j]) return comparisons; // 타겟 찾을 시 비교횟수 리턴
        else if (target > array[j]) low = j + 1; 
		else high = j - 1;
		comparisons++;
	}
	    
    return comparisons;
}

double getAverageInterpolationSearchComparecount(int array[]){
    int totalComparisons = 0;
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];  // 랜덤 타겟 값 생성
        totalComparisons += InterpolationSearch(array, target);  // 이진 탐색 수행 및 비교 횟수 합산
    }
    return (double)totalComparisons / SIZE;
}

// 배열 내용 일부를 출력하는 함수
void printArray(int *array) {
    printf("Array Sorting Result:\n");
    
    for(int i = 0; i < 20; i++)  // 첫 20개 요소 출력
        printf("%4d ", array[i]);
    printf("\n");
    for(int i = SIZE-20; i < SIZE; i++)  // 마지막 20개 요소 출력
        printf("%4d ", array[i]);
    printf("\n\n");
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);
    
    QuickSort(array, 0, SIZE-1);
    printArray(array);
    
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array));
    
    return 0;
}