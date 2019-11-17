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

void insertionSort(int* array, int size) { // 1. ���� ���� 
	int insert;
	for (int i = 1; i < size; i++) { // �迭�� �պκ� �迭�� ũ�⸦ ������Ű�鼭 
		for (int j = 0; j < i; j++) { // �� �պκ� �迭�� ���Ҹ� ó������ Ž���ϸ� 
			if (array[i] < array[j]) { // �ٷ� ���� ���Һ��� ū ���� �߰ߵǸ� 
				insert = array[i];  // �̸� �� ���Ұ� ���Ե� �ڸ���� �Ǵ��ϰ� 
				for (int k = i - 1; k >= j; k--) { // �� ���Ҹ� �� �ڷ� �� ĭ �� ��� �Ŀ� 
					array[k + 1] = array[k];
				}
				array[j] = insert; // ���Ե� �ڸ��� �� ���Ҹ� �����Ѵ�. 
			}
		}
	}
}

void selectionSort(int* array, int size) { // 2. ���� ���� 
	int minIndex;
	for (int i = 0; i < size - 1; i++) { // �κ� �迭�� ũ�⸦ �������� �����鼭 
		minIndex = i; // �� �κ� �迭�� �ٷ� �ڿ� �ش��ϴ� ���Һ��� ������ 
		for (int j = i + 1; j < size; j++) {  // �� ������ �������� ���ϸ鼭 
			if (array[j] < array[minIndex]) {
				minIndex = j; // �ּҰ��� ���Ѵ�. 
			}
		}
		swap(&array[i], &array[minIndex]); // �׸��� �� �ּҰ��� �κ� �迭�� �� �ڿ� �ٲ۴�. 
	}
}

void bubbleSort(int* array, int size) { // 3. ���� ���� 
	bool flag = false; 

	for (int i = size - 1; i >= 1; i--) { // 3-1. ������ �����ϴ� �κ� �迭�� �� �ں��� �ٿ�������  
		if (flag) // 3-5. ���� ���� �������� �� ���� �ٲ��� �ʾҴٸ� 
			break; // 3-6. ������ ������. 
		flag = true;
		for (int j = 0; j < i; j++) { // 3-2. �� �κ� �迭���� �յڸ� �ݺ��� ���ϸ鼭 
			if (array[j] > array[j + 1]) { // 3-3. ���� ���� ���Ұ� ���� ���Һ��� ���� ũ�� 
				swap(&array[j], &array[j + 1]); // 3-4. �ٲ۴�. 
				flag = false;
			}
		}
	}
}

void merge(int* array, int ss, int se, int es, int ee) { // 4-3. �պ� 
	int* mergedArray = new int[ee - es + se - ss + 2]; // ������ �迭�� �� ������ �����. 
	int si, ei, mi;  
	si = ss; // �� �迭�� ���� �ε��� 
	ei = es; // �� �迭�� ���� �ε��� 
	mi = 0; // �պ��� �迭�� ���� �ε��� 

	while (si <= se && ei <= ee) { // �� �迭�� �ε����� �� �迭�� �ε����� ������ ũ�⸦ ���� �ʴ� ������ 
		mergedArray[mi++] = array[si] < array[ei] ? array[si++] : array[ei++]; // �պ��� �迭�� �� �迭 �� ū ���� �ִ´�. 
	}
	while (si <= se) { // ���� �� �迭���� ���� ���� �ִ´�. 
		mergedArray[mi++] = array[si++];
	}
	while (ei <= ee) { // �� �迭���� ���� ���� �ִ´�. 
		mergedArray[mi++] = array[ei++];
	}
	for (int i = ss; i <= ee; i++) { // ���� �迭�� �պ��� �Ϸ�� �迭�� ������ �����Ѵ�. 
		array[i] = mergedArray[i - ss];
	}
	delete(mergedArray);
}

void mergeSort(int* array, int s, int e) { // 4. �պ� ���� 
	if (s == e) { // 4-1. ���� �ε����� �� �ε����� ���ٸ�, �� ������ ������ �ϳ���� 
		return; // 4-2. 
	}
	int m = (s + e) / 2; // 4-1. �迭�� �������� ������. 
	mergeSort(array, s, m); // 4-2. �������� �迭�� �պκа� 
	mergeSort(array, m + 1, e); // �޺κп� ���ؼ��� ���� ���� ������ �ݺ��Ѵ�. 
	merge(array, s, m, m + 1, e); // 4-3. �������� �� �迭�� �պ��Ѵ�. 
}

void quickSort(int* array, int s, int e) { // 5. �� ���� 
	if (s >= e) // �������� ���� ���ų� ���� �������� �Ѿ�� ��� �����Ѵ�. 
		return;

	int left = s; // �������� �ε��� 
	int right = e; // ������ �ε��� 
	int pivot = array[(s + e) / 2]; // ���� ���� ����� ������ ���ϱ�� �Ѵ�. 

	while (left <= right) { // ���� �ε����� ������ �ε������� �۰ų� ���� ��� 
		while (array[left] < pivot) { // ���� �ε����� ���� ���� ������ �۴ٸ� 
			left++; // ���� �ε����� ������Ų��. 
		}
		while (array[right] > pivot) { // ������ �ε����� ���� ���� ������ ũ�� 
			right--; // ������ �ε����� ���ҽ�Ų��. 
		}
		if (left <= right) { // ���� ������ �������� �Ѿ�� �ʾҴٸ� 
			swap(&array[left], &array[right]); // ���ʰ� �������� ���� �ٲٰ� 
			left++; // ���� �ε����� ���� 
			right--; // ������ �ε����� ���ҽ�Ų��. 
		}
	}

	quickSort(array, s, right); // ���������� ������ �ε��� 
	quickSort(array, left, e); // ���� �ε������� ������ �迭�� ���ؼ� �� ������ �ݺ��Ѵ�. 
}

void heapSort(int* array, int size) { // 6. �ּ� �� ���� 
	int heapSize = 2;
	while (size > heapSize - 1) { // ���� ���� ������ ���� �迭�� �ε����� �̿��� ���̹Ƿ� ũ�⸦ �����ش�. 
		heapSize *= 2; // Ʈ���� �����Ѵٸ� �� ������ �����ص� �ȴ�. 
	}
	Heap myheap(heapSize);

	for (int i = 0; i < size; i++) { // ���� �ִ´�. 
		myheap.push(array[i]);
	}
	for (int i = 0; i < size; i++) { // ������ �� ���� �迭�� �ִ´�. 
		array[i] = myheap.top();
		myheap.pop();
	}
}

void countSort(int* array, int size) { // 7. ī��Ʈ ���� (��� ����) 
	int max = 0;
	int i;

	for (i = 0; i < size; i++) { // �ִ밪�� ���Ѵ�. 
		max = array[i] > max ? array[i] : max;
	}
	max++;
	int* count = new int[max]; // �ִ밪 ũ�� + 1��ŭ�� �迭�� �����. 
	fill_n(count, max, 0); // �� �迭�� ���� 0���� �ʱ�ȭ�Ѵ�. 

	for (i = 0; i < size; i++) { // �迭�� ������ 
		count[array[i]]++; // �ش� ���� �ش��ϴ� �迭�� ���� ������Ų��. 
	}

	i = 0;

	while (i < size) { // �迭�� �ε����� ��ü ũ�⺸�� ���� ������ 
		for (int j = 0; j < max; j++) { // ��� �迭�� ������ 
			for (int k = 0; k < count[j]; k++) { // ����� ����ŭ 
				array[i++] = j; // �迭�� �� ���� �����Ѵ�. 
			}
		}
	}

	delete[] count;
}

int numlen(int input) { // ������ �ڸ����� ���ϴ� �Լ� 
	int length = 0;
	while (input > 0) {
		input /= 10;
		length++;
	}
	return length;
}

int pow(int num, int ex) { // ���������� �̿��� �ŵ������� ���ϴ� �Լ� 
	if (ex == 0)
		return 1;
	else if (ex == 1)
		return num;
	else
		return pow(num, ex / 2) * pow(num, ex / 2) * (ex % 2 == 1 ? num : 1);
}

void radixSort(int* array, int size) { // 8. ��� ���� 
	int max = 0;

	for (int i = 0; i < size; i++) { // �ִ밪�� ���Ѵ�. 
		max = array[i] > max ? array[i] : max;
	}
	int digit = numlen(max);  // �� �ִ밪�� �ڸ����� ���Ѵ�. 
	int k = 0;
	int j;
	Queue* myqueue = new Queue[10]; // ť�� �����ϰ� 
	for (int i = 0; i < 10; i++) {
		myqueue[i] = Queue(); // �ʱ�ȭ�Ѵ�. 
	}
	for (int i = 0; i < digit; i++) { // ���� ������ �ִ밪�� �ڸ�����ŭ �ݺ��Ѵ�. 
		for (j = 0; j < size; j++) { // �迭�� �����鼭 
			myqueue[(array[j] % pow(10, i + 1)) / pow(10, i)].push(array[j]); // ������ �ڸ����� �ش��ϴ� ť�� ���� �ִ´�. 
		}
		j = 0;
		k = 0;
		while (k < 10 && j < size) { // �׸��� �� ť���� 
			if (myqueue[k].isEmpty()) {
				k++;
				continue;
			}
			array[j++] = myqueue[k].front(); // ���� �� �迭�� �ٽ� �����Ѵ�. 
			myqueue[k].pop();
		}
	}
}

void treeSort(int* array, int size) { // 9. Ʈ�� ���� 
	BTree mytree;
	mytree.init();

	for (int i = 0; i < size; i++) { // ���� Ʈ���� �ִ´�. 
		mytree.insert(array[i]);
	}

	mytree.printTree(); // ���� Ʈ���� ����Ѵ�. 
}

bool isSorted(int* array, int size) { // ���ĵƴ��� Ȯ���ϴ� �Լ� 
	int sorted = true;
	for (int i = 0; i < size - 1; i++) {
		sorted = (array[i] < array[i+1]);
		if (!sorted)
			break;
	}
	return sorted;
}

void bogoSort(int* array, int size) { // 10. ���� ���� 
	srand(time(NULL));
	int aIndex;
	int bIndex;

	while (!isSorted(array, size)) { // ���ĵ� ������ 
		aIndex = rand() % size; // ������ 
		bIndex = rand() % size; // �� �ε����� �̾Ƽ� 
		if (aIndex > bIndex) swap(&aIndex, &bIndex); // ������ �� 
		if (array[aIndex] > array[bIndex]) // ���� �ε��� ���� �� ũ�ٸ� 
			swap(array + aIndex, array + bIndex); // �ٲ۴�. 
	}
}
