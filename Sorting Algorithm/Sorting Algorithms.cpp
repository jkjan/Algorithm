#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "myheap.h"
#include "myqueue.h"
#include "mytree.h"

using namespace std;

void printArray(int* array, int size);

void insertionSort(int* array, int size);
void selectionSort(int* array, int size);
void bubbleSort(int* array, int size);
void mergeSort(int* array, int s, int e);
void quickSort(int* array, int s, int e);
void heapSort(int* array, int size);
void countSort(int* array, int size);
void radixSort(int* array, int size);
void treeSort(int* array, int size);
void bogoSort(int* array, int size);

int* intArray;

int main(int argc, char** argv) {
	int sortingSelect;
	clock_t start, end;

	intArray = new int[SIZE];

	srand(time(NULL));

	for (int i = 0; i < SIZE; i++) {
		intArray[i] = rand() % 100000;
	}

	cout << "Which sorting algorithm do you want me to use, sir?" << endl;
	cout << endl;
	cout << "1 : Insertion Sort" << endl;
	cout << "2 : Selection Sort" << endl;
	cout << "3 : Bubble Sort" << endl;
	cout << "4 : Merge Sort" << endl;
	cout << "5 : Quick Sort" << endl;
	cout << "6 : Heap Sort" << endl;
	cout << "7 : Count Sort" << endl;
	cout << "8 : Radix Sort" << endl;
	cout << "9 : Tree Sort" << endl;
	cout << "10 : Bogo Sort (BONUS!)" << endl;
	cout << endl;

	cin >> sortingSelect;
	cout << endl;

	cout << "original array : " << endl;
	printArray(intArray, SIZE);

	cout << endl;
	switch (sortingSelect) {
	case 1:
		start = clock();
		insertionSort(intArray, SIZE);
		end = clock();
		break;
	case 2:
		start = clock();
		selectionSort(intArray, SIZE);
		end = clock();
		break;
	case 3:
		start = clock();
		bubbleSort(intArray, SIZE);
		end = clock();
		break;
	case 4:
		start = clock();
		mergeSort(intArray, 0, SIZE - 1);
		end = clock();
		break;
	case 5:
		start = clock();
		quickSort(intArray, 0, SIZE - 1);
		end = clock();
		break;
	case 6:
		start = clock();
		heapSort(intArray, SIZE);
		end = clock();
		break;
	case 7:
		start = clock();
		countSort(intArray, SIZE);
		end = clock();
		break;
	case 8:
		start = clock();
		radixSort(intArray, SIZE);
		end = clock();
		break;
	case 9:
		start = clock();
		treeSort(intArray, SIZE);
		end = clock();
		break;
	case 10:
		cout << "Stay calm and wait. It is no infinite loop." << endl;
		start = clock();
		bogoSort(intArray, SIZE);
		end = clock();
		break;
	default:
		break;
	}
	cout << "sorted array : " << endl;
	printArray(intArray, SIZE);
	cout << endl;
	printf("%.8f seconds", (double)(end - start) / CLOCKS_PER_SEC);
	delete[] intArray;
	return 0;
}

void printArray(int* array, int size) {
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insertionSort(int* array, int size) { // 1. 삽입 정렬 
	int insert;
	for (int i = 1; i < size; i++) { // 배열의 앞부분 배열의 크기를 증가시키면서 
		for (int j = 0; j < i; j++) { // 그 앞부분 배열의 원소를 처음부터 탐색하며 
			if (array[i] < array[j]) { // 바로 뒤의 원소보다 큰 값이 발견되면 
				insert = array[i];  // 이를 그 원소가 삽입될 자리라고 판단하고 
				for (int k = i - 1; k >= j; k--) { // 그 원소를 다 뒤로 한 칸 씩 당긴 후에 
					array[k + 1] = array[k];
				}
				array[j] = insert; // 삽입될 자리에 그 원소를 삽입한다. 
			}
		}
	}
}

void selectionSort(int* array, int size) { // 2. 선택 정렬 
	int minIndex;
	for (int i = 0; i < size - 1; i++) { // 부분 배열의 크기를 증가시켜 나가면서 
		minIndex = i; // 그 부분 배열의 바로 뒤에 해당하는 원소부터 시작해 
		for (int j = i + 1; j < size; j++) {  // 맨 끝까지 차례차례 비교하면서 
			if (array[j] < array[minIndex]) {
				minIndex = j; // 최소값을 구한다. 
			}
		}
		swap(&array[i], &array[minIndex]); // 그리고 그 최소값을 부분 배열의 맨 뒤와 바꾼다. 
	}
}

void bubbleSort(int* array, int size) { // 3. 버블 정렬 
	bool flag = false; 

	for (int i = size - 1; i >= 1; i--) { // 3-1. 정렬을 시행하는 부분 배열을 맨 뒤부터 줄여나가며  
		if (flag) // 3-5. 만일 앞의 과정에서 한 번도 바뀌지 않았다면 
			break; // 3-6. 정렬을 끝낸다. 
		flag = true;
		for (int j = 0; j < i; j++) { // 3-2. 그 부분 배열에서 앞뒤를 반복해 비교하면서 
			if (array[j] > array[j + 1]) { // 3-3. 만약 이전 원소가 이후 원소보다 값이 크면 
				swap(&array[j], &array[j + 1]); // 3-4. 바꾼다. 
				flag = false;
			}
		}
	}
}

void merge(int* array, int ss, int se, int es, int ee) { // 4-3. 합병 
	int* mergedArray = new int[ee - es + se - ss + 2]; // 합쳐진 배열이 들어갈 공간을 만든다. 
	int si, ei, mi;  
	si = ss; // 앞 배열의 시작 인덱스 
	ei = es; // 뒤 배열의 시작 인덱스 
	mi = 0; // 합병될 배열의 시작 인덱스 

	while (si <= se && ei <= ee) { // 앞 배열의 인덱스와 뒤 배열의 인덱스가 각각의 크기를 넘지 않는 선에서 
		mergedArray[mi++] = array[si] < array[ei] ? array[si++] : array[ei++]; // 합병될 배열에 두 배열 중 큰 수를 넣는다. 
	}
	while (si <= se) { // 이후 앞 배열에서 남은 수를 넣는다. 
		mergedArray[mi++] = array[si++];
	}
	while (ei <= ee) { // 뒤 배열에서 남은 수를 넣는다. 
		mergedArray[mi++] = array[ei++];
	}
	for (int i = ss; i <= ee; i++) { // 원본 배열에 합병이 완료된 배열의 값들을 복사한다. 
		array[i] = mergedArray[i - ss];
	}
	delete(mergedArray);
}

void mergeSort(int* array, int s, int e) { // 4. 합병 정렬 
	if (s == e) { // 4-1. 시작 인덱스와 끝 인덱스가 같다면, 즉 원소의 개수가 하나라면 
		return; // 4-2. 
	}
	int m = (s + e) / 2; // 4-1. 배열을 절반으로 나눈다. 
	mergeSort(array, s, m); // 4-2. 나뉘어진 배열의 앞부분과 
	mergeSort(array, m + 1, e); // 뒷부분에 대해서도 각각 같은 과정을 반복한다. 
	merge(array, s, m, m + 1, e); // 4-3. 나뉘어진 두 배열을 합병한다. 
}

void quickSort(int* array, int s, int e) { // 5. 퀵 정렬 
	if (s >= e) // 시작점이 끝과 같거나 끝이 시작점을 넘어갔을 경우 종료한다. 
		return;

	int left = s; // 시작점의 인덱스 
	int right = e; // 끝점의 인덱스 
	int pivot = array[(s + e) / 2]; // 기준 값은 가운데의 값으로 정하기로 한다. 

	while (left <= right) { // 왼쪽 인덱스가 오른쪽 인덱스보다 작거나 같을 경우 
		while (array[left] < pivot) { // 왼쪽 인덱스의 값이 기준 값보다 작다면 
			left++; // 왼쪽 인덱스를 증가시킨다. 
		}
		while (array[right] > pivot) { // 오른쪽 인덱스의 값이 기준 값보다 크면 
			right--; // 오른쪽 인덱스를 감소시킨다. 
		}
		if (left <= right) { // 만일 왼쪽이 오른쪽을 넘어가지 않았다면 
			swap(&array[left], &array[right]); // 왼쪽과 오른쪽의 값을 바꾸고 
			left++; // 왼쪽 인덱스를 증가 
			right--; // 오른쪽 인덱스를 감소시킨다. 
		}
	}

	quickSort(array, s, right); // 시작점부터 오른쪽 인덱스 
	quickSort(array, left, e); // 왼쪽 인덱스부터 끝점의 배열에 대해서 위 과정을 반복한다. 
}

void heapSort(int* array, int size) { // 6. 최소 힙 정렬 
	int heapSize = 2;
	while (size > heapSize - 1) { // 현재 직접 구현한 힙은 배열의 인덱스를 이용한 힙이므로 크기를 구해준다. 
		heapSize *= 2; // 트리로 구현한다면 이 과정을 생략해도 된다. 
	}
	Heap myheap(heapSize);

	for (int i = 0; i < size; i++) { // 힙에 넣는다. 
		myheap.push(array[i]);
	}
	for (int i = 0; i < size; i++) { // 힙에서 뺀 값을 배열에 넣는다. 
		array[i] = myheap.top();
		myheap.pop();
	}
}

void countSort(int* array, int size) { // 7. 카운트 정렬 (계수 정렬) 
	int max = 0;
	int i;

	for (i = 0; i < size; i++) { // 최대값을 구한다. 
		max = array[i] > max ? array[i] : max;
	}
	max++;
	int* count = new int[max]; // 최대값 크기 + 1만큼의 배열을 만든다. 
	fill_n(count, max, 0); // 그 배열을 전부 0으로 초기화한다. 

	for (i = 0; i < size; i++) { // 배열을 읽으며 
		count[array[i]]++; // 해당 값에 해당하는 배열의 값을 증가시킨다. 
	}

	i = 0;

	while (i < size) { // 배열의 인덱스가 전체 크기보다 작을 때까지 
		for (int j = 0; j < max; j++) { // 계수 배열을 읽으며 
			for (int k = 0; k < count[j]; k++) { // 계수된 수만큼 
				array[i++] = j; // 배열에 그 값을 저장한다. 
			}
		}
	}

	delete[] count;
}

int numlen(int input) { // 숫자의 자리수를 구하는 함수 
	int length = 0;
	while (input > 0) {
		input /= 10;
		length++;
	}
	return length;
}

int pow(int num, int ex) { // 분할정복을 이용한 거듭제곱을 구하는 함수 
	if (ex == 0)
		return 1;
	else if (ex == 1)
		return num;
	else
		return pow(num, ex / 2) * pow(num, ex / 2) * (ex % 2 == 1 ? num : 1);
}

void radixSort(int* array, int size) { // 8. 기수 정렬 
	int max = 0;

	for (int i = 0; i < size; i++) { // 최대값을 구한다. 
		max = array[i] > max ? array[i] : max;
	}
	int digit = numlen(max);  // 그 최대값의 자리수를 구한다. 
	int k = 0;
	int j;
	Queue* myqueue = new Queue[10]; // 큐를 생성하고 
	for (int i = 0; i < 10; i++) {
		myqueue[i] = Queue(); // 초기화한다. 
	}
	for (int i = 0; i < digit; i++) { // 밑의 과정을 최대값의 자리수만큼 반복한다. 
		for (j = 0; j < size; j++) { // 배열을 읽으면서 
			myqueue[(array[j] % pow(10, i + 1)) / pow(10, i)].push(array[j]); // 원소의 자리수에 해당하는 큐에 값을 넣는다. 
		}
		j = 0;
		k = 0;
		while (k < 10 && j < size) { // 그리고 그 큐에서 
			if (myqueue[k].isEmpty()) {
				k++;
				continue;
			}
			array[j++] = myqueue[k].front(); // 값을 빼 배열에 다시 저장한다. 
			myqueue[k].pop();
		}
	}
}

void treeSort(int* array, int size) { // 9. 트리 정렬 
	BTree mytree;
	mytree.init();

	for (int i = 0; i < size; i++) { // 이진 트리에 넣는다. 
		mytree.insert(array[i]);
	}

	mytree.printTree(); // 이진 트리를 출력한다. 
}

bool isSorted(int* array, int size) { // 정렬됐는지 확인하는 함수 
	int sorted = true;
	for (int i = 0; i < size - 1; i++) {
		sorted = (array[i] < array[i+1]);
		if (!sorted)
			break;
	}
	return sorted;
}

void bogoSort(int* array, int size) { // 10. 보고 정렬 
	srand(time(NULL));
	int aIndex;
	int bIndex;

	while (!isSorted(array, size)) { // 정렬될 때까지 
		aIndex = rand() % size; // 랜덤한 
		bIndex = rand() % size; // 두 인덱스를 뽑아서 
		if (aIndex > bIndex) swap(&aIndex, &bIndex); // 정렬한 후 
		if (array[aIndex] > array[bIndex]) // 앞의 인덱스 값이 더 크다면 
			swap(array + aIndex, array + bIndex); // 바꾼다. 
	}
}
