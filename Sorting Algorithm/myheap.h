#ifndef MYHEAP
#define HEAP

extern void swap(int* a, int* b);

class Heap {
private:
	int* heap;
	int cnt;
	int size;
public:
	Heap(int size);
	void push(int data);
	void pop();
	int top();
	int getSize();
	int getCount();
	bool isEmpty();
	bool isFull();
	~Heap();
};

Heap::Heap(int size) {
	this->heap = new int[size];
	this->size = size;
	this->cnt = 1;
}

void Heap::push(int data) { // bottom-up 방식의 push 
	int insertAt = this->cnt; // 맨 끝의 인덱스를 저장한다. 
	this->heap[insertAt] = data; // 맨 끝에 원소를 넣는다. 
	while (insertAt > 1) { // 인덱스가 1보다 클 때까지 
		if (this->heap[insertAt / 2] > this->heap[insertAt]) { // 인덱스의 값이 인덱스의 부모의 값보다 작다면 
			swap(&this->heap[insertAt / 2], &this->heap[insertAt]); // 바꾼다. 
			insertAt /= 2; // 인덱스를 부모로 이동한다. 
		}
		else // 같지 않다면 더이상 반복하지 않는다. 
			break;
	}
	this->cnt++;
}

void Heap::pop() { // top-down 방식의 pop 
	int insertAt = 1; // 삭제할 가장 위의 원소의 인덱스 
	this->heap[insertAt] = this->heap[this->cnt - 1]; // 가장 밑에 있는 원소를 맨 위에 집어넣는다. 

	int to;

	while (insertAt * 2 < this->cnt) { // 힙의 크기를 넘기지 않을 때까지 
		to = insertAt * 2; // 자식 중에서 

		if ((insertAt * 2 + 1 < this->cnt) && (this->heap[insertAt * 2] > this->heap[insertAt * 2 + 1])) { // 만일 오른쪽 자식도 존재하고 그 값이 왼쪽 자식보다 작다면 
			to = insertAt * 2 + 1; // 오른쪽 자식도 본다. 
		}

		if (this->heap[insertAt] > this->heap[to]) { // 위 과정에서 정해진 자식이 내 현재 값보다 작다면 
			swap(&this->heap[insertAt], &this->heap[to]); // 바꾼다. 
			insertAt = to; // 그 자식을 이동한다. 
		}
		else
			break;
	}
	this->cnt--;
}

int Heap::top() { // 최소 힙의 정의에 따라 맨 위의 원소를 반환한다. 
	return this->heap[1];
}

int Heap::getSize() {
	return this->size;
}

int Heap::getCount() {
	return this->cnt;
}

bool Heap::isEmpty() {
	return this->cnt <= 1;
}

bool Heap::isFull() {
	return this->cnt > this->size;
}

Heap::~Heap() {
	delete[] this->heap;
}

#endif
