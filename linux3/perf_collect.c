#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char* opts[] = {"O0", "O1", "O2", "O3", "Ofast"};
    const char* dirs[] = {"/mnt/hgfs/paixu/linux1", "/mnt/hgfs/paixu/linux2", "/mnt/hgfs/paixu/linux3"};
    const char* algos[] = {"快排递归", "快排非递归", "并行归并排序"};
    FILE* csv = fopen("perf_data.csv", "w");
    if (!csv) { perror("创建CSV失败"); return 1; }
    fprintf(csv, "算法名称,优化等级,执行时间(秒)\n");

    for (int d = 0; d < 3; d++) {
        for (int o = 0; o < 5; o++) {
            char cmd[256] = {0};
            sprintf(cmd, "cd %s && time -f \"%%e\" ./%s > /dev/null 2> temp_time.txt", dirs[d], opts[o]);
            system(cmd);

            FILE* tf = fopen("temp_time.txt", "r");
            if (!tf) { printf("跳过 %s %s\n", algos[d], opts[o]); continue; }
            char time_buf[32] = {0};
            fgets(time_buf, sizeof(time_buf), tf);
            fclose(tf);

            fprintf(csv, "%s,%s,%s", algos[d], opts[o], time_buf);
            printf("已记录：%s %s 耗时 %s 秒\n", algos[d], opts[o], time_buf);
        }
    }

    fclose(csv);
    system("rm temp_time.txt");
    printf("性能数据已保存至 perf_data.csv\n");
    return 0;
}
