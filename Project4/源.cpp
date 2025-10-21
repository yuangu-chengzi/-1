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
        printf("�޷����ļ� %s ����д��\n", file_path);
        return;
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < num_records; i++) {
        int num = rand() % 100001;
        fprintf(file, "%d\n", num);
    }
    fclose(file);
    printf("�ɹ����� %d ���������ݵ� %s\n", num_records, file_path);
}
// ��ȡ�������ݵ�����
void read_int_data(const char* file_path, int* arr, int num_records) {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, file_path, "r");
    if (err != 0 || file == NULL) {
        printf("�޷����ļ� %s ���ж�ȡ\n", file_path);
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
    // ���ɲ���ȡ10������������
    generate_int_test_data("large_merge_data.txt", large_size);
    read_int_data("large_merge_data.txt", data, large_size);
    // ���ò��й鲢����
    double start = omp_get_wtime();
    merge_sort(data, large_size);
    double end = omp_get_wtime();
    printf("���й鲢�����ʱ��%.4f ��\n", end - start);
    // ��֤������
    printf("�����ǰ 5 �����ݣ�%d, %d, %d, %d, %d\n",
        data[0], data[1], data[2], data[3], data[4]);
    free(data);
    return 0;
}