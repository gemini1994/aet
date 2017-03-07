"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import numpy as np
import matplotlib.pyplot as plt


n_groups = 15

data = []
target = open("./ipc.txt")
for line in target:
    a = [float(x) for x in line.strip().split()]
    data.append(a)

full1 = data[0]
noover1 = data[1]
our1 = data[2]

#fig, ax = plt.subplots()

index = np.arange(n_groups)
bar_width = 0.2

opacity = 0.4
#error_config = {'ecolor': '0.3'}

rects1 = plt.bar(0.2+index, full1, bar_width,
                 alpha=opacity,
                 color='b',
                 label='full share')

rects2 = plt.bar(0.2+index + bar_width, noover1, bar_width,
                 alpha=opacity,
                 color='r',
                 label='best non-overlap')

rects3 = plt.bar(0.2+index + 2*bar_width, our1, bar_width,
                 alpha=opacity,
                 color='y',
                 label='our algorithm')

plt.axis([0,15,4,20])
plt.xlabel('Number of workload')
plt.ylabel('IPC')
#plt.title('Metric: IPC')
plt.xticks(0.2+index + bar_width*1.5, ('4', '6', '8', '10', '12','4', '6', '8', '10', '12','4', '6', '8', '10', '12'))
#plt.legend()
plt.legend(loc='upper left',fontsize = 'small')

plt.tight_layout()
plt.show()
