#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>
#include<math.h>
#define maxlen 100
using namespace std;

double missrate[maxlen];
double missnum[maxlen];
double IPC[maxlen];
int _index = 0;

int main(int argv, char** argc){
    if(argv != 2){
        printf("usage: ./data filename\n");
        exit(-1);
    }

    FILE* fin;
    char* filename = strdup(argc[1]);

    fin = fopen(filename,"rt");

    if(fin == NULL){
        printf("file not exit\n");
        exit(-1);
    }
    size_t len = 500;
    char * buffer = new char[len];
    getline(&buffer,&len,fin);
    while(!feof(fin)){
        //getline(&buffer,&len,fin);
        //printf("%s\n",buffer);
        missrate[_index] = atof(strtok(buffer," "));
        //printf("%lf\n",missrate[_index]);
        IPC[_index]= atof(strtok(NULL," "));
        missnum[_index] = atof(strtok(NULL," "));
        _index++;
        getline(&buffer,&len,fin);
    }
    //for(int i = 0;i<_index;i++) printf("%lf\n",missrate[i]);
    fclose(fin);
    double _ipc = 0;
    double _missrate = 0;
    for(int i = 0;i<_index;i++){
        _ipc += IPC[i];
        _missrate += missrate[i];
    }
    _ipc /= _index;
    _missrate /= _index;

    double cov = 0;
    for(int i =0;i<_index;i++){
        cov+=(IPC[i]-_ipc)*(missrate[i]-_missrate);
    }
    cov /= (_index-1);
    printf("%lf\n",cov);
    double error = 0;
    for(int i=0;i<_index;i++){
        error+= fabs(missnum[i]/1000000-missrate[i])/(missnum[i]/1000000);
    }
    error /= _index;
    printf("%lf\n",error);
}
