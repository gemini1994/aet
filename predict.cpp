#ifndef _PREDICT_H_
#define _PREDICT_H_
    #include "predict.h"
#endif

uint64_t m;
Segment segment[WAY+1];
int segment_num;
Workload workload[MAXN];
int workload_num;
double occupancy[MAXN][WAY+1];
uint64_t accesses;
bool need_calc_ar;


void segmentation() {
    set<int> current;
    set<int> tmp;
    segment_num = 0;

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

void init_occupancy() {
    for (int i = 0; i < segment_num; i++) {
        uint64_t segment_ways = segment[i].ends - segment[i].begins + 1;
        uint64_t segment_blocks = segment_ways * WAY_SIZE / BLOCK;

        for (set<int>::iterator iter = segment[i].workload.begin();
             iter != segment[i].workload.end(); iter++) {
            int wid = *iter;
            occupancy[wid][i] =
                (double)segment_blocks / segment[i].workload.size();
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
        // if(occ<0) printf("error\n");
        workload[i].miss_ratio = workload[i].mrc[(uint64_t)occ];
        // printf("in o2m workload[%d] occ = %d, miss_ratio: %lf
        // \n",i,occ,workload[i].miss_ratio);
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
            miss_num[wid] =
                (workload[wid].miss_ratio * workload[wid].access_rate *
                 accesses * segment_ways / workload[wid].ways);
            // printf("miss_num %lf\n",miss_num[wid]);
            miss_num_total += miss_num[wid];
            // printf("workload[%d].miss_ratio: %lf, workload[%d].access_rate:
            // %lf,accesses: %d, segment_ways: %d, workload[%d].ways: %d,
            // miss_num[%d]:
            // %d\n",wid,workload[wid].miss_ratio,wid,workload[wid].access_rate,accesses,segment_ways,wid,workload[wid].ways,wid,miss_num[wid]);
        }
        // printf("miss_num_total: %d\n",miss_num_total);

        for (set<int>::iterator iter = segment[i].workload.begin();
             iter != segment[i].workload.end(); iter++) {
            int wid = *iter;
            occupancy[wid][i] = occupancy[wid][i] +
                                miss_num[wid] *
                                    (segment_blocks - occupancy[wid][i]) /
                                    segment_blocks -
                                (miss_num_total - miss_num[wid]) *
                                    occupancy[wid][i] / segment_blocks;
        }
    }
}

double predict_total_miss_rate() {
    char filename[100];
    memset(segment, 0, sizeof(segment));
    memset(occupancy, 0, sizeof(occupancy));
  
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
    for (int i = 0; i < 2000; i++) {
        o2m();
        m2o();
        /*
        for( int j = 0; j< workload_num; j++ ){
            if(j==0)printf("%d\n",(int)workload[j].occ);
        }
        */
        // printf("\n");
        if (i % 10 == 0)
            accesses--;
    }
    o2m();

    double pre_total_miss_ratio = 0;

    for (int i = 0; i < workload_num; i++) {
        pre_total_miss_ratio += workload[i].miss_ratio;
    } // printf("%15s\t%s\t%lf\t%lf\t%lf\n", workload[i].name,
      // workload[i].allocation, workload[i].access_rate,
      // workload[i].miss_ratio,workload[i].occ);
    return pre_total_miss_ratio;
}
