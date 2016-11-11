#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <set>
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
    double access_rate, miss_rate;
    uint64_t access_num;
    double mrc[MAXS];
};

Node *hash_set[MAXH];
uint64_t rtd[MAXT];
FILE *fin, *fout;
uint64_t m;

Segment segment[WAY+1];
int segment_num = 0;
Workload workload[MAXN];
int workload_num;
uint64_t occupancy[MAXN][WAY+1];

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

uint64_t find(uint64_t now, int idx = -1) {
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


void calc_mrc(int i) {
    double sum = 0;
    uint64_t T = 0;
    double tot = 0;
    double N = workload[i].access_num;
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
        if (i == 0 || tmp != current) {
            segment[segment_num].begins = i;
            segment[segment_num].ends = i;
            segment[segment_num].workload = tmp;
            current = tmp;
            segment_num++;
        } else {
            segment[segment_num-1].ends = i;
        }
    }
}

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

void o2m() {
    for (int i = 0; i < workload_num; i++) {
        uint64_t occ = 0;
        for (int j = 0; j < segment_num; j++) {
            occ += occupancy[i][j];
        }
        workload[i].miss_rate = workload[i].mrc[occ];
    }
}


void m2o() {
    for (int i = 0; i < segment_num; i++) {
        uint64_t segment_ways = segment[i].ends - segment[i].begins + 1;
        uint64_t segment_blocks = segment_ways * WAY_SIZE / BLOCK;
        uint64_t miss_num[MAXN], miss_num_total = 0;

        for (set<int>::iterator iter = segment[i].workload.begin();
            iter != segment[i].workload.end(); iter++) {
            int wid = *iter;
            miss_num[wid] = (uint64_t) workload[wid].miss_rate * workload[wid].access_rate * accesses * segment_ways / workload[wid].ways;
            miss_num_total += miss_num[wid];
        }
        
        for (set<int>::iterator iter = segment[i].workload.begin();
            iter != segment[i].workload.end(); iter++) {
            int wid = *iter;
            occupancy[wid][i] = occupancy[wid][i] + miss_num[wid] * (segment_blocks - occupancy[wid][i]) / segment_blocks 
                                - (miss_num_total - miss_num[wid]) * occupancy[wid][i] / segment_blocks; 
        }
    }
}

bool need_calc_ar = false;
char filename[100];

int main(int argv, char **argc) {
    workload_num = argv / 2 - 1;
    if (argc[1][0] == '1') {
        need_calc_ar = true;
    }

    for (int i = 0; i < workload_num; i++) {
        workload[i].name = strdup(argc[i * 2 + 2]);
        workload[i].allocation = strdup(argc[i * 2 + 3]);
        workload[i].cos = strtouint64(workload[i].allocation);
        workload[i].ways = count_1s(workload[i].cos);
        workload[i].miss_rate = 0;
        strcpy(filename, workload[i].name);
        strcat(filename, ".ref");
        fin = fopen(filename, "rb");
        calc_mrc(i);
        if (need_calc_ar) {
            workload[i].access_rate = workload[i].mrc[L2_CACHE_SIZE / BLOCK];
        } else {
            workload[i].access_rate = 1;
        }
        fclose(fin);
    }

    segmentation();

    for (int i = 0; i < workload_num; i++) {
        calc_mrc(i);
        if (need_calc_ar) {
            workload[i].access_rate = workload[i].mrc[L2_CACHE_SIZE / BLOCK];
        }
    }

    init_occupancy();

    // iteration process
    for (accesses = MAXS; accesses >= 100; accesses -= 10) {
        o2m();
        m2o();
    }
    
    o2m();


    for (int i = 0; i < workload_num; i++) {
        printf("%s\t%s\t%lf\t%lf:", workload[i].name, workload[i].allocation,
               workload[i].access_rate, workload[i].miss_rate);
        for (int j = 0; j < segment_num; j++) {
            printf("\t%llu", occupancy[i][j]);
        }
        printf("\n");
    }

    // sprintf(filename,"aetcount.txt");
    // fout = fopen(filename,"w");
    // fclose(fin);
    // fclose(fout);
    return 0;
}
