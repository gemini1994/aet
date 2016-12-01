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


struct Benchmark{
    char *name;
    double access_rate;
    //Benchmark()
} *benchmarks[8];

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

inline uint64_t strtouint64(const char *s) {
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

inline int count_1s(int v) {
    int num = 0;
    while (v) {
        v &= (v - 1);
        num++;
    }
    return num;
}

double predict_total_miss_rate();