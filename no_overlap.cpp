#ifndef _PREDICT_H_
#define _PREDICT_H_
    #include "predict.h"
#endif

extern Workload workload[MAXN];
extern int workload_num;
extern bool need_calc_ar;

int *way;

struct best{
    char allo[1000];
    double value;
} metrics[5];

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

void display(){
    for(int i=0; i<workload_num; i++){
        printf("%15s: %s\n",workload[i].name,cos2Pic(workload[i].cos));
    }
    printf("\n");
}

void dfs(int i, int rest){
    if(i == workload_num-1){
        way[i] = rest;
        //calculate cos
        int index = 0;
        for(int k = 0; k < workload_num; k++){
            for(int v = 0; v< way[k]; v++){
                workload[k].cos += (uint64_t)(1<<index);
                index++;
            }
            workload[k].ways = count_1s(workload[k].cos);
        }
        char buffer[1000];
        double _miss,_ipc,_ws,_ms,_fs;
        predict_all(CPI,PENALTY,&_miss,&_ipc,&_ws,&_ms,&_fs);
        //printf("%lf\n",_ms);
        //for(int k = 0;k<5;k++){
        //    printf("%lf ",metrics[k].value);
        //    if(k==4)printf("\n");
        //}
        //printf("%lf %lf %lf %lf %lf\n",_miss,_ipc,_ws,_ms,_fs);
        for(int k = 0; k<workload_num; k++) {
            strcat(buffer,workload[k].name);
            strcat(buffer," ");
            strcat(buffer,ull216Str(workload[k].cos));
            strcat(buffer," ");
            //printf("%s %s ",workload[k].name, ull216Str(workload[k].cos));
            //if(k==workload_num-1) printf(buffer,"\0");
        }
        //printf("%s\n",buffer);
        if(_miss<metrics[0].value){
            metrics[0].value = _miss;
            strcpy(metrics[0].allo,buffer);
        }
        if(_ipc>metrics[1].value){
            metrics[1].value = _ipc;
            strcpy(metrics[1].allo,buffer);
        }
        if(_ws<metrics[2].value){
            metrics[2].value = _ws;
            strcpy(metrics[2].allo,buffer);
        }
        if(_ms<metrics[3].value){
            metrics[3].value = _ms;
            strcpy(metrics[3].allo,buffer);
        }
        if(_fs<metrics[4].value){
            metrics[4].value = _fs;
            strcpy(metrics[4].allo,buffer);
        }
        for(int k = 0; k < workload_num; k++) workload[k].cos = 0;
        strcpy(buffer,"");
    }
    else
    for(int j = 1; j <= rest-(workload_num-i-1); j++){
        way[i] = j;
        dfs(i+1,rest-j);
    }
}


int main(int argv, char **argc) {

    char filename[100];
    char target[100];
    workload_num = argv-1;
    way = new int[workload_num];
    for (int i = 0; i < workload_num; i++) {
        workload[i].occ = 0;
        workload[i].name = strdup(argc[i + 1]);
        //workload[i].allocation = strdup(argc[i * 2 + 2]);
        //workload[i].cos = strtouint64(workload[i].allocation);
        //workload[i].ways = count_1s(workload[i].cos);
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
    memset(metrics,0,sizeof(metrics));
    metrics[0].value = 100; metrics[2].value = 100; metrics[3].value = 100; metrics[4].value = 100;
    get_accessrate();
    get_baseIPC();
    dfs(0,20);
    //double tmp = predict_total_ipc(CPI,PENALTY);
/*
    for(int i = 0; i < workload_num; i++){
	printf("%s: %lf\n", workload[i].name, workload[i].miss_ratio);
    }
*/
    //printf("%s missrate: %lf, ipc: %lf\n",workload[0].name,workload[0].miss_ratio,tmp);
    printf("####################################################################\n");
    for(int i = 0;i<5;i++)
        printf("%s value%lf\n",metrics[i].allo,metrics[i].value);
    delete []way;
    return 0;
}
