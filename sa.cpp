#ifndef _PREDICT_H_
#define _PREDICT_H_
    #include "predict.h"
#endif

extern Workload workload[MAXN];
extern int workload_num;
extern bool need_calc_ar;


double T = 10000;//temperature
double T_min = 1;//threshold
double k = 0.0001;//constant

FILE *fin;
double best, cur_miss_rate;

char *ull2BinaryStr(uint64_t cos) {
    char temp[256];
    char *s = new char[256];
    int i = 0;
    while (cos) {
        temp[i] = cos % 2 + '0';
        cos /= 2;
        i++;
    }
    for (int j = 0; j < i; j++)
        s[j] = temp[i - j - 1];
    s[i] = 0;
    return s;
}

char *ull216Str(uint64_t cos) {
    char *s = new char[256];
    strcpy(s, "0x");
    char temp[256];
    sprintf(temp, "%llx", cos);
    strcat(s, temp);
    return s;
}
bool containOne1(uint64_t cos) {
    int c = 0;
    while (cos) {
        if (cos % 2 == 1)
            c++;
        cos = cos >> 1;
    }
    if (c == 1)
        return true;
    else
        return false;
}
// direction: 0 right expand, 1 right reduce, 2 left expand, 3 left reduce
uint64_t modifyCos(int index, int d) {
    uint64_t cos = workload[index].cos;
    uint64_t pre_value = cos;
    if ((cos >= 1 << (MAXN - 1) && d == 2) || ((cos % 2 == 1) && d == 0) ||
        (containOne1(cos) && (d == 1 || d == 3)))
        return pre_value;
    if (d == 0) { // right expand
        int c = 0;
        while (cos % 2 == 0) {
            cos = cos >> 1;
            c++;
        }
        workload[index].cos += 1 << (c - 1);
    } else if (d == 1) {
        int c = 0;
        while (cos % 2 == 0) {
            cos = cos >> 1;
            c++;
        }
        workload[index].cos -= 1 << c;
    } else if (d == 2) {
        int c = 0;
        while (cos % 2 == 0) {
            cos = cos >> 1;
            c++;
        }
        while (cos % 2) {
            cos = cos >> 1;
            c++;
        }
        workload[index].cos += 1 << c;
    } else if (d == 3) {
        int c = 0;
        while (cos % 2 == 0) {
            cos = cos >> 1;
            c++;
        }
        while (cos % 2) {
            cos = cos >> 1;
            c++;
        }
        workload[index].cos -= 1 << (c - 1);
    }
    return pre_value;
}

void get_mrc(int i) {
    int c = 0;
    double pre = 0;
    for (; c < MAXS; c++) {
        if (fscanf(fin, "%lf", &workload[i].mrc[c]) > 0)
            ;
        else {
            pre = workload[i].mrc[c - 1];
            break;
        }
    }
    for (; c < MAXS; c++)
        workload[i].mrc[c] = pre;
}

int main(int argv, char **argc) {
    char filename[100];
    srand(time(NULL));

    workload_num = argv / 2 - 1;
    need_calc_ar = false;
    if (argc[1][0] == '1') {
        need_calc_ar = true;
    }

    for (int i = 0; i < workload_num; i++) {
        workload[i].occ = 0;
        workload[i].name = strdup(argc[i * 2 + 2]);
        workload[i].allocation = strdup(argc[i * 2 + 3]);
        workload[i].cos = strtouint64(workload[i].allocation);
        workload[i].ways = count_1s(workload[i].cos);
        workload[i].miss_ratio = 0;
        strcpy(filename, workload[i].name);
        strcat(filename, ".txt");
        fin = fopen(filename, "rb");
        // calc_mrc(i);
        get_mrc(i);
        if (need_calc_ar) {
            workload[i].access_rate = workload[i].mrc[L2_CACHE_SIZE / BLOCK];
        } else {
            workload[i].access_rate = 1;
        }
        fclose(fin);
    }

    best = predict_total_miss_rate();
    cur_miss_rate = best;

    while (T >= T_min) {
        int target = rand() % workload_num;
        int direction =
            rand() %
            4; // 0 right expand, 1 right reduce, 2 left expand, 3 left reduce
        uint64_t pre_cos = modifyCos(target, direction);

        double tmp = predict_total_miss_rate();
        if (tmp < best)
            best = tmp;
        double df = tmp - cur_miss_rate;
        if ((df > 0) && ((rand() % 1000 / (float)1000) > exp(-df / (k * T)))) {
            workload[target].cos = pre_cos;
        } else {
            cur_miss_rate = tmp;
        }
        T--;
    }

    printf("\n\nThe best: %lf\n", best);

    return 0;
}