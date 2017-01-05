#ifndef _PREDICT_H_
#define _PREDICT_H_
    #include "predict.h"
#endif

extern Workload workload[MAXN];
extern int workload_num;
extern bool need_calc_ar;


double T = 10000;//temperature
double T_min = 1;//threshold
double k = 6e-7;//constant

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

void get_accessrate(){
    FILE *acc =  fopen("access_rate.txt","rb");
    if(!acc){
        printf("access_rate file not exist\n");
        exit(-1);
    }
    char name[100];
    double access_rate;
    double total = 0;
    while(fscanf(acc,"%s %lf",name,&access_rate)==2){
        total += access_rate;
        for(int i=0; i<workload_num; i++){
            if(strcmp(workload[i].name,name)==0){
                workload[i].access_rate = access_rate;
                break;
            }
        }
    }
    for(int i=0; i<workload_num;i++){
        workload[i].access_rate /= total;
    }
    fclose(acc);
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

void display(){
    for(int i=0; i<workload_num; i++){
        printf("%15s: %s\n",workload[i].name,cos2Pic(workload[i].cos));
    }
    printf("\n");
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
        get_mrc(i);
        fclose(fin);
    }

    get_accessrate();
    double tmp = predict_total_miss_rate();
    for(int i = 0; i < workload_num; i++){
	printf("%s: %lf\n", workload[i].name, workload[i].miss_ratio);
    }

    return 0;
}
