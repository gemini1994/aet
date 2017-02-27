#ifndef _PREDICT_H_
#define _PREDICT_H_
    #include "predict.h"
#endif

extern Workload workload[MAXN];
extern int workload_num;
extern bool need_calc_ar;
extern double CPI;
extern double PENALTY;


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

	double best_accuracy = 0;
	double best_c = 0;
	double best_p = 0;
    if(argv!=2){
        printf("usage: ./select_para filename\n");
        exit(-1);
    }
    char *filename = strdup(argc[1]);
    //API = atof(argc[2])/1000;
    FILE *fin = fopen(filename,"rt");
    if(!fin){
        printf("file not found\n");
        exit(-1);
    }

    char benchmark_name[100][100];
    double base_ipc[100];
    double error = 0;
    int benchmark_num = 0;
    workload_num = 1;
    size_t len = 500;
    char *buffer = new char[len];
    char *temp;
    getline(&buffer,&len,fin);
    while(!feof(fin)){
        temp = strtok(buffer," ");
        strcpy(benchmark_name[benchmark_num],temp);
        temp = strtok(NULL," ");
        base_ipc[benchmark_num] = atof(temp);
        benchmark_num++;
    	getline(&buffer,&len,fin);
    }
    fclose(fin);
    char _filename[100];
    char target[100];
    for(CPI = 0.1; CPI<2; CPI+=0.01)
        for(PENALTY = 50; PENALTY < 2000; PENALTY += 10){
            error = 0;
            for(int i = 0; i < benchmark_num; i++){
                workload[0].occ = 0;
                workload[0].name = new char[100];
		strcpy(workload[0].name,benchmark_name[i]);
                workload[0].cos = 1048575;
                workload[0].ways = count_1s(workload[0].cos);
                workload[0].miss_ratio = 0;
                strcpy(_filename,workload[0].name);
                strcpy(target,"./mrc/");
                strcat(_filename,"_real.txt");
                strcat(target,_filename);
                fin = fopen(target,"rb");
                if(!fin){
                    printf("file not exits\n");
                    exit(-1);
                }
                get_mrc(0,fin);
                fclose(fin);
                get_accessrate();
                get_baseIPC();
                double tmp = predict_total_ipc(CPI,PENALTY);
                error += fabs(tmp-base_ipc[i])/base_ipc[i];
		delete workload[0].name;
		delete workload[0].allocation;
            }
		if(best_accuracy < 1-error/benchmark_num){
			best_accuracy = 1-error/benchmark_num;
			best_c = CPI;
			best_p = PENALTY;
		}
            printf("%lf,%lf,%lf\n",CPI,PENALTY,1-error/benchmark_num);
        }
	printf("\nbest: %lf,%lf,%lf\n",best_c,best_p,best_accuracy);
    return 0;
}
