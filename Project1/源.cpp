#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void quick_sort(int arr[], int start, int end) {
    if (start >= end) {
        return;
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
        while (arr[left] <=pivot && left < right) {
            left++;
        }
        if (arr[left] > pivot) {
            arr[right] = arr[left];
            right--;
        }
    }
    arr[left] = pivot;
    quick_sort(arr, start, left - 1);
    quick_sort(arr, right + 1, end);
}


void generate_test_data(const char* file_path, int num_records, int is_integer) {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, file_path, "w");
    if (err != 0 || file == NULL) {
        printf("无法打开文件 %s 进行写入\n", file_path);
        return;
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < num_records; i++) {
        if (is_integer) {
            int num = rand() % 100001;
            fprintf(file, "%d\n", num);
        }
        else {
            float num = (float)rand() / RAND_MAX * 100000.0f;
            fprintf(file, "%.2f\n", num);
        }
    }
    fclose(file);
    printf("成功生成 %d 条%s数据到 %s\n", num_records,
        is_integer ? "整数" : "浮点", file_path);
}
// 从文件读取整数数据到数组
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
    // 生成10万条整数测试数据
    generate_test_data("large_int_data.txt", large_size, 1);
    // 读取生成的测试数据
    read_int_data("large_int_data.txt", data, large_size);
    // 调用快速排序函数对数据进行排序
    quick_sort(data, 0, large_size - 1);
    // 打印排序后前5条数据验证（可选）
    printf("排序后前 5 条数据：%d, %d, %d, %d, %d\n",
        data[0], data[1], data[2], data[3], data[4]);
    free(data);
    return 0;
}