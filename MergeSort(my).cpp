#include<iostream>

using namespace std;

class Node {
public:
	int key, value;
};

Node tmp[100];
void PartSort(Node *arr, int start, int end, int mid) {
	int i = start, j = mid + 1;
	int index = start;
	while (i <= mid && j <= end) {
		if (arr[i].key < arr[j].key) {
			tmp[index] = arr[i];
			i++;
		}
		else {
			tmp[index] = arr[j];
			j++;
		}
		index++;
	}

	while (i <= mid) {
		tmp[index] = arr[i];
		i++;
		index++;
	}

	while (j <= end) {
		tmp[index] = arr[j];
		j++;
		index++;
	}
}


void MergeSort(Node *arr, int start, int end) {
	if (start >= end)
		return;
	
	int mid = (end - start) / 2 + start;

	MergeSort(arr, start, mid);
	MergeSort(arr, mid + 1, end);

	PartSort(arr, start, end, mid);

	for (int i = start; i <= end; i++)
		arr[i] = tmp[i];

}


int main(void) {
	Node arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i].key = 9 - i;
		arr[i].value = 9 - i;
	}

	MergeSort(arr, 0, 9);

	cout << endl;

	/*
	Node arr[10];
	
	for (int i = 0; i <= 4; i++) {
		arr[i].key = i + 5;
		arr[i].value = i + 5;
	}

	for (int i = 5; i <= 9; i++) {
		arr[i].key = i - 5;
		arr[i].value = i - 5;
	}

	int start = 0, end = 9;
	int mid = (end - start) / 2 + start;

	PartSort(arr, start, end, mid);

	cout << endl;
	*/
	return 0;
}
