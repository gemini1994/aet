#ifndef _PREDICT_H_
#define _PREDICT_H_
    #include "predict.h"
#endif

extern Workload workload[MAXN];
extern int workload_num;
extern bool need_calc_ar;



FILE *fin;

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

char *cos2Pic(uint64_t cos){
    char temp[256];
    char *s = new char[256];
    int i = 0;
    while(cos){
        if(cos%2==0) temp[i] = ' ';
        else temp[i] = '*';
        i++;
        cos /=2;
    }
    for(;i<20;i++) temp[i]=' ';
    for(int j=0; j<i; j++)
        s[j] = temp[i-j-1];
    s[i] = '\0';
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

int main(int argv, char **argc) {
    char filename[100];
    char target[100];

    workload_num = argv / 2 ;

    for (int i = 0; i < workload_num; i++) {
        workload[i].occ = 0;
        workload[i].name = strdup(argc[i * 2 + 1]);
        workload[i].allocation = strdup(argc[i * 2 + 2]);
        workload[i].cos = strtouint64(workload[i].allocation);
        workload[i].ways = count_1s(workload[i].cos);
        workload[i].miss_ratio = 0;
        strcpy(filename, workload[i].name);
        strcpy(target,"./mrc/");
        strcat(filename, ".txt");
        strcat(target,filename);
        fin = fopen(target, "rb");
        if(!fin){
            printf("file not exist\n");
            exit(-1);
        }
        // calc_mrc(i);
        get_mrc(i,fin);
        fclose(fin);
    }

    get_accessrate();
    get_baseIPC();
    double tmp = predict_total_ipc(CPI,PENALTY);
/*
    for(int i = 0; i < workload_num; i++){
	printf("%s: %lf\n", workload[i].name, workload[i].miss_ratio);
    }
*/
    printf("%s missrate: %lf, ipc: %lf\n",workload[0].name,workload[0].miss_ratio,tmp);
    return 0;
}
