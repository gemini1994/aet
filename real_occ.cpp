#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

    miss = new double [workload_num];
    occ = new double [workload_num];

    FILE* fin;
    char* filename = strdup(argc[2]);
    workload_num = atoi(argc[1]);
    fin = fopen(filename,"rt");

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
        printf("%s",buffer);
        temp = strtok(buffer," \t");
        temp = strtok(NULL," \t");
        m = strtok(NULL," \t");//miss1
        o = strtok(NULL," \t");//llc1
        m = strtok(m,"k");
        miss[i] += atof(m);
        occ[i] += atof(o);
        }
        getline(&buffer,&len,fin);
        //printf("%lf\n",miss1);
    }
    printf("OK\n");
    for(int i = 0; i < workload_num; i++){
        printf("miss%d: %lfk, llc%d: %lfKB\n",i,miss[i]/c,i,occ[i]/c);
    }
}
