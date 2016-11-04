#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <set>
using namespace std;
typedef unsigned long long uint64_t; 
const uint64_t CACHE_LINE = 64; // Cache Line Size is 64kb
// const int PGAP = 1024/64;
const uint64_t MAXN = 20;
const uint64_t MAXT = 10000+3;
const uint64_t MAXH = 19999997;
const uint64_t domain = 256;
// const int CacheLineSize = 30*1024*1024/64;
const uint64_t WAY = 20;
const uint64_t WAY_SIZE = (56320 << 10) / WAY / CACHE_LINE;
const uint64_t L2_CACHE_SIZE = (5632 << 10) / WAY / CACHE_LINE;


struct Node {
    uint64_t addr,label;
    Node *nxt;
    Node(uint64_t _addr = 0, uint64_t _label = 0, Node *_nxt = NULL)
         : addr(_addr),label(_label),nxt(_nxt) {}
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
    double access_rate, miss_rate;
    uint64_t access_num;
    uint64_t rtd[MAXT];
};

Node *hash_set[MAXH];
FILE *fin,*fout;
uint64_t m;

Segment segment[WAY + 1];
int segment_num = 0;
Workload workload[MAXN];
int workload_num;

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

int count_1s(int v)  
{  
    int num = 0;  
    while(v)  
    {  
        v &= (v-1);  
        num++;  
    }  
    return num;  
}  


uint64_t domain_value_to_index(uint64_t value) {
    uint64_t loc = 0,step = 1;
    int index = 0;
    while (loc+step*domain<value) {
        loc += step*domain;
        step *= 2;
        index += domain;
    }
    while (loc<value) index++,loc += step;
    return index;
}

uint64_t domain_index_to_value(uint64_t index) {
    uint64_t value = 0,step = 1;
    while (index>domain) {
        value += step*domain;
        step *= 2;
        index -= domain;
    }
    while (index>0) {
        value += step;
        index--;
    }
    return value;
}

void insert(uint64_t now, int idx) {
    int t = now%MAXH;
    Node *tmp = new Node(now,workload[idx].access_num,hash_set[t]);
    hash_set[t] = tmp;
}

uint64_t find(uint64_t now, int idx = -1) {
    int t = now%MAXH;
    Node *tmp = hash_set[t], *pre = NULL;
    while (tmp) {
        if (tmp->addr==now) {
            uint64_t tlabel = tmp->label;
            if (pre==NULL) hash_set[t] = tmp->nxt;
            else pre->nxt = tmp->nxt;
            delete tmp;
            return tlabel;
        }
        pre = tmp;
        tmp = tmp->nxt;
    }
    return 0;
}

void init_rtd(int idx) {
    memset(hash_set, 0, sizeof(hash_set));
    workload[idx].access_num = 0;
    uint64_t addr;
    TNode data;
    while (fread(&data, sizeof(data), 1, fin)) {
        addr = data.offset>>6;
        workload[idx].access_num++;
        //if (n%100000000==0) printf("%lld\n",n);
        uint64_t t = find(addr);
        if (t) workload[idx].rtd[domain_value_to_index(workload[idx].access_num-t)]++;
        insert(addr, idx);
    }
}

// void solve() {
//     double sum = 0; uint64_t T = 0;
//     double tot = 0;
//     double N = n;
//     uint64_t step = 1; int dom = 0,dT = 0,loc = 0;
//     m = CacheLineSize;
//     for (uint64_t c = 1; c<=m; c++) {
//         while (T<=n && tot/N<c) {
//             tot += N-sum;
//             T++;
//             if (T>loc) {
//                 if (++dom>domain) dom = 1,step *= 2;
//                 loc += step;
//                 dT++;
//             }
//             sum += 1.0*rtd[dT]/step;
//         }
//         //ans[c] = 1.0*(N-sum)/N;
//         if (c%PGAP==0) fprintf(fout,"%.6lf\n",1.0*(N-sum)/N);
//     }
// }



void calc_segment_missrate(const Segment & segment) {
    double ar[MAXN];
    double ar_total = 0;
    uint64_t step[MAXN]; 
    int dom[MAXN] = {0}, dt[MAXN] = {0}, loc[MAXN] = {0};
    double sum[MAXN] = {0}, sump[MAXN] = {0};
    uint64_t ct[MAXN] = {0}; 
    uint64_t segment_ways = segment.ends - segment.begins + 1;
    uint64_t segment_size = segment_ways * WAY_SIZE;

    for (set<int>::iterator iter = segment.workload.begin();iter!=segment.workload.end();iter++) {
	int wid = *iter;
        step[wid] = 1;
        ar[wid] = ((double)workload[wid].ways / segment_ways) * workload[wid].access_rate;
        ar_total += ar[wid];
    }

    uint64_t aet;
    uint64_t cur;
    for (aet = 1; aet<=1000000000; aet++) {
        cur = 0;
        for (set<int>::iterator iter= segment.workload.begin();iter!=segment.workload.end();iter++) {
	    int wid = *iter;
	    sump[wid] += ((double)workload[wid].access_num - sum[wid]) / workload[wid].access_num;
            if ((int)(ar[wid] / ar_total * aet) > ct[wid]) {       
                ct[wid]++;
                if (ct[wid] > loc[wid]) {
                    if (++dom[wid]>domain) dom[wid] = 1,step[wid] *= 2;
                    loc[wid] += step[wid];
                    dt[wid]++;
                }
                sum[wid] += (double) workload[wid].rtd[dt[wid]] / step[wid];                
            }
            cur += sump[wid] * ar[wid] / ar_total;
        }
        if (cur > segment_size) {
            break;
        }
    }
    for (set<int>::iterator iter = segment.workload.begin();iter!=segment.workload.end();iter++) {
	int wid = *iter;
        workload[wid].miss_rate += (((double)workload[wid].access_num - sum[wid]) / workload[wid].access_num) * segment_ways / workload[wid].ways; 
    }
}

void solve() {
    for (int i=1; i<=segment_num; i++) {
        calc_segment_missrate(segment[i]);
    }
}

void calc_access_rate(int i) {
    double sum = 0; uint64_t T = 0;
    double tot = 0;
    double N = workload[i].access_num;
    uint64_t step = 1; int dom = 0,dT = 0,loc = 0;
    while (T<=N && tot/N<L2_CACHE_SIZE) {
        tot += N-sum;
        T++;
        if (T>loc) {
            if (++dom>domain) dom = 1,step *= 2;
            loc += step;
            dT++;
        }
        sum += 1.0 * workload[i].rtd[dT]/step;
    }
    workload[i].access_rate = 1.0*(N-sum)/N;
}

void segmentation() {
    set<int> current;
    set<int> tmp;

    for (int i=0; i<WAY; i++) {
        tmp.clear();
        for (int j=0; j<workload_num; j++) {
            if ((1 << i) & workload[j].cos) {
                tmp.insert(j);
            }
        }
        if (i == 0 || tmp != current) {
            segment_num++;
            segment[segment_num].begins = i;
            segment[segment_num].ends = i;
            segment[segment_num].workload = tmp;
            current = tmp;
        } else {
            segment[segment_num].ends = i;
        }
    }
}

bool need_calc_ar = false;

int main(int argv, char **argc)
{
    workload_num = argv / 2 - 1;
    if (argc[1][0] == '1') {
        need_calc_ar = true;
    } 

    for (int i=0; i<workload_num; i++) {
        workload[i].name = strdup(argc[i*2+2]);
        workload[i].allocation = strdup(argc[i*2+3]);
        workload[i].cos = strtouint64(workload[i].allocation);
        workload[i].ways = count_1s(workload[i].cos);
        workload[i].access_rate = 1;
        workload[i].miss_rate = 0;
        memset(workload[i].rtd, 0, sizeof(workload[i].rtd));
    }

    segmentation();

    for (int i=0; i<workload_num; i++) {
        char filename[100];
        strcpy(filename, workload[i].name);
        strcat(filename, ".ref");
        fin = fopen(filename,"rb");
        init_rtd(i);
        fclose(fin);
    }

    if (need_calc_ar) {
        for (int i=0; i<workload_num; i++) {
            calc_access_rate(i);
        }
    }

    solve();

    for (int i=0; i<workload_num; i++) {
        printf("%s\t%s\t%lf\t%lf\n", workload[i].name, workload[i].allocation, workload[i].access_rate, workload[i].miss_rate);
    }

    // sprintf(filename,"aetcount.txt");
    // fout = fopen(filename,"w");
    // fclose(fin);
    // fclose(fout);
    return 0;
}
