## [result]
<img src="./result.png" width="600">

## [code]
<div align="center">
  <img src="./code2.png" width="400">
  <img src="./code3.png" width="400">
</div>

<div align="center">
  <img src="./code4.png" width="400">
  <img src="./code5.png" width="400">

</div>

<div align="center">
  <img src="./code6.png" width="400">
  <img src="./code7.png" width="400">
</div>

<div align="center">
  <img src="./code8.png" width="400">
  <img src="./code9.png" width="400">
</div>

## [이진 탐색 트리와 AVL 트리 비교 분석]

### 실험 개요
- 데이터 크기: 2000개의 작업(SIZE 매크로)
- 데이터 범위: 0-999 사이의 무작위 숫자(VALUE 매크로)
- 작업 유형: 삽입(A=0), 삭제(A=1), 탐색(A=2)을 무작위로 수행
- 비교 대상: 이진 탐색 트리(BST)와 AVL 트리의 탐색 성능
- 측정 항목: 각 트리에서의 평균 비교 횟수 (compareCount/searchCount)

### 실험 과정
1. 각 트리 구조별로 2000회의 배치 작업 수행
   - doAVLBatch(): AVL 트리에 대한 작업
   - doBinaryBatch(): 이진 탐색 트리에 대한 작업
2. 각 작업마다:
   - 0-2 사이의 무작위 수 A로 작업 종류 결정
   - 0-999 사이의 무작위 수 B로 데이터 값 결정
3. 탐색 작업 시 비교 횟수를 카운트하여 평균 계산

### 성능 차이 분석
1. 트리 균형 유지
   - BST: 삽입 순서에 따라 불균형 발생 가능
   - AVL: 4가지 회전 연산으로 항상 균형 유지
     * 왼쪽-왼쪽(LL) 케이스: 오른쪽 회전
     * 오른쪽-오른쪽(RR) 케이스: 왼쪽 회전
     * 왼쪽-오른쪽(LR) 케이스: 왼쪽-오른쪽 이중 회전
     * 오른쪽-왼쪽(RL) 케이스: 오른쪽-왼쪽 이중 회전

2. 탐색 성능
   - BST: 트리가 불균형할 경우 탐색 비교 횟수 증가
   - AVL: 항상 균형을 유지하여 일관된 탐색 성능 보장

### 결론
실험 결과, AVL 트리와 이진 탐색 트리의 평균 비교 횟수가 비슷하게 나타났습니다. 
이는 무작위로 생성된 데이터의 특성상 이진 탐색 트리도 비교적 균형잡힌 형태를 유지하기 때문입니다.
다만, AVL 트리는 자동 균형 조정 메커니즘을 통해 최악의 경우에도 O(log n)의 성능을 보장하는 반면,
이진 탐색 트리는 데이터 삽입 순서에 따라 최악의 경우 O(n)의 성능이 될 수 있다는 이론적 차이가 있습니다.