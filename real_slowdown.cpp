#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>
using namespace std;

double CPI = 0.6;
double PENALTY = 600;

double total_missnum = 0;
double total_ipc = 0;
double ws = 0;
double ms = 0;
double fs = 0;

double baseipc[100];

int main(int argv, char** argc){
    if(argv != 3){
        printf("usage: ./real_metrics workload_num filename\n");
        exit(-1);
    }
    int workload_num = 0;
    int c = 0;
    double *miss;
    //double *occ;
    double *IPC;
    FILE* fin;
    char* filename = strdup(argc[2]);
    workload_num = atoi(argc[1]);
    fin = fopen(filename,"rt");
    printf("input baseipc\n");
    for(int i = 0; i<workload_num; i++)
        scanf("%lf",&baseipc[i]);
    miss = new double [workload_num];
    //occ = new double [workload_num];
    IPC = new double [workload_num];

    memset(miss,0,sizeof(double)*workload_num);
    //memset(occ,0,sizeof(double)*workload_num);
    memset(IPC,0,sizeof(double)*workload_num);

    if(fin == NULL){
        printf("file not found\n");
        exit(-1);
    }
    size_t len = 500;
    char * buffer = new char[len];
    char * temp;
    char *m,*o,*I;
    //remove title
    getline(&buffer,&len,fin);
    getline(&buffer,&len,fin);
    getline(&buffer,&len,fin);

    //remove cold start
    for(int i = 0;i<50;i++){
        getline(&buffer,&len,fin);
        getline(&buffer,&len,fin);
        for(int j = 0; j < workload_num ;j++)
            getline(&buffer,&len,fin);
    }

    while(!feof(fin)){
        c++;
        //getline(&buffer,&len,fin);
        getline(&buffer,&len,fin);

        for(int i = 0; i < workload_num; i++){
            getline(&buffer,&len,fin);
            //printf("%s",buffer);
            temp = strtok(buffer," \t");
            I = strtok(NULL," \t");
            m = strtok(NULL," \t");//miss1
            o = strtok(NULL," \t");//llc1
            m = strtok(m,"k");
            //IPC[i] += (atof(I)==0?0:(1/atof(I)));
            //miss[i] += (atof(m)==0?0:(1/atof(m)));
            //occ[i] += (atof(o)==0?0:(1/atof(o)));
            IPC[i] += atof(I);
            miss[i] += atof(m);
            //occ[i] = (occ[i]*(c-1) + atof(o))/c;
        }
        getline(&buffer,&len,fin);
    }
    for(int i = 0;i<workload_num;i++){
            IPC[i] = IPC[i]/c;
            miss[i] = miss[i]/c;
            //occ[i] = c*(1/occ[i]);
    }
    for(int i = 0; i < workload_num; i++){
        //printf("MISS%d: %lfk, IPC%d: %lf, \n",i,miss[i],i,ipc[i]);
         printf("%lf\n",baseipc[i]/IPC[i]);
    }
    fclose(fin);
    delete miss;
    delete IPC;
    //delete occ;
}
