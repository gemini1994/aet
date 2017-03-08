#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt

n_groups = 10
index = np.arange(n_groups)
data = []
target = open("./slowdown.txt")
i = 3
for line in target:
    if i==3:
        a = line.strip().split()
        data.append(a)
        i = 0
    else:
        a = [float(x) for x in line.strip().split()]
        data.append(a)
        i += 1
#ws = (2.302215,1.173829,1.662305,1.379330,1.807729,1.804873,1.409274,1.179289,1.267336,1.625169)
#ms = (3.617407,1.073733,1.660431,1.727669,1.471084,1.715320,1.363607,3.177756,1.657094,3.202971)
#fs = (2.890952,1.285745,1.797710,1.368337,2.845843,2.328545,1.588748,1.229131,1.017742,2.956141)

plt.figure(figsize=(20,10))
plt.axis([-0.5,9.5,0,5])
plt.plot(index,data[1],'ro-',label = '1');
plt.plot(index,data[2],'go-', label = '2');
plt.plot(index,data[3],'bo-',label = '3');
plt.xlabel("benchmarks");
plt.ylabel("slowdown");
#plt.xticks(index, ('omnetpp', 'leslie3d', 'bwaves', 'zeusmp','povray','libquantum','milc','gobmk','hmmer','sjeng'))
plt.xticks(index,data[0])
plt.legend(loc = 'upper left',fontsize = 'small')
plt.show()
