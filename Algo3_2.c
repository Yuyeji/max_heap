#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS

int heap_size(int *arr);
int Parent(int x);
void Min_Heapify(int * arr, int i, int size);
void Build_Min_Heap(int * arr);
int Heap_Extract_Min(int *arr);
void Min_Heap_Sort(int *arr);
void Min_Heap_Insert(int *arr, int key);
void Min_Heap_Decrease_Key(int *arr, int x, int key);
void Min_Heap_Decrease_Key_No_Constraint(int *arr, int x, int key);


int main(void) {
	int *arr; // ������ �����͸� ������ ������ ���� ����.
	int size = 1;
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("test.txt", "r");

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}

	arr = (int *)malloc(sizeof(int));

	while (feof(f) == 0) {
		arr = (int *)realloc(arr, (size) * sizeof(int));
		fscanf(f, "%d", &arr[size-1]);
		size++;
	}

	//Min_Heap_Sort(arr);
	//Min_Heap_Insert(arr, -5);
//	Min_Heap_Decrease_Key(arr, heap_size(arr) - 1, 900);

	//Min_Heap_Decrease_Key(arr, heap_size(arr)-1, 1);
	
	startTime = clock();

	Build_Min_Heap(arr);
	Min_Heap_Decrease_Key_No_Constraint(arr, size - 1, 5);

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	for (int j = 0; j < heap_size(arr); j++) {
		printf("%d\n", arr[j]);
	}

	printf("min_value : %d\n", Heap_Extract_Min(arr));

	printf("���� �ð� : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // �׽�Ʈ ���� ����.

}

int heap_size(int *arr) {
	return (_msize((void*)arr) / sizeof(int));
}

int Parent(int x) {
	int p;

	if ((x % 2) == 0) { //¦��
		p = x / 2 - 1;
	}
	else { //Ȧ��
		p = x / 2;
	}
	return p;
}

void Build_Min_Heap(int *arr) {
	int n = heap_size(arr); //arr�� ũ��
	int i;

	for (i = n / 2;i >= 0;i--) {
		Min_Heapify(arr, i, n);
	}
}

void Min_Heapify(int *arr, int i, int size) {
	int smallest, left, right, temp;
	int n = size;

	left = (2 * i + 1);
	right = (2 * i + 2);

	//smallest�� �� ����
	if (left < n && arr[left] < arr[i])
		smallest = left;
	else
		smallest = i;

	if (right < n && arr[right] < arr[smallest])
		smallest = right;

	if (smallest != i) {
		//swap
		temp = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = temp;

		Min_Heapify(arr, smallest, n); //��� �̿�
	}
}

int Heap_Extract_Min(int *arr) { //����
	int i, min_value, left, temp;
	int size = heap_size(arr);

	Build_Min_Heap(arr); // Min-Heap ����
	i = size;
	min_value = arr[0]; //root���� �ּҰ�

	//swap
	temp = arr[0];
	arr[0] = arr[i];
	arr[i] = temp;

	i -= 1;
	Min_Heapify(arr, 0, i);

	return min_value; //�ּҰ� ��ȯ
}

void Min_Heap_Sort(int *arr) { //�������� ����
	int size = heap_size(arr);
	int i, temp;

	Build_Min_Heap(arr); // Min-Heap ����

	for (i = size - 1; i >= 0; i--) {
		//swap
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		size -= 1;
		Min_Heapify(arr, 0, size);
	}
}

void Min_Heap_Insert(int *arr, int key) { //����
	int size = heap_size(arr);
	int k = key; //�����ϱ� ���ϴ� ��

	size++; //size ����
	arr = (int *)realloc(arr, (size) * sizeof(int)); //arrũ�⸦ ������
	arr[size-1] = INT_MAX; //������ ���� ���Ѵ�� ũ�� ����.
	Min_Heap_Decrease_Key(arr, size-1, k); //�����Լ� ȣ��
}

void Min_Heap_Decrease_Key(int *arr, int x, int key) {
	int k = key; //�����ϱ� ���ϴ� ��
	int s = x; //arr�� ũ��
	int temp;

	if (k < arr[s]) { //key���� ������ ������ ������
		arr[s] = k; //�迭�� ������ ���� key������ �ٲ�.
		while (s > 0 && arr[Parent(s)] > arr[s]) {
			temp = arr[s];
			arr[s] = arr[Parent(s)];
			arr[Parent(s)] = temp;

			s = Parent(s);
		}
	}
	else { //ũ��
		printf("new key is larger than current key\n");
	}
}

void Min_Heap_Decrease_Key_No_Constraint(int *arr, int x, int key) {
	int k = key;
	int s = x;
	int temp;

	arr[s] = k;
	while (s > 0 && arr[Parent(s)] > arr[s]) {
		temp = arr[s];
		arr[s] = arr[Parent(s)];
		arr[Parent(s)] = temp;

		s = s / 2;
	}
	Build_Min_Heap(arr);
}