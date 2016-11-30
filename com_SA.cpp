#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <set>
#include <time.h>
#include <math.h>
using namespace std;
typedef unsigned long long uint64_t;
const uint64_t CACHE_LINE = 64; // Cache Line Size is 64B
const uint64_t MAXN = 20;
const uint64_t MAXT = 10000 + 3;
const uint64_t MAXH = 19999997;
const uint64_t domain = 256;
const uint64_t WAY = 20;
const uint64_t WAY_SIZE = (56320 << 10) / WAY / CACHE_LINE;
const uint64_t L2_CACHE_SIZE = (256 << 10) / CACHE_LINE;
const uint64_t BLOCK = 16; // 1 block = 16 cache lines
const uint64_t MAXS = WAY_SIZE * WAY / BLOCK; // granularity is 1KB, (16 cache lines)

double T = 10000;//temperature
double T_min = 1;//threshold
double k = 0.0001;//constant

struct Benchmark{
    char *name;
    double access_rate;
    //Benchmark()
} *benchmarks[8];

struct Node {
    uint64_t addr, label;
    Node *nxt;
    Node(uint64_t _addr = 0, uint64_t _label = 0, Node *_nxt = NULL)
        : addr(_addr), label(_label), nxt(_nxt) {}
};

struct TNode {
    uint64_t offset;
};

struct Segment {
    int begins, ends;
    set<int> workload;
};

struct Workload {
    char *name;
    char *allocation;
    uint64_t cos;
    int ways;
    double access_rate, miss_ratio;
    uint64_t access_num;
    double mrc[MAXS];
    double occ;
    uint64_t occ_lbound;
    uint64_t occ_rbound;
};

Node *hash_set[MAXH];
uint64_t rtd[MAXT];
FILE *fin, *fout;
uint64_t m;

Segment segment[WAY+1];
int segment_num = 0;
Workload workload[MAXN];
int workload_num;
double occupancy[MAXN][WAY+1];

uint64_t accesses;

uint64_t strtouint64(const char *s) {
    const char *str = s;
    int base = 10;
    uint64_t n = 0;
    char *endptr = NULL;

    if (strncasecmp(s, "0x", 2) == 0) {
        base = 16;
        s += 2;
    }

    n = strtoull(s, &endptr, base);

    if (!(*s != '\0' && *endptr == '\0')) {
        printf("Error converting '%s' to unsigned number!\n", str);
        exit(-1);
    }

    return n;
}

int count_1s(int v) {
    int num = 0;
    while (v) {
        v &= (v - 1);
        num++;
    }
    return num;
}

uint64_t domain_value_to_index(uint64_t value) {
    uint64_t loc = 0, step = 1;
    int index = 0;
    while (loc + step * domain < value) {
        loc += step * domain;
        step *= 2;
        index += domain;
    }
    while (loc < value)
        index++, loc += step;
    return index;
}

uint64_t domain_index_to_value(uint64_t index) {
    uint64_t value = 0, step = 1;
    while (index > domain) {
        value += step * domain;
        step *= 2;
        index -= domain;
    }
    while (index > 0) {
        value += step;
        index--;
    }
    return value;
}

void insert(uint64_t now, int idx) {
    int t = now % MAXH;
    Node *tmp = new Node(now, workload[idx].access_num, hash_set[t]);
    hash_set[t] = tmp;
}

uint64_t find(uint64_t now) {
    int t = now % MAXH;
    Node *tmp = hash_set[t], *pre = NULL;
    while (tmp) {
        if (tmp->addr == now) {
            uint64_t tlabel = tmp->label;
            if (pre == NULL)
                hash_set[t] = tmp->nxt;
            else
                pre->nxt = tmp->nxt;
            delete tmp;
            return tlabel;
        }
        pre = tmp;
        tmp = tmp->nxt;
    }
    return 0;
}

void get_mrc(int i){
    int c = 0;
    double pre = 0;
    for(; c < MAXS; c++){
	if(fscanf(fin,"%lf",&workload[i].mrc[c])>0);
        else {
	    pre = workload[i].mrc[c-1];
	    break;
	}
    }
    for(; c < MAXS; c++) workload[i].mrc[c] = pre;
}

void calc_mrc(int i) {
    double sum = 0;
    uint64_t T = 0;
    double tot = 0;
    uint64_t step = 1;
    int dom = 0, dT = 0, loc = 0;
    uint64_t addr;
    TNode data;

    memset(hash_set, 0, sizeof(hash_set));
    memset(rtd, 0, sizeof(rtd));
    workload[i].access_num = 0;

    while (fread(&data, sizeof(data), 1, fin)) {
        addr = data.offset >> 6;
        workload[i].access_num++;
        uint64_t t = find(addr);
        if (t)
            rtd[domain_value_to_index(workload[i].access_num - t)]++;
        insert(addr, i);
    }

    double N = workload[i].access_num;
    //for(int i = 0;i<MAXT;i++)
    	//printf("rtd[%d]: %d\n",i,rtd[i]);
    workload[i].mrc[0] = 1;
    for (int c = 1; c < MAXS; c++) {
        while (T <= N && tot / N < (c * BLOCK)) {
            tot += N - sum;
            T++;
            if (T > loc) {
                if (++dom > domain)
                    dom = 1, step *= 2;
                loc += step;
                dT++;
            }
            sum += 1.0 * rtd[dT] / step;
        }
        workload[i].mrc[c] = 1.0 * (N - sum) / N;
        //printf("workload[%d].mrc[%d]:  %lf\n",i,c,workload[i].mrc[c]);
    }
}

void segmentation() {
    set<int> current;
    set<int> tmp;

    for (int i = 0; i < WAY; i++) {
        tmp.clear();
        for (int j = 0; j < workload_num; j++) {
            if ((1 << i) & workload[j].cos) {
                tmp.insert(j);
            }
        }
        if (tmp.size() == 0) {
            continue;
        }
        if (segment_num == 0 || tmp != current) {
            segment[segment_num].begins = i;
            segment[segment_num].ends = i;
            segment[segment_num].workload = tmp;
            current = tmp;
            segment_num++;
        } else {
            segment[segment_num - 1].ends = i;
        }
    }
}

/*
void init_occupancy() {
    for (int i = 0; i < segment_num; i++) {
        uint64_t segment_ways = segment[i].ends - segment[i].begins + 1;
        uint64_t segment_blocks = segment_ways * WAY_SIZE / BLOCK;
        uint64_t remain_num = segment[i].workload.size();
        uint64_t blocks = segment_blocks / remain_num, remains = segment_blocks % remain_num;

        for (set<int>::iterator iter = segment[i].workload.begin();
            iter != segment[i].workload.end(); iter++) {
            int wid = *iter;
            if (remain_num == remains)
                blocks ++;
            occupancy[wid][i] = blocks;
            remain_num --;
        }
    }
}
*/
void init_occupancy() {
    for (int i = 0; i < segment_num; i++) {
        uint64_t segment_ways = segment[i].ends - segment[i].begins + 1;
        uint64_t segment_blocks = segment_ways * WAY_SIZE / BLOCK;

        for (set<int>::iterator iter = segment[i].workload.begin();
            iter != segment[i].workload.end(); iter++) {
            int wid = *iter;
            occupancy[wid][i] = (double)segment_blocks/segment[i].workload.size();
        }
    }
}

void o2m() {
    for (int i = 0; i < workload_num; i++) {
        double occ = 0;
        for (int j = 0; j < segment_num; j++) {
            occ += occupancy[i][j];
        }
        workload[i].occ = occ;
        //if(occ<0) printf("error\n");
        workload[i].miss_ratio = workload[i].mrc[(uint64_t)occ];
        //printf("in o2m workload[%d] occ = %d, miss_ratio: %lf \n",i,occ,workload[i].miss_ratio);
    }
}


void m2o() {
    for (int i = 0; i < segment_num; i++) {
        uint64_t segment_ways = segment[i].ends - segment[i].begins + 1;
        uint64_t segment_blocks = segment_ways * WAY_SIZE / BLOCK;
        double miss_num[MAXN], miss_num_total = 0;

        for (set<int>::iterator iter = segment[i].workload.begin();
            iter != segment[i].workload.end(); iter++) {
            int wid = *iter;
            miss_num[wid] = (workload[wid].miss_ratio * workload[wid].access_rate * accesses * segment_ways / workload[wid].ways);
            //printf("miss_num %lf\n",miss_num[wid]);
            miss_num_total += miss_num[wid];
	    //printf("workload[%d].miss_ratio: %lf, workload[%d].access_rate: %lf,accesses: %d, segment_ways: %d, workload[%d].ways: %d, miss_num[%d]: %d\n",wid,workload[wid].miss_ratio,wid,workload[wid].access_rate,accesses,segment_ways,wid,workload[wid].ways,wid,miss_num[wid]);
        }
        //printf("miss_num_total: %d\n",miss_num_total);

        for (set<int>::iterator iter = segment[i].workload.begin();
            iter != segment[i].workload.end(); iter++) {
            int wid = *iter;
            occupancy[wid][i] = occupancy[wid][i] + miss_num[wid] * (segment_blocks - occupancy[wid][i]) / segment_blocks
                                - (miss_num_total - miss_num[wid]) * occupancy[wid][i] / segment_blocks;
        }
    }
}


char* ull2BinaryStr(uint64_t cos){
    char temp[256];
    char *s = new char[256];
    int i = 0;
    while(cos){
        temp[i] = cos%2+'0';
        cos/=2;
        i++;
    }
    for(int j=0;j<i;j++) s[j] = temp[i-j-1];
    s[i] = 0;
    return s;
}

char* ull216Str(uint64_t cos){
    char *s = new char[256];
    strcpy(s,"0x");
    char temp[256];
    sprintf(temp,"%X",cos);
    strcat(s,temp);
    return s;
}
bool containOne1(uint64_t cos){
    int c = 0;
    while(cos){
        if(cos%2==1) c++;
        cos=cos>>1;
    }
    if(c==1) return true;
    else return false;
}
//direction: 0 right expand, 1 right reduce, 2 left expand, 3 left reduce
uint64_t modifyCos(int index, int d){
    uint64_t cos = workload[index].cos;
    uint64_t pre_value = cos;
    if((cos >= 2<<(MAXN-1) && d==2)||((cos%2==1)&& d==0)||(containOne1(cos)&&(d==1||d==3)))
        return pre_value;
    if(d==0){//right expand
        int c = 0;
        while(cos%2==0){
            cos=cos>>1;
            c++;
        }
        workload[index].cos += 1<<(c-1);
    }
    else if(d==1){
        int c = 0;
        while(cos%2==0){
            cos=cos>>1;
            c++;
        }
        workload[index].cos -= 1<<c;
    }
    else if(d==2){
        int c = 0;
        while(cos%2==0){
            cos=cos>>1;
            c++;
        }
        while(cos%2){
            cos=cos>>1;
            c++;
        }
        workload[index].cos += 1<<c;
    }
    else if(d==3){
        int c = 0;
        while(cos%2==0){
            cos=cos>>1;
            c++;
        }
        while(cos%2){
            cos=cos>>1;
            c++;
        }
        workload[index].cos -= 1<<(c-1);
    }
    return pre_value;
}

bool need_calc_ar = false;
char filename[100];

int main(int argv, char **argc) {
    workload_num = argv / 2 - 1;
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
        //calc_mrc(i);
    	get_mrc(i);
        if (need_calc_ar) {
            workload[i].access_rate = workload[i].mrc[L2_CACHE_SIZE / BLOCK];
        } else {
            workload[i].access_rate = 1;
        }
        fclose(fin);
    }
    segmentation();
    init_occupancy();
    // iteration process
    /*
    for (accesses = 1000; accesses >= 100; accesses -= 1) {
        o2m();
        m2o();
    }
    */
    accesses = 500;
    for(int i =0; i < 2000; i++){
        o2m();
        m2o();
	/*
        for( int j = 0; j< workload_num; j++ ){
            if(j==0)printf("%d\n",(int)workload[j].occ);
        }
	*/
        //printf("\n");
	    if(i%10 == 0) accesses--;
    }
    o2m();

    segment_num = 0;
    double pre_total_miss_ratio = 0;
    double cur_total_miss_ratio = 0;
    double best;
    for (int i = 0; i < workload_num; i++) {
	    pre_total_miss_ratio += workload[i].miss_ratio;
    }   //printf("%15s\t%s\t%lf\t%lf\t%lf\n", workload[i].name, workload[i].allocation, workload[i].access_rate, workload[i].miss_ratio,workload[i].occ);
    printf("total miss ratio: %lf\n",pre_total_miss_ratio);
    best = pre_total_miss_ratio;
    srand(time(NULL));

    while( T >= T_min){

        int target = rand()%workload_num;
        int direction = rand()%4;//0 right expand, 1 right reduce, 2 left expand, 3 left reduce
        //printf("%d %d\n",target,direction);
        uint64_t pre_cos = modifyCos(target, direction);

        segmentation();
        init_occupancy();
        //get total miss_ratio
        accesses = 500;
        for(int i=0; i< 2000; i++){
            o2m();
            m2o();
            if(i%10==0) accesses--;
        }
        o2m();

	    segment_num = 0;
        for(int i=0; i<workload_num; i++){
            cur_total_miss_ratio += workload[i].miss_ratio;
        }

        printf("total miss ratio: %lf\n",cur_total_miss_ratio);
	    printf("allocation: \n");
	    for(int i = 0;i<workload_num;i++){
	        printf("%s %s ",workload[i].name,ull216Str(workload[i].cos));
	        if(i==workload_num-1) printf("\n\n");
	    }
	    if(cur_total_miss_ratio<best) best=cur_total_miss_ratio;
        double df = cur_total_miss_ratio - pre_total_miss_ratio;
        if((df>0) && ((rand()%1000/(float)1000) >exp(-df/(k*T))))
            workload[target].cos = pre_cos;
        pre_total_miss_ratio = cur_total_miss_ratio;
        cur_total_miss_ratio = 0;
        T--;
    }
	printf("\n\nThe best: %lf\n",best);

    // sprintf(filename,"aetcount.txt");
    // fout = fopen(filename,"w");
    // fclose(fin);
    // fclose(fout);
    return 0;
}
