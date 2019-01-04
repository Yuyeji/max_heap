#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS

int heap_size(int *arr);
int Parent(int x);
void Max_Heapify(int * arr, int i,int size);
void Build_Max_Heap(int * arr);
int Heap_Extract_Max(int *arr);
void Max_Heap_Sort(int *arr);
void Max_Heap_Insert(int *arr, int key);
void Max_Heap_Increase_Key(int *arr, int x, int key);
void Max_Heap_Increase_Key_No_Constraint(int *arr, int x, int key);


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

	startTime = clock();
	//Max_Heap_Sort(arr);
	//Max_Heap_Insert(arr, 1);
	//Max_Heap_Increase_Key(arr, heap_size(arr) - 1, 1000);


	Build_Max_Heap(arr);
	Max_Heap_Increase_Key_No_Constraint(arr, size-1, 100);

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);


	for (int j = 0; j < heap_size(arr); j++) {
		printf("%d\n", arr[j]);
	}

	printf("max_value : %d\n", Heap_Extract_Max(arr));

	printf("���� �ð� : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // �׽�Ʈ ���� ����.

}

int heap_size(int *arr) { //arr�� ũ��
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

void Build_Max_Heap(int *arr) {
	int n = heap_size(arr); //arr�� ũ��
	int i;

	for (i = n / 2; i >= 0; i--) { 
		Max_Heapify(arr, i, n);
	}
}

void Max_Heapify(int * arr, int i, int size) {
	int largest, left, right, temp;
	int n = size;

	left = (2 * i + 1);
	right = (2 * i + 2);
	
	//largest�� ����
	if (left < n && arr[left] > arr[i])
		largest = left;
	else
		largest = i;

	if (right < n && arr[right] > arr[largest])
		largest = right;

	if (largest != i) {
		//swap
		temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		Max_Heapify(arr, largest, n); //��� �̿�
	}
}

int Heap_Extract_Max(int *arr) { //����
	int i,max_value,left, temp;
	int size = heap_size(arr);

	Build_Max_Heap(arr); //Max-heap ����
	i = size;
	max_value = arr[0]; //root���� �ִ밪

	//swap
	temp = arr[0];
	arr[0] = arr[i];
	arr[i] = temp;

	i -= 1;
	Max_Heapify(arr, 0, i);

	return max_value; //�ִ밪 ��ȯ
}

void Max_Heap_Sort(int *arr) { //�������� ����
	int size = heap_size(arr);
	int i,temp;

	Build_Max_Heap(arr); //Max-heap ����

	for (i = size -1; i >= 0; i--) {
		//swap
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		size -= 1;
		Max_Heapify(arr, 0, size);
	}
}

void Max_Heap_Insert(int *arr, int key) { //����
	int size = heap_size(arr);
	int k = key; //�����ϱ� ���ϴ� ��

	size++; //size ����
	arr = (int *)realloc(arr, (size) * sizeof(int)); //arrũ�⸦ ������
	arr[size-1] = INT_MIN; //������ ���� ���Ѵ�� �۰� ����.
	Max_Heap_Increase_Key(arr, size-1, k); //�����Լ� ȣ��
}

void Max_Heap_Increase_Key(int *arr, int x, int key) {
	int k = key; //�����ϱ� ���ϴ� ��
	int s = x; //arr�� ũ��
	int temp;

	if( k < arr[s]){ //key���� ������ ������ ������
		printf("new key is smaller than current key\n");
	}
	else { //ũ��
		arr[s] = k; //�迭�� ������ ���� key������ �ٲ�.
		while (s > 0 && arr[Parent(s)] < arr[s]) {
			//swap
			temp = arr[s];
			arr[s] = arr[Parent(s)];
			arr[Parent(s)] = temp;

			s = Parent(s);
		}
	}
}

void Max_Heap_Increase_Key_No_Constraint(int *arr, int x, int key) { //���Ǿ��� ����
	int k = key; //�����ϱ� ���ϴ� ��
	int s = x; //arr�� ũ��
	int temp;

	arr[s] = k; //�迭�� ������ ���� key������ �ٲ�.
	while (s > 0 && arr[Parent(s)] < arr[s]) {
		//swap
		temp = arr[s];
		arr[s] = arr[Parent(s)];
		arr[Parent(s)] = temp;

		s = Parent(s);
	}
	Build_Max_Heap(arr);
}