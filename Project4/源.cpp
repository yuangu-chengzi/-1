#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

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
        #pragma omp parallel
        {
            #pragma omp section
            {

                #pragma omp section
                {
                    msort(arr, temparr, left, mid);
                }
                #pragma omp section
                {
                    msort(arr, temparr, mid + 1, right);
                }
            }
        }

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
    generate_int_test_data("large_merge_data.txt", large_size);
    read_int_data("large_merge_data.txt", data, large_size);
    // 调用并行归并排序
    double start = omp_get_wtime();
    merge_sort(data, large_size);
    double end = omp_get_wtime();
    printf("并行归并排序耗时：%.4f 秒\n", end - start);
    // 验证排序结果
    printf("排序后前 5 条数据：%d, %d, %d, %d, %d\n",
        data[0], data[1], data[2], data[3], data[4]);
    free(data);
    return 0;
}