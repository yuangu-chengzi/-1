#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct stack
{
	int L;
	int R;
	struct stack* next;
}sta;

sta* stack = NULL;
void push(int L, int R)
{
	if (L >= R) {
		return;
	}
	sta* tp = (sta*)malloc(sizeof(sta));
	if (NULL == tp)
		return;
	tp->L = L;
	tp->R = R;
	tp->next = stack;
	stack = tp;
}
sta top(void)
{
	if (stack == NULL) {
		sta a = { 0 };
		return a;
	}
	return *stack;
}
void pop(void)
{
	if (stack == NULL)
		return;
	sta* pt = stack;
	stack = stack->next;
	free(pt);
}
bool Isempty(void)
{
    return stack != NULL;
}
void Free(void)
{
	while (stack)
		pop();
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int media(int* arr, int left, int right)
{
    int mid = right / 2;
    if (arr[left] > arr[mid]) {
        swap(&arr[left], &arr[mid]);
    }
    if (arr[left] > arr[right]) {
        swap(&arr[left], &arr[right]);
    }
    if (arr[mid] > arr[right]) {
        swap(&arr[mid], &arr[right]);
    }
    swap(&arr[left], &arr[mid]);
    return arr[left];
}

int quick_sort(int arr[], int start, int end) {
    if (start >= end) {
        return 0;
    }
    int left = start;
    int right = end;
    int pivot = media(arr, left, right);
    while (left < right) {
        while (arr[right] > pivot && left < right) {
            right--;
        }
        if (arr[right] < pivot) {
            arr[left] = arr[right];
            left++;
        }
        while (arr[left] <= pivot && left < right) {
            left++;
        }
        if (arr[left] > pivot) {
            arr[right] = arr[left];
            right--;
        }
    }
    arr[left] = pivot;
    return left;
}

void Sort(int a[], int L, int R)
{
    push(L, R);
    while (Isempty()) {
        sta tp = top();
        pop();
        int m = quick_sort(a, tp.L, tp.R);
        push(tp.L, m - 1);
        push(m + 1, tp.R);
    }
}

void generate_int_test_data(const char* file_path, int num_records) {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, file_path, "w");
    if (err != 0 || file == NULL) {
        printf("无法打开文件 %s 进行写入\n", file_path);
        return;
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < num_records; i++) {
        int num = rand() % 100001;
        fprintf(file, "%d\n", num);
    }
    fclose(file);
    printf("成功生成 %d 条整数数据到 %s\n", num_records, file_path);
}
// 读取整数数据到数组
void read_int_data(const char* file_path, int* arr, int num_records) {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, file_path, "r");
    if (err != 0 || file == NULL) {
        printf("无法打开文件 %s 进行读取\n", file_path);
        return;
    }
    for (int i = 0; i < num_records; i++) {
        fscanf_s(file, "%d", &arr[i]);
    }
    fclose(file);
}
int main() {
    int large_size = 100000;
    int* data = (int*)malloc(large_size * sizeof(int));
    // 生成并读取10万条测试数据
    generate_int_test_data("large_int_data.txt", large_size);
    read_int_data("large_int_data.txt", data, large_size);
    // 调用你的非递归快速排序
    Sort(data, 0, large_size - 1);
    // 验证排序结果
    printf("排序后前 5 条数据：%d, %d, %d, %d, %d\n",
        data[0], data[1], data[2], data[3], data[4]);
    free(data);
    return 0;
}