#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int temparr[], int left, int mid, int right)
{
	int tl = left;
	int tr = mid + 1;
	int pos = left;
	while (tl <= mid && tr <= right)
	{
		if (arr[tl] < arr[tr])
			temparr[pos++] = arr[tl++];
		else
			temparr[pos++] = arr[tr++];
	}
	while (tl <= mid)
		temparr[pos++] = arr[tl++];
	while (tr <= right)
		temparr[pos++] = arr[tr++];
	while (left <= right) {
		arr[left] = temparr[left];
		left++;
	}
}

void msort(int arr[], int temparr[], int left, int right)
{
	if (left < right) {
		int mid = (left + right) / 2;
		msort(arr, temparr, left, mid);
		msort(arr, temparr, mid + 1, right);
		merge(arr, temparr, left, mid, right);
	}
}

void merge_sort(int arr[], int n)
{
	int* temparr = (int*)malloc(n * sizeof(int));
	if (temparr) {
		msort(arr, temparr, 0, n - 1);
		free(temparr);
	}
	else {
		printf("error");
	}
}

int main()
{
	int a[9] = { 9,5,2,7,12,4,3,1,11 };
	merge_sort(a, 9);
	for (int i = 0; i < 9; i++) {
		printf("%d ", a[i]);
	}
	return 0;
}