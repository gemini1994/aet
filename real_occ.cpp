#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>

using namespace std;

int main(int argv, char** argc){
    if(argv != 3){
        printf("usage: ./real_occ workload_num filename\n");
        exit(-1);
    }
    int workload_num = 0;
    int c = 0;
    double *miss;
    double *occ;
    FILE* fin;
    char* filename = strdup(argc[2]);
    workload_num = atoi(argc[1]);
    fin = fopen(filename,"rt");
    miss = new double [workload_num];
    occ = new double [workload_num];

    memset(miss,0,sizeof(double)*workload_num);
    memset(occ,0,sizeof(double)*workload_num);

    if(fin == NULL){
        printf("file not exit\n");
        exit(-1);
    }
    size_t len = 500;
    char * buffer = new char[len];
    char * temp;
    char *m,*o;
    //remove title
    getline(&buffer,&len,fin);
    getline(&buffer,&len,fin);
    getline(&buffer,&len,fin);

    //remove cold start
    for(int i = 0;i<10;i++){
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
            temp = strtok(NULL," \t");
            m = strtok(NULL," \t");//miss1
            o = strtok(NULL," \t");//llc1
            m = strtok(m,"k");
            miss[i] = (miss[i]*(c-1) + atof(m))/c;
            occ[i] = (occ[i]*(c-1) + atof(o))/c;
        }
        getline(&buffer,&len,fin);
    }

    for(int i = 0; i < workload_num; i++){
        printf("miss%d: %lfk, llc%d: %lfKB\n",i,miss[i],i,occ[i]);
    }
    fclose(fin);
    delete miss;
    delete occ;
}
