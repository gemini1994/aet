#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt
plt.figure(figsize=(40,40))
n_groups = 10
index = np.arange(n_groups)
data = []
points = [(0,1.139871),(1,1.467701),(2,0.589419),(3,1.353832),(4,1.880968),(5,2.098467),(6,1.655078),(7,1.873005),(8,1.396645 ),(9,1.313679)]
target = open("./case_ipc.txt")
i = 0
for line in target:
    if i==0:
        a = line.strip().split()
        data.append(a)
        i = 1
    else:
        a = [float(x) for x in line.strip().split()]
        data.append(a)

#ws = (2.302215,1.173829,1.662305,1.379330,1.807729,1.804873,1.409274,1.179289,1.267336,1.625169)
#ms = (3.617407,1.073733,1.660431,1.727669,1.471084,1.715320,1.363607,3.177756,1.657094,3.202971)
#fs = (2.890952,1.285745,1.797710,1.368337,2.845843,2.328545,1.588748,1.229131,1.017742,2.956141)

plt.axis([-0.5,9.5,0,2.4])
plt.plot(index,data[3],'cD-',label = 'Full share',markersize = 55,markeredgecolor = 'w',linewidth = 16);
plt.plot(index,data[1],'ko:',label = 'Throughput',markersize = 55,markeredgecolor = 'w',linewidth = 16);
plt.plot(index,data[2],'ms-.', label = 'Fair slowdown',markersize = 55,markeredgecolor = 'w',linewidth = 16);


for pt in points:
    # plot (x,y) pairs.
    # vertical line: 2 x,y pairs: (a,0) and (a,b)
    plt.plot( [pt[0],pt[0]], [0,pt[1]],linewidth = 2,color='k',linestyle= '--' )

#plt.plot(index,data[4],'ys-',label = 'Non-overlap');
#plt.plot(index,data[5],'k*-',label = 'Full contention');

#plt.xlabel("Benchmarks",size = 60);
plt.ylabel("IPC",size = 80);
#plt.xticks(index, ('omnetpp', 'leslie3d', 'bwaves', 'zeusmp','povray','libquantum','milc','gobmk','hmmer','sjeng'))
plt.xticks(index,data[0],size = 75,rotation = 50)
plt.yticks(size = 75)
#plt.legend(loc='upper center',fontsize=55,bbox_to_anchor=(0.5, 1.07),
#          fancybox=True, shadow=True, ncol=3)
plt.legend(loc='upper left',fontsize=80)
plt.tight_layout()
plt.savefig('case_ipc.pdf')
#plt.show()
