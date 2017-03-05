#!/usr/bin/python
#import math
#import sys
import matplotlib.pyplot as plt

x0 = []
y0 = []
z0 = []

result0 = open("./complete_8_mfc.txt")


for line in result0:
    a = line.strip().split()
    x0.append(float(a[0]))
    y0.append(float(a[1]))
    z0.append(float(a[2]))

plt.subplot(2, 1, 1)
plt.plot(x0, y0, 'ro')
#plt.plot(y6, x6, "blue", label = "0.1%");
#plt.plot(y7, x7, "yellow", label = "0.01%");
#plt.xlim([15, 23])
#plt.ylim([0,float(sys.argv[2])])
plt.xlabel("miss_rate", size=15)
plt.ylabel("IPC", size=15)
plt.subplot(2, 1, 2)
plt.plot(x0, z0, 'ro')
plt.ylabel("miss_num", size=15)
#plt.legend(loc="upper right")
#plt.title(sys.argv[1])
#plt.show()
#savepath="nine.pdf"
#plt.savefig(savepath, box_inches="tight")

plt.show()
